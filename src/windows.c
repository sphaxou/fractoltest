/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 21:03:44 by vgallois          #+#    #+#             */
/*   Updated: 2017/10/24 00:23:58 by vgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include "libft.h"

t_mlx		*mlxdel(t_mlx *mlx)
{
	if (mlx->window != NULL)
		mlx_destroy_window(mlx->mlx, mlx->window);
	if (mlx->image != NULL)
		del_image(mlx, mlx->image);
	ft_memdel((void **)&mlx);
	return (NULL);
}

t_mlx		*init(t_fractal *f)
{
	t_mlx	*mlx;

	if ((mlx = ft_memalloc(sizeof(t_mlx))) == NULL)
		return (NULL);
	if ((mlx->mlx = mlx_init()) == NULL ||
		(mlx->window = mlx_new_window(mlx->mlx, WIN_WIDTH,
			WIN_HEIGHT, ft_strjoin("Fract'ol - ", f->name))) == NULL ||
		(mlx->image = new_image(mlx)) == NULL ||
		(mlx->data = ft_memalloc(sizeof(t_pixel) * WIN_WIDTH
								* WIN_HEIGHT)) == NULL)
		return (mlxdel(mlx));
	mlx->mouse.isdown = 0;
	mlx->fractal = f;
	mlx->mouselock = 1 - f->mouse;
	mlx->palette = get_palettes();
	mlx->smooth = 1;
	return (mlx);
}
