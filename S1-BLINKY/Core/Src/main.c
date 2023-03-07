#include "main.h"
#include <assert.h>
#include <stdbool.h>


void SystemClock_Config(void);
static void MX_GPIO_Init(void);

#define GPIOA_ST                  (( volatile )(( unsigned int *)0x40010800 ))
#define GPIOB_ST                  (( volatile )(( unsigned int *)0x40010C00 ))
#define GPIOC_ST                  (( volatile )(( unsigned int *)0x40011000 ))
#define GPIOD_ST                  (( volatile )(( unsigned int *)0x40011400 ))
#define GPIOE_ST                  (( volatile )(( unsigned int *)0x40011800 ))
 
                                   //0b0000.0000.0000.0000
#define GPIOX_PIN_0                (unsigned int )0x0001
#define GPIOX_PIN_1                (unsigned int )0x0002
#define GPIOX_PIN_2                (unsigned int )0x0004
#define GPIOX_PIN_3                (unsigned int )0x0008
#define GPIOX_PIN_4                (unsigned int )0x0010
#define GPIOX_PIN_5                (unsigned int )0x0020                    //  0b0000000000100000
#define GPIOX_PIN_6                (unsigned int )0x0040
#define GPIOX_PIN_7                (unsigned int )0x0080
#define GPIOX_PIN_8                (unsigned int )0x0100
#define GPIOX_PIN_9                (unsigned int )0x0200
#define GPIOX_PIN_10               (unsigned int )0x0400
#define GPIOX_PIN_11               (unsigned int )0x0800
#define GPIOX_PIN_12               (unsigned int )0x1000
#define GPIOX_PIN_13               (unsigned int )0x2000
#define GPIOX_PIN_14               (unsigned int )0x4000
#define GPIOX_PIN_15               (unsigned int )0x8000

typedef enum Valx{
	LOGIC_LOW_STATE 	= 0,
	LOGIC_HIGH_STATE	   ,
	LOGIC_UNK_STATE	     ,
}Valx_t;

typedef enum boolVal{
    BOOLVAL_SE      = 0,
    BOOLVAL_HG         ,
    BOOLVAL_SX         ,
}boolVal_t;

bool led_writepin(unsigned int GPIOx, unsigned int Pinx){
    assert(GPIOx > BOOLVAL_SE && Pinx > BOOLVAL_SE );
    HAL_GPIO_WritePin(GPIOx,Pinx,LOGIC_HIGH_STATE);    
    return true;
}

bool led_erasepin(unsigned int GPIOx, unsigned int Pinx){
    assert(GPIOx > BOOLVAL_SE && Pinx > BOOLVAL_SE );
    HAL_GPIO_WritePin(GPIOx,Pinx,LOGIC_LOW_STATE);    
    return true;
}

bool led_blinkpin(unsigned int GPIOx, unsigned int Pinx){
    assert(GPIOx > BOOLVAL_SE && Pinx > BOOLVAL_SE );
    HAL_GPIO_TogglePin(GPIOx,Pinx);    
    return true;
}


int main(void)
{

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  while (1) {
    led_writepin(GPIOA_ST,GPIOX_PIN_5);
    HAL_Delay(1000);
    led_erasepin(GPIOA_ST,GPIOX_PIN_5);
    HAL_Delay(1000);

    /*STM32F103RBT6
    Vout = 3.3v
    PORT = A.B.C.D.E.F
    */
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

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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
