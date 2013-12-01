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
 * Copyright (C) 2009-2013 Cyril Hrubis <metan@ucw.cz>                       *
 *                                                                           *
 *****************************************************************************/

%% extends "filter.c.t"

%% block descr
Generic Point filer
%% endblock

%% block body

#include <errno.h>

#include "core/GP_Context.h"
#include "core/GP_GetPutPixel.h"
#include "core/GP_Debug.h"

#include "filters/GP_ApplyTables.h"

%% for pt in pixeltypes
%%  if not pt.is_unknown() and not pt.is_palette()
static int apply_tables_{{ pt.name }}(const GP_Context *const src,
                                      GP_Coord x_src, GP_Coord y_src,
                                      GP_Size w_src, GP_Size h_src,
                                      GP_Context *dst,
                                      GP_Coord x_dst, GP_Coord y_dst,
                                      const GP_FilterTables *const tables,
                                      GP_ProgressCallback *callback)
{
	GP_DEBUG(1, "Point filter %ux%u", w_src, h_src);

	unsigned int x, y;

%%   for c in pt.chanslist
	GP_Pixel {{ c.name }};
%%   endfor

	for (y = 0; y < h_src; y++) {
		for (x = 0; x < w_src; x++) {
			unsigned int src_x = x_src + x;
			unsigned int src_y = y_src + y;
			unsigned int dst_x = x_dst + x;
			unsigned int dst_y = y_dst + y;

			GP_Pixel pix = GP_GetPixel_Raw_{{ pt.pixelsize.suffix }}(src, src_x, src_y);

%%   for c in pt.chanslist
			{{ c.name }} = GP_Pixel_GET_{{ c[0] }}_{{ pt.name }}(pix);
			{{ c.name }} = tables->table[{{ c.idx }}][{{ c.name }}];
%%    endfor

			pix = GP_Pixel_CREATE_{{ pt.name }}({{ expand_chanslist(pt, "", "") }});
			GP_PutPixel_Raw_{{ pt.pixelsize.suffix }}(dst, dst_x, dst_y, pix);
		}

		if (GP_ProgressCallbackReport(callback, y, h_src, w_src)) {
			errno = ECANCELED;
			return 1;
		}
	}

	GP_ProgressCallbackDone(callback);

	return 0;
}

%%  endif
%% endfor

int GP_FilterTablesApply(const GP_Context *const src,
                         GP_Coord x_src, GP_Coord y_src,
                         GP_Size w_src, GP_Size h_src,
                         GP_Context *dst,
                         GP_Coord x_dst, GP_Coord y_dst,
                         const GP_FilterTables *const tables,
                         GP_ProgressCallback *callback)
{
	GP_ASSERT(src->pixel_type == dst->pixel_type);
	//TODO: Assert size

	switch (src->pixel_type) {
%% for pt in pixeltypes
%%  if not pt.is_unknown() and not pt.is_palette()
	case GP_PIXEL_{{ pt.name }}:
		return apply_tables_{{ pt.name }}(src, x_src, y_src,
		                                  w_src, h_src, dst,
		                                  x_dst, y_dst,
		                                  tables, callback);
	break;
%%  endif
%% endfor
	default:
		errno = EINVAL;
		return -1;
	}
}

%% endblock body