/*
 * Copyright (c) 2021 Espressif Systems (Shanghai) Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>

#include <zephyr/device.h>
#include <soc.h>
#include <Peripheral/inc/ch32v00x.h>

static void soc_ch32v003_delay_start(void)
{
	/* TODO(nzmichaelh): remove. */
	for (volatile int i = 0; i < 500000; i++) {
		__asm("nop");
		__asm("nop");
		__asm("nop");
		__asm("nop");
		__asm("nop");
	}
}

static void soc_ch32v003_sysclock_hsi(void)
{
	/* Flash 0 wait state */
	FLASH->ACTLR = (FLASH->ACTLR & ~FLASH_ACTLR_LATENCY) | FLASH_ACTLR_LATENCY_1;

	/* HCLK = SYSCLK = APB1 */
	RCC->CFGR0 |= RCC_HPRE_DIV1;
	/* PLLCLK = HSI * 2 */
	RCC->CFGR0 = (RCC->CFGR0 & ~RCC_PLLSRC) | RCC_PLLSRC_HSI_Mul2;

	/* Enable PLL */
	RCC->CTLR |= RCC_PLLON;
	while ((RCC->CTLR & RCC_PLLRDY) == 0) {
	}

	/* Select PLL as system clock source */
	RCC->CFGR0 = (RCC->CFGR0 & ~RCC_SW) | RCC_SW_PLL;
	while ((RCC->CFGR0 & RCC_SWS) != RCC_SWS_PLL) {
	}
}

static int soc_ch32v003_init(const struct device *arg)
{
	ARG_UNUSED(arg);

	soc_ch32v003_delay_start();

	RCC->CTLR |= RCC_HSION;
	// PLLSRC = 0, which is the HSI.
	RCC->CFGR0 = RCC_MCO_NOCLOCK & ~RCC_PLLSRC;
	// Turn off PLLON, CSSON, HSEON.
	RCC->CTLR &= (uint32_t)0xFEF6FFFF;
	// Turn off HSEBYP.
	RCC->CTLR &= (uint32_t)0xFFFBFFFF;
	// Turn off PLLSRC again?
	RCC->CFGR0 &= (uint32_t)0xFFFEFFFF;
	// Write to INTR to clear the CSSC, PLLRDYC, HSERDYC, and LSIRDYC flags.
	RCC->INTR = 0x009F0000;

	soc_ch32v003_sysclock_hsi();

	return 0;
}

SYS_INIT(soc_ch32v003_init, PRE_KERNEL_1, 0);
