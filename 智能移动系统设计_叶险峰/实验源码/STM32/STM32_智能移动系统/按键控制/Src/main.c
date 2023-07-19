/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define KEY HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_15)
#define right_trace HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14)
#define left_trace HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15)
#define left_avoid HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12)
#define right_avoid HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t key = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void forward(uint8_t speed,uint8_t time);
uint8_t Key_Scan(uint8_t mode);
void left(uint8_t speed,uint8_t time);
void right(uint8_t speed,uint8_t time);
void trace(uint8_t speed,uint8_t time);
void back(uint8_t speed,uint8_t time);
void avoid(uint8_t speed);
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
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		key =Key_Scan(1);
		switch(key)
		{
			case 0:
			{
				trace(50,1);break;
			}
			//////////////////
			case 1:
				{
					avoid(50);break;
				}
			case 2:
			{back(30,100);break;}
			
			default:{forward(30,100);break;}
		}
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void forward(uint8_t speed,uint8_t time)
{  
  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,speed);//设置占空比speed%
  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,speed);//设置占空比speed%
  //左轮
	L298N_IN1 = 0; 
	L298N_IN2 = 1;
//右轮
	L298N_IN3 = 1; 
	L298N_IN4 = 0;
	HAL_Delay(time*10);  
  }
uint8_t Key_Scan(uint8_t mode)
	{
    static uint8_t key_up = 1;
    if(mode)    key_up = 1;
    if(key_up && (KEY == 0))
			{
        HAL_Delay(10);
        key_up = 0;
        if(KEY == 0) 
		{
					key++;
					
    }
			}
    else if(KEY == 1){
        key_up = 1;
    }
		if(key>3) key = 0;
    return key;

}
void left(uint8_t speed,uint8_t time)
{  
  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,speed);//设置占空比speed%
  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,speed);//设置占空比speed%
  //左轮
	L298N_IN1 = 0; 
	L298N_IN2 = 0;
//右轮
	L298N_IN3 = 1; 
	L298N_IN4 = 0;
	HAL_Delay(time*10);  
  }
void right(uint8_t speed,uint8_t time)
{  
  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,speed);//设置占空比speed%
  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,speed);//设置占空比speed%
  //左轮
	L298N_IN1 = 0; 
	L298N_IN2 = 1;
//右轮
	L298N_IN3 = 0; 
	L298N_IN4 = 0;
	HAL_Delay(time*10);  
  }
void back(uint8_t speed,uint8_t time)
{  
  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,speed);//设置占空比speed%
  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,speed);//设置占空比speed%
  //左轮
	L298N_IN1 = 1; 
	L298N_IN2 = 0;
//右轮
	L298N_IN3 = 0; 
	L298N_IN4 = 1;
	HAL_Delay(time*10);  
  }
void trace(uint8_t speed,uint8_t time)
{	
	
	while(1){
if(right_trace == 1 && left_trace == 1)
{
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,speed);
  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,speed);
	L298N_IN1 = 0; 
	L298N_IN2 = 0;
	L298N_IN3 = 0; 
	L298N_IN4 = 0;
}else if(right_trace == 1&&left_trace == 0){
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,speed);
  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,speed);	
	L298N_IN1 = 0; 
	L298N_IN2 = 0;
	L298N_IN3 = 1; 
	L298N_IN4 = 0;
}else if(right_trace == 0&&left_trace == 1){
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,speed);
  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,speed);	
	L298N_IN1 = 0; 
	L298N_IN2 = 1;
	L298N_IN3 = 0; 
	L298N_IN4 = 0;
}else if(right_trace == 0&&left_trace == 0){
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,30);
  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,30);
	L298N_IN1 = 0; 
	L298N_IN2 = 1;
	L298N_IN3 = 1; 
	L298N_IN4 = 0;
}
key = Key_Scan(1);
if(key != 0){HAL_Delay(1000); break;}
	}
}
void avoid(uint8_t speed)
{
	
	while(1){
if(right_avoid == 1 && left_avoid == 1)
{
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,speed);
  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,speed);
	L298N_IN1 = 0; 
	L298N_IN2 = 1;
	L298N_IN3 = 1; 
	L298N_IN4 = 0;
}else if(right_avoid == 1&&left_avoid == 0)
{
	back(speed,80);
	right(speed,80);
}else if(right_avoid == 0&&left_avoid== 1){
  back(speed,80);
	left(speed,80);
}else if(right_avoid == 0&&left_avoid == 0){
	back(speed,80);
	right(speed,80);
}
if(key != 1){HAL_Delay(1000); break;}


	}
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
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
