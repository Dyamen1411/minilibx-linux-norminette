/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_flush_event.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyamen <dyamen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 01:51:57 by Charlie Roo       #+#    #+#             */
/*   Updated: 2023/09/04 01:52:38 by dyamen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int	mlx_flush_event(t_xvar *xvar)
{
	XEvent	ev;

	while (XPending(xvar->display))
		XNextEvent(xvar->display, &ev);
}
