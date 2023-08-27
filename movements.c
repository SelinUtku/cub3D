/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 22:07:35 by sutku             #+#    #+#             */
/*   Updated: 2023/08/27 03:31:18 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	keypress_up(t_game *game)
{
	double	delta_x;
	double	delta_y;

	delta_x = game->player.dir_x * MOVE_SPEED;
	delta_y = game->player.dir_y * MOVE_SPEED;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		if (game->map.map[(int)(game->player.y)] \
		[(int)(game->player.x + delta_x)] == '0')
			game->player.x += delta_x;
		if (game->map.map[(int)(game->player.y + delta_y)] \
		[(int)(game->player.x)] == '0')
			game->player.y += delta_y;
		draw_map(game);
	}
}

void	keypress_down(t_game *game)
{
	double	delta_x;
	double	delta_y;

	delta_x = game->player.dir_x * MOVE_SPEED;
	delta_y = game->player.dir_y * MOVE_SPEED;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		if (game->map.map[(int)(game->player.y)] \
		[(int)(game->player.x - delta_x)] == '0')
			game->player.x -= delta_x;
		if (game->map.map[(int)(game->player.y - delta_y)] \
		[(int)game->player.x] == '0')
			game->player.y -= delta_y;
		draw_map(game);
	}
}

void	keypress_left(t_game *game)
{
	double	delta_x;
	double	delta_y;

	delta_x = game->player.dir_y * MOVE_SPEED;
	delta_y = game->player.dir_x * MOVE_SPEED;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		if (game->map.map[(int)game->player.y] \
		[(int)(game->player.x + delta_x)] == '0')
			game->player.x += delta_x;
		if (game->map.map[(int)(game->player.y - delta_y)] \
		[(int)game->player.x] == '0')
			game->player.y -= delta_y;
		draw_map(game);
	}
}

void	keypress_right(t_game *game)
{
	double	delta_x;
	double	delta_y;

	delta_x = game->player.dir_y * MOVE_SPEED;
	delta_y = game->player.dir_x * MOVE_SPEED;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		if (game->map.map[(int)game->player.y] \
		[(int)(game->player.x - delta_x)] == '0')
			game->player.x -= delta_x;
		if (game->map.map[(int)(game->player.y + delta_y)] \
		[(int)game->player.x] == '0')
			game->player.y += delta_y;
		draw_map(game);
	}
}
