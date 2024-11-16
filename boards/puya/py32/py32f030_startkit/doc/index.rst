.. zephyr:board:: py32f030_startkit

This board has the bare minimum components required to power on the
PY32F030K18T6 MCU. Most of the GPIOs on the PY32 SoC have been exposed in the
external headers with silk screen labels that match the SoC's pin names.

For practical use, you'll need to add additional components
and circuits using a breadboard, for example.

More information about the board and PY32F030K18T6 can be found at:

- `PY32F030 reference manual`_
- `PY32F030 data sheet`_

Hardware
********

- PY32F030K18T6 ARM Cortex-M0+ processor
- 64 KiB of flash memory and 8 KiB of RAM
- 24 MHz quartz crystal
- 1 user LED
- One reset button
- 2-way jumper (BOOT0)
- Serial
- SWD (1x4 male dupont (2.54mm))
- USB port (power only)

Supported Features
==================

The Zephyr py32f030_startkit board configuration supports the following
hardware features:

+-----------+------------+-------------------------------------+
| Interface | Controller | Driver/Component                    |
+===========+============+=====================================+
| NVIC      | on-chip    | nested vector interrupt controller  |
+-----------+------------+-------------------------------------+
| UART      | on-chip    | serial port                         |
+-----------+------------+-------------------------------------+
| PINMUX    | on-chip    | pinmux                              |
+-----------+------------+-------------------------------------+
| GPIO      | on-chip    | gpio                                |
+-----------+------------+-------------------------------------+

Other hardware features are not yet supported on this Zephyr port.

The default configuration can be found in
:zephyr_file:`boards/puya/py32/py32f030_startkit/py32f030_startkit_defconfig`

Pin Mapping
===========

Default Zephyr Peripheral Mapping:
----------------------------------

- UART_1 TX/RX : PA9/PA10
- LED : PA11

Programming and Debugging
*************************

Applications for the ``py32f030_startkit`` board configuration can be built and
flashed in the usual way (see :ref:`build_an_application` and
:ref:`application_run` for more details).

Flashing
========

The board can be flashed by using a CMSIS-DAP in-circuit debugger and
programmer. This interface is supported by the pyOCD version included in the
Zephyr SDK.

Flashing an application to PY32F030 Start Kit Board
---------------------------------------------------

Here is an example for the :zephyr:code-sample:`blinky` application.

.. zephyr-app-commands::
   :zephyr-app: samples/basic/blinky
   :board: py32f030_startkit
   :goals: build flash

You will see the LED blinking every second.

Debugging
=========

You can debug an application in the usual way. Here is an example for the
:zephyr:code-sample:`blinky` application.

.. zephyr-app-commands::
   :zephyr-app: samples/basic/blinky
   :board: py32f030_startkit
   :maybe-skip-config:
   :goals: debug

References
**********

.. target-notes::

.. _PY32F030 SVD reference:
   https://github.com/IOsetting/py32f0-template/blob/main/Misc/SVD/py32f030xx.svd

.. _PY32F030 data sheet:
   https://www.puyasemi.com/en/py32_series.html
