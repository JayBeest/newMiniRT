/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_color.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:22:28 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/11/03 02:22:31 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <rt_datatypes.h>
#include <rt_vector_utils.h>

int	color_to_int(t_color color)
{
	return ((color.r << 24) | (color.g << 16) | (color.b << 8) | color.a);
}

void	init_intensity(t_color_intensity *intensity, double init, t_color color)
{
	intensity->r = ((double)color.r / 255) * init;
	intensity->g = ((double)color.g / 255) * init;
	intensity->b = ((double)color.b / 255) * init;
	intensity->a = ((double)color.a / 255) * init;
}

void	update_intensity(t_color_intensity *intensity, t_color_intensity add, t_color color)
{
	intensity->r += ((double)color.r / 255) * add.r;
	intensity->g += ((double)color.g / 255) * add.g;
	intensity->b += ((double)color.b / 255) * add.b;
	intensity->a += ((double)color.a / 255) * add.a;
}

t_color_intensity	update_multiply_intensity(t_color_intensity og, double factor, t_color color)
{
	og.r *= ((double)color.r / 255) * factor;
	og.g *= ((double)color.g / 255) * factor;
	og.b *= ((double)color.b / 255) * factor;
	og.a *= ((double)color.a / 255) * factor;
	return (og);
}

t_color_intensity color_to_intensity(t_color color)
{
	t_color_intensity	intensity;

	intensity.r = (double)color.r / 255;
	intensity.g = (double)color.g / 255;
	intensity.b = (double)color.b / 255;
	intensity.a = (double)color.a / 255;
	return (intensity);
}

int	aggregate_to_int(t_color_aggregate agg)
{
	t_color	color;

	double scale = 1.0 / (double)agg.source_counter;
	color.r = (unsigned char)((double)agg.intensity.r * scale * 255.999);
	color.g = (unsigned char)((double)agg.intensity.g * scale * 255.999);
	color.b = (unsigned char)((double)agg.intensity.b * scale * 255.999);
	color.a = (unsigned char)((double)agg.intensity.a * scale * 255.999);
	return ((color.r << 24) | (color.g << 16) | (color.b << 8) | color.a);
}

t_color	aggregate_to_color(t_color_aggregate agg)
{
	t_color	color;

	double scale = 1.0 / (double)agg.source_counter;
	color.r = (unsigned char)((double)agg.intensity.r * scale * 255.999);
	color.g = (unsigned char)((double)agg.intensity.g * scale * 255.999);
	color.b = (unsigned char)((double)agg.intensity.b * scale * 255.999);
	color.a = (unsigned char)((double)agg.intensity.a * scale * 255.999);
	return (color);
}

t_color	add_color(t_color a, t_color b)
{
	return ((t_color){a.r + b.r, a.g + b.g, a.b + b.b, a.a + b.a});
}

void	add_to_aggregate(t_color_aggregate *agg, t_color_intensity to_add)
{
	agg->intensity.r = agg->intensity.r + to_add.r;
	agg->intensity.g = agg->intensity.g + to_add.g;
	agg->intensity.b = agg->intensity.b + to_add.b;
	agg->intensity.a = agg->intensity.a + to_add.a;
	agg->source_counter++;
}

t_color	multiply_color(t_color_intensity intensity, t_color color)
{
	int	r;
	int	g;
	int	b;
	int a;

	r = (int)((double)color.r * intensity.r);
	g = (int)((double)color.g * intensity.g);
	b = (int)((double)color.b * intensity.b);
	a = (int)((double)color.a * intensity.a);
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

t_color	y_gradient(t_vector o, t_vector d, t_scene *scene)
{
	t_vector			unit_direction;
	t_color_ratio	color_ratio;
	double				t;
	t_color			color;
	(void)o;

	unit_direction = unit_vector(d);
	t = 0.5 * (unit_direction.y + 1.0);
	color_ratio = add_vector(multiply_vector((t_vector) {1, 1, 1}, 1.0 - t),
							 multiply_vector((t_vector) {scene->bg_color.x, scene->bg_color.y, scene->bg_color.z}, t));
	color.a = 255;
	color.r = (int)(255.999 * color_ratio.x);
	color.g = (int)(255.999 * color_ratio.y);
	color.b = (int)(255.999 * color_ratio.z);
	return (color);
}

t_color	all_the_colors(t_resolution pixel, t_scene *scene)
{
	double		r;
	double		g;
	double		b;
	t_color	color;

	r = ((double)pixel.x + (double)scene->canvas.x / 2) / ((double)scene->canvas.x - 1);
	g = ((double)pixel.y + (double)scene->canvas.y / 2) / ((double)scene->canvas.y - 1);
	b = scene->bg_color.z;
	color.a = 255;
	color.r = (int)(255.999 * r);
	color.g = (int)(255.999 * g);
	color.b = (int)(255.999 * b);
	return (color);
}
