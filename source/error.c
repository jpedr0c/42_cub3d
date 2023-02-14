#include "../include/cub3d.h"

/* return perror with custom error code */
int	perror_ret(const char *s, int ret_code)
{
	if (s != NULL)
		perror(s);
	else if (NAME != NULL)
		perror(NAME);
	else
		perror("error");
	return (ret_code);
}

/* return custom error with custom error code */
int	error_ret(const char *s, int ret_code)
{
	if (NAME != NULL)
	{
		write(STDERR_FILENO, NAME, ft_strlen(NAME));
	}
	else
		write(STDERR_FILENO, "error", 5);
	write(STDERR_FILENO, ": ", 2);
	if (s)
		write(STDERR_FILENO, s, ft_strlen(s));
	exit(ret_code);
	return (ret_code);
}

int	print_error(char *str, char *color, int value_return)
{
	char	*reset_color;

	reset_color = DEFAULT;
	printf("%sError\n", color);
	printf("%s%s\n", str, reset_color);
	return (value_return);
}

void	print_error_exit(char *str, char *color, int exit_code)
{
	char *reset_color;

	reset_color = DEFAULT;
	printf("%sError\n", color);
	printf("%s%s\n", str, reset_color);
	if (exit_code == 1)
		exit(1);
}