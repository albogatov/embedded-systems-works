#include "hal.h"
#include <bitset>

int i = 0;
int leds[] = {GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_11, GPIO_PIN_12};
bitset<4> sw;
unsigned int sw_pins[4] = {GPIO_PIN_12, GPIO_PIN_10, GPIO_PIN_8, GPIO_PIN_4};
int frames[8][8] = {
    {1,0,0,0,0,0,0,1},
    {1,1,0,0,0,0,1,1},
    {1,1,1,0,0,1,1,1},
    {1,1,1,1,1,1,1,1},
    {1,1,1,0,0,1,1,1},
    {1,1,0,0,0,0,1,1},
    {1,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,0},
};

void TIM7_IRQ_Handler();
void TIM6_IRQ_Handler();
void process();
void set_led(int num[8]);
void reset_led(int num[8]);

int umain() {
 
    registerTIM6_IRQHandler(TIM6_IRQ_Handler);
    registerTIM7_IRQHandler(TIM7_IRQ_Handler);
    
    __enable_irq();
    
    WRITE_REG(TIM6_ARR, 500);
    WRITE_REG(TIM6_DIER, TIM_DIER_UIE);
    WRITE_REG(TIM6_PSC,0);
    
    WRITE_REG(TIM7_ARR, 500);
    WRITE_REG(TIM7_DIER, TIM_DIER_UIE);
    WRITE_REG(TIM7_PSC,1);
    
    WRITE_REG(TIM6_CR1, TIM_CR1_CEN);
	
    WRITE_REG(TIM7_CR1, TIM_CR1_CEN);
    
    return 0;
}

void process() {
    for(int i = 0; i<4; i++) {
        GPIO_PinState state = HAL_GPIO_ReadPin(GPIOE, sw_pins[i]);
        sw[i] = state == GPIO_PIN_SET;
    }
}

void set_led(int num[8]) {
    for (int i = 0; i < 8;i++){
        if (num[i] == 1) {
            HAL_GPIO_WritePin(GPIOD,leds[i],GPIO_PIN_SET);
        }
    }
}

void reset_led(int num[8]) {
    for (int i = 0; i < 8;i++){
        if (num[i] == 0) {
            HAL_GPIO_WritePin(GPIOD,leds[i],GPIO_PIN_RESET);
        }
    }
}

void TIM6_IRQ_Handler() {
    set_led(frames[i]);
}

void TIM7_IRQ_Handler() {
	int delay = sw.to_ulong()*100;
    reset_led(frames[i]);
    i++;
    if(i > 8) i=0;
    process();
    WRITE_REG(TIM6_ARR, 500 + delay);
    WRITE_REG(TIM7_ARR, 500 + delay);
}