/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyamen <dyamen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 02:47:22 by Charlie Roo       #+#    #+#             */
/*   Updated: 2023/09/04 04:34:59 by dyamen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int	mlx_key_hook(t_win_list *win, int (*funct)(void *), void *param)
{
	win->hooks[KeyRelease].hook = funct;
	win->hooks[KeyRelease].param = param;
	win->hooks[KeyRelease].mask = KeyReleaseMask;
}
