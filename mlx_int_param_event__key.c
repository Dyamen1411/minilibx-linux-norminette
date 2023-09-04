/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_param_event__key.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyamen <dyamen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 02:13:46 by dyamen            #+#    #+#             */
/*   Updated: 2023/09/04 02:21:54 by dyamen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int	mlx_int_param__key_press(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
	win->hooks[KeyPress].hook(XkbKeycodeToKeysym(xvar->display,
			ev->xkey.keycode, 0, 0), win->hooks[KeyPress].param);
}

int	mlx_int_param__key_release(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
	win->hooks[KeyRelease].hook(XkbKeycodeToKeysym(xvar->display,
			ev->xkey.keycode, 0, 0), win->hooks[KeyRelease].param);
}
