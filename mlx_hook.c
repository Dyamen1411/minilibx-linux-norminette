/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyamen <dyamen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 01:56:10 by Charlie Roo       #+#    #+#             */
/*   Updated: 2023/09/04 04:37:14 by dyamen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int	mlx_hook(t_win_list *win, int x_event, int x_mask,
	int (*funct)(void *), void *param)
{
	win->hooks[x_event].hook = funct;
	win->hooks[x_event].param = param;
	win->hooks[x_event].mask = x_mask;
}


int	mlx_do_key_autorepeatoff(t_xvar *xvar)
{
	XAutoRepeatOff(xvar->display);
}

int	mlx_do_key_autorepeaton(t_xvar *xvar)
{
	XAutoRepeatOn(xvar->display);
}


int	mlx_do_sync(t_xvar *xvar)
{
	XSync(xvar->display, False);
}
