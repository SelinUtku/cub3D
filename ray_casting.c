/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:27:11 by sutku             #+#    #+#             */
/*   Updated: 2023/08/26 04:43:50 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_wall_hit(t_game *game, t_coord *dda);

t_coord	dda(t_game *game)
{
	t_coord	dda;

	dda.map_x = (int)(game->player->x);
	dda.map_y = (int)(game->player->y);
	dda.step_x = 1;
	dda.step_y = 1;
	if (game->ray.x < 0)
	{
		dda.step_x = -1;
		dda.x = (game->player->x - dda.map_x) * game->ray.delta_x;
	}
	else
		dda.x = (dda.map_x + 1.0 - game->player->x) * game->ray.delta_x;
	if (game->ray.y < 0)
	{
		dda.step_y = -1;
		dda.y = (game->player->y - dda.map_y) * game->ray.delta_y;
	}
	else
		dda.y = (dda.map_y + 1.0 - game->player->y) * game->ray.delta_y;
	check_wall_hit(game, &dda);
	return (dda);
}

void	check_wall_hit(t_game *game, t_coord *dda)
{
	while (true)
	{
		if (dda->x < dda->y)
		{
			dda->x += game->ray.delta_x;
			dda->map_x += dda->step_x;
			if (game->ray.x > 0)
				game->wall.side = EA;
			else
				game->wall.side = WE;
		}
		else
		{
			dda->y += game->ray.delta_y;
			dda->map_y += dda->step_y;
			if (game->ray.y > 0)
				game->wall.side = SO;
			else
				game->wall.side = NO;
		}
		if (game->map.map[dda->map_y][dda->map_x] == '1')
			break ;
	}
}
