#include <stdlib.h>
#include <datatypes.h>
#include <scene_printer.h>
#include <alloc.h>

#include <stdio.h>
#include <string.h>

void	init_rt(t_rt_scene *scene)
{
	bzero(scene, sizeof(t_rt_scene));

	scene->resolution.x = RESOLUTION_X;
	scene->resolution.y = RESOLUTION_Y;

	scene->light_amount = 1;
	scene->object_amount = 3;
}

void	init_mock_rt(t_rt_scene *scene)
{
	scene->ambient_light.intensity = 0.2;
	scene->ambient_light.color = (t_rt_color){255, 255, 255, 255};

	scene->camera.coordinates = (t_rt_vector){-50, 0, 20};
	scene->camera.orientation = (t_rt_vector){0, 0, 0};
	scene->camera.fov = 70;
	scene->spot_lights[0].coordinates = (t_rt_vector){-40, 0, 30};
	scene->spot_lights[0].intensity = 0.7;
	scene->spot_lights[0].color = (t_rt_color){255, 255, 255, 255};

	scene->objects[0].plane.type = PLANE;
	scene->objects[0].plane.coordinates = (t_rt_vector){0, 0, 0};
	scene->objects[0].plane.orientation = (t_rt_vector){0, 1.0, 0};
	scene->objects[0].plane.color = (t_rt_color){255, 0, 255, 255};
	scene->objects[1].sphere.type = SPHERE;
	scene->objects[1].sphere.coordinates = (t_rt_vector){0, 0, 20};
	scene->objects[1].sphere.diameter = 20;
	scene->objects[1].sphere.color = (t_rt_color){255, 0, 0, 255};
	scene->objects[2].cylinder.coordinates = (t_rt_vector){50.0, 0.0, 20.6};
	scene->objects[2].cylinder.orientation = (t_rt_vector){0, 0, 1.0};
	scene->objects[2].cylinder.diameter = 14.2;
	scene->objects[2].cylinder.height = 21.42;
	scene->objects[2].cylinder.color = (t_rt_color){10, 0, 255, 255};
}

int main( void )
{
	t_rt_scene	scene;

	init_rt(&scene);
	allocate_objects(&scene.objects, scene.object_amount);
	allocate_spot_lights(&scene.spot_lights, scene.light_amount);
	init_mock_rt(&scene);
	print_scene(scene);

	return 0;
}
