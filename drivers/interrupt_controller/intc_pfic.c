/*
 * Copyright (c) 2017 Jean-Paul Etienne <fractalclone@gmail.com>
 * Contributors: 2018 Antmicro <www.antmicro.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT wch_pfic

#include <zephyr/kernel.h>
#include <zephyr/arch/cpu.h>
#include <zephyr/init.h>

#include <zephyr/irq.h>
#include <ch32v00x.h>

void arch_irq_enable(unsigned int irq)
{
	PFIC->IENR[irq / 32] = 1 << (irq % 32);
}

void arch_irq_disable(unsigned int irq)
{
	PFIC->IRER[irq / 32] |= 1 << (irq % 32);
}

int arch_irq_is_enabled(unsigned int irq)
{
	return ((PFIC->ISR[irq >> 5] & (1 << (irq & 0x1F))) != 0);
}

// extern void (*_isr_wrapper)(void);

static int pfic_init(const struct device *dev)
{
	ARG_UNUSED(dev);

	return 0;
}

SYS_INIT(pfic_init, PRE_KERNEL_1, CONFIG_INTC_INIT_PRIORITY);
