/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_ext_randr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyamen <dyamen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 01:09:23 by dyamen            #+#    #+#             */
/*   Updated: 2023/09/04 01:50:59 by dyamen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"
#include <unistd.h>
#include <X11/extensions/Xrandr.h>

typedef struct s_settings {
	XWindowAttributes	watt;
	XRRScreenResources	*res;
	XRROutputInfo		*o_info;
	XRRCrtcInfo			*crtc;
	RRMode				mode_candidate;
	int					idx_output;
	int					idx_candidate;
	int					mode_status;
}	t_settings;

/* global for independant extension */
RRMode	g_saved_mode = 0;

void	get_output_info(t_xvar *xvar, t_settings *sp)
{
	int	i;

	sp->o_info = NULL;
	sp->idx_output = -1;
	i = sp->res->noutput;
	while (i--)
	{
		sp->o_info = XRRGetOutputInfo(xvar->display,
				sp->res, sp->res->outputs[i]);
		if (sp->o_info->connection == RR_Connected)
		{
			sp->idx_output = i;
			i = 0;
		}
		else
			XRRFreeOutputInfo(sp->o_info);
	}
}

void	get_index_candidate(int fullscreen, t_settings *sp)
{
	int	i;
	int	j;

	if (!fullscreen && g_saved_mode == -1)
		return (0);
	sp->idx_candidate = -1;
	i = sp->o_info->nmode;
	while (i--)
	{
		j = sp->res->nmode;
		while (j--)
			if (sp->res->modes[j].id == sp->o_info->modes[i]
				&& sp->res->modes[j].width >= sp->watt.width
				&& sp->res->modes[j].height >= sp->watt.height
				&& (sp->idx_candidate == -1
					|| sp->res->modes[sp->idx_candidate].width
					> sp->res->modes[j].width
					|| sp->res->modes[sp->idx_candidate].height
					> sp->res->modes[j].height))
				sp->idx_candidate = i;
	}
}

void	handle_fullscreen(int fullscreen, t_settings *sp,
	t_xvar *xvar, t_win_list *win)
{
	sp->mode_status = XRRSetCrtcConfig(xvar->display, sp->res, sp->o_info->crtc,
			CurrentTime, 0, 0, sp->mode_candidate, sp->crtc->rotation,
			&sp->res->outputs[sp->idx_output], 1);
	XMoveWindow(xvar->display, win->window, 0, 0);
	XMapRaised(xvar->display, win->window);
	if (fullscreen)
	{
		printf("found mode : %d x %d\n Status %d\n",
			sp->res->modes[sp->idx_candidate].width,
			sp->res->modes[sp->idx_candidate].height,
			sp->mode_status);
		XGrabKeyboard(xvar->display, win->window, False,
			GrabModeAsync, GrabModeAsync, CurrentTime);
	}
	else
	{
		printf("back previous mode\n");
		XUngrabPointer(xvar->display, CurrentTime);
		XUngrabKeyboard(xvar->display, CurrentTime);
	}
	XSync(xvar->display, False);
	sleep(1);
	XRRFreeCrtcInfo(sp->crtc);
	XRRFreeOutputInfo(sp->o_info);
	XRRFreeScreenResources(sp->res);
}

int	mlx_ext_fullscreen(t_xvar *xvar, t_win_list *win, int fullscreen)
{
	t_settings	s;
	int			i;

	if (!XGetWindowAttributes(xvar->display, win->window, &s.watt))
		return (0);
	s.res = XRRGetScreenResources(xvar->display, xvar->root);
	get_output_info(xvar, &s);
	if (!s.o_info)
	{
		XRRFreeScreenResources(s.res);
		return (0);
	}
	get_index_candidate(fullscreen, &s);
	if (s.idx_candidate < 0)
	{
		XRRFreeOutputInfo(s.o_info);
		XRRFreeScreenResources(s.res);
		return (0);
	}
	s.mode_candidate = s.o_info->modes[s.idx_candidate];
	if (!fullscreen)
		s.mode_candidate = g_saved_mode;
	s.crtc = XRRGetCrtcInfo(xvar->display, s.res, s.o_info->crtc);
	g_saved_mode = s.crtc->mode;
	handle_fullscreen(fullscreen, &s, xvar, win);
}
