#ifndef RT_DATA_TYPES_H
# define RT_DATA_TYPES_H

# include <stdbool.h>
# include <MLX42.h>
# include <rt_alias.h>

# define IMAGE_WIDTH 640

typedef enum e_err
{
	NO_ERR,
	MALLOC_F,
	OPEN_F,
	MLX_INIT_F,
	MLX_NEW_IMG_F,
	PARSE_F,
	INVALID_ARG,
	INVALID_FILE,
	INVALID_EXT,
	INVALID_OBJ,
	AMBIENT_SET,
	PIXEL_OOB,
	ERR_COUNTER
}		t_err;

typedef enum e_rt_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	NO_OBJECT
}		t_rt_obj_type;

typedef struct s_rt_color
{
	unsigned char 		r;
	unsigned char 		g;
	unsigned char 		b;
	unsigned char 		a;
}				t_rt_color;

typedef struct s_rt_color_aggregate
{
	t_rt_color_ratio	ratios;
	int					source_counter;
}			t_rt_color_aggregate;

typedef struct s_rt_scene_size
{
	int					width;
	int					height;
}			t_rt_scene_size;

typedef struct s_rt_vector
{
	float				x;
	float				y;
	float				z;
}				t_rt_vector;

typedef struct s_rt_obj_default
{
	t_rt_obj_type		type;
	t_rt_color			color;
}				t_rt_obj_default;

typedef struct s_rt_obj_sphere
{
	t_rt_obj_type		type;
	t_rt_color			color;
	t_rt_vector			coordinates;
	float				diameter;
}				t_rt_obj_sphere;

typedef struct s_rt_obj_plane
{
	t_rt_obj_type		type;
	t_rt_color			color;
	t_rt_vector			coordinates;
	t_rt_vector			orientation;
}				t_rt_obj_plane;

typedef struct s_rt_obj_cylinder
{
	t_rt_obj_type		type;
	t_rt_color			color;
	t_rt_vector			coordinates;
	t_rt_vector			orientation;
	float				diameter;
	float				height;
}				t_rt_obj_cylinder;

typedef union u_rt_obj_union
{
	t_rt_obj_default	def;
	t_rt_obj_sphere		sphere;
	t_rt_obj_plane		plane;
	t_rt_obj_cylinder	cylinder;
}				t_rt_obj_union;

typedef struct s_rt_ambient_light
{
	float				intensity;
	t_rt_color			color;
	bool				set;
}				t_rt_ambient_light;

typedef struct s_rt_spot_light
{
	t_rt_vector			coordinates;
	float				intensity;
	t_rt_color			color;
}				t_rt_spot_light;

typedef struct s_rt_camera
{
	t_rt_vector			coordinates;
	t_rt_vector			orientation;
	int					fov;
}				t_rt_camera;

typedef struct s_rt_viewport
{
	float				width;
	float				height;
	float				focal_length;
	t_rt_vector			coordinates;
	t_rt_vector			orientation;
}				t_rt_viewport;

typedef struct s_rt_scene
{
	t_rt_obj_union *	objects;
	t_rt_spot_light *	spot_lights;
	t_rt_ambient_light	ambient_light;
	t_rt_camera	*		cameras;
	t_rt_scene_size		size;
	t_rt_viewport		viewport;
	int					object_amount;
	int					light_amount;
	int					camera_amount;

	float				aspect_ratio;

	float				blue;
}				t_rt_scene;

typedef struct s_rt_mlx
{
	mlx_t				*mlx;
	mlx_image_t			*img;
	mlx_image_t 		*text;
	mlx_image_t 		*fps;
}		t_rt_mlx;

typedef struct s_minirt
{
	t_rt_mlx			mlx;
	t_rt_scene			scene;
}		t_mini_rt;

typedef struct s_quad_abc
{
	float				a;
	float				b;
	float				c;
}		t_quad_abc;

typedef	struct s_quad_result
{
	float				t1;
	float				t2;
}		t_quad_result;

typedef struct s_intersect_result
{
	float				closest_t;
	t_rt_obj_union		*closest_obj;
}				t_intersect_result;

typedef struct s_mult_pixel
{
	int					min_x;
	int					max_x;
	int					min_y;
	int					max_y;
}		t_mult_pixel;

typedef struct s_multipt
{
	t_mini_rt			*rt;
	int 				id;
}		t_pthr_arg;

#endif