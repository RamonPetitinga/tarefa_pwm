#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22
#define PWM_FREQ 50      // Frequência de 50Hz
#define PWM_PERIOD 20000 // Período em microsegundos (20ms)

void setup_pwm(uint gpio)
{
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(gpio);

    // Configura o divisor para obter a frequência de 50Hz
    pwm_set_clkdiv(slice_num, 64.0f);

    // O contador PWM deve "envolver" a cada 20ms (50Hz)
    pwm_set_wrap(slice_num, 39062); // 125MHz / 64 = 1.953125 MHz; 1.953125 MHz / 50Hz = 39062

    pwm_set_enabled(slice_num, true);
}

void set_servo_pulse(uint gpio, uint16_t pulse_width_us)
{
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    uint16_t level = (pulse_width_us * (39062)) / PWM_PERIOD;
    pwm_set_gpio_level(gpio, level);
}

int main()
{
    stdio_init_all();
    setup_pwm(SERVO_PIN);

    while (true)
    {
        // Posiciona o servo em 180 graus (2400us)
        set_servo_pulse(SERVO_PIN, 2400);
        sleep_ms(5000);

        // Posiciona o servo em 90 graus (1470us)
        set_servo_pulse(SERVO_PIN, 1470);
        sleep_ms(5000);

        // Posiciona o servo em 0 graus (500us)
        set_servo_pulse(SERVO_PIN, 500);
        sleep_ms(5000);

        // Movimentação suave entre 0 e 180 graus
        for (uint16_t pulse = 500; pulse <= 2400; pulse += 5)
        {
            set_servo_pulse(SERVO_PIN, pulse);
            sleep_ms(10);
        }
        for (uint16_t pulse = 2400; pulse >= 500; pulse -= 5)
        {
            set_servo_pulse(SERVO_PIN, pulse);
            sleep_ms(10);
        }
    }
}