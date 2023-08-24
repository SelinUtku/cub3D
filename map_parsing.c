/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:11:16 by sutku             #+#    #+#             */
/*   Updated: 2023/08/24 05:10:33 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	adjust_map(t_game *game);
void	first_check_map(t_game *game);
void	print_map(t_game *game);
bool	check_valid_chracters(t_game *game, char c);
void	find_player_direction(t_game *game, char c);

char	*delete_slash_n(char *str)
{
	char	*temp;

	temp = ft_strrchr(str, '\n');
	if (temp)
		*temp = '\0';
	return (str);
}
      
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

void	read_the_map(t_game *game, int fd)
{
	char	*str;
	int		i;
	int		line;

	str = get_next_line(fd);
	if (!str)
		exit (EXIT_FAILURE);
	while (str)
	{
		i = 0;
		while (ft_isspace(str[i]))
			i++;
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

void	print_map(t_game *game)
{
	int i = 0;
	while (game->map.map[i])
	{
		printf("%s len = %d\n", game->map.map[i], ft_strlen(game->map.map[i]));
		i++;
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
			{
				printf("Invalid character!\n");
				exit(EXIT_FAILURE);
			}
			j++;
		}
		if (j == 0)
		{
			printf("Empty line in map.!");
			exit(EXIT_FAILURE);
		}
		else if (j > max_width)
			max_width = j;
		i++;
	}
	if (game->dir == -1)
	{
		printf("No player direction\n");
		exit(EXIT_FAILURE);
	}
	game->map.height = i;
	game->map.width = max_width;
}

void	adjust_map(t_game *game)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (game->map.map[i])
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

bool	check_valid_chracters(t_game *game, char c)
{
	static int	num_player = 0;

	if (c == '1' || c == '0')
		return (true);
	else if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
	{
		num_player++;
		if (num_player > 1)
		{
			printf("Multiple player direction\n");
			exit(EXIT_FAILURE);
		}
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

void	is_valid_map(t_game *game)
{
	first_check_map(game);
	adjust_map(game);
	print_map(game);
	left_wall_check(game);
	right_wall_check(game);
	top_wall_check(game);
	bottom_wall_check(game);
}
