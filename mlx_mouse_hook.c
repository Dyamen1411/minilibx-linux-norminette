/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyamen <dyamen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 03:31:05 by Charlie Roo       #+#    #+#             */
/*   Updated: 2023/09/04 03:31:43 by dyamen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int	mlx_mouse_hook(t_win_list *win, int (*funct)(), void *param)
{
	win->hooks[ButtonPress].hook = funct;
	win->hooks[ButtonPress].param = param;
	win->hooks[ButtonPress].mask = ButtonPressMask;
}
