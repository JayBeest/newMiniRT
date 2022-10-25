#include <rt_datatypes.h>

t_rt_color	all_the_colors(t_rt_resolution pixel, t_rt_scene *scene)
{
	float		r;
	float		g;
	float		b;
	t_rt_color	color;

	r = ((float)pixel.x + (float)scene->size.width / 2) / ((float)scene->size.width - 1);
	g = ((float)pixel.y + (float)scene->size.height / 2) / ((float)scene->size.height - 1);
	b = scene->blue;
	color.a = 255;
	color.r = (int)(255.999 * r);
	color.g = (int)(255.999 * g);
	color.b = (int)(255.999 * b);
	return (color);
}
