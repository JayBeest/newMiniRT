#ifndef RT_DATA_TYPES_H
# define RT_DATA_TYPES_H

# include <stdbool.h>
# include <MLX42.h>

# define IMAGE_WIDTH 512
# define EPSILON 1e-6

# define CAMERA_MOVE_STEP 0.1
# define CAMERA_ZOOM_FACTOR 1.5
# define FPS 30
# define MULTI_SAMPLE 0

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
}			t_err;

typedef enum e_rt_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	NO_OBJECT
}			t_rt_obj_type;

typedef struct s_rt_vector
{
	double				x;
	double				y;
	double				z;
}			t_rt_vector;

typedef t_rt_vector t_rt_point;
typedef t_rt_vector t_rt_color_ratio;

typedef struct s_rt_resolution
{
	int					x;
	int					y;
}			t_rt_resolution;

typedef t_rt_resolution t_rt_canvas_size;

typedef struct s_rt_color
{
	unsigned char 		r;
	unsigned char 		g;
	unsigned char 		b;
	unsigned char 		a;
}			t_rt_color;

typedef struct s_rt_color_intensity
{
	double				r;
	double				g;
	double				b;
	double				a;
}			t_rt_color_intensity;

typedef struct s_rt_color_aggregate
{
	t_rt_color_intensity	intensity;
	unsigned long		source_counter;
}			t_rt_color_aggregate;


typedef struct s_rt_obj_default
{
	t_rt_obj_type		type;
	t_rt_color			color;
	t_rt_point			coordinates;
	float				reflective;
	float				metal_fuzz;
	int					specular;
}			t_rt_obj_default;

typedef struct s_rt_obj_sphere
{
	t_rt_obj_type		type;
	t_rt_color			color;
	t_rt_point			coordinates;
	float				reflective;
	float				metal_fuzz;
	int					specular;
	double				radius;
}			t_rt_obj_sphere;

typedef struct s_rt_obj_plane
{
	t_rt_obj_type		type;
	t_rt_color			color;
	t_rt_point			coordinates;
	float				reflective;
	float				metal_fuzz;
	int					specular;
	t_rt_vector			orientation;
}			t_rt_obj_plane;

typedef struct s_rt_obj_cylinder
{
	t_rt_obj_type		type;
	t_rt_color			color;
	t_rt_point			coordinates;
	float				reflective;
	float				metal_fuzz;
	int					specular;
	t_rt_vector			orientation;
	double				radius;
	double				height;
}			t_rt_obj_cylinder;

typedef union u_rt_obj_union
{
	t_rt_obj_default	def;
	t_rt_obj_sphere		sphere;
	t_rt_obj_plane		plane;
	t_rt_obj_cylinder	cylinder;
}			t_rt_obj_union;

typedef struct s_rt_ambient_light
{
	double				intensity;
	t_rt_color			color;
	bool				set;
}			t_rt_ambient_light;

typedef struct s_rt_spot_light
{
	t_rt_point			coordinates;
	double				intensity;
	t_rt_color			color;
	bool				toggle;
}			t_rt_spot_light;

typedef struct s_rt_camera
{
	t_rt_point			coordinates;
	t_rt_vector			orientation;
	int					fov;
	int					zoom_level;
}			t_rt_camera;

typedef struct s_rt_viewport
{
	double				width;
	double				height;
	double				focal_length;
	t_rt_point			coordinates;
	t_rt_vector			orientation;
//	t_rt_resolution		size;
	double				x_ratio;
	double				y_ratio;
}			t_rt_viewport;

typedef struct s_rt_scene
{
	t_rt_obj_union *	objects;
	t_rt_spot_light *	spot_lights;
	t_rt_ambient_light	ambient_light;
	t_rt_camera	*		cameras;
	t_rt_resolution		canvas;
	t_rt_viewport		viewport;
	t_rt_color_ratio	bg_color;
	int					object_amount;
	int					light_amount;
	int					camera_amount;

	double				aspect_ratio;

//	double				red;
//	double				green;
//	double				blue;
	int					recursion_depth;
	int					msaa;
	int					hud;
	bool				bare_toggle;
}			t_rt_scene;

typedef struct s_rt_mlx
{
	mlx_t				*mlx;
	mlx_image_t			*img;
	mlx_image_t 		*text;
	mlx_image_t 		*fps;
	mlx_image_t 		*rgb;
	mlx_image_t			*ref;
	mlx_image_t			*msaa;
}			t_rt_mlx;

typedef struct s_mini_rt
{
	t_rt_mlx			mlx;
	t_rt_scene			scene;
}			t_mini_rt;

#endif
