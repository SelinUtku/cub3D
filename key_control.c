/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:33:18 by Cutku             #+#    #+#             */
/*   Updated: 2023/08/19 20:35:20 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int map3[18][24] = {
				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1},
				{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1},
				{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

void	keypress_up_down(t_game *game)
{
	double	delta_x;
	double	delta_y;

	delta_x = game->player->dir_x * MOVE_SPEED;
	delta_y = game->player->dir_y * MOVE_SPEED;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		if (map3[(int)(game->player->x + delta_x)][(int)game->player->y] != 1)
			game->player->x += delta_x;
		if (map3[(int)game->player->x][(int)(game->player->y + delta_y)] != 1)
			game->player->y += delta_y;
		draw_map(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		if (map3[(int)(game->player->x - delta_x)][(int)(game->player->y)] != 1)
			game->player->x -= delta_x;
		if (map3[(int)game->player->x][(int)(game->player->y - delta_y)] != 1)
			game->player->y -= delta_y;
		draw_map(game);
	}
}

void	keypress_left_right(t_game *game)
{
	double	delta_x;
	double	delta_y;

	delta_x = game->player->dir_y * MOVE_SPEED;
	delta_y = game->player->dir_x * MOVE_SPEED;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		if (map3[(int)(game->player->x + delta_x)][(int)game->player->y] != 1) 
			game->player->x += delta_x;
		if (map3[(int)game->player->x][(int)(game->player->y - delta_y)] != 1)
			game->player->y -= delta_y;
		draw_map(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		if (map3[(int)(game->player->x - delta_x)][(int)game->player->y] != 1) 
			game->player->x -= delta_x;
		if (map3[(int)game->player->x][(int)(game->player->y + delta_y)] != 1)
			game->player->y += delta_y;
		draw_map(game);
	}
}

void	keypress_left_rotate(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rot;
	double	sin_rot;

	old_dir_x = game->player->dir_x;
	cos_rot = cos(ROT_SPEED);
	sin_rot = sin(ROT_SPEED);
	game->player->dir_x = game->player->dir_x * cos_rot - game->player->dir_y * sin_rot;
	game->player->dir_y = old_dir_x * sin_rot + game->player->dir_y * cos_rot;
	old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos_rot - game->plane_y * sin_rot;
	game->plane_y = old_plane_x * sin_rot + game->plane_y * cos_rot;
	draw_map(game);
}

void	keypress_right_rotate(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rot;
	double	sin_rot;

	old_dir_x = game->player->dir_x;
	cos_rot = cos(-ROT_SPEED);
	sin_rot = sin(-ROT_SPEED);
	game->player->dir_x = game->player->dir_x * cos_rot - game->player->dir_y * sin_rot;
	game->player->dir_y = old_dir_x * sin_rot + game->player->dir_y * cos_rot;
	old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos_rot - game->plane_y * sin_rot;
	game->plane_y = old_plane_x * sin_rot + game->plane_y * cos_rot;
	draw_map(game);
}

void	ft_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) || mlx_is_key_down(game->mlx, MLX_KEY_S))
		keypress_up_down(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A) || mlx_is_key_down(game->mlx, MLX_KEY_D))
		keypress_left_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		keypress_left_rotate(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		keypress_right_rotate(game);
}
