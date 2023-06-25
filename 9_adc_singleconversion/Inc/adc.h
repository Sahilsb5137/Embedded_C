/*
 * adc.h
 *
 *  Created on: May 3, 2023
 *      Author: 14699
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void adc_init(void);
void start_conversion (void);
uint32_t adc_read(void);

#endif /* ADC_H_ */
