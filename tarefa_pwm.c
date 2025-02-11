#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22     // GPIO usada para controlar o servo
#define PWM_FREQUENCY 50 // Frequência do PWM (50Hz)
#define PWM_WRAP 20000   // Período do PWM em microssegundos (20ms)

void set_servo_pulse(uint slice, uint channel, uint pulse_width)
{
    // Define a largura do pulso PWM
    pwm_set_chan_level(slice, channel, pulse_width);
}

int main()
{
    stdio_init_all();

    // Configuração do PWM na GPIO 22
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);
    uint channel = pwm_gpio_to_channel(SERVO_PIN);

    pwm_set_wrap(slice_num, PWM_WRAP); // Define o período do PWM (20ms)
    pwm_set_clkdiv(slice_num, 125.0);  // Reduz a frequência do clock para ajustar o PWM
    pwm_set_enabled(slice_num, true);  // Habilita o PWM

    // Movendo o servo para 180°, 90° e 0° com intervalo de 5 segundos
    printf("Movendo para 180 graus...\n");
    set_servo_pulse(slice_num, channel, 2400);
    sleep_ms(5000);

    printf("Movendo para 90 graus...\n");
    set_servo_pulse(slice_num, channel, 1470);
    sleep_ms(5000);

    printf("Movendo para 0 graus...\n");
    set_servo_pulse(slice_num, channel, 500);
    sleep_ms(5000);

    // Movimentação contínua entre 0° e 180°
    printf("Iniciando movimento contínuo entre 0° e 180°...\n");

    while (1)
    {
        // Subindo de 0° para 180°
        for (uint pulse = 500; pulse <= 2400; pulse += 5)
        {
            set_servo_pulse(slice_num, channel, pulse);
            sleep_ms(10);
        }
        // Descendo de 180° para 0°
        for (uint pulse = 2400; pulse >= 500; pulse -= 5)
        {
            set_servo_pulse(slice_num, channel, pulse);
            sleep_ms(10);
        }
    }

    return 0;
}