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

void	set_viewport_ratio(t_viewport *viewport, t_resolution canvas)
{
	viewport->x_ratio = viewport->width / (double)canvas.x;
	viewport->y_ratio = viewport->height / (double)canvas.y;
	printf("viewport/canvas ratios - x: %f y: %f\n", viewport->x_ratio, viewport->y_ratio);
}

void	set_viewport(t_scene *scene, double aspect_ratio)
{
	t_viewport	*viewport;
	int				i;
	double			diagonal;
	double			radians;

	viewport = &scene->viewport;
	radians = (double)scene->cameras[scene->cc].fov * (double)M_PI / 180;
	viewport->height = 2;
	viewport->width = viewport->height * aspect_ratio;
	diagonal = sqrt(viewport->width * viewport->width + \
	viewport->height * viewport->height);
	viewport->focal_length = diagonal / 2 / tan(radians / 2);
//	printf("\n\nwidth: %f\nheight: %f\ndiagonal: %f\nfov: %d\nfocal length: %f\n\n", viewport->width, viewport->height, diagonal, scene->camera[scene->cc].fov, viewport->focal_length);
	i = scene->cameras[scene->cc].zoom_level;
	while (i > 1)
	{
		viewport->height /= CAMERA_ZOOM_FACTOR;
		viewport->width = viewport->height * aspect_ratio;
		i--;
	}
	set_viewport_ratio(viewport, scene->canvas);
}
