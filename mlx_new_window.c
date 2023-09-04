/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_new_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyamen <dyamen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 04:03:19 by Charlie Roo       #+#    #+#             */
/*   Updated: 2023/09/04 04:03:33 by dyamen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** We do not use White/BlackPixel macro, TrueColor Visual make sure
** 0 is black & -1 is white
**
** With mlx_int_wait_first_expose, no flush is needed.
*/

#include "mlx_int.h"

typedef struct s_window_settings {
	t_win_list				*win;
	XSetWindowAttributes	xswa;
	XGCValues				xgcv;
	int						width;
	int						height;
	char					*title;
}	t_window_settings;

void	create_window(t_window_settings *ws, t_xvar *xvar)
{
	ws->win->window = XCreateWindow(xvar->display, xvar->root, 0, 0,
			ws->width, ws->height,
			0, CopyFromParent, InputOutput, xvar->visual,
			CWEventMask | CWBackPixel | CWBorderPixel | CWColormap, &ws->xswa);
	mlx_int_anti_resize_win(xvar, ws->win->window, ws->width, ws->height);
	XStoreName(xvar->display, ws->win->window, ws->title);
	XSetWMProtocols(xvar->display, ws->win->window, &xvar->wm_delete_window, 1);
}

void	*mlx_new_window(t_xvar *xvar, int size_x, int size_y, char *title)
{
	t_window_settings	ws;

	ws.win = malloc(sizeof(t_win_list));
	if (!ws.win)
		return ((void *) 0);
	ws.width = size_x;
	ws.height = size_y;
	ws.title = title;
	ws.xswa.background_pixel = 0;
	ws.xswa.border_pixel = -1;
	ws.xswa.colormap = xvar->cmap;
	ws.xswa.event_mask = 0xFFFFFF;
	ws.xgcv.foreground = -1;
	ws.xgcv.function = GXcopy;
	ws.xgcv.plane_mask = AllPlanes;
	create_window(&ws, xvar);
	ws.win->gc = XCreateGC(xvar->display, ws.win->window,
			GCFunction | GCPlaneMask | GCForeground, &ws.xgcv);
	ws.win->next = xvar->win_list;
	xvar->win_list = ws.win;
	bzero(&ws.win->hooks, sizeof(ws.win->hooks));
	XMapRaised(xvar->display, ws.win->window);
	mlx_int_wait_first_expose(xvar, ws.win->window);
	return (ws.win);
}
