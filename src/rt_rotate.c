#include <math.h>
#include <rt_datatypes.h>
#include <rt_rotate.h>
#include <rt_math_utils.h>

t_rt_vector rotate_vector_x(t_rt_vector original_vector, double radians)
{
	t_rt_vector	rotated_vector;

	rotated_vector.x = original_vector.x;
	rotated_vector.y = original_vector.y * cos(radians) - original_vector.z * sin(radians);
	rotated_vector.z = original_vector.y * sin(radians) + original_vector.z * cos(radians);
	return (rotated_vector);
}

t_rt_vector rotate_vector_y(t_rt_vector original_vector, double radians)
{
	t_rt_vector	rotated_vector;

	rotated_vector.x = original_vector.x * cos(radians) + original_vector.z * sin(radians);
	rotated_vector.y = original_vector.y;
	rotated_vector.z = -original_vector.x * sin(radians) + original_vector.z * cos(radians);
	return (rotated_vector);
}

t_rt_vector rotate_vector_z(t_rt_vector original_vector, double radians)
{
	t_rt_vector	rotated_vector;

	rotated_vector.x = original_vector.x * cos(radians) - original_vector.y * sin(radians);
	rotated_vector.y = original_vector.x * sin(radians) + original_vector.y * cos(radians);
	rotated_vector.z = original_vector.z;
	return (rotated_vector);
}

t_rt_vector	rotate_vector(t_rt_vector original_vector, t_rt_vector rotation)
{
	t_rt_vector	rotated_vector;

	rotated_vector = rotate_vector_x(original_vector, degrees_to_radians(rotation.y * 360));
	rotated_vector = rotate_vector_y(rotated_vector, degrees_to_radians(rotation.x * 360));
	rotated_vector = rotate_vector_z(rotated_vector, degrees_to_radians(rotation.z * 360));
	(void)rotation;
	return (rotated_vector);
}
