/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_light.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:23:00 by jcorneli      #+#    #+#                 */
/*   Updated: 2023/04/28 21:56:42 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <rt_datatypes.h>
#include <rt_vector_utils.h>
#include <rt_color.h>
#include <rt_trace.h>
#include <rt_intersect.h>

void	add_diffuse_light(t_color_intensity *intensity, t_light *light, \
	t_vector n, t_vector l)
{
	t_color_intensity	to_add;
	double				n_dot_l;

	n_dot_l = dot_product(n, l);
	if (n_dot_l > 0)
	{
		init_intensity(&to_add, light->intensity * n_dot_l / \
		(vector_length(n) * vector_length(l)), light->color);
		update_intensity(intensity, to_add, light->color);
	}
}

void	add_specular_light(t_color_intensity *intensity, t_light *light, \
	t_ray ray, t_vector l)
{
	t_color_intensity	to_add;
	double				r_dot_v;
	t_vector			r;

	{
		r = reflect_sphere(l, ray.normal);
		r_dot_v = dot_product(r, ray.reverse_direction);
		if (r_dot_v > 0)
		{
			to_add = update_multiply_intensity(*intensity, \
				pow(r_dot_v / (sqrt(dot_product(r, r)) * \
				sqrt(dot_product(ray.reverse_direction, \
				ray.reverse_direction))), (int)ray.t_max), \
				light->color);
			update_intensity(intensity, to_add, light->color);
		}
	}
}

t_color	calculate_light(t_obj_union *obj, t_ray ray, t_scene *scene)
{
	t_color_intensity	intensity;
	t_vector			l;
	int					i;
	// t_intersect_result	shadow;

	i = 0;
	init_intensity(&intensity, scene->ambient_light.intensity, \
		scene->ambient_light.color);
	while (i < scene->light_amount)
	{
		l = substract_vector(scene->lights[i].coordinates, ray.inters_p);
		// shadow = get_closest_intersection(scene, ray.inters_p, scene->lights[i].coordinates, (t_minmax){EPSILON, INFINITY});
		if (!scene->lights[i].toggle || scene->lights[i].intensity < EPSILON || \
			(get_closest_intersection(scene, ray.inters_p, scene->lights[i].coordinates, (t_minmax){EPSILON, INFINITY})).closest_obj) // == shadow or light out
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
