/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:27:11 by sutku             #+#    #+#             */
/*   Updated: 2023/08/24 23:51:46 by sutku            ###   ########.fr       */
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
	if (game->ray.x * dda.step_x < 0)
	{
		dda.step_x = -dda.step_x;
		dda.x = (game->player->x - dda.map_x) * game->ray.delta_x;
	}
	else
		dda.x = (dda.map_x + 1.0 - game->player->x) * game->ray.delta_x;
	if (game->ray.y * dda.step_y < 0)
	{
		dda.step_y = -dda.step_y;
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
				game->wall.side = 0;
			else
				game->wall.side = 2;
		}
		else
		{
			dda->y += game->ray.delta_y;
			dda->map_y += dda->step_y;
			if (game->ray.y > 0)
				game->wall.side = 1;
			else
				game->wall.side = 3;
		}
		if (map2[dda->map_x][dda->map_y] == 1)
			break ;
	}
}
