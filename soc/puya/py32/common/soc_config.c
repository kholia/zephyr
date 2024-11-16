/*
 * Copyright (c) 2021 Andrés Manelli <am@toroid.io>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/** @file
 * @brief System module to support early STM32 MCU configuration
 */

#include <zephyr/device.h>
#include <zephyr/init.h>
#include <soc.h>
#include <zephyr/arch/cpu.h>
#include <py32f0xx_ll_system.h>
#include <py32f0xx_ll_bus.h>
#include <py32f0xx_ll_pwr.h>

/**
 * @brief Perform SoC configuration at boot.
 *
 * This should be run early during the boot process but after basic hardware
 * initialization is done.
 *
 * @return 0
 */
static int st_stm32_common_config(void)
{
	return 0;
}

SYS_INIT(st_stm32_common_config, PRE_KERNEL_1, 1);
