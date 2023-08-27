/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 01:41:19 by sutku             #+#    #+#             */
/*   Updated: 2023/08/27 01:43:30 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	add_line_to_map(t_game *game, char *str, int line)
{
	char	**temp;
	int		i;

	temp = game->map.map;
	game->map.map = malloc (sizeof(char *) * (line + 1));
	i = 0;
	while (temp && temp[i])
	{
		game->map.map[i] = temp[i];
		i++;
	}
	game->map.map[i] = str;
	game->map.map[i + 1] = NULL;
	free(temp);
}

void	read_the_map(t_game *game, int fd, char *first_str)
{
	char	*str;
	int		i;
	int		line;

	str = first_str;
	if (!str)
		error_handler(game, NO_MAP);
	while (str)
	{
		i = 0;
		skip_spaces(str, &i);
		if (str[i] != '\n' && str[i] != '\0')
			break ;
		else
			free(str);
		str = get_next_line(fd);
	}
	line = 0;
	while (str)
	{
		line++;
		add_line_to_map(game, delete_slash_n(str), line);
		str = get_next_line(fd);
	}
}

void	first_check_map(t_game *game)
{
	int	max_width;
	int	i;
	int	j;

	max_width = -1;
	i = 0;
	while (game->map.map[i] != NULL)
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (check_valid_chracters(game, game->map.map[i][j]) == false)
				error_handler(game, INV_CHAR);
			j++;
		}
		if (j == 0)
			error_handler(game, EMPTY_LINE);
		else if (j > max_width)
			max_width = j;
		i++;
	}
	if (game->dir == NON)
		error_handler(game, NO_PLAY_DIR);
	game->map.height = i;
	game->map.width = max_width;
}

void	adjust_map(t_game *game)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		temp = malloc(game->map.width + 1);
		while (game->map.map[i][j] != '\0')
		{
			temp[j] = game->map.map[i][j];
			j++;
		}
		while (j < game->map.width)
		{
			temp[j] = ' ';
			j++;
		}
		temp[j] = '\0';
		free(game->map.map[i]);
		game->map.map[i] = temp;
		i++;
	}
}

void	is_valid_map(t_game *game)
{
	first_check_map(game);
	adjust_map(game);
	left_wall_check(game);
	right_wall_check(game);
	top_wall_check(game);
	bottom_wall_check(game);
}
