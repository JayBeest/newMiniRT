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
#include <rt_draw_utils.h>
#include <rt_color.h>

#include <stdio.h>

void	init_intensity(t_rt_color_intensity *intensity, float init, t_rt_color color)
{
	intensity->r = ((float)color.r / 255) * init;
	intensity->g = ((float)color.g / 255) * init;
	intensity->b = ((float)color.b / 255) * init;
	intensity->a = ((float)color.a / 255) * init;
}

void	update_intensity(t_rt_color_intensity *intensity, t_rt_color_intensity add, t_rt_color color)
{
	intensity->r += ((float)color.r / 255) * add.r;
	intensity->g += ((float)color.g / 255) * add.g;
	intensity->b += ((float)color.b / 255) * add.b;
	intensity->a += ((float)color.a / 255) * add.a;
}

t_rt_color_intensity	update_multiply_intensity(t_rt_color_intensity og, float factor, t_rt_color color)
{
	og.r *= ((float)color.r / 255) * factor;
	og.g *= ((float)color.g / 255) * factor;
	og.b *= ((float)color.b / 255) * factor;
	og.a *= ((float)color.a / 255) * factor;
	return (og);
}

t_rt_color	calculate_light(t_rt_obj_union *obj, t_rt_vector n, t_rt_vector p, t_rt_vector v, t_rt_scene *scene)
{
	t_rt_color_intensity	intensity;
	t_rt_color_intensity 	to_add;
	t_rt_vector				r;
	t_rt_vector				l;
	float					n_dot_l;
	float					r_dot_v;
	t_intersect_result		shadow;
	int i = 0;

	ft_bzero(&shadow, sizeof(t_intersect_result));
	init_intensity(&intensity, scene->ambient_light.intensity, scene->ambient_light.color);
	while (i < scene->light_amount)
	{
		t_rt_vector lp = substract_rt_vector(scene->spot_lights[i].coordinates, p);
		t_rt_vector ln = substract_rt_vector(scene->spot_lights[i].coordinates, n);
//		if (scene.lights->type == POINT_L)
//		{
			l = ln;
			shadow = get_closest_intersection(scene, p, l, EPSILON, 1);
//		}
//		else if (scene.lights->type == DIRECT_L)
//		{
//			l = scene.lights->vector;
//			shadow = get_closest_intersection(scene.shapes, p, l, EPSILON, INFINITY, obj);
//		}
		if (shadow.closest_obj && shadow.closest_obj != obj)
		{
			i++;
			continue ;
		}
//		if (scene.lights->type == POINT_L)
			l = ln;
		n_dot_l = dot_product(n, l);
		if (n_dot_l > 0)
		{
			init_intensity(&to_add, scene->spot_lights[i].intensity * n_dot_l / (sqrtf(dot_product(n, n)) * sqrtf(dot_product(l, l))), scene->spot_lights[i].color);
			update_intensity(&intensity, to_add, scene->spot_lights[i].color);
		}
//		if (scene->spot_lights[i].specular != -1)
//		{
			// printf("shape_id: %d specular: %d\n", shape->id, shape->specular);
//			if (scene->spot_lights[i].type = POINT_L)
				l = lp;

			r = multip_vector(n, 2);
			r = multip_vector(r, dot_product(n, l));
			r = substract_rt_vector(r, l);
			r_dot_v = dot_product(r, v);
//			(void)r_dot_v;
			if (r_dot_v > 0)
			{
				to_add = update_multiply_intensity(intensity, powf(r_dot_v / (sqrtf(dot_product(r, r)) * sqrtf(dot_product(v, v))), obj->def.specular), scene->spot_lights[i].color);
				update_intensity(&intensity, to_add, scene->spot_lights[i].color);
			}
//		}
		i++;
	}
	(void)v;
	return (multip_color(intensity, obj->def.color));
}

t_rt_color	precalculate_light(t_rt_obj_union *closest_obj, t_rt_vector o, t_rt_vector d, float closest_t, t_rt_scene *scene)
{
	t_rt_vector	p;
	t_rt_vector	n;
	t_rt_vector	v;

	p = multip_vector(d, closest_t);
	p = add_vector(p, o);
	n = substract_rt_vector(p, closest_obj->def.coordinates);// coordinates??!
	n = multip_vector(n, (float)1 / sqrtf(dot_product(n, n)));
//	if (closest_obj->specular != -1)
//		v = multip_vector(d, -1);
//	else
		v = (t_rt_vector){0, 0, 0};
	return (calculate_light(closest_obj, n, p, v, scene));
}
