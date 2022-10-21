#ifndef RT_DATATYPES_H
# define RT_DATATYPES_H

# define RESOLUTION_X 768
# define RESOLUTION_Y 768

typedef enum e_err
{
	NO_ERR,
	MALLOC_F,
	MLX_INIT_F,
	MLX_NEW_IMG_F,
	PARSE_F,
	INVALID_ARG,
	INVALID_FILE,
	INVALID_OBJ,
	PIXEL_OOB
}		t_err;

typedef enum e_rt_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER
}		t_rt_obj_type;

typedef struct s_rt_color
{
	unsigned char 	r;
	unsigned char 	g;
	unsigned char 	b;
	unsigned char 	a;
}			t_rt_color;

typedef struct s_rt_resolution
{
	unsigned int	x;
	unsigned int	y;
}		t_rt_resolution;

typedef struct s_rt_vector
{
	double	x;
	double	y;
	double	z;
}			t_rt_vector;

typedef struct s_rt_obj_default
{
	t_rt_obj_type		type;
}		t_rt_obj_default;

typedef struct s_rt_obj_sphere
{
	t_rt_obj_type		type;
	t_rt_vector			coordinates;
	t_rt_color			color;
	double				diameter;
}		t_rt_obj_sphere;

typedef struct s_rt_obj_plane
{
	t_rt_obj_type		type;
	t_rt_vector			coordinates;
	t_rt_color			color;
	t_rt_vector			orientation;
}		t_rt_obj_plane;

typedef struct s_rt_obj_cylinder
{
	t_rt_obj_type		type;
	t_rt_vector			coordinates;
	t_rt_color			color;
	t_rt_vector			orientation;
	double				diameter;
	double				height;
}		t_rt_obj_cylinder;

typedef union u_rt_obj_union
{
	t_rt_obj_default	def;
	t_rt_obj_sphere		sphere;
	t_rt_obj_plane		plane;
	t_rt_obj_cylinder	cylinder;
}		t_rt_obj_union;

typedef struct s_rt_ambient_light
{
	double				intensity;
	t_rt_color			color;
}		t_rt_ambient_light;

typedef struct s_rt_spot_light
{
	double				intensity;
	t_rt_color			color;
	t_rt_vector			coordinates;
}		t_rt_spot_light;

typedef struct s_rt_camera
{
	t_rt_vector			coordinates;
	t_rt_vector			orientation;
	unsigned int		fov;
}		t_rt_camera;

typedef struct s_rt_scene
{
	t_rt_obj_union *	objects;
	t_rt_ambient_light	ambient_light;
	t_rt_spot_light *	spot_lights;
	t_rt_camera			camera;
	t_rt_resolution		resolution;
	int					object_amount;
	int					light_amount;

}		t_rt_scene;

#endif
