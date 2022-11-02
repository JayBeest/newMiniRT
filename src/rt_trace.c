/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:29:55 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/27 20:24:53 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <libft.h>
#include <rt_datatypes.h>
#include <rt_vector_utils.h>
#include <rt_trace.h>
#include <rt_intersect.h>
#include <rt_light.h>
#include <rt_color.h>

#include <stdlib.h>

t_vector	reflect_sphere(t_vector ray, t_vector normal) // one also needed for plane and others I think
{
	t_vector	new_ray;

	new_ray = multiply_vector(normal, 2);
	new_ray = multiply_vector(new_ray, dot_product(normal, ray));
	new_ray = substract_vector(new_ray, ray);
	return (new_ray);
}

t_rt_ray	init_rt_ray(t_point origin, t_point destination, double t_min, double t_max)
{
	t_rt_ray	ray;

	ft_bzero(&ray, sizeof(ray));
	ray.origin = origin;
	ray.destination = destination;
	ray.t_min = t_min;
	ray.t_max = t_max;
	return (ray);
}

t_color	trace_reflection(t_rt_ray ray, t_intersect_result intersect_result, t_scene *scene, int recursion_depth)
{
	ray.destination = reflect_sphere(multiply_vector(ray.destination, -1), ray.normal);
	ray.destination = add_vector(ray.destination, multiply_vector(rnd_scalar(), intersect_result.closest_obj->def.metal_fuzz));
	ray.origin = ray.intersection_point;
	ray.t_max = INFINITY;
	ray.t_min = EPSILON;
	return (trace_ray(ray, scene, recursion_depth - 1));
}

t_color	trace_ray(t_rt_ray ray, t_scene *scene, int recursion_depth)
{
	t_color			local_color;
	t_color			reflected_color;
	t_intersect_result	ir;

	ft_bzero(&ir, sizeof(ir));
	ir = get_closest_intersection(scene, ray.origin, ray.destination, ray.t_min, ray.t_max);
	if (!ir.closest_obj)
		return (y_gradient(ray.origin, ray.destination, scene));
	ray.intersection_point = multiply_vector(ray.destination, ir.closest_t); // Calc intersection
	ray.intersection_point = add_vector(ray.intersection_point, ray.origin);
	ray.normal = substract_vector(ray.intersection_point, ir.closest_obj->def.coordinates); // Calc sphere normal
	ray.normal = multiply_vector(ray.normal, (double)1 / sqrt(dot_product(ray.normal, ray.normal)));
	if (ir.closest_obj->def.specular > 0)
		ray.reverse_direction = multiply_vector(ray.destination, -1);
	else
		ray.reverse_direction = (t_vector){0, 0, 0};
	local_color = calculate_light(ir.closest_obj, ray, scene);
	if (scene->bare_toggle || ir.closest_obj->def.reflective <= 0 || \
		recursion_depth <= 0)
		return (local_color);
	reflected_color = trace_reflection(ray, ir, scene, recursion_depth);
	return (add_color(multiply_color((t_color_intensity){ir.closest_obj->def.reflective, ir.closest_obj->def.reflective, ir.closest_obj->def.reflective, 1}, reflected_color), multiply_color((t_color_intensity){1 - ir.closest_obj->def.reflective, 1 - ir.closest_obj->def.reflective, 1 - ir.closest_obj->def.reflective, 1}, local_color)));
}
