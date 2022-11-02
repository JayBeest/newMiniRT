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
#include <rt_render.h>
#include <rt_trace.h>
#include <rt_intersect.h>
#include <rt_color.h>

#include <stdio.h>
#include <stdlib.h>

void	init_intensity(t_color_intensity *intensity, double init, t_color color)
{
	intensity->r = ((double)color.r / 255) * init;
	intensity->g = ((double)color.g / 255) * init;
	intensity->b = ((double)color.b / 255) * init;
	intensity->a = ((double)color.a / 255) * init;
}

void	update_intensity(t_color_intensity *intensity, t_color_intensity add, t_color color)
{
	intensity->r += ((double)color.r / 255) * add.r;
	intensity->g += ((double)color.g / 255) * add.g;
	intensity->b += ((double)color.b / 255) * add.b;
	intensity->a += ((double)color.a / 255) * add.a;
}

t_color_intensity	update_multiply_intensity(t_color_intensity og, double factor, t_color color)
{
	og.r *= ((double)color.r / 255) * factor;
	og.g *= ((double)color.g / 255) * factor;
	og.b *= ((double)color.b / 255) * factor;
	og.a *= ((double)color.a / 255) * factor;
	return (og);
}

t_vector	reflect_sphere(t_vector ray, t_vector normal) // one also needed for plane and others I think
{
	t_vector	new_ray;

	new_ray = multiply_vector(normal, 2);
	new_ray = multiply_vector(new_ray, dot_product(normal, ray));
	new_ray = substract_vector(new_ray, ray);
	return (new_ray);
}

t_vector	rnd_scalar()
{
	t_vector	random;

	random.x = (double)rand() / RAND_MAX;
	random.y = (double)rand() / RAND_MAX;
	random.z = (double)rand() / RAND_MAX;
	return (random);
}

void	add_diffuse_light(t_color_intensity *intensity, t_spot_light *light, t_vector n, t_vector l)
{
	double					n_dot_l;
	t_color_intensity 	to_add;

	n_dot_l = dot_product(n, l);
	if (n_dot_l > 0)
	{
		init_intensity(&to_add, light->intensity * n_dot_l / (sqrt(dot_product(n, n)) * sqrt(dot_product(l, l))), light->color);
		update_intensity(intensity, to_add, light->color);
	}
}

void	add_specular_light(t_color_intensity *intensity, t_spot_light *light, t_rt_ray ray, t_vector l)
{
	t_color_intensity 	to_add;
	double					r_dot_v;
	t_vector				r;

	{
		r = reflect_sphere(l, ray.normal);
		r_dot_v = dot_product(r, ray.reverse_direction);
		if (r_dot_v > 0)
		{
			to_add = update_multiply_intensity(*intensity, pow(r_dot_v / (sqrt(dot_product(r, r)) * sqrt(dot_product(ray.reverse_direction, ray.reverse_direction))), (int)ray.t_max), light->color);
			update_intensity(intensity, to_add, light->color);
		}
	}
}

t_color	calculate_light(t_obj_union *obj, t_rt_ray ray, t_scene *scene)
{
	t_color_intensity	intensity;
	t_vector				l;
	int						i;

	i = 0;
	init_intensity(&intensity, scene->ambient_light.intensity, scene->ambient_light.color);
	while (i < scene->light_amount)
	{
		l = substract_vector(scene->lights[i].coordinates, ray.intersection_point);
		if (!scene->lights[i].toggle || scene->lights[i].intensity < EPSILON || \
			(get_closest_intersection(scene, ray.intersection_point, l, EPSILON, 1)).closest_obj) // == shadow or light out
		{
			i++;
			continue ;
		}
		add_diffuse_light(&intensity, &scene->lights[i], ray.normal, l);
		ray.t_max = obj->def.specular; // 'hack' for add_specular_light()
		if (obj->def.specular > 0)
			add_specular_light(&intensity, &scene->lights[i], ray, l);
		i++;
	}
	return (multiply_color(intensity, obj->def.color));
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
