/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_get_visual.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyamen <dyamen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 02:12:07 by Charlie Roo       #+#    #+#             */
/*   Updated: 2023/09/04 02:13:18 by dyamen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

// We need a private colormap for non-default Visual.

int	mlx_int_get_visual(t_xvar *xvar)
{
	XVisualInfo	*vi;
	XVisualInfo	template;
	int			nb_item;

	xvar->private_cmap = 0;
	xvar->visual = DefaultVisual(xvar->display, xvar->screen);
	if (xvar->visual->class == TrueColor)
		return (0);
	template.class = TrueColor;
	template.depth = xvar->depth;
	vi = XGetVisualInfo(xvar->display, VisualDepthMask | VisualClassMask,
			&template, &nb_item);
	if (!vi)
		return (-1);
	xvar->visual = vi->visual;
	xvar->private_cmap = 1;
	return (0);
}
