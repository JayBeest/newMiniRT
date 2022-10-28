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
#include <rt_render.h>
#include <rt_render_utils.h>
#include <rt_vector_utils.h>
#include <rt_intersect.h>
#include <rt_draw_utils.h>
#include <rt_color.h>

#include <stdio.h>

void	init_intensity(t_rt_color_intensity *intensity, double init, t_rt_color color)
{
	intensity->r = ((double)color.r / 255) * init;
	intensity->g = ((double)color.g / 255) * init;
	intensity->b = ((double)color.b / 255) * init;
	intensity->a = ((double)color.a / 255) * init;
}

void	update_intensity(t_rt_color_intensity *intensity, t_rt_color_intensity add, t_rt_color color)
{
	intensity->r += ((double)color.r / 255) * add.r;
	intensity->g += ((double)color.g / 255) * add.g;
	intensity->b += ((double)color.b / 255) * add.b;
	intensity->a += ((double)color.a / 255) * add.a;
}

t_rt_color_intensity	update_multiply_intensity(t_rt_color_intensity og, double factor, t_rt_color color)
{
	og.r *= ((double)color.r / 255) * factor;
	og.g *= ((double)color.g / 255) * factor;
	og.b *= ((double)color.b / 255) * factor;
	og.a *= ((double)color.a / 255) * factor;
	return (og);
}

t_rt_vector	reflect_ray(t_rt_vector ray, t_rt_vector normal)
{
	t_rt_vector	new_ray;

	new_ray = multiply_vector(normal, 2);
	new_ray = multiply_vector(new_ray, dot_product(normal, ray));
	new_ray = substract_vector(new_ray, ray);
	return (new_ray);
}

t_rt_color	calculate_light(t_rt_obj_union *obj, t_rt_vector n, t_rt_vector p, t_rt_vector v, t_rt_scene *scene)
{
	t_rt_color_intensity	intensity;
	t_rt_color_intensity 	to_add;
	t_rt_vector				r;
	t_rt_vector				l;
	double					n_dot_l;
	double					r_dot_v;
	t_intersect_result		shadow;
	int i = 0;

	ft_bzero(&shadow, sizeof(t_intersect_result));
	init_intensity(&intensity, scene->ambient_light.intensity, scene->ambient_light.color);
	while (i < scene->light_amount)
	{
		if (scene->spot_lights[i].intensity < EPSILON)
		{
			i++;
			continue;
		}
		t_rt_vector lp = substract_vector(scene->spot_lights[i].coordinates, p);
//		if (scene.lights->type == POINT_L)
			l = lp;
//		else if (scene.lights->type == DIRECT_L)
//			l = scene.lights->vector;
		shadow = get_closest_intersection(scene, p, l, EPSILON, 1);
		if (shadow.closest_obj && shadow.closest_obj != obj)
		{
			i++;
			continue ;
		}
		n_dot_l = dot_product(n, l);
		if (n_dot_l > 0)
		{
			init_intensity(&to_add, scene->spot_lights[i].intensity * n_dot_l / (sqrt(dot_product(n, n)) * sqrt(dot_product(l, l))), scene->spot_lights[i].color);
			update_intensity(&intensity, to_add, scene->spot_lights[i].color);
		}
		if (obj->def.specular > 0)
		{
			r = reflect_ray(l, n);
			r_dot_v = dot_product(r, v);
			if (r_dot_v > 0)
			{
				to_add = update_multiply_intensity(intensity, pow(r_dot_v / (sqrt(dot_product(r, r)) * sqrt(dot_product(v, v))), obj->def.specular), scene->spot_lights[i].color);
				update_intensity(&intensity, to_add, scene->spot_lights[i].color);
			}
		}
		i++;
	}
	return (multiply_color(intensity, obj->def.color));
}

t_rt_color	precalculate_light(t_intersect_result intersect_result, t_rt_ray ray, t_rt_scene *scene, int recursion_depth)
{
	t_rt_vector		n;
	t_rt_vector		v;
	t_rt_vector		p;
	t_rt_color		local_color;
	t_rt_color		reflected_color;

	p = multiply_vector(ray.direction, intersect_result.closest_t); // Calc intersection
	p = add_vector(p, ray.origin);
	n = substract_vector(p, intersect_result.closest_obj->def.coordinates); // Calc sphere normal
	n = multiply_vector(n, (double)1 / sqrt(dot_product(n, n)));
	if (intersect_result.closest_obj->def.specular > 0)
		v = multiply_vector(ray.direction, -1);
	else
		v = (t_rt_vector){0, 0, 0};
	local_color = calculate_light(intersect_result.closest_obj, n, p, v, scene);
	if (intersect_result.closest_obj->def.reflective <= 0 || recursion_depth <= 0)
		return (local_color);
	ray.direction = reflect_ray(multiply_vector(ray.direction, -1), n);
	ray.origin = p;
	ray.t_max = INFINITY;
	ray.t_min = EPSILON;
	reflected_color = trace_ray(ray, scene, recursion_depth - 1);
	return (add_color(multiply_color((t_rt_color_intensity){intersect_result.closest_obj->def.reflective, intersect_result.closest_obj->def.reflective, intersect_result.closest_obj->def.reflective, 1}, reflected_color), multiply_color((t_rt_color_intensity){1 - intersect_result.closest_obj->def.reflective, 1 - intersect_result.closest_obj->def.reflective, 1 - intersect_result.closest_obj->def.reflective, 1},local_color)));
}
