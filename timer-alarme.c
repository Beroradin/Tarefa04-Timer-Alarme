#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define RED_PIN 13
#define GREEN_PIN 11
#define BLUE_PIN 12
#define BUTTON_PIN 5

volatile bool sequence_running = false;

int64_t turn_off_green_callback(alarm_id_t id, void *user_data);
int64_t turn_off_blue_callback(alarm_id_t id, void *user_data);
int64_t turn_off_red_callback(alarm_id_t id, void *user_data);

void start_led_sequence() {
    if (sequence_running) return;
    sequence_running = true;
    
    gpio_put(RED_PIN, 1);
    gpio_put(BLUE_PIN, 1);
    gpio_put(GREEN_PIN, 1);
    add_alarm_in_ms(3000, turn_off_red_callback, NULL, false);
}

int64_t turn_off_red_callback(alarm_id_t id, void *user_data) {
    gpio_put(RED_PIN, 0);
    add_alarm_in_ms(3000, turn_off_blue_callback, NULL, false);
    return 0;
}

int64_t turn_off_blue_callback(alarm_id_t id, void *user_data) {
    gpio_put(BLUE_PIN, 0);
    add_alarm_in_ms(3000, turn_off_green_callback, NULL, false);
    return 0;
}

int64_t turn_off_green_callback(alarm_id_t id, void *user_data) {
    gpio_put(GREEN_PIN, 0);
    sequence_running = false;
    return 0;
}

bool button_pressed() {
    static uint32_t last_press_time = 0;
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    if (current_time - last_press_time < 200) {
        return false;
    }
    last_press_time = current_time;
    return true;
}

int main() {
    stdio_init_all();
    gpio_init(RED_PIN);
    gpio_set_dir(RED_PIN, GPIO_OUT);
    gpio_init(BLUE_PIN);
    gpio_set_dir(BLUE_PIN, GPIO_OUT);
    gpio_init(GREEN_PIN);
    gpio_set_dir(GREEN_PIN, GPIO_OUT);
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    while (1) {
        if (gpio_get(BUTTON_PIN) == 0 && button_pressed()) {
            start_led_sequence();
        }
        sleep_ms(10);
    }
}
