/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 01:48:12 by sutku             #+#    #+#             */
/*   Updated: 2023/08/27 04:03:09 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_direction(t_game *game)
{
	if (game->dir == WE || game->dir == EA)
	{
		game->player.dir_y = 0.0;
		game->plane_x = 0.0;
		game->player.dir_x = -1.0;
		game->plane_y = -0.66;
		if (game->dir == EA)
		{
			game->player.dir_x = 1.0;
			game->plane_y = 0.66;
		}
	}
	else if (game->dir == NO || game->dir == SO)
	{
		game->player.dir_x = 0.0;
		game->plane_y = 0.0;
		game->player.dir_y = -1.0;
		game->plane_x = 0.66;
		if (game->dir == SO)
		{
			game->player.dir_y = 1.0;
			game->plane_x = -0.66;
		}
	}
	keypress_right_rotate(game);
}

void	init_struct(t_game *game)
{
	game->mlx = NULL;
	game->wall.num_texture[NO] = 0;
	game->wall.num_texture[SO] = 0;
	game->wall.num_texture[WE] = 0;
	game->wall.num_texture[EA] = 0;
	game->map.map = NULL;
	game->num_elements = 0;
	game->f = 0;
	game->c = 0;
	game->dir = NON;
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", false);
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void	player_position(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < game->map.width)
		{
			if (game->map.map[y][x] == 'N' || game->map.map[y][x] == 'E' \
			|| game->map.map[y][x] == 'S' || game->map.map[y][x] == 'W')
			{
				game->player.x = (double)x;
				game->player.y = (double)y;
				return ;
			}
		}
	}
}
