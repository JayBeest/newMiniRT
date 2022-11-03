#ifndef RT_HOOK_H
# define RT_HOOK_H

void	rt_resize_hook(int x, int y, void *arg);
void	rt_mouse_hook(enum mouse_key e_key, enum action e_action, \
		enum modifier_key e_modifier, void *arg);
void	rt_hook(void *arg);

#endif
