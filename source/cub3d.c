#include "../include/cub3d.h"

int	main(int argc, char *argv[])
{
	t_vars	*vars;

	if (argc != 2)
		return (error_ret("Usage: ./cub3D map.cub\n", 1));
	vars = (t_vars *)malloc(sizeof(t_vars));
	vars->map = (t_map *)malloc(sizeof(t_map));
	ft_putstr_fd("Parsing...\n", STDOUT_FILENO);
	if (is_valid_args(argc, argv) != 0)
		return (1);
	init_map(vars->map);
	if (read_map(vars->map, argv[1]) != 0)
		return (1);
	if (init_parser(vars->map, argv[1]) != 0)
		return (1);
	ft_putstr_fd("Starting minilibx...\n", STDOUT_FILENO);
	if (init_game(vars) != 0)
		return (EXIT_FAILURE);
	ft_putstr_fd("Quit\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
