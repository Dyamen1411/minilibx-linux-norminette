/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pixel_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyamen <dyamen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 04:04:11 by Charlie Roo       #+#    #+#             */
/*   Updated: 2023/09/04 04:04:57 by dyamen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int	mlx_pixel_put(t_xvar *xvar, t_win_list *win, int x, int y, int color)
{
	XGCValues	xgcv;

	xgcv.foreground = mlx_int_get_good_color(xvar, color);
	XChangeGC(xvar->display, win->gc, GCForeground, &xgcv);
	XDrawPoint(xvar->display, win->window, win->gc, x, y);
	if (xvar->do_flush)
		XFlush(xvar->display);
}
