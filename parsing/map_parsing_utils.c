/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 01:42:44 by sutku             #+#    #+#             */
/*   Updated: 2023/08/27 01:43:26 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	check_valid_chracters(t_game *game, char c)
{
	static int	num_player = 0;

	if (c == '1' || c == '0')
		return (true);
	else if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
	{
		num_player++;
		if (num_player > 1)
			error_handler(game, MULTI_DIR);
		find_player_direction(game, c);
		return (true);
	}
	else if (c == ' ')
		return (true);
	else
		return (false);
}

void	find_player_direction(t_game *game, char c)
{
	if (c == 'N')
		game->dir = NO;
	else if (c == 'S')
		game->dir = SO;
	else if (c == 'W')
		game->dir = WE;
	else if (c == 'E')
		game->dir = EA;
}
