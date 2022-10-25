#include <rt_datatypes.h>
#include <rt_vector_utils.h>

int	color_to_int(t_rt_color color)
{
	return ((color.r << 24) | (color.g << 16) | (color.b << 8) | color.a);
}

t_rt_color	multip_color(t_rt_color_intensity intensity, t_rt_color color)
{
	int	r;
	int	g;
	int	b;
	int a;

	r = (int)((float)color.r * intensity.r);
	g = (int)((float)color.g * intensity.g);
	b = (int)((float)color.b * intensity.b);
	a = (int)((float)color.a * intensity.a);
	if (r > 255)
		r = 255;
	else if (r < 0)
		r = 0;
	if (g > 255)
		g = 255;
	else if (g < 0)
		g = 0;
	if (b > 255)
		b = 255;
	else if (b < 0)
		b = 0;
	if (a > 255)
		a = 255;
	else if (a < 0)
		a = 0;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return (color);
}

t_rt_color	y_gradient(t_rt_vector o, t_rt_vector d, t_rt_scene *scene)
{
	t_rt_vector			unit_direction;
	t_rt_color_ratio	color_ratio;
	float		t;
	t_rt_color	color;
	(void)o;

	unit_direction = unit_vector(d);
	t = 0.5f * (unit_direction.y + 1.0f);
	color_ratio = add_vector(multip_vector((t_rt_vector){1, 1, 1}, 1.0f - t), multip_vector((t_rt_vector){scene->red, scene->green, scene->blue}, t));
	color.a = 255;
	color.r = (int)(255.999 * color_ratio.x);
	color.g = (int)(255.999 * color_ratio.y);
	color.b = (int)(255.999 * color_ratio.z);
	return (color);
}

t_rt_color	all_the_colors(t_rt_resolution pixel, t_rt_scene *scene)
{
	float		r;
	float		g;
	float		b;
	t_rt_color	color;

	r = ((float)pixel.x + (float)scene->canvas.x / 2) / ((float)scene->canvas.x - 1);
	g = ((float)pixel.y + (float)scene->canvas.y / 2) / ((float)scene->canvas.y - 1);
	b = scene->blue;
	color.a = 255;
	color.r = (int)(255.999 * r);
	color.g = (int)(255.999 * g);
	color.b = (int)(255.999 * b);
	return (color);
}
