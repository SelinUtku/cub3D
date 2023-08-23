/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:11:16 by sutku             #+#    #+#             */
/*   Updated: 2023/08/23 00:56:41 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*delete_slash_n(char *str)
{
	int		len;
	char	*s;
	int		i;

	len = ft_strlen(str);
	s = malloc(sizeof(char) * len + 1);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	free(str);
	return (s);
}

void	add_line_to_map(t_game *game, char *str, int line)
{
	char	**temp;
	int		i;

	temp = game->map;
	game->map = malloc (sizeof(char *) * (line + 1));
	i = 0;
	while (temp && temp[i])
	{
		game->map[i] = temp[i];
		i++;
	}
	game->map[i] = str;
	game->map[i + 1] = NULL;
	free(temp);
}

void	check_walls_horizantal(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (ft_isspace(game->map[i][j]))
			j++;
		if (game->map[i][j] != '1')
		{
			ft_putendl_fd("Map is not surrounded by walls !", 2);
			exit (EXIT_FAILURE);
		}
		while (game->map[i][j] != '\0' && !ft_isspace(game->map[i][j]))
			j++;
		if (game->map[i][j - 1] != '1')
		{
			ft_putendl_fd("Map is not surrounded by walls !", 2);
			exit (EXIT_FAILURE);		
		}
		i++;
	}
}
void	check_walls_vertical(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (game->map[i])
	{
		i = 0;
		while (ft_isspace(game->map[i][j]))
			i++;
		if (game->map[i][j] != '1')
		{
			ft_putendl_fd("Map is not surrounded by walls !", 2);
			exit (EXIT_FAILURE);
		}
		j++;
	}
}

void	read_the_map(t_game *game, int fd)
{
	char	*str;
	int		i;
	int		line;

	game->map = malloc(sizeof(char *) * 2);
	str = get_next_line(fd);
	if (!str)
		exit (EXIT_FAILURE); // map is not given
	while (str)
	{
		i = 0;
		while (ft_isspace(str[i]))
			i++;
		if (str[i] != '\n' && str[i] != '\0')
		{
			line = 1;
			game->map[0] = delete_slash_n(str);
			game->map[1] = NULL;
			break ;
		}
		else
			free(str);
		str = get_next_line(fd);
	}
	while (str)
	{
		str = get_next_line(fd);
		if (str)
		{
			line++;
			add_line_to_map(game, delete_slash_n(str), line);
		}
	}
		// i = 0;
		// while (game->map[i])
		// {
		// 	printf("%s len = %d\n", game->map[i], ft_strlen(game->map[i]));
		// 	i++;
		// }
}

bool	check_valid_chracters(char c)
{
	if (c == '1' || c == '0')
		return (true);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
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

void	check_player_direction_exist(t_game *game)
{
	if (game->dir < 0 || game->dir > 3)
	{
		ft_putendl_fd("Player direction is not given !", 2);
		exit(EXIT_FAILURE);
	}
}

void	is_valid_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j] != '\0')
		{
			if (!check_valid_chracters(game->map[i][j]))
			{
				ft_putendl_fd("Invalid character !", 2);
				exit (EXIT_FAILURE);
			}
			find_player_direction(game, game->map[i][j]);
			j++;
		}
		i++;
	} 
	check_player_direction_exist(game);
	// check_walls_horizantal(game);
	// check_walls_vertical(game);
	// iceride bosluk varsayi kontrol edemiyorum
}
