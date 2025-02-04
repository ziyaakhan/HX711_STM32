/*
 * HX711.h
 *
 *  Created on: Jan 17, 2025
 *      Author: Ziya
 */

#ifndef INC_HX711_H_
#define INC_HX711_H_

#define CHANNEL_A_GAIN128 25
#define CHANNEL_B_GAIN32  26
#define CHANNEL_A_GAIN64  27

#define SIGNED_BIT 0x800000

#define HX711_BIT 24 // HX711 24bit adc

#define CALIBRATION_FACTORY 22.6F
#define TARE_VALUE 52300

extern uint32_t 	HX711_READ();
extern void 	HX711_Init();

#endif /* INC_HX711_H_ */


