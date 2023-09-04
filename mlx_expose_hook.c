/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_expose_hook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyamen <dyamen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 01:07:49 by Charlie roo       #+#    #+#             */
/*   Updated: 2023/09/04 04:35:16 by dyamen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int	mlx_expose_hook(t_win_list *win, int (*funct)(void *), void *param)
{
	win->hooks[Expose].hook = funct;
	win->hooks[Expose].param = param;
	win->hooks[Expose].mask = ExposureMask;
}
