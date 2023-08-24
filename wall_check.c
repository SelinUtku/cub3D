/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 01:17:35 by sutku             #+#    #+#             */
/*   Updated: 2023/08/24 01:28:44 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	left_wall_check(t_game *game)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		flag = 0;
		while (game->map.map[i][j])
		{
			if (ft_isspace(game->map.map[i][j]))
				flag = 0;
			else if (game->map.map[i][j] == '1')
				flag = 1;
			else if (game->map.map[i][j] != '1' && flag == 0)
			{
				ft_putendl_fd("Map left is not surrounded by walls !", 2);
				exit (EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
}

void	right_wall_check(t_game *game)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	while (game->map.map[i])
	{
		j = game->map.width - 1;
		flag = 0;
		while (j > -1)
		{
			if (ft_isspace(game->map.map[i][j]))
				flag = 0;
			else if (game->map.map[i][j] == '1')
				flag = 1;
			else if (game->map.map[i][j] != '1' && flag == 0)
			{
				ft_putendl_fd("Map right is not surrounded by walls !", 2);
				exit (EXIT_FAILURE);
			}
			j--;
		}
		i++;
	}
}

void	top_wall_check(t_game *game)
{
	int	i;
	int	j;
	int	flag;

	j = 0;
	while (j < game->map.width)
	{
		i = 0;
		flag = 0;
		while (game->map.map[i])
		{
			if (ft_isspace(game->map.map[i][j]))
				flag = 0;
			else if (game->map.map[i][j] == '1')
				flag = 1;
			else if (game->map.map[i][j] != '1' && flag == 0)
			{
				ft_putendl_fd("Map top is not surrounded by walls !", 2);
				exit (EXIT_FAILURE);
			}
			i++;
		}
		j++;
	}
}

void	bottom_wall_check(t_game *game)
{
	int	i;
	int	j;
	int	flag;

	j = 0;
	while (j < game->map.width)
	{
		i = game->map.height - 1;
		flag = 0;
		while (i > -1)
		{
			if (ft_isspace(game->map.map[i][j]))
				flag = 0;
			else if (game->map.map[i][j] == '1')
				flag = 1;
			else if (game->map.map[i][j] != '1' && flag == 0)
			{
				ft_putendl_fd("Map bottom is not surrounded by walls !", 2);
				exit (EXIT_FAILURE);
			}
			i--;
		}
		j++;
	}
}
