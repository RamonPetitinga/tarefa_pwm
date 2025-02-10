#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Definições de pinos e configurações PWM
#define PIN_SERVO 22                                     // Pino de controle do servo motor
#define LED_RGB_PIN 12                                   // Pino de controle do LED RGB
#define PWM_FREQ 50                                      // Frequência do PWM (50Hz para servos)
#define CLOCK_FREQ 125000000                             // Frequência do clock da CPU (125 MHz)
#define PWM_DIVIDER 64.0                                 // Reduz a frequência do clock para PWM
#define PWM_WRAP (CLOCK_FREQ / (PWM_DIVIDER * PWM_FREQ)) // Valor de "wrap" do PWM para 50Hz

// Função para configurar o PWM em um pino específico
void setup_pwm(uint pin, uint *slice_num, uint *channel)
{
    gpio_set_function(pin, GPIO_FUNC_PWM);
    *slice_num = pwm_gpio_to_slice_num(pin); // Obtém o slice PWM do pino
    *channel = pwm_gpio_to_channel(pin);     // Obtém o canal PWM do pino

    pwm_set_clkdiv(*slice_num, PWM_DIVIDER); // Define o divisor de clock do PWM
    pwm_set_wrap(*slice_num, PWM_WRAP);      // Define o valor de "wrap" do PWM
    pwm_set_enabled(*slice_num, true);       // Habilita o PWM no slice correspondente
}

// Função para definir o ângulo do servo com base no pulso em microssegundos
void set_servo_angle(uint slice_num, uint channel, float pulse_us)
{
    uint16_t level = (pulse_us / 20000.0) * PWM_WRAP; // Converte tempo de pulso para nível de PWM
    pwm_set_chan_level(slice_num, channel, level);    // Define o nível do PWM para o servo
}

// Função para definir o brilho do LED com base no pulso em microssegundos
void set_led_brightness(uint slice_num, uint channel, float pulse_us)
{
    uint16_t level = (pulse_us / 20000.0) * PWM_WRAP; // Converte tempo de pulso para nível de PWM
    pwm_set_chan_level(slice_num, channel, level);    // Define o nível do PWM para o LED
}

int main()
{
    stdio_init_all(); // Inicializa entrada e saída padrão
    sleep_ms(500);    // Pequeno atraso para estabilização do sistema

    uint slice_num_servo, channel_servo;
    uint slice_num_led, channel_led;

    // Configuração do PWM para o servo
    setup_pwm(PIN_SERVO, &slice_num_servo, &channel_servo);

    // Configuração do PWM para o LED
    setup_pwm(LED_RGB_PIN, &slice_num_led, &channel_led);

    // Define o servo para a posição inicial de 270° (sul) e ajusta o brilho do LED proporcionalmente
    set_servo_angle(slice_num_servo, channel_servo, 2400);
    set_led_brightness(slice_num_led, channel_led, 2400);
    sleep_ms(5000);

    // Move o servo para 0° (leste) e ajusta o LED
    set_servo_angle(slice_num_servo, channel_servo, 1470);
    set_led_brightness(slice_num_led, channel_led, 1470);
    sleep_ms(5000);

    // Move o servo para 90° (norte) e ajusta o LED
    set_servo_angle(slice_num_servo, channel_servo, 500);
    set_led_brightness(slice_num_led, channel_led, 500);
    sleep_ms(5000);

    while (1)
    {
        // Movimento suave do servo de 90° para 270° passando por 0°
        for (float pulse = 500; pulse <= 2400; pulse += 5)
        {
            set_servo_angle(slice_num_servo, channel_servo, pulse);
            set_led_brightness(slice_num_led, channel_led, pulse);
            sleep_ms(10); // Pequeno atraso para suavizar o movimento
        }

        // Movimento suave do servo de 270° para 90° passando por 0°
        for (float pulse = 2400; pulse >= 500; pulse -= 5)
        {
            set_servo_angle(slice_num_servo, channel_servo, pulse);
            set_led_brightness(slice_num_led, channel_led, pulse);
            sleep_ms(10); // Pequeno atraso para suavizar o movimento
        }
    }
}