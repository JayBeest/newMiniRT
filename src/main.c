#include <stdlib.h>
#include <datatypes.h>
#include <alloc.h>

#include <stdio.h>
#include <string.h>

void	init_rt(t_rt_scene *scene)
{
	bzero(scene, sizeof(t_rt_scene));
	scene->resolution.x = RESOLUTION_X;
	scene->resolution.y = RESOLUTION_Y;
}

void	init_mock_rt(t_rt_scene *scene) {
	scene->light_amount = 1;
	scene->object_amount = 3;

	scene->ambient_light.intensity = 0.2;
	scene->ambient_light.color = (t_rt_color) {255, 255, 255, 255};

	scene->camera.coordinates = (t_rt_vector) {-50, 0, 20};
	scene->camera.orientation = (t_rt_vector) {0, 0, 0};
	scene->camera.fov = 70;
	scene->spot_lights[0].coordinates = (t_rt_vector) {-40, 0, 30};
	scene->spot_lights[0].intensity = 0.7;
	scene->spot_lights[0].color = (t_rt_color) {255, 255, 255, 255};

	scene->objects[0].plane.type = PLANE;
	scene->objects[0].plane.coordinates = (t_rt_vector) {0, 0, 0};
	scene->objects[0].plane.orientation = (t_rt_vector) {0, 1.0, 0};
	scene->objects[0].plane.color = (t_rt_color) {255, 0, 255, 255};
	scene->objects[1].sphere.type = SPHERE;
	scene->objects[1].sphere.coordinates = (t_rt_vector) {0, 0, 20};
	scene->objects[1].sphere.diameter = 20;
	scene->objects[1].sphere.color = (t_rt_color) {255, 0, 0, 255};
	scene->objects[2].cylinder.coordinates = (t_rt_vector) {50.0, 0.0, 20.6};
	scene->objects[2].cylinder.orientation = (t_rt_vector) {0, 0, 1.0};
	scene->objects[2].cylinder.diameter = 14.2;
	scene->objects[2].cylinder.height = 21.42;
	scene->objects[2].cylinder.color = (t_rt_color) {10, 0, 255, 255};

}

void	print_color(t_rt_color color)
{
	printf("color: %d(R) %d(G) %d(B) %d(A)\n", color.r, color.g, color.b, color.a);
}

void	print_coordinates(t_rt_vector coordinates)
{
	printf("coordinates: %f(x) %f(y) %f(z)\n", coordinates.x, coordinates.y, coordinates.z);
}

void	print_orientation(t_rt_vector orientation)
{
	printf("orientation: %f(x) %f(y) %f(z)\n", orientation.x, orientation.y, orientation.z);
}

void	print_ambient_light(t_rt_ambient_light ambient)
{
	printf("	- Ambient light -\n");
	printf("intensity: %f\n", ambient.intensity);
	print_color(ambient.color);
}

void	print_camera(t_rt_camera camera)
{
	printf("	- Camera -\n");
	print_coordinates(camera.coordinates);
	print_orientation(camera.orientation);
	printf("fov: %d\n", camera.fov);
}

void	print_spotlights(t_rt_spot_light *spotlights, int amount)
{
	int i = 0;
	while (i < amount)
	{
		printf("	- Spotlight[%d] -\n", i);
		printf("intensity: %f\n", spotlights[i].intensity);
		print_color(spotlights[i].color);
		print_coordinates(spotlights[i].coordinates);
		i++;
	}
}

void	print_sphere(t_rt_obj_sphere sphere)
{
	printf("type: SPHERE\n");
	print_coordinates(sphere.coordinates);
	print_color(sphere.color);
	printf("diameter: %f\n", sphere.diameter);
}

void	print_plane(t_rt_obj_plane plane)
{
	printf("type: PLANE\n");
	print_coordinates(plane.coordinates);
	print_color(plane.color);
	print_orientation(plane.orientation);
}

void	print_cylinder(t_rt_obj_cylinder cylinder)
{
	printf("type: CYLINDER\n");
	print_coordinates(cylinder.coordinates);
	print_color(cylinder.color);
	print_orientation(cylinder.orientation);
	printf("diameter: %f\n", cylinder.diameter);
	printf("height: %f\n", cylinder.height);
}

void	print_objects(t_rt_obj_union *objects, int amount)
{
	int i = 0;
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

void	print_scene(t_rt_scene scene)
{
	printf("		*** MiniRT Scene ***\n");
	printf("resolution: %dx%d\n", scene.resolution.x, scene.resolution.y);
	print_ambient_light(scene.ambient_light);
	print_camera(scene.camera);
	print_spotlights(scene.spot_lights, scene.light_amount);
	print_objects(scene.objects, scene.object_amount);
}

int main( void )
{
	t_rt_scene	scene;

	init_rt(&scene);
	allocate_objects(&scene.objects, 3);
	allocate_spot_lights(&scene.spot_lights, 1);
	init_mock_rt(&scene);
//	scene.objects[0].cylinder.type = CYLINDER;
//	scene.objects[0].cylinder.height = 12.4;
//	scene.objects[1].sphere.type = SPHERE;
//	scene.objects[1].sphere.coordinates = (t_rt_vector){12.2, 32.3, 1.1};
//	scene.objects[2].plane.type = PLANE;
//	scene.objects[2].plane.color = (t_rt_color){12, 255, 102, 255};

	print_scene(scene);

	return 0;
}
