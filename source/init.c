#include "../include/cub3d.h"

int	initialize_vars(t_vars *vars)
{
	vars->frame = -1;
	vars->keys.w = 0;
	vars->keys.s = 0;
	vars->keys.a = 0;
	vars->keys.d = 0;
	vars->keys.right_arrow = 0;
	vars->keys.left_arrow = 0;
	vars->keys.shift = 0;
	player_init(vars);
	vars->ray = (t_ray *)malloc(sizeof(t_ray));
	if (vars->ray == NULL)
		print_error_exit("Could not allocate\n", REDN, 1);
	return (0);
}

int	initialise_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->img.addr = mlx_get_data_addr(vars->img.img,
										&vars->img.bpp,
										&vars->img.line_len,
										&vars->img.endian);
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "cub3D");
	if (init_texture(vars) != 0)
		return (1);
	return (0);
}

int	close_window(t_vars *vars)
{
	free_all(vars);
	ft_putstr_fd("Quit\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
	return (0);
}

int	game_loop(t_vars *vars)
{
	if (++vars->frame >= 60)
		vars->frame = 0;
	handle_keypress(vars);
	draw(vars);
	return (0);
}

int	init_game(t_vars *vars)
{
	if (initialize_vars(vars))
	{
		free_all(vars);
		print_error_exit("Unable to allocate variables", REDN, 1);
	}
	if (initialise_mlx(vars) != 0)
		return (1);
	mlx_hook(vars->win, 2, (1L << 0), key_press_hook, vars);
	mlx_hook(vars->win, 3, (1L << 1), key_release_hook, vars);
	mlx_hook(vars->win, 17, (1L << 17), close_window, vars);
	mlx_loop_hook(vars->mlx, game_loop, vars);
	mlx_loop(vars->mlx);
	free_all(vars);
	return (0);
}
