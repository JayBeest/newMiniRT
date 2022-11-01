/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_render_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:29:58 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/27 17:29:53 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <libft.h>
#include <rt_datatypes.h>
#include <rt_render.h>

#include <stdio.h>



t_rt_ray	init_rt_ray(t_rt_point origin, t_rt_point destination, double t_min, double t_max)
{
	t_rt_ray	ray;

	ft_bzero(&ray, sizeof(ray));
	ray.origin = origin;
	ray.destination = destination;
	ray.t_min = t_min;
	ray.t_max = t_max;
	return (ray);
}
