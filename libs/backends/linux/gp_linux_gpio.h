// SPDX-License-Identifier: LGPL-2.1-or-later
/*
 * Copyright (C) 2023 Cyril Hrubis <metan@ucw.cz>
 */

#ifndef GP_LINUX_GPIO_H
#define GP_LINUX_GPIO_H

#include <stdint.h>

enum gp_gpio_dir {
	GP_GPIO_IN = 0,
	GP_GPIO_OUT = 1,
};

struct gp_gpio {
	const uint16_t nr;
	/* enum gp_gpio_dir */
	const uint16_t dir:1;
	int fd;
};

/**
 * @brief Closes and unexports previously exported GPIOs
 *
 * @gpio An array of GPIO descriptions
 * @gpio_cnt A number of GPIOs in the gpio array
 */
void gp_gpio_unexport(struct gp_gpio *gpio, unsigned int gpio_cnt);

/**
 * @brief Exports and opens GPIOs
 *
 * Export and opens all GPIOs in the description atomically.
 *
 * @gpio An array of GPIO descriptions
 * @gpio_Cnt A number of GPIOs in the gpio array
 * @return Non-zero on success (all GPIOs were exported succesfully), non-zero
 *         otherwise.
 */
int gp_gpio_export(struct gp_gpio *gpio, unsigned int gpio_cnt);

/**
 * @brief Writes a GPIO value
 *
 * @self An output GPIO
 * @val A value, zero turns the GPIO off, non-zero on.
 */
int gp_gpio_write(struct gp_gpio *self, int val);

/**
 * @brief Reads a GPIO value.
 *
 * @self An input GPIO
 * @return A GPIO state.
 */
int gp_gpio_read(struct gp_gpio *self);

#endif /* GP_LINUX_GPIO_H */