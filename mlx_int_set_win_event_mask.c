/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_set_win_event_mask.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyamen <dyamen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 02:23:44 by Charlie Roo       #+#    #+#             */
/*   Updated: 2023/09/04 02:24:55 by dyamen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int	mlx_int_set_win_event_mask(t_xvar *xvar)
{
	t_win_list				*win;
	int						mask;
	int						i;
	XSetWindowAttributes	xwa;

	win = xvar->win_list;
	while (win)
	{
		xwa.event_mask = 0;
		i = MLX_MAX_EVENT;
		while (i--)
			xwa.event_mask |= win->hooks[i].mask;
		XChangeWindowAttributes(xvar->display, win->window, CWEventMask, &xwa);
		win = win->next;
	}
}
