/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_wait_first_expose.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyamen <dyamen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 02:42:11 by ocrouzet          #+#    #+#             */
/*   Updated: 2023/09/04 02:42:59 by dyamen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int	mlx_int_wait_first_expose(t_xvar *xvar, Window win)
{
	XEvent	ev;

	XWindowEvent(xvar->display, win, ExposureMask, &ev);
	XPutBackEvent(xvar->display, &ev);
}
