/*
 * Copyright (c) 2020 ITE Corporation. All Rights Reserved.
 * Jyunlin Chen <jyunlin.chen@ite.com.tw>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/toolchain.h>

/* Exports */
GTEXT(__start)

/* Imports */
GTEXT(__initialize)

SECTION_FUNC(vectors, ivt)
	.option norvc
	j       __start
	.rept 38
	j	_isr_wrapper
	.endr

SECTION_FUNC(vectors, __start)
	/* Use the default mtvec of 0x03 */
	j	__initialize
