/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_render_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 21:29:58 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/04/27 17:29:53 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <datatypes.h>
#include <rt_vector_utils.h>

t_vector	canvas_to_viewport(int x, int y, t_scene scene)
{
	t_vector	v;

	v.x = x * scene.viewport_x / scene.resolution_x;
	v.y = y * scene.viewport_y / scene.resolution_y;
	v.z = scene.d;
	// v = multip_vector(v, 1 / dot_product(v, v));
	return (v);
}

t_color	multip_color(t_color_intensity intensity, t_color color)
{
	int	r;
	int	g;
	int	b;
	int a;

	r = color.r * intensity.r;
	g = color.g * intensity.g;
	b = color.b * intensity.b;
	a = color.a * intensity.a;
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





