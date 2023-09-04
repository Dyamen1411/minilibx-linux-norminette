/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_param_event__button.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyamen <dyamen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 02:13:46 by dyamen            #+#    #+#             */
/*   Updated: 2023/09/04 02:22:11 by dyamen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int	mlx_int_param__button_press(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
	win->hooks[ButtonPress].hook(ev->xbutton.button, ev->xbutton.x,
		ev->xbutton.y, win->hooks[ButtonPress].param);
}

int	mlx_int_param__button_release(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
	win->hooks[ButtonRelease].hook(ev->xbutton.button,
		ev->xbutton.x, ev->xbutton.y, win->hooks[ButtonRelease].param);
}
