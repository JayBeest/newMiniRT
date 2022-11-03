/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_scene_printer.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:23:28 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/11/03 02:23:29 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <rt_datatypes.h>

void	print_vector(t_vector vector)
{
	printf("x: %f  y: %f  z: %f\n", vector.x, vector.y, vector.z);
}

void	print_color(t_color color)
{
	printf("color(rgba): %d %d %d %d\n", color.r, color.g, color.b, color.a);
}

void	print_coordinates(t_vector coordinates)
{
	printf("coordinates: %f(x) %f(y) %f(z)\n", coordinates.x, coordinates.y, coordinates.z);
}

void	print_orientation(t_vector orientation)
{
	printf("orientation: %f(x) %f(y) %f(z)\n", orientation.x, orientation.y, orientation.z);
}

void	print_ambient_light(t_ambient_light ambient)
{
	printf("	- Ambient light -\n");
	printf("intensity: %f\n", ambient.intensity);
	print_color(ambient.color);
}

void	print_camera(t_camera *camera, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		printf("	- Camera[%d] -\n", i);
		print_coordinates(camera[i].coordinates);
		print_orientation(camera[i].orientation);
		printf("fov: %d\n", camera[i].fov);
		i++;
	}
}

void	print_spotlights(t_light *spotlights, int amount)
{
	int i;

	i = 0;
	while (i < amount)
	{
		printf("	- Spotlight[%d] -\n", i);
		printf("intensity: %f\n", spotlights[i].intensity);
		print_color(spotlights[i].color);
		print_coordinates(spotlights[i].coordinates);
		i++;
	}
}

void	print_sphere(t_obj_sphere sphere)
{
	printf("type: SPHERE\n");
	print_coordinates(sphere.coordinates);
	print_color(sphere.color);
	printf("radius: %f\n", sphere.radius);
}

void	print_plane(t_obj_plane plane)
{
	printf("type: PLANE\n");
	print_coordinates(plane.coordinates);
	print_color(plane.color);
	print_orientation(plane.orientation);
}

void	print_cylinder(t_obj_cylinder cylinder)
{
	printf("type: CYLINDER\n");
	print_coordinates(cylinder.coordinates);
	print_color(cylinder.color);
	print_orientation(cylinder.orientation);
	printf("radius: %f\n", cylinder.radius);
	printf("height: %f\n", cylinder.height);
}

void	print_objects(t_obj_union *objects, int amount)
{
	int i;

	i = 0;
	while (i < amount)
	{
		printf("	- Object[%d] -\n", i);
		if (objects[i].def.type == SPHERE)
			print_sphere(objects[i].sphere);
		else if (objects[i].def.type == PLANE)
			print_plane(objects[i].plane);
		else if (objects[i].def.type == CYLINDER)
			print_cylinder(objects[i].cylinder);
		i++;
	}
}

void	print_scene(t_scene scene)
{
	printf("		*** MiniRT Scene ***\n");
	printf("resolution: %dx%d\n", scene.canvas.x, scene.canvas.y);
	print_ambient_light(scene.ambient_light);
	print_camera(scene.cameras, scene.camera_amount);
	print_spotlights(scene.lights, scene.light_amount);
	print_objects(scene.objects, scene.object_amount);
}
