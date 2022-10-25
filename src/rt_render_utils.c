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

#include <math.h>
#include <rt_datatypes.h>
#include <stdio.h>

void	set_viewport(t_rt_viewport *viewport, t_rt_camera *camera, float aspect_ratio)
{
	float	radians;
	float	diagonal;

	radians = (float)camera->fov * (float)M_PI / 180;
	viewport->height = 1.0f;
	viewport->width = viewport->height * aspect_ratio;
	diagonal = sqrtf(viewport->width * viewport->width + viewport->height * viewport->height);
	viewport->focal_length = diagonal / 2 / tanf(radians / 2);
	printf("\n\nwidth: %f\nheight: %f\ndiagonal: %f\nfov: %d\nfocal length: %f\n\n", viewport->width, viewport->height, diagonal,  camera->fov, viewport->focal_length);
}

t_rt_vector	canvas_to_viewport(int x, int y, t_rt_scene *scene)
{
	t_rt_vector	v;

	v.x = (float)x * scene->viewport.width / (float)scene->size.width;  //static divisions in a loop..
	v.y = (float)y * scene->viewport.height / (float)scene->size.height;
	v.z = scene->viewport.focal_length;
	// v = multip_vector(v, 1 / dot_product(v, v));
	return (v);
}
