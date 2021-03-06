/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 22:10:09 by vgallois          #+#    #+#             */
/*   Updated: 2017/10/25 19:38:10 by vgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fractol.h"

t_fractal	*get_fractals(void)
{
	static t_fractal array[8] = {
		{"mandelbrot", mandelbrot_viewport, mandelbrot_pixel, 0},
		{"julia", julia_viewport, julia_pixel, 1},
		{"burningship", burningship_viewport, burningship_pixel, 0},
		{NULL, NULL, NULL, 0}
	};

	return (array);
}

t_fractal	*fractal_match(char *str)
{
	t_fractal	*f;
	int			i;

	f = get_fractals();
	i = 0;
	while (f[i].name != NULL)
	{
		if ((ft_strcmp(f[i].name, str)) == 0)
			return (&f[i]);
		i++;
	}
	return (&f[i]);
}
