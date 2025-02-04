/*
 * HX711.c
 *
 *  Created on: Jan 17, 2025
 *      Author: Ziya
 */
#include "main.h"
#include "HX711.h"

/*
 *@brief: Initalize and gain set HX711
 *	Change gain see datasheet page 4 table 3
 *@param: none
 *@return: void
 *@author: ziya
 */
void 	HX711_Init()
{
	//LL_GPIO_ResetOutputPin(SCK_GPIO_Port, SCK_Pin);
	HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, 0);

	uint8_t i;
	i = 0;
	while(i < CHANNEL_A_GAIN128)
	{
		//LL_GPIO_SetOutputPin(SCK_GPIO_Port, SCK_Pin);
		//LL_GPIO_ResetOutputPin(SCK_GPIO_Port, SCK_Pin);
		HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, 1);
		HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, 0);
		i++;
	}
}

/*
 * @brief: Data pini normalde set edilmis durumda data hazır olduğunda reset olur. Data pini reset olduğunda clock pulse vererek okuma yapar
 * datasheet sayfe 8
 * @param: none
 * @return: uint32_t value; hx711 adc value
 * @author ziya
 */
uint32_t 	HX711_READ()
{
	uint32_t value;
	value = 0;

	//while(!LL_GPIO_IsInputPinSet(DT_GPIO_Port, DT_Pin));
	//while (HAL_GPIO_ReadPin(DT_GPIO_Port, DT_Pin) == GPIO_PIN_SET);
	while(HAL_GPIO_ReadPin(DT_GPIO_Port, DT_Pin) == GPIO_PIN_SET); //interrupta kullanılırsa buna gerek yok

	uint8_t i;
	i = 0;
	while(i < HX711_BIT)
	{
		//LL_GPIO_SetOutputPin(SCK_GPIO_Port, SCK_Pin);
		HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, 1);
		value = value << 1;
		//LL_GPIO_ResetOutputPin(SCK_GPIO_Port, SCK_Pin);
		HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, 0);

		if(HAL_GPIO_ReadPin(DT_GPIO_Port, DT_Pin) == GPIO_PIN_SET)
		{
			value++;
		}
		i++;
	}

	//LL_GPIO_SetOutputPin(SCK_GPIO_Port, SCK_Pin);
	//LL_GPIO_ResetOutputPin(SCK_GPIO_Port, SCK_Pin);
	HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, 1);
	HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, 0);

	value ^ SIGNED_BIT;

	return value;
}
