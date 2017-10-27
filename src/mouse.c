/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 23:09:47 by vgallois          #+#    #+#             */
/*   Updated: 2017/10/27 18:38:36 by vgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		hook_mousedown(int button, int x, int y, t_mlx *mlx)
{
	if (button == 4)
	{
		zoom(x, y, &mlx->viewport, 1 / ZOOM);
		render(mlx);
	}
	else if (button == 5)
	{
		zoom(x, y, &mlx->viewport, ZOOM);
		render(mlx);
	}
	if (y < 0)
		return (0);
	mlx->mouse.isdown |= 1 << button;
	return (0);
}

int		hook_mouseup(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	mlx->mouse.isdown &= ~(1 << button);
	return (0);
}

int		hook_mousemove(int x, int y, t_mlx *mlx)
{
	double w;
	double h;

	mlx->mouse.lastx = mlx->mouse.x;
	mlx->mouse.lasty = mlx->mouse.y;
	mlx->mouse.x = x;
	mlx->mouse.y = y;
	if (!mlx->mouselock)
		mlx->viewport.mouse = screen_to_complex(x, y, &mlx->viewport);
	if (mlx->mouse.isdown & (1 << 1))
	{
		w = (mlx->viewport.xmax - mlx->viewport.xmin) * mlx->viewport.zoom;
		h = (mlx->viewport.ymax - mlx->viewport.ymin) * mlx->viewport.zoom;
		mlx->viewport.offx += (double)(mlx->mouse.lastx - mlx->mouse.x)
			/ WIN_WIDTH * w;
		mlx->viewport.offy += (double)(mlx->mouse.lasty - mlx->mouse.y)
			/ WIN_HEIGHT * h;
	}
	else if (mlx->mouse.isdown & (1 << 2))
		zoom(x, y, &mlx->viewport,
				mlx->mouse.lasty > mlx->mouse.y ? 1 / ZOOM : ZOOM);
	if (mlx->mouse.isdown || (mlx->fractal->mouse && !mlx->mouselock))
		render(mlx);
	return (0);
}
