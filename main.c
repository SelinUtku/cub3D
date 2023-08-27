/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:19:17 by sutku             #+#    #+#             */
/*   Updated: 2023/08/27 04:04:34 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_key_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		keypress_up(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		keypress_down(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		keypress_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		keypress_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		keypress_left_rotate(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		keypress_right_rotate(game);
}

int	check_argv(char **argv)
{
	int	len;
	int	fd;

	len = ft_strlen(argv[1]);
	if (len > 4 && (ft_strncmp(argv[1] + len - 4, ".cub", 4) == 0))
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			ft_putendl_fd(FILE, 2);
			exit (EXIT_FAILURE);
		}
	}
	else
	{
		ft_putstr_fd("Not .cub file!\n", 2);
		exit (EXIT_FAILURE);
	}
	return (fd);
}

void	leaks(void)
{
	system("leaks cub3D");
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (ft_putendl_fd("No argument !", 2), EXIT_FAILURE);
	atexit(&leaks);
	check_argv(argv);
	init_struct(&game);
	if (mlx_image_to_window(game.mlx, game.img, 0, 0) == -1)
	{
		mlx_close_window(game.mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	open_map_file(&game, check_argv(argv));
	player_position(&game);
	init_player_direction(&game);
	draw_map(&game);
	mlx_loop_hook(game.mlx, ft_key_hook, &game);
	mlx_loop(game.mlx);
	free_all(&game);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
