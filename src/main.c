#include <stdlib.h>
#include <datatypes.h>
#include <alloc.h>

#include <stdio.h>
#include <string.h>

void	init_rt(t_rt_scene * scene)
{
	bzero(scene, sizeof(t_rt_scene));
	scene->resolution.x = RESOLUTION_X;
	scene->resolution.y = RESOLUTION_Y;
}

int main( void )
{
	t_rt_scene	scene;

	init_rt(&scene);
	allocate_objects(&scene.objects, 3);
	scene.objects[0].cylinder.type = CYLINDER;
	scene.objects[0].cylinder.height = 12.4;
	scene.objects[1].sphere.type = SPHERE;
	scene.objects[1].sphere.coordinates = (t_rt_vector){12.2, 32.3, 1.1};
	scene.objects[2].plane.type = PLANE;
	scene.objects[2].plane.color = (t_rt_color){12, 255, 102, 255};

	for (int i = 0; i < 3; i++)
	{
		if (scene.objects[i].def.type == CYLINDER)
		{
			printf("Cylinder found, height: %f\n", scene.objects[i].cylinder.height);
		}
		else if (scene.objects[i].def.type == SPHERE)
		{
			printf("Sphere found, y-coordinate: %f\n", scene.objects[i].sphere.coordinates.y);
		}
		else if (scene.objects[i].def.type == PLANE)
		{
			printf("Plane found, b-color: %d\n", scene.objects[i].plane.color.b);
		}
	}
	return 0;
}
