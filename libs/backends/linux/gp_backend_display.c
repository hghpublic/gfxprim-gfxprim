// SPDX-License-Identifier: LGPL-2.1-or-later
/*
 * Copyright (C) 2023 Cyril Hrubis <metan@ucw.cz>
 */

#include <string.h>
#include <inttypes.h>

#include <core/gp_core.h>
#include <backends/gp_backend.h>
#include <backends/gp_display.h>

const struct gp_backend_display_model gp_backend_display_models[] = {
	[GP_WAVESHARE_7_5_V2] = {.name = "WaveShare-7.5-v2",
	                         .desc = "1BPP Grayscale 7.5 inch SPI e-ink display"},
	[GP_WAVESHARE_3_7] = {.name = "WaveShare-3.7",
	                      .desc = "1BPP/4BPP Grayscale 3.7 inch SPI e-ink display"},
	[GP_WEACT_2_13_BW] = {.name = "WeAct-2.13",
	                      .desc = "1BPP Grayscale 2.13 inch SPI e-ink display"},
	[GP_WEACT_2_9_BW] = {.name = "WeAct-2.9",
	                      .desc = "1BPP Grayscale 2.9 inch SPI e-ink display"},
	[GP_GMG12864] = {.name = "GMG12864",
	                 .desc = "1BPP Grayscale 58.5x46.5mm SPI LCD display"},
	[GP_JLX256128_1] = {.name = "JLX256128-1",
	                    .desc = "JLX Grayscale SPI LCD display 1bpp mode"},
	[GP_JLX256128_2] = {.name = "JLX256128-2",
	                    .desc = "JLX Grayscale SPI LCD display 2bpp mode"},
	{}
};

gp_backend *gp_waveshare_7_5_v2_init(void);
gp_backend *gp_waveshare_3_7_init(void);
gp_backend *gp_weact_2_13_init(void);

gp_backend *gp_ssd16xx_init(unsigned int w, unsigned int h, int dpi);

gp_backend *gp_st7565_init(unsigned int dpi);
gp_backend *gp_st75256_init(unsigned int dpi, unsigned int bpp);

/*
 * Horizontal DPI is 108
 * Vertical DPI is 100
 */
#define JLX256128_DPI 104

static gp_ev_queue event_queue;

gp_backend *gp_backend_display_init(enum gp_backend_display_model_ids model)
{
	gp_backend *ret = NULL;

	switch (model) {
	case GP_WAVESHARE_7_5_V2:
		ret = gp_waveshare_7_5_v2_init();
	break;
	case GP_WAVESHARE_3_7:
		ret = gp_waveshare_3_7_init();
	break;
	case GP_WEACT_2_13_BW:
		ret = gp_ssd16xx_init(122, 250, 130);
	break;
	case GP_WEACT_2_9_BW:
		ret = gp_ssd16xx_init(128, 296, 125);
	break;
	case GP_GMG12864:
		ret = gp_st7565_init(67);
	break;
	case GP_JLX256128_1:
		ret = gp_st75256_init(JLX256128_DPI, 1);
	break;
	case GP_JLX256128_2:
		ret = gp_st75256_init(JLX256128_DPI, 2);
	break;
	default:
		GP_FATAL("Invalid model %i\n", model);
		return NULL;
	}

	if (ret) {
		ret->event_queue = &event_queue;
		gp_ev_queue_init(ret->event_queue, ret->pixmap->w, ret->pixmap->h, 0, NULL, NULL, GP_EVENT_QUEUE_LOAD_KEYMAP);
	}

	return ret;
}
