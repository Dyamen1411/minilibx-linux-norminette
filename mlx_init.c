/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyamen <dyamen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 01:57:38 by Charlie Roo       #+#    #+#             */
/*   Updated: 2023/09/04 02:09:08 by dyamen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

void	*_mlx_finish_init(t_xvar *xvar)
{
	xvar->win_list = 0;
	xvar->loop_hook = 0;
	xvar->loop_param = (void *)0;
	xvar->do_flush = 1;
	xvar->wm_delete_window = XInternAtom(xvar->display, "WM_DELETE_WINDOW",
			False);
	xvar->wm_protocols = XInternAtom (xvar->display, "WM_PROTOCOLS", False);
	mlx_int_deal_shm(xvar);
	if (xvar->private_cmap)
		xvar->cmap = XCreateColormap(xvar->display, xvar->root, xvar->visual,
				AllocNone);
	mlx_int_rgb_conversion(xvar);
	xvar->end_loop = 0;
	return (xvar);
}

void	*mlx_init(void)
{
	t_xvar	*xvar;

	xvar = malloc(sizeof(*xvar));
	if (!xvar)
		return ((void *) 0);
	xvar->display = XOpenDisplay("");
	if (xvar->display == 0)
	{
		free(xvar);
		return ((void *) 0);
	}
	xvar->screen = DefaultScreen(xvar->display);
	xvar->root = DefaultRootWindow(xvar->display);
	xvar->cmap = DefaultColormap(xvar->display, xvar->screen);
	xvar->depth = DefaultDepth(xvar->display, xvar->screen);
	if (mlx_int_get_visual(xvar) != -1)
		return (_mlx_finish_init(xvar));
	printf(ERR_NO_TRUECOLOR);
	exit(1);
}


/*
** pshm_format of -1 :	Not XYBitmap|XYPixmap|ZPixmap
** alpha libX need a check of the DISPLAY env var, or shm is allowed
** in remote Xserver connections.
*/
int	mlx_int_deal_shm(t_xvar *xvar)
{
	int		use_pshm;
	int		bidon;
	char	*dpy;
	char	buff[33];

	xvar->use_xshm = XShmQueryVersion(
			xvar->display, &bidon, &bidon, &(use_pshm));
	if (xvar->use_xshm && use_pshm)
		xvar->pshm_format = XShmPixmapFormat(xvar->display);
	else
		xvar->pshm_format = -1;
	gethostname(buff, 32);
	dpy = getenv(ENV_DISPLAY);
	if (dpy && strlen(dpy) && *dpy != ':' && strncmp(dpy, buff, strlen(buff))
		&& strncmp(dpy, LOCALHOST, strlen(LOCALHOST)))
	{
		xvar->pshm_format = -1;
		xvar->use_xshm = 0;
	}
}

/*
** TrueColor Visual is needed to have *_mask correctly set
*/

void	_mlx_int_rgb_conversion(unsigned long *mask_ptr, int *dec_ptr)
{
	while (!(*mask_ptr & 1))
	{
		*mask_ptr >>= 1;
		++*dec_ptr;
	}
	++dec_ptr;
	while (*mask_ptr & 1)
	{
		*mask_ptr >>= 1;
		++*dec_ptr;
	}
}

int	mlx_int_rgb_conversion(t_xvar *xvar)
{
	bzero(xvar->decrgb, sizeof(int) * 6);
	_mlx_int_rgb_conversion(&xvar->visual->red_mask, &xvar->decrgb[0]);
	_mlx_int_rgb_conversion(&xvar->visual->green_mask, &xvar->decrgb[2]);
	_mlx_int_rgb_conversion(&xvar->visual->blue_mask, &xvar->decrgb[4]);
}
