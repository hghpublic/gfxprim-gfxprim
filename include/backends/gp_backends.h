/*****************************************************************************
 * This file is part of gfxprim library.                                     *
 *                                                                           *
 * Gfxprim is free software; you can redistribute it and/or                  *
 * modify it under the terms of the GNU Lesser General Public                *
 * License as published by the Free Software Foundation; either              *
 * version 2.1 of the License, or (at your option) any later version.        *
 *                                                                           *
 * Gfxprim is distributed in the hope that it will be useful,                *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Lesser General Public License for more details.                           *
 *                                                                           *
 * You should have received a copy of the GNU Lesser General Public          *
 * License along with gfxprim; if not, write to the Free Software            *
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,                        *
 * Boston, MA  02110-1301  USA                                               *
 *                                                                           *
 * Copyright (C) 2009-2012 Cyril Hrubis <metan@ucw.cz>                       *
 *                                                                           *
 *****************************************************************************/

/*

  Catch all header for backends.

 */

#ifndef BACKENDS_GP_BACKENDS_H
#define BACKENDS_GP_BACKENDS_H

/*
 * Base backend definitions.
 */
#include <backends/gp_backend.h>

/*
 * Backends.
 */
#include <backends/gp_linux_fb.h>
#include <backends/gp_sdl.h>
#include <backends/gp_x11.h>
#include "backends/gp_xcb.h"
#include <backends/gp_aalib.h>
#include <backends/gp_backend_virtual.h>

/*
 * Simplified backend initalization.
 */
#include <backends/gp_backend_init.h>

#endif /* BACKENDS_GP_BACKENDS_H */