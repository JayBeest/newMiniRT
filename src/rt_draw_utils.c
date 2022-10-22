/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_draw_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:28:55 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/26 21:28:56 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <rt_datatypes.h>

int	color_to_int(t_rt_color color)
{
	return ((color.r << 24) | (color.g << 16) | (color.b << 8) | color.a);
}

t_err	rt_putpixel(int x, int y, int color, t_mini_rt *rt)
{
	int	canvas_x;
	int	canvas_y;

	canvas_x = 	rt->scene.resolution_x / 2 + x;
	canvas_y = 	rt->scene.resolution_y / 2 - y;
//	if (canvas_x < 0 || canvas_x >= rt->scene.resolution_x || canvas_y < 0
//		|| canvas_y >= rt->scene.resolution_y)
//		return (PIXEL_OOB);
	mlx_put_pixel(rt->mlx.img, canvas_x, canvas_y, color);
	return (NO_ERR);
}