/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyamen <dyamen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 02:58:31 by Charlie roo       #+#    #+#             */
/*   Updated: 2023/09/04 04:33:41 by dyamen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

extern	int	(*(g_mlx_int_param_event[]))(t_xvar*, XEvent*, t_win_list*);

static int	win_count(t_xvar *xvar)
{
	int			i;
	t_win_list	*win;

	i = 0;
	win = xvar->win_list;
	while (win)
	{
		win = win->next;
		++i;
	}
	return (i);
}

int	mlx_loop_end(t_xvar *xvar)
{
	xvar->end_loop = 1;
	return (1);
}

int	mlx_loop(t_xvar *xvar)
{
	XEvent		ev;
	t_win_list	*w;

	mlx_int_set_win_event_mask(xvar);
	xvar->do_flush = 0;
	while (win_count(xvar) && !xvar->end_loop)
	{
		while (!xvar->end_loop && (!xvar->loop_hook || XPending(xvar->display)))
		{
			XNextEvent(xvar->display, &ev);
			w = xvar->win_list;
			while (w && (w->window != ev.xany.window))
				w = w->next;
			if (w && ev.type == ClientMessage && w->hooks[DestroyNotify].hook
				&& ev.xclient.message_type == xvar->wm_protocols
				&& ev.xclient.data.l[0] == xvar->wm_delete_window)
				w->hooks[DestroyNotify].hook(w->hooks[DestroyNotify].param);
			if (w && ev.type < MLX_MAX_EVENT && w->hooks[ev.type].hook)
				g_mlx_int_param_event[ev.type](xvar, &ev, w);
		}
		XSync(xvar->display, False);
		if (xvar->loop_hook)
			xvar->loop_hook(xvar->loop_param);
	}
	return (0);
}
