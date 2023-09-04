/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_param_event.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyamen <dyamen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 02:13:46 by Charlie Roo       #+#    #+#             */
/*   Updated: 2023/09/04 03:29:40 by dyamen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int	mlx_int_param__key_press(t_xvar *xvar, XEvent *ev, t_win_list *win);
int	mlx_int_param__key_release(t_xvar *xvar, XEvent *ev, t_win_list *win);
int	mlx_int_param__button_press(t_xvar *xvar, XEvent *ev, t_win_list *win);
int	mlx_int_param__button_release(t_xvar *xvar, XEvent *ev, t_win_list *win);
int	mlx_int_param__motion_notify(t_xvar *xvar, XEvent *ev, t_win_list *win);
int	mlx_int_param__expose(t_xvar *xvar, XEvent *ev, t_win_list *win);
int	mlx_int_param__generic(t_xvar *xvar, XEvent *ev, t_win_list *win);
int	mlx_int_param_undef(t_xvar *xvar, XEvent *ev, t_win_list *win);

int	(*g_mlx_int_param_event[])(t_xvar*, XEvent*, t_win_list*) = {
	mlx_int_param_undef,
	mlx_int_param_undef,
	mlx_int_param__key_press,
	mlx_int_param__key_release,
	mlx_int_param__button_press,
	mlx_int_param__button_release,
	mlx_int_param__motion_notify,
	mlx_int_param__generic,
	mlx_int_param__generic,
	mlx_int_param__generic,
	mlx_int_param__generic,
	mlx_int_param__generic,
	mlx_int_param__expose,
	mlx_int_param__generic,
	mlx_int_param__generic,
	mlx_int_param__generic,
	mlx_int_param__generic,
	mlx_int_param__generic,
	mlx_int_param__generic,
	mlx_int_param__generic,
	mlx_int_param__generic,
	mlx_int_param__generic,
	mlx_int_param__generic,
	mlx_int_param__generic,
	mlx_int_param__generic,
	mlx_int_param__generic,
	mlx_int_param__generic,
	mlx_int_param__generic,
	mlx_int_param__generic,
	mlx_int_param__generic,
	mlx_int_param__generic,
	mlx_int_param__generic,
	mlx_int_param__generic,
	mlx_int_param__generic,
	mlx_int_param__generic,
	mlx_int_param__generic
};

int	mlx_int_param_undef(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
	(void) xvar;
	(void) ev;
	(void) win;
}

int	mlx_int_param__motion_notify(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
	win->hooks[MotionNotify].hook(ev->xbutton.x, ev->xbutton.y,
		win->hooks[MotionNotify].param);
}

int	mlx_int_param__expose(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
	if (!ev->xexpose.count)
		win->hooks[Expose].hook(win->hooks[Expose].param);
}

int	mlx_int_param__generic(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
	win->hooks[ev->type].hook(win->hooks[ev->type].param);
}
