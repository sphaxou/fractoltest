/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:42:59 by vgallois          #+#    #+#             */
/*   Updated: 2017/10/27 18:37:07 by vgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "mlx.h"

int		die(char *reason)
{
	ft_putendl(reason);
	return (1);
}

int		hook_expose(t_mlx *mlx)
{
	render(mlx);
	return (0);
}

int		main(int argc, char **argv)
{
	t_mlx		*mlx;
	t_fractal	*f;

	if ((argc != 2) || (((ft_strcmp(argv[1], "mandelbrot")))
				&& (ft_strcmp(argv[1], "julia"))
				&& (ft_strcmp(argv[1], "burningship"))))
		return (die("usage:./fractol fractal_name"));
	f = fractal_match(argv[1]);
	if (f->name == NULL)
		return (die("wrong argument."));
	if (!(mlx = init(f)))
		return (die("error: mlx couldn't init"));
	reset_viewport(mlx);
	render(mlx);
	mlx_key_hook(mlx->window, hook_keydown, mlx);
	mlx_expose_hook(mlx->window, hook_expose, mlx);
	mlx_hook(mlx->window, 4, 1L << 2, hook_mousedown, mlx);
	mlx_hook(mlx->window, 5, 1L << 3, hook_mouseup, mlx);
	mlx_hook(mlx->window, 6, 1L << 6, hook_mousemove, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
