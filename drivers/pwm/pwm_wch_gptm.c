/*
 * Copyright (c) 2021 Sun Amar.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT wch_gptm

#include <zephyr/drivers/pwm.h>
#include <zephyr/dt-bindings/pwm/pwm.h>
#include <zephyr/drivers/clock_control.h>

#include <ch32v00x_tim.h>

/** PWM configuration. */
struct pwm_wch_gptm_config {
	TIM_TypeDef *regs;
	const struct device *clock_dev;
	uint8_t clock_id;
	uint16_t prescaler;
};

static int pwm_wch_gptm_set_cycles(const struct device *dev, uint32_t channel,
				   uint32_t period_cycles, uint32_t pulse_cycles, pwm_flags_t flags)
{
	const struct pwm_wch_gptm_config *config = dev->config;
	TIM_TypeDef *regs = config->regs;
	uint16_t ocxm;

	if (period_cycles > UINT16_MAX) {
		return -ENOTSUP;
	}

	if (period_cycles == 0) {
		/* Force the output to 'invalid' */
		ocxm = 0x04;
	} else {
		/* PWM mode 1 */
		ocxm = 0x06;
	}

	switch (channel) {
	case 1:
		regs->CH1CVR = pulse_cycles;
		regs->CHCTLR1 = (regs->CHCTLR1 & ~TIM_OC1M) | (ocxm * TIM_OC1M_0);
		break;
	case 2:
		regs->CH2CVR = pulse_cycles;
		regs->CHCTLR1 = (regs->CHCTLR1 & ~TIM_OC2M) | (ocxm * TIM_OC2M_0);
		break;
	case 3:
		regs->CH3CVR = pulse_cycles;
		regs->CHCTLR2 = (regs->CHCTLR2 & ~TIM_OC3M) | (ocxm * TIM_OC3M_0);
		break;
	case 4:
		regs->CH4CVR = pulse_cycles;
		regs->CHCTLR2 = (regs->CHCTLR2 & ~TIM_OC4M) | (ocxm * TIM_OC4M_0);
		break;
	default:
		return -EINVAL;
	}

	regs->ATRLR = period_cycles;
	//	regs->CCER = TIM_CC4E;
	//	return 0;

	/* Set the polarity and enable */
	uint16_t shift = 4 * (channel - 1);
	if ((flags & PWM_POLARITY_INVERTED) != 0U) {
		regs->CCER = TIM_CC1E << shift;
		//		regs->CCER = (regs->CCER & ~(0x0F << shift) | (TIM_CC1E << shift);
	} else {
		regs->CCER = (TIM_CC1P | TIM_CC1E) << shift;
		//		regs->CCER = regs->CCER | (TIM_CC1P << shift) | (TIM_CC1E << shift);
	}

	return 0;
}

static int pwm_wch_gptm_get_cycles_per_sec(const struct device *dev, uint32_t channel,
					   uint64_t *cycles)
{
	const struct pwm_wch_gptm_config *config = dev->config;

	/* APB1 is connected to SYSCLK */
	*cycles = CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC / (config->prescaler + 1);

	return 0;
}

static const struct pwm_driver_api pwm_wch_gptm_driver_api = {
	.set_cycles = pwm_wch_gptm_set_cycles,
	.get_cycles_per_sec = pwm_wch_gptm_get_cycles_per_sec,
};

static int pwm_wch_gptm_init(const struct device *dev)
{
	const struct pwm_wch_gptm_config *config = dev->config;
	TIM_TypeDef *regs = config->regs;

	clock_control_on(config->clock_dev, (clock_control_subsys_t *)(uintptr_t)config->clock_id);
	GPIOD->CFGLR = (GPIOD->CFGLR & ~(0xF << (4 * 4))) | (9 << (4 * 4));
	//	AFIO->PCFR1 |= AFIO_PCFR1_TIM2_REMAP_FULLREMAP;
	/* Disable and configure the counter */
	regs->CTLR1 = TIM_ARPE & ~TIM_CEN;
	regs->PSC = config->prescaler;

	regs->CTLR1 |= TIM_CEN;

	return 0;
}

#define PWM_WCH_GPTM_INIT(idx)                                                                     \
	static const struct pwm_wch_gptm_config pwm_wch_gptm_##idx##_config = {                    \
		.regs = (TIM_TypeDef *)DT_INST_REG_ADDR(idx),                                      \
		.prescaler = DT_INST_PROP(idx, prescaler) - 1,                                     \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(idx)),                              \
		.clock_id = DT_INST_CLOCKS_CELL(idx, id),                                          \
	};                                                                                         \
	DEVICE_DT_INST_DEFINE(idx, &pwm_wch_gptm_init, NULL, NULL, &pwm_wch_gptm_##idx##_config,   \
			      POST_KERNEL, CONFIG_PWM_INIT_PRIORITY, &pwm_wch_gptm_driver_api);

DT_INST_FOREACH_STATUS_OKAY(PWM_WCH_GPTM_INIT)
