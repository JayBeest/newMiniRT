/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_hook.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcorneli <jcorneli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:22:53 by jcorneli      #+#    #+#                 */
/*   Updated: 2022/11/03 02:22:54 by jcorneli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <MLX42.h>
#include <rt_datatypes.h>
#include <rt_render.h>
#include <rt_controls.h>
#include <rt_time.h>

#include <stdio.h>
#include <rt_scene_printer.h>

void	rt_resize_hook(int x, int y, void *arg)
{
	t_mini_rt			*mini_rt;
	t_mlx			*mlx;

	mini_rt = arg;
	mlx = &mini_rt->mlx;
	mini_rt->scene.canvas.x = x;
	mini_rt->scene.canvas.y = y;
	mini_rt->scene.aspect_ratio = (double)x / y;
	set_viewport(&mini_rt->scene, mini_rt->scene.aspect_ratio);
	mlx_resize_image(mlx->img, x, y);
	render_scene(mlx, &mini_rt->scene);
}

void	rt_mouse_hook(enum mouse_key e_key, enum action e_action, enum modifier_key e_modifier, void *arg)
{
	t_mini_rt			*mini_rt;
	t_mlx			*mlx;
	t_resolution		mouse;

	mini_rt = arg;
	mlx = &mini_rt->mlx;
	if (e_key == MLX_MOUSE_BUTTON_LEFT && e_action == MLX_PRESS)
	{
		mlx_get_mouse_pos(mlx->mlx, &mouse.x, &mouse.y);
		double	converted_x;
		double	converted_y;
		converted_x = (double)(mini_rt->scene.canvas.x / -2 + mouse.x) / (mini_rt->scene.canvas.x / 2);
		converted_y = (double)(mini_rt->scene.canvas.y / -2 + mouse.y) / (mini_rt->scene.canvas.y / -2);
		int diagonal = sqrt(mini_rt->scene.canvas.x * mini_rt->scene.canvas.x + mini_rt->scene.canvas.y * mini_rt->scene.canvas.y);
		t_resolution fov;
		fov.x = (double)mini_rt->scene.canvas.x / diagonal * mini_rt->scene.cameras[mini_rt->scene.cc].fov / mini_rt->scene.cameras[mini_rt->scene.cc].zoom_level;
		fov.y = (double)mini_rt->scene.canvas.y / diagonal * mini_rt->scene.cameras[mini_rt->scene.cc].fov / mini_rt->scene.cameras[mini_rt->scene.cc].zoom_level;
//		printf("mouse - x: %d  y: %d\n", mouse.x, mouse.y);
//		printf("  - converted - x: %f  y: %f\n", converted_x, converted_y);
//		printf("  - fov - x: %d  y: %d\n", fov.x, fov.y);
		mini_rt->scene.cameras[mini_rt->scene.cc].orientation.x += converted_x * fov.x / 360 / 2 ;
		if (mini_rt->scene.cameras[mini_rt->scene.cc].orientation.x > 1)
			mini_rt->scene.cameras[mini_rt->scene.cc].orientation.x -= 1;

		mini_rt->scene.cameras[mini_rt->scene.cc].orientation.y += -converted_y * fov.y / 360 / 2 ;
		if (mini_rt->scene.cameras[mini_rt->scene.cc].orientation.y > 1)
			mini_rt->scene.cameras[mini_rt->scene.cc].orientation.y -= 1;
//		printf("camera.x = %f\ncamera.y = %f\n", mini_rt->scene.camera[mini_rt->scene.cc].orientation.x, mini_rt->scene.camera[mini_rt->scene.cc].orientation.y);
		render_scene(mlx, &mini_rt->scene);
	}
	(void)e_modifier;
}

void	rt_hook(void *arg)
{
	static size_t		mlx_loop_counter = 0;
	static t_time_stamp	previous;
	t_time_stamp		current_frame_start = set_time();

	if (mlx_loop_counter == 0)
		previous = current_frame_start;
	mlx_loop_counter++;
	rt_controls(&((t_mini_rt *)arg)->mlx, &((t_mini_rt *)arg)->scene);
	t_nano	took = nano_passed(current_frame_start);
	if (mlx_loop_counter % ((t_mini_rt *)arg)->scene.fps == 0)
	{
		float sixty_took = (float)nano_passed(previous) / 1000;
		printf("-------> %d mlx_frames: %.3f ms (%.0f fps)\n", ((t_mini_rt *)arg)->scene.fps, sixty_took, (double)((t_mini_rt *)arg)->scene.fps / (sixty_took / 1000));
		previous = current_frame_start;
	}
	if (took < 1000000 / ((t_mini_rt *)arg)->scene.fps)
		rt_sleep_nano(1000000 / ((t_mini_rt *)arg)->scene.fps - took - 1000);
}
