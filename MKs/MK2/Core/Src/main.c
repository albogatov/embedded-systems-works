/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "kb.h"
#include "sdk_uart.h"
#include "pca9538.h"
#include "oled.h"
#include "fonts.h"
#include "tim.h"
#include "buzzer.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
	uint32_t megalovania_melody[] = {
			N_D3, N_D3, N_D4, N_A3, 0, N_GS3, N_G3, N_F3, N_D3, N_F3, N_G3, N_C3, N_C3, N_D4, N_A3, 0, N_GS3, N_G3, N_F3, N_D3, N_F3, N_G3, N_B2, N_B2, N_D4, N_A3, 0, N_GS3, N_G3, N_F3, N_D3, N_F3, N_G3, N_AS2, N_AS2, N_D4, N_A3, 0, N_GS3, N_G3, N_F3, N_D3, N_F3, N_G3, N_D3, N_D3, N_D4, N_A3, 0, N_GS3, N_G3, N_F3, N_D3, N_F3, N_G3, N_C3, N_C3, N_D4, N_A3, 0, N_GS3, N_G3, N_F3, N_D3, N_F3, N_G3, N_B2, N_B2, N_D4, N_A3, 0, N_GS3, N_G3, N_F3, N_D3, N_F3, N_G3, N_AS2, N_AS2, N_D4, N_A3, 0, N_GS3, N_G3, N_F3, N_D3, N_F3, N_G3, N_D4, N_D4, N_D5, N_A4, 0, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, N_C4, N_C4, N_D5, N_A4, 0, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, N_B3, N_B3, N_D5, N_A4, 0, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, N_AS3, N_AS3, N_D5, N_A4, 0, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, N_D4, N_D4, N_D5, N_A4, 0, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, N_C4, N_C4, N_D5, N_A4, 0, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, N_B3, N_B3, N_D5, N_A4, 0, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, N_AS3, N_AS3, N_D5, N_A4, 0, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, N_F4, N_F4, N_F4, N_F4, N_F4, N_D4, N_D4, N_D4, N_F4, N_F4, N_F4, N_G4, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, 0, N_F4, N_F4, N_F4, N_G4, N_GS4, N_A4, N_C5, N_A4, N_D5, N_D5, N_D5, N_A4, N_D5, N_C5, N_F4, N_F4, N_F4, N_F4, N_F4, N_D4, N_D4, N_D4, N_F4, N_F4, N_F4, N_F4, N_D4, N_F4, N_E4, N_D4, N_C4, 0, N_G4, N_E4, N_D4, N_D4, N_D4, N_D4, N_F3, N_G3, N_AS3, N_C4, N_D4, N_F4, N_C5, 0, N_F4, N_D4, N_F4, N_G4, N_GS4, N_G4, N_F4, N_D4, N_GS4, N_G4, N_F4, N_D4, N_F4, N_F4, N_F4, N_GS4, N_A4, N_C5, N_A4, N_GS4, N_G4, N_F4, N_D4, N_E4, N_F4, N_G4, N_A4, N_C5, N_CS5, N_GS4, N_GS4, N_G4, N_F4, N_G4, N_F3, N_G3, N_A3, N_F4, N_E4, N_D4, N_E4, N_F4, N_G4, N_E4, N_A4, N_A4, N_G4, N_F4, N_DS4, N_CS4, N_DS4, 0, N_F4, N_D4, N_F4, N_G4, N_GS4, N_G4, N_F4, N_D4, N_GS4, N_G4, N_F4, N_D4, N_F4, N_F4, N_F4, N_GS4, N_A4, N_C5, N_A4, N_GS4, N_G4, N_F4, N_D4, N_E4, N_F4, N_G4, N_A4, N_C5, N_CS5, N_GS4, N_GS4, N_G4, N_F4, N_G4, N_F3, N_G3, N_A3, N_F4, N_E4, N_D4, N_E4, N_F4, N_G4, N_E4, N_A4, N_A4, N_G4, N_F4, N_DS4, N_CS4, N_DS4,
	};
	uint32_t megalovania_delays[] = {
			16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 8, 16, 8, 8, 8, 8, 4, 16, 8, 16, 8, 8, 8, 16, 16, 16, 16, 16, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 8, 16, 16, 16, 2, 8, 16, 8, 8, 8, 8, 4, 16, 8, 16, 8, 8, 8, 8, 8, 16, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8, 15, 8, 8, 2, 3, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 2, 16, 8, 16, 8, 16, 16, 16, 16, 16, 16, 8, 8, 8, 8,  8, 8, 16, 16, 16, 2, 8, 8, 8, 8, 4, 4, 4, 4, 4, 4, 2, 8, 8, 8, 8, 2, 2, 3, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 2, 16, 8, 16, 8, 16, 16, 16, 16, 16, 16, 8, 8, 8, 8,  8, 8, 16, 16, 16, 2, 8, 8, 8, 8, 4, 4, 4, 4, 4, 4, 2, 8, 8, 8, 8, 2, 1
	};
	uint32_t zelda_melody[] = {
			N_AS4, 0, 0, N_AS4, N_AS4, N_AS4, N_AS4, N_AS4, 0, N_GS4, N_AS4, 0, 0, N_AS4, N_AS4, N_AS4, N_AS4, N_AS4, 0, N_GS4, N_AS4, 0, 0, N_AS4, N_AS4, N_AS4, N_AS4, N_AS4, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_AS4, N_F3, N_F3, 0, N_AS4, N_AS4, N_C5, N_D5, N_DS5, N_F5, 0, N_F5, N_F5, N_FS5, N_GS5, N_AS5, 0, N_AS5, N_AS5, N_AS5, N_GS5, N_FS5, N_GS5, 0, N_FS5, N_F5, N_F5, N_DS5, N_DS5, N_F5, N_FS5, N_F5, N_DS5, N_CS5, N_CS5, N_DS5, N_F5, N_DS5, N_CS5, N_C5, N_C5, N_D5, N_E5, N_G5, N_F5, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_AS4, N_F3, N_F3, 0, N_AS4, N_AS4, N_C5, N_D5, N_DS5, N_F5, 0, N_F5, N_F5, N_FS5, N_GS5, N_AS5, 0, N_CS6, N_C6, N_A5, 0, N_F5, N_FS5, 0, N_AS5, N_A5, N_F5, 0, N_F5, N_FS5, 0, N_AS5, N_A5, N_F5, 0, N_D5, N_DS5, 0, N_FS5, N_F5, N_CS5, 0, N_AS4, N_C5, N_C5, N_D5, N_E5, 0, N_G5, N_F5, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_AS4, N_F3, N_F3, 0, N_AS4, N_AS4, N_C5, N_D5, N_DS5, N_F5, 0, N_F5, N_F5, N_FS5, N_GS5, N_AS5, 0, N_AS5, N_AS5, N_AS5, N_GS5, N_FS5, N_GS5, 0, N_FS5, N_F5, N_F5, N_DS5, N_DS5, N_F5, N_FS5, N_F5, N_DS5, N_CS5, N_CS5, N_DS5, N_F5, N_DS5, N_CS5, N_C5, N_C5, N_D5, N_E5, N_G5, N_F5, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_AS4, N_F3, N_F3, 0, N_AS4, N_AS4, N_C5, N_D5, N_DS5, N_F5, 0, N_F5, N_F5, N_FS5, N_GS5, N_AS5, 0, N_CS6, N_C6, N_A5, 0, N_F5, N_FS5, 0, N_AS5, N_A5, N_F5, 0, N_F5, N_FS5, 0, N_AS5, N_A5, N_F5, 0, N_D5, N_DS5, 0, N_FS5, N_F5, N_CS5, 0, N_AS4, N_C5, N_C5, N_D5, N_E5, 0, N_G5, N_F5, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3
	};
	uint32_t zelda_delays[] = {
			2, 8, 8, 8, 8, 8, 8, 6, 16, 16, 4, 8, 8, 8, 8, 8, 8, 6, 16, 16, 4, 8, 8, 8, 8, 8, 8, 8, 16, 16, 8, 16, 16, 8, 16, 16, 8, 8, 4, 4, 6, 16, 16, 16, 16, 16, 16, 2, 8, 8, 8 ,8 ,8, 2, 8, 8, 8 ,8 ,8, 8, 6, 16, 16, 2, 4, 8, 16, 16, 2, 8, 8, 8, 16, 16, 2, 8, 8, 8, 16, 16, 2, 4, 8, 16, 16, 8, 16, 16, 8, 16, 16, 8, 8, 4, 4, 6, 16, 16, 16, 16, 16, 16, 2, 8, 8, 8 ,8 ,8, 2, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 8, 16, 16, 4, 4, 4, 8, 16, 16, 8, 16, 16, 8, 16, 16, 8, 8, 4, 4, 6, 16, 16, 16, 16, 16, 16, 2, 8, 8, 8 ,8 ,8, 2, 8, 8, 8 ,8 ,8, 8, 6, 16, 16, 2, 4, 8, 16, 16, 2, 8, 8, 8, 16, 16, 2, 8, 8, 8, 16, 16, 2, 4, 8, 16, 16, 8, 16, 16, 8, 16, 16, 8, 8, 4, 4, 6, 16, 16, 16, 16, 16, 16, 2, 8, 8, 8 ,8 ,8, 2, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 8, 16, 16, 4, 4, 4, 8, 16, 16, 8, 16, 16, 8, 16, 16, 8, 8
	};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void KB_Test( void );
void oled_timer(uint8_t OLED_Keys[4]);
void ALARM( void );
void oled_clear( void );
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART6_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  oled_Init();
  MX_TIM2_Init();
  Buzzer_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */
	ALARM();
    /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void ALARM( void ) {
	uint8_t row[4] = {ROW4, ROW3, ROW2, ROW1};
	uint8_t key;
	uint8_t old_key;
	uint8_t keys[4] = {0x30,0x30,0x30,0x30};
	  oled_clear();
	  oled_display_string("Time: ", Font_11x18, White);
	  oled_timer(keys);
	  oled_update();
	  uint8_t is_running = 0;
	  uint8_t is_onpause = 0;
	  uint8_t pos = 0;
	  int count = 0;
	  int reset = 0;
	  int limit = 3600;
	  uint32_t time = 0;

	  uint8_t seconds;
	  uint8_t seconds_by_ten;
	  uint8_t minutes;
	  uint8_t minutes_by_ten;

	  while (1){
	    if (is_running){
	    	if (time >= limit) {
	    		time = limit;
	    	}
	      while (time != 0) {
	        HAL_Delay(25);
	        count++;
	        if (!is_onpause && count == 1000 / 28) {
	          time--;
	          minutes_by_ten = time / 600;
	          count = 0;
	          minutes = (time - 600 * minutes_by_ten) / 60;
	          seconds_by_ten = (time - 600 * minutes_by_ten - 60 * minutes) / 10;
	          seconds = (time - 600 * minutes_by_ten - 60 * minutes - 10 * seconds_by_ten);
	          keys[0] = 0x30 + seconds;
	          keys[1] = 0x30 + seconds_by_ten;
	          keys[2] = 0x30 + minutes;
	          keys[3] = 0x30 + minutes_by_ten;
	          oled_timer(keys);
	        }

	          old_key = key;
	          key = get_key( row[0] );
	          if (key == 0x0C && old_key != key) {
	            if (is_onpause) {
	              is_onpause = 0;
	            } else {
	              is_onpause = 1;
	            }
	            count = 0;
	          }
	          if (key == 0x0B) {
	        	  reset = 1;
	        	  return;
	          }
	      }
	      is_running = 0;

	      pos = 0;
	      keys[0] = 0x30;
	      keys[1] = 0x30;
	      keys[2] = 0x30;
	      keys[3] = 0x30;
	      oled_timer(keys);
	      if (!reset) {
	    	  buzzer_play(megalovania_melody, megalovania_delays, sizeof(megalovania_melody) / sizeof(uint32_t));
	      }
	      reset = 0;

	    }
	    for ( int i = 0; i < 4; i++ ){
	      old_key = key;
	      key = get_key( row[i] );
	      if (key != old_key){
	        // 7 8 9
	        // 4 5 6
	        // 1 2 3
	        // 0 S B
	        if (key >= 0x00 && key <= 0x0A && !is_running){
	          keys[pos] = 0x30 + key;
	          if (pos == 0) {
	            time=0;
	             keys[1] = 0x30;
	             keys[2] = 0x30;
	             keys[3] = 0x30;
	            time += key;
	            pos++;
	          }else  if (pos == 1) {
	             time += 10*key;
	              pos++;
	          }else if (pos == 2) {
	            time += 60*key;
	              pos++;
	          } else if (pos == 3){
	        	  if (key > 5) {
	        		  key = 5;
	        		  keys[pos] = 0x30 + key;
	        	  }
	            time += 600*key;
	            pos = 0;
	          }
	          oled_timer(keys);
	        } else if (key == 0x0B){
	            return;
	        } else if (key == 0x0C){
	          if (!is_running){
	            is_running  = 1;
	          } else {
	            if (is_onpause){
	              is_onpause = 0;
	            } else {
	              is_onpause = 1;
	            }
	          }
	        }
	      }
	      HAL_Delay(20);
	    }
	  }
}

void oled_timer(uint8_t OLED_Keys[4]){
	oled_SetCursor(30, 30);
	for (int i = 3; i >= 0; i--) {
			if (i == 1){
				oled_WriteChar(0x3A, Font_16x26, White);
			}
			oled_WriteChar(OLED_Keys[i], Font_16x26, White);
		}
	oled_update();
}

void oled_clear( void ) {
	oled_Fill(Black);
	oled_SetCursor(0, 0);
	oled_update();
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_
FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
