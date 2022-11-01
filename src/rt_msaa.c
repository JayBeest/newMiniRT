#include <math.h>
#include <libft.h>
#include <rt_datatypes.h>
#include <rt_math_utils.h>
#include <rt_render.h>
#include <rt_render_utils.h>
#include <rt_trace.h>
#include <rt_color.h>

t_rt_color 	rand_multi_sample(t_rt_scene *scene, t_rt_resolution pixel)
{
	t_rt_color_aggregate	aggregate;

	ft_bzero(&aggregate, sizeof(t_rt_color_aggregate));
	int	i = 0;
	while (i < scene->msaa)
	{
		double u = pixel.x + random_double();
		double v = pixel.y + random_double();
		t_rt_point	destination = canvas_to_viewport(u, v, scene);
		add_to_aggregate(&aggregate, color_to_intensity(trace_ray(init_rt_ray(scene->cameras[0].coordinates, destination, 1, INFINITY), scene, scene->recursion_depth)));
		i++;
	}
	return (aggregate_to_color(aggregate));
}
