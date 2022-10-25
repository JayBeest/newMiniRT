#include <rt_datatypes.h>

int	color_to_int(t_rt_color color)
{
	return ((color.r << 24) | (color.g << 16) | (color.b << 8) | color.a);
}

//t_rt_color	multip_color(t_color_intensity intensity, t_color color)
//{
//	int	r;
//	int	g;
//	int	b;
//	int a;
//
//	r = color.r * intensity.r;
//	g = color.g * intensity.g;
//	b = color.b * intensity.b;
//	a = color.a * intensity.a;
//	if (r > 255)
//		r = 255;
//	else if (r < 0)
//		r = 0;
//	if (g > 255)
//		g = 255;
//	else if (g < 0)
//		g = 0;
//	if (b > 255)
//		b = 255;
//	else if (b < 0)
//		b = 0;
//	if (a > 255)
//		a = 255;
//	else if (a < 0)
//		a = 0;
//	color.r = r;
//	color.g = g;
//	color.b = b;
//	color.a = a;
//	return (color);
//}


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
