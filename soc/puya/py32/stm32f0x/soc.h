/*
 * Copyright (c) 2017 RnDity Sp. z o.o.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file SoC configuration macros for the STM32F0 family processors.
 *
 * Based on reference manual:
 *   STM32F030x4/x7/x8/xC,
 *   STM32F070x7/xB advanced ARM ® -based MCUs
 *
 * Chapter 2.2: Memory organization
 */


#ifndef _STM32F0_SOC_H_
#define _STM32F0_SOC_H_

#ifndef _ASMLANGUAGE

#include <stm32f0xx.h>

/* The STM32 HAL headers define these, but they conflict with the Zephyr can.h */
#undef CAN_MODE_NORMAL
#undef CAN_MODE_LOOPBACK

#endif /* !_ASMLANGUAGE */

#endif /* _STM32F0_SOC_H_ */
