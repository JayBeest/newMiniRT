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
#include <libft.h>
#include <rt_datatypes.h>
#include <rt_error.h>



int	color_to_int(t_rt_color color)
{
	return ((color.r << 24) | (color.g << 16) | (color.b << 8) | color.a);
}

t_err	rt_put_pixel(t_rt_scene_size pixel, int color, t_rt_scene *scene, t_rt_mlx *mlx)
{
//	int	canvas_x;
//	int	canvas_y;
//
//	canvas_x = 	scene->resolution.x / 2 + pixel.x;
//	canvas_y = 	scene->resolution.y / 2 - pixel.y;
//	if (canvas_x < 0 || canvas_x >= scene->resolution.x || canvas_y < 0
//		|| canvas_y >= scene->resolution.y)
//		return (err_msg(PIXEL_OOB, ft_itoa(pixel.x), pixel.y, NULL));
	(void)scene;
	mlx_put_pixel(mlx->img, pixel.width, pixel.height, color);
	return (NO_ERR);
}
