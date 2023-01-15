/*
 * Copyright (c) 2018 Foundries.io Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT wch_systick

#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/util.h>
#include <zephyr/drivers/timer/system_timer.h>
#include <soc.h>
#include <zephyr/irq.h>
#include <Peripheral/inc/ch32v00x.h>

#define STK_SWIE  (1 << 31)
#define STK_STRE  (1 << 3)
#define STK_STCLK (1 << 2)
#define STK_STIE  (1 << 1)
#define STK_STE	  (1 << 0)

#define STK_CNTIF (1 << 0)

#define CYCLES_PER_SEC	sys_clock_hw_cycles_per_sec()
#define CYCLES_PER_TICK (CYCLES_PER_SEC / CONFIG_SYS_CLOCK_TICKS_PER_SEC)

#define SYSTICK ((SysTick_Type *)(DT_INST_REG_ADDR(0)))

struct ch32v00x_systick_device {
};

static volatile uint32_t ch32v00x_systick_count;

static void ch32v00x_systick_irq(const struct ch32v00x_systick_device *unused)
{
	ARG_UNUSED(unused);

	SYSTICK->SR = 0;
	ch32v00x_systick_count += CYCLES_PER_TICK; /* Track cycles. */
	sys_clock_announce(1);			   /* Poke the scheduler. */
}

uint32_t sys_clock_cycle_get_32(void)
{
	return ch32v00x_systick_count + SYSTICK->CNT;
}

uint32_t sys_clock_elapsed(void)
{
	return 0;
}

static int ch32v00x_systick_init(const struct device *unused)
{
	ARG_UNUSED(unused);
	IRQ_CONNECT(DT_INST_IRQN(0), 0, ch32v00x_systick_irq, NULL, 0);

	SYSTICK->SR = 0;
	SYSTICK->CMP = CYCLES_PER_TICK;
	SYSTICK->CNT = 0;
	SYSTICK->CTLR = STK_STRE | STK_STCLK | STK_STIE | STK_STE;

        irq_enable(DT_INST_IRQN(0));

	return 0;
}

SYS_INIT(ch32v00x_systick_init, PRE_KERNEL_2, CONFIG_SYSTEM_CLOCK_INIT_PRIORITY);
