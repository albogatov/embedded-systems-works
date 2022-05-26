#include <iostream>
#include "hal.h"
#include <cmath>

int leds[] = {GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_11, GPIO_PIN_12};
int switches[] = {GPIO_PIN_4, GPIO_PIN_8, GPIO_PIN_10, GPIO_PIN_12};
int delay = 500;
int n = 3;

void red() {
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
}

void green() {
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
}

void yellow() {
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
}

bool check_value(const int * switches, const int n, int * bits) {
    int sum = 0;
    for (int i = 0; i < 4; i++) {
        bits[i] = HAL_GPIO_ReadPin(GPIOE, switches[i]) == GPIO_PIN_SET;
        sum += bits[i] * (int) pow(2, 3 - i);
    }
    return sum == n;
}

void nbtn_click() {
    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15) == GPIO_PIN_RESET) 
		red();
}

void lights_reboot(const int * leds) {
    for (int i = 0; i < 8; i++) 
		HAL_GPIO_WritePin(GPIOD, leds[i], GPIO_PIN_RESET);
}

void set_up_switches(const int * leds, const int * bits) {
    for (int i = 0; i < 4; i++)
        HAL_GPIO_WritePin(GPIOD, leds[i], bits[i] == 1 ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

int umain() {
    while (true) {
        int bits[] = {0, 0, 0, 0};
		int count = 0;
		int reverse = 3;
        bool start = true;
        bool nbtn_pressed = false;
        if (check_value(switches, n, bits)) {
			while (check_value(switches, n, bits)) {
					lights_reboot(leds);
					for (int i = 0 ; i < 11 && check_value(switches, n, bits); start = false, i++) {
						if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15) == GPIO_PIN_RESET) {
							nbtn_pressed = !nbtn_pressed;
							HAL_Delay(delay);
						}
						if (nbtn_pressed) {
							i--;
							red();
							continue;
						}
						green();
						count++;
						if (start) {
							HAL_GPIO_WritePin(GPIOD, leds[7], GPIO_PIN_SET);
							HAL_GPIO_WritePin(GPIOD, leds[6], GPIO_PIN_SET);
							HAL_Delay(delay);
						}
						if (count % 12 < 7) {
							HAL_GPIO_WritePin(GPIOD, leds[7 - i % 8], GPIO_PIN_RESET);
							HAL_GPIO_WritePin(GPIOD, leds[7 - (i + 2) % 8], GPIO_PIN_SET);
						} else if (count % 12 == 7) {
							HAL_GPIO_WritePin(GPIOD, leds[(i + 2) % 8], GPIO_PIN_RESET);
							HAL_GPIO_WritePin(GPIOD, leds[8 - i % 8], GPIO_PIN_SET);
						} else {
							HAL_GPIO_WritePin(GPIOD, leds[(i + 2) % 8], GPIO_PIN_RESET);
							HAL_GPIO_WritePin(GPIOD, leds[reverse], GPIO_PIN_SET);
							reverse++;
						}
						HAL_Delay(delay);
					}
					lights_reboot(leds);
					count = 0;
					reverse = 3;
					start = true;
			}
        }
        yellow();
        set_up_switches(leds, bits);
    }

    return 0;
}