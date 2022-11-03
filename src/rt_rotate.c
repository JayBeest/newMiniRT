/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_rotate.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:23:24 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/11/03 02:23:25 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <rt_datatypes.h>
#include <rt_rotate.h>
#include <rt_math_utils.h>

t_vector	rotate_vector_x(t_vector og_vector, double radians)
{
	t_vector	rotated_v;

	rotated_v.x = og_vector.x;
	rotated_v.y = og_vector.y * cos(radians) - og_vector.z * sin(radians);
	rotated_v.z = og_vector.y * sin(radians) + og_vector.z * cos(radians);
	return (rotated_v);
}

t_vector	rotate_vector_y(t_vector og_vector, double radians)
{
	t_vector	rotated_v;

	rotated_v.x = og_vector.x * cos(radians) + og_vector.z * sin(radians);
	rotated_v.y = og_vector.y;
	rotated_v.z = -og_vector.x * sin(radians) + og_vector.z * cos(radians);
	return (rotated_v);
}

t_vector	rotate_vector_z(t_vector og_vector, double radians)
{
	t_vector	rotated_v;

	rotated_v.x = og_vector.x * cos(radians) - og_vector.y * sin(radians);
	rotated_v.y = og_vector.x * sin(radians) + og_vector.y * cos(radians);
	rotated_v.z = og_vector.z;
	return (rotated_v);
}

t_vector	rotate_vector(t_vector og_vector, t_vector rotation)
{
	t_vector	rotated_v;

	rotated_v = rotate_vector_x(og_vector, deg_to_rad(rotation.y * 360));
	rotated_v = rotate_vector_y(rotated_v, deg_to_rad(rotation.x * 360));
	rotated_v = rotate_vector_z(rotated_v, deg_to_rad(rotation.z * 360));
	(void)rotation;
	return (rotated_v);
}
