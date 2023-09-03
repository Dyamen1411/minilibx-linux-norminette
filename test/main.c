/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyamen <dyamen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 00:36:03 by dyamen            #+#    #+#             */
/*   Updated: 2023/09/04 00:57:35 by dyamen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_int.h"

#define WIN1_SX		242
#define WIN1_SY		242
#define IM1_SX		42
#define IM1_SY		42
#define IM3_SX		242
#define IM3_SY		242

void	*g_mlx;
void	*g_win1;
void	*g_win2;
void	*g_win3;
void	*g_im1;
void	*g_im2;
void	*g_im3;
void	*g_im4;
int		g_bpp1;
int		g_bpp2;
int		g_bpp3;
int		g_bpp4;
int		g_sl1;
int		g_sl2;
int		g_sl3;
int		g_sl4;
int		g_endian1;
int		g_endian2;
int		g_endian3;
int		g_endian4;
char	*g_data1;
char	*g_data2;
char	*g_data3;
char	*g_data4;
int		g_xpm1_x;
int		g_xpm1_y;
int		g_local_endian;

int	color_map_1(void *win, int w, int h);
int	color_map_2(unsigned char *data, int bpp, int sl, int w, int h, int endian,
		int type);

int	expose_win1(void *p)
{
	mlx_put_image_to_window(g_mlx, g_win1, g_im3, 0, 0);
}

int	expose_win2(void *p)
{
	mlx_put_image_to_window(g_mlx, g_win2, g_im4, 0, 0);
	mlx_put_image_to_window(g_mlx, g_win2, g_im2, 0, 0);
}

int	key_win1(int key, void *p)
{
	printf("Key in Win1 : %d\n", key);
	if (key == 0xFF1B)
		exit(0);
}

int	key_win2(int key, void *p)
{
	printf("Key in Win2 : %d\n", key);
	if (key == 0xFF1B)
		exit(0);
}

int	key_win3(int key, void *p)
{
	printf("Key in Win3 : %d\n", key);
	if (key == 0xFF1B)
		mlx_destroy_window(g_mlx, g_win3);
}

int	mouse_win1(int button, int x, int y, void *p)
{
	printf("Mouse in Win1, button %d at %dx%d.\n", button, x, y);
}

int	mouse_win2(int button, int x, int y, void *p)
{
	printf("Mouse in Win2, button %d at %dx%d.\n", button, x, y);
}

int	mouse_win3(int x, int y, void *p)
{
	printf("Mouse moving in Win3, at %dx%d.\n", x, y);
}

int	main(void)
{
	int	a;

	printf("MinilibX Test Program\n");
	a = 0x11223344;
	if (((unsigned char *)&a)[0] == 0x11)
		g_local_endian = 1;
	else
		g_local_endian = 0;
	printf(" => Local Endian : %d\n", g_local_endian);
	printf(" => Connection ...");
	g_mlx = mlx_init();
	if (!g_mlx)
	{
		printf(" !! KO !!\n");
		exit(1);
	}
	printf("OK (use_xshm %d pshm_format %d)\n",
		((t_xvar *)g_mlx)->use_xshm,
		((t_xvar *)g_mlx)->pshm_format
		);
	printf(" => Window1 %dx%d \"Title 1\" ...", WIN1_SX, WIN1_SY);
	g_win1 = mlx_new_window(g_mlx, WIN1_SX, WIN1_SY, "Title1");
	if (!g_win1)
	{
		printf(" !! KO !!\n");
		exit(1);
	}
	printf("OK\n");
	printf(" => Colormap sans event ...");
	color_map_1(g_win1, WIN1_SX, WIN1_SY);
	printf("OK\n");
	sleep(2);
	printf(" => Clear Window ...");
	mlx_clear_window(g_mlx, g_win1);
	printf("OK\n");
	sleep(2);
	printf(" => Image1 ZPixmap %dx%d ...", IM1_SX, IM1_SY);
	g_im1 = mlx_new_image(g_mlx, IM1_SX, IM1_SY);
	if (!g_im1)
	{
		printf(" !! KO !!\n");
		exit(1);
	}
	g_data1 = mlx_get_data_addr(g_im1, &g_bpp1, &g_sl1, &g_endian1);
	printf("OK (bpp1: %d, sizeline1: %d endian: %d type: %d)\n",
		g_bpp1, g_sl1, g_endian1, ((t_img *)g_im1)->type
		);
	printf(" => Fill Image1 ...");
	color_map_2(g_data1, g_bpp1, g_sl1, IM1_SX, IM1_SY, g_endian1, 1);
	printf("OK (pixmap : %d)\n", (int)((t_img *)g_im1)->pix);
	printf(" => Put Image1 ...");
	mlx_put_image_to_window(g_mlx, g_win1, g_im1, 20, 20);
	printf("OK\n");
	sleep(2);
	printf(" => Destroy Image1 ... ");
	mlx_destroy_image(g_mlx, g_im1);
	printf("OK\n");
	sleep(2);
	printf(" => Image3 ZPixmap %dx%d ...", IM3_SX, IM3_SY);
	g_im3 = mlx_new_image(g_mlx, IM3_SX, IM3_SY);
	if (!g_im3)
	{
		printf(" !! KO !!\n");
		exit(1);
	}
	g_data3 = mlx_get_data_addr(g_im3, &g_bpp3, &g_sl3, &g_endian3);
	printf("OK (bpp3 %d, sizeline3 %d endian3 %d type %d)\n",
		g_bpp3, g_sl3, g_endian3, ((t_img *)g_im3)->type
		);
	printf(" => Fill Image3 ...");
	color_map_2(g_data3, g_bpp3, g_sl3, IM3_SX, IM3_SY, g_endian3, 1);
	printf("OK (pixmap : %d)\n", (int)((t_img *)g_im3)->pix);
	printf(" => Put Image3 ...");
	mlx_put_image_to_window(g_mlx, g_win1, g_im3, 20, 20);
	printf("OK\n");
	sleep(2);
	printf(" => String ...");
	mlx_string_put(g_mlx, g_win1, 5, WIN1_SY / 2, 0xFF99FF, "String output");
	mlx_string_put(
		g_mlx, g_win1, 15, WIN1_SY / 2 + 20, 0x00FFFF, "MinilibX test"
		);
	printf("OK\n");
	sleep(2);
	printf(" => Xpm from file ...");
	g_im2 = mlx_xpm_file_to_image(g_mlx, "open.xpm", &g_xpm1_x, &g_xpm1_y);
	if (!g_im2)
	{
		printf(" !! KO !!\n");
		exit(1);
	}
	g_data2 = mlx_get_data_addr(g_im2, &g_bpp2, &g_sl2, &g_endian2);
	printf("OK (xpm %dx%d)(img bpp2: %d, sizeline2: %d endian: %d type: %d)\n",
		g_xpm1_x, g_xpm1_y, g_bpp2, g_sl2, g_endian2, ((t_img *)g_im2)->type);
	sleep(2);
	printf(" => Put xpm ...");
	mlx_put_image_to_window(g_mlx, g_win1, g_im2, 0, 0);
	mlx_put_image_to_window(g_mlx, g_win1, g_im2, 100, 100);
	printf("OK\n");
	sleep(2);
	printf(" => 2nd window,");
	g_win2 = mlx_new_window(g_mlx, WIN1_SX, WIN1_SY, "Title2");
	g_im4 = mlx_new_image(g_mlx, IM3_SX, IM3_SY);
	if (!g_im4)
	{
		printf(" !! KO !!\n");
		exit(1);
	}
	g_data4 = mlx_get_data_addr(g_im4, &g_bpp4, &g_sl4, &g_endian4);
	color_map_2(g_data4, g_bpp4, g_sl4, IM3_SX, IM3_SY, g_endian4, 2);
	printf(" 3rd window, Installing hooks ...");
	g_win3 = mlx_new_window(g_mlx, WIN1_SX, WIN1_SY, "Title3");
	mlx_expose_hook(g_win1, expose_win1, 0);
	mlx_mouse_hook(g_win1, mouse_win1, 0);
	mlx_key_hook(g_win1, key_win1, 0);
	mlx_expose_hook(g_win2, expose_win2, 0);
	mlx_mouse_hook(g_win2, mouse_win2, 0);
	mlx_key_hook(g_win2, key_win2, 0);
	mlx_key_hook(g_win3, key_win3, 0);
	mlx_hook(g_win3, MotionNotify, PointerMotionMask, mouse_win3, 0);
	printf("OK\nNow in Loop. Just play. Esc in 3 to destroy, 1&2 to quit.\n");
	mlx_loop(g_mlx);
}


int	color_map_1(void *win, int w, int h)
{
	int	x;
	int	y;
	int	color;

	x = w;
	while (x--)
	{
		y = h;
		while (y--)
		{
			color = (x * 255) / w;
			color += (((w - x) * 255) / w) << 16;
			color += ((y * 255) / h) << 8;
			mlx_pixel_put(g_mlx, win, x, y, color);
		}
	}
}

int	color_map_2(unsigned char *data, int bpp, int sl,
	int w, int h, int endian, int type)
{
	int				x;
	int				y;
	int				opp;
	int				dec;
	int				color;
	int				color2;
	unsigned char	*ptr;

	opp = bpp / 8;
	printf("(opp : %d) ", opp);
	y = h;
	while (y--)
	{
		ptr = data + y * sl;
		x = w;
		while (x--)
		{
			if (type == 2)
				color = (y * 255) / w;
			else
				color = (x * 255) / w;
			color += (((w - x) * 255) / w) << 16;
			color += ((y * 255) / h) << 8;
			color2 = mlx_get_color_value(g_mlx, color);
			dec = opp;
			while (dec--)
			{
				if (endian == g_local_endian)
				{
					if (endian)
						*(ptr + x * opp + dec)
							= ((unsigned char *)(&color2))[4 - opp + dec];
					else
						*(ptr + x * opp + dec)
							= ((unsigned char *)(&color2))[dec];
				}
				else
				{
					if (endian)
						*(ptr + x * opp + dec)
							= ((unsigned char *)(&color2))[opp - 1 - dec];
					else
						*(ptr + x * opp + dec)
							= ((unsigned char *)(&color2))[3 - dec];
				}
			}
		}
	}
}
