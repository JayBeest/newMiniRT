/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_trace.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:29:55 by jcorneli      #+#    #+#                 */
/*   Updated: 2023/04/28 00:20:10 by jcorneli      ########   odam.nl         */
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

t_vector	reflect_sphere(t_vector ray, t_vector normal)
{
	t_vector	new_ray;

	new_ray = multiply_vector(normal, 2);
	new_ray = multiply_vector(new_ray, dot_product(normal, ray));
	new_ray = substract_vector(new_ray, ray);
	return (new_ray);
}

t_ray	init_ray(t_point origin, t_point destination, t_minmax t)
{
	t_ray	ray;

	ft_bzero(&ray, sizeof(ray));
	ray.origin = origin;
	ray.dest = destination;
	ray.t_min = t.min;
	ray.t_max = t.max;
	return (ray);
}

t_color	assemble_color(t_color local, t_color reflected, t_intersect_result ir)
{
	t_color_intensity	refl;
	t_color_intensity	loca;

	refl.r = ir.closest_obj->def.reflective;
	refl.g = refl.r;
	refl.b = refl.r;
	refl.a = refl.r;
	loca.r = 1 - ir.closest_obj->def.reflective;
	loca.g = loca.r;
	loca.b = loca.r;
	loca.a = loca.r;
	return (add_color(multiply_color(refl, reflected), \
		multiply_color(loca, local)));
}

void	calculate_reflected_ray(t_ray *ray, t_intersect_result *ir)
{	
	ray->dest = reflect_sphere(multiply_vector(ray->dest, -1), ray->normal);
	ray->dest = add_vector(ray->dest, multiply_vector(rnd_scalar(), \
		ir->closest_obj->def.metal_fuzz));
	ray->origin = ray->inters_p;
	ray->t_max = INFINITY;
	ray->t_min = EPSILON;
}

t_vector	refract(t_vector uv, t_vector n, double etai_over_etat)
{
	double		cos_theta = fmin(dot_product(multiply_vector(uv, -1), n), 1.0);
	t_vector	r_out_perp = multiply_vector(add_vector(uv, multiply_vector(n, cos_theta)), etai_over_etat);
	t_vector	r_out_parallel = multiply_vector(n, -1 * sqrt(fabs(1.0 - length_squared(r_out_perp))));
	return (add_vector(r_out_perp, r_out_parallel));
}

void	calculate_refracted_ray(t_ray *ray, t_intersect_result *ir)
{
	(void)ir;
//	t_color_ratio	attenuation = (t_color_ratio){1.0, 1.0, 1.0};
	double			refraction_ratio = 0.7;
//	double			index_of_refraction = 1.5;
	t_vector		unit_direction = unit_vector(substract_vector(ray->dest, ray->origin));
	t_vector		refracted = refract(unit_direction, ray->normal, refraction_ratio);
	*ray = init_ray(ray->inters_p, refracted, (t_minmax){EPSILON, INFINITY});
}

void	calculate_intersect_ray(t_ray *ray, t_intersect_result *ir)
{
	ray->inters_p = multiply_vector(ray->dest, ir->closest_t);
	ray->inters_p = add_vector(ray->inters_p, ray->origin);
	if (ir->closest_obj->def.type == SPHERE)
	{
		ray->normal = substract_vector(ray->inters_p, \
			ir->closest_obj->def.coordinates);
		ray->normal = multiply_vector(ray->normal, \
			(double)1 / sqrt(dot_product(ray->normal, ray->normal)));
	}
	else if (ir->closest_obj->def.type == PLANE)
	{
		ray->normal = ir->closest_obj->plane.orientation;
	}
	if (ir->closest_obj->def.specular > 0)
		ray->reverse_direction = multiply_vector(ray->dest, -1);
	else
		ray->reverse_direction = (t_vector){0, 0, 0};
}

t_color	trace_ray(t_ray ray, t_scene *scene, int recursion_depth)
{
	t_color				local;
	t_color				reflected;
//	t_color				refracted;
	t_intersect_result	ir;

	ft_bzero(&ir, sizeof(ir));
	ir = get_closest_intersection(scene, ray.origin, ray.dest, \
		(t_minmax){ray.t_min, ray.t_max});
	if (!ir.closest_obj)
		return (y_gradient(ray.origin, ray.dest, scene));
	calculate_intersect_ray(&ray, &ir);
	local = calculate_light(ir.closest_obj, ray, scene);
	if (scene->bare_toggle || ir.closest_obj->def.reflective <= 0 || \
		recursion_depth <= 0)
		return (local);
//	calculate_refracted_ray(&ray, &ir);
	calculate_reflected_ray(&ray, &ir);
	reflected = trace_ray(ray, scene, recursion_depth - 1);
	return (assemble_color(local, reflected, ir));
}
