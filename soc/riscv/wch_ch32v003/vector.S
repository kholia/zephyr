/*
 * Copyright (c) 2020 ITE Corporation. All Rights Reserved.
 * Jyunlin Chen <jyunlin.chen@ite.com.tw>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/toolchain.h>

/* exports */
GTEXT(__start)

/* imports */
GTEXT(__initialize)

SECTION_FUNC(vectors, __start)
	/* Jump to __initialize */
	tail __initialize
