/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_get_color_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyamen <dyamen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 01:53:04 by Charlie Roo       #+#    #+#             */
/*   Updated: 2023/09/04 01:54:59 by dyamen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int	mlx_get_color_value(t_xvar *xvar, int color)
{
	return (mlx_int_get_good_color(xvar, color));
}

int	mlx_int_get_good_color(t_xvar *xvar, int color)
{
	XColor	xc;

	if (xvar->depth >= 24)
		return (color);
	xc.red = (color >> 8) & 0xFF00;
	xc.green = color & 0xFF00;
	xc.blue = (color << 8) & 0xFF00;
	xc.pixel = (xc.red >> (16 - xvar->decrgb[1])) << xvar->decrgb[0];
	xc.pixel += (xc.green >> (16 - xvar->decrgb[3])) << xvar->decrgb[2];
	xc.pixel += (xc.blue >> (16 - xvar->decrgb[5])) << xvar->decrgb[4];
	return (xc.pixel);
}
