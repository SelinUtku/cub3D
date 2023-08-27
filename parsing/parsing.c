/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:19:07 by sutku             #+#    #+#             */
/*   Updated: 2023/08/27 01:44:48 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	open_map_file(t_game *game, int fd)
{
	char	*str;

	str = parse_the_elements(game, fd);
	free_elements(game);
	read_the_map(game, fd, str);
	is_valid_map(game);
	close(fd);
}

char	*parse_the_elements(t_game *game, int fd)
{
	int		i;
	char	*str;

	str = get_next_line(fd);
	while (str != NULL && game->num_elements < 6)
	{
		i = 0;
		skip_spaces(str, &i);
		if (str[i] != '\n')
		{
			game->elements[game->num_elements] = delete_slash_n(str);
			game->num_elements++;
		}
		else
			free(str);
		str = get_next_line(fd);
	}
	game->elements[game->num_elements] = NULL;
	if (game->num_elements != 6)
	{
		free_elements(game);
		error_handler(game, W_FILE);
	}
	check_validity_of_elements(game);
	return (str);
}

bool	check_number_of_elements(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->wall.num_texture[i] == 0)
		{
			ft_putendl_fd(MISS_TEXT, 2);
			return (false);
		}
		i++;
	}
	if (game->f != 1)
		return (ft_putendl_fd(W_FLOOR, 2), false);
	if (game->c != 1)
		return (ft_putendl_fd(W_CEILING, 2), false);
	return (true);
}

void	check_validity_of_elements(t_game *game)
{
	int		id;

	id = 0;
	while (game->elements[id])
	{
		direction_or_color(game, game->elements[id]);
		id++;
	}
	if (check_number_of_elements(game) == false)
	{
		free_elements(game);
		exit (EXIT_FAILURE);
	}
}

void	direction_or_color(t_game *game, char *str)
{
	int	start;
	int	len;

	start = 0;
	skip_spaces(str, &start);
	len = 0;
	while (str[len + start] != ' ' && str[len + start] != '\0')
		len++;
	if (len == 2)
		is_valid_direction(game, str + start);
	else if (len == 1 && (str[start] == 'F' || str[start] == 'C'))
		floor_or_ceiling(game, str + start);
	else
	{
		free_elements(game);
		error_handler(game, W_ELEMENT);
	}
}
