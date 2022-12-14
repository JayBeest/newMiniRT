/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_msaa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:23:06 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/11/03 02:23:07 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <libft.h>
#include <rt_datatypes.h>
#include <rt_math_utils.h>
#include <rt_render.h>
#include <rt_trace.h>
#include <rt_color.h>

t_color 	rand_multi_sample(t_scene *scene, t_resolution pixel)
{
	t_color_aggregate	aggregate;
	t_point				destination;
	t_ray			ray;
	t_color				color;

	ft_bzero(&aggregate, sizeof(t_color_aggregate));
	int	i = 0;
	while (i < scene->msaa)
	{
		double u = pixel.x + random_double();
		double v = pixel.y + random_double();
		destination = canvas_to_viewport(u, v, scene);
		ray = init_ray(scene->cameras[scene->cc].coordinates, destination, \
			(t_minmax){1, INFINITY});
		color = trace_ray(ray, scene, scene->recursion_depth);
		add_to_aggregate(&aggregate, color_to_intensity(color));
		i++;
	}
	return (aggregate_to_color(aggregate));
}
