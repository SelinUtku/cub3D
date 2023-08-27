/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:33:18 by Cutku             #+#    #+#             */
/*   Updated: 2023/08/26 22:51:10 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	keypress_right_rotate(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rot;
	double	sin_rot;

	old_dir_x = game->player.dir_x;
	cos_rot = cos(ROT_SPEED);
	sin_rot = sin(ROT_SPEED);
	game->player.dir_x = game->player.dir_x * cos_rot \
	- game->player.dir_y * sin_rot;
	game->player.dir_y = old_dir_x * sin_rot + game->player.dir_y * cos_rot;
	old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos_rot - game->plane_y * sin_rot;
	game->plane_y = old_plane_x * sin_rot + game->plane_y * cos_rot;
	draw_map(game);
}

void	keypress_left_rotate(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rot;
	double	sin_rot;

	old_dir_x = game->player.dir_x;
	cos_rot = cos(-ROT_SPEED);
	sin_rot = sin(-ROT_SPEED);
	game->player.dir_x = game->player.dir_x * cos_rot \
	- game->player.dir_y * sin_rot;
	game->player.dir_y = old_dir_x * sin_rot + game->player.dir_y * cos_rot;
	old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos_rot - game->plane_y * sin_rot;
	game->plane_y = old_plane_x * sin_rot + game->plane_y * cos_rot;
	draw_map(game);
}
