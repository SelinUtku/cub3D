/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:27:11 by sutku             #+#    #+#             */
/*   Updated: 2023/08/20 17:08:25 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isspace(char a);
int	ft_strcmp(char *str1, char *str2);
int	len_of_double_array(char **str);
char	**parse_the_map(t_game *game, char *path);
bool	check_direction_identifiers(char *str);
bool	check_color_identifiers(char *str);
bool	floor_and_ceiling_color(t_game *game, char **str);
void	match_direction_and_texture(t_game *game, char *str, char *path);
void	free_double_char_arr(char **str);
void	check_validity_of_input(t_game *game, char **str);
char 	*delete_slash_n(char *str);
bool	is_valid_rgb(char *str);
void	error_message_wrong_input(t_game *game, char **temp, char **str, char *msg);

bool	is_valid_rgb(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		if (str[i] < '0' || str[i] > '9')
		{
			ft_putendl_fd("Rgb colors are not number !", 2);
			return (false);
		}
		i++;
	}
	i = ft_atoi(str);
	if (i < 0 || i > 255)
	{
		ft_putendl_fd("Rgb colors are not 0-255 !", 2);
		return (false);
	}
	return (true);
}

int	ft_isspace(char a)
{
	if (a == 32 || a == 9)
		return (1);
	return (0);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (1);
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			break ;
		i++;
	}
	return ((str1[i] - str2[i]) != 0);
}

int	len_of_double_array(char **str)
{
	int	len;

	len = 0;
	while(str[len])
		len++;
	return(len);
}

char	**parse_the_map(t_game *game, char *path)
{
	int		fd;
	int		id;
	int		i;
	char	*str;
	char	**input;

	input = malloc(sizeof(char *) * 7);
	fd = open (path, O_RDONLY);
	if (fd < 0)
		ft_putendl_fd("FILE", 2);
	id = 0;
	str = get_next_line(fd);
	if (!str)
		exit(EXIT_FAILURE); // map is empty
	while (str && id < 6)
	{
		i = 0;
		while (ft_isspace(str[i]))
			i++;
		if (str[i] != '\n')
		{
			input[id] = str;
			id++;
		}
		else
			free (str);
		str = get_next_line(fd);
	}
	input[id] = NULL;
	if (id != 6)
	{
		ft_putendl_fd("Incomplete map !", 2);
		if (str)
			free(str);
		free_double_char_arr(input);
		exit(EXIT_FAILURE);
	}
	return (input);
}

bool	check_direction_identifiers(char *str)
{
	if (!ft_strcmp("NO", str) || !ft_strcmp("SO", str) || !ft_strcmp("WE", str) || !ft_strcmp("EA", str))
		return (true);
	return (false);
}

bool	check_color_identifiers(char *str)
{
	if (!ft_strcmp("F", str) || !ft_strcmp("C", str))
		return (true);
	return (false);
}

bool	r_g_b_control(char *s1, char *s2, char *s3, t_color *color)
{
	if (is_valid_rgb(s1) && is_valid_rgb(s2) && is_valid_rgb(s3))
	{
		color->r = ft_atoi(s1);
		color->g = ft_atoi(s2);
		color->b = ft_atoi(s3);
		return (true);
	}
	return (false);
}

bool	floor_and_ceiling_color(t_game *game, char **str)
{
	char	**temp;
	t_color	*color;

	if (!ft_strcmp("F", str[0]))
	{
		color = &game->f_color;
		game->f++;
	}
	else if (!ft_strcmp("C", str[0]))
	{
		color = &game->c_color;
		game->c++;
	}
	else
		return (ft_putendl_fd(F_C, 2), false);
	temp = ft_split(str[1], ',');
	if (!temp)
		return (ft_putendl_fd("Error", 2), false);
	if (len_of_double_array(temp) != 3)
		return (ft_putendl_fd(RGB_COLOR, 2), free_double_char_arr(temp), false);
	if (!r_g_b_control(temp[0], temp[1], temp[2], color))
		return (free_double_char_arr(temp), false);
	return (free_double_char_arr(temp), true);
}

void	match_direction_and_texture(t_game *game, char *str, char *path)
{
	if (!ft_strcmp("NO", str))
	{
		game->wall.texture[NO] = mlx_load_xpm42(path)->texture;
		game->wall.no++;
	}
	else if (!ft_strcmp("SO", str))
	{
		game->wall.texture[SO] = mlx_load_xpm42(path)->texture;
		game->wall.so++;
	}
	else if (!ft_strcmp("WE", str))
	{
		game->wall.texture[WE] = mlx_load_xpm42(path)->texture;
		game->wall.we++;
	}
	else if (!ft_strcmp("EA", str))
	{
		game->wall.texture[EA] = mlx_load_xpm42(path)->texture;
		game->wall.ea++;
	}
}

void	free_double_char_arr(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	check_number_of_elements(t_game *game)
{
	if (game->wall.no != 1 || game->wall.so != 1 || game->wall.ea != 1 || game->wall.we != 1)
	{
		ft_putendl_fd("Duplicate or missing direction !", 2);
		exit(EXIT_FAILURE);
	}
	if (game->f != 1 || game->c != 1)
	{
		ft_putendl_fd("Duplicate or missing floor or ceiling argument !", 2);
		exit(EXIT_FAILURE);
	}
}

void	check_validity_of_input(t_game *game, char **str)
{
	int		id;
	int		fd;
	char	**temp;

	id = 0;
	while (str[id])
	{
		temp = ft_split(str[id], ' ');
		if (!temp)
			error_message_wrong_input(game, NULL, str, "Error");
		if (len_of_double_array(temp) != 2)
			error_message_wrong_input(game, temp, str, MORE_ELEMENT);
		if (check_direction_identifiers(temp[0]) == true)
		{
			temp[1] = delete_slash_n(temp[1]);
			fd = open(temp[1], O_RDONLY);
			if (fd < 0)
				error_message_wrong_input(game, temp, str, FILE);
			match_direction_and_texture(game, temp[0], temp[1]);
		}
		else
		{
			if (check_color_identifiers(temp[0]) == false)
				error_message_wrong_input(game, temp, str, D_C);
			if (floor_and_ceiling_color(game, temp) == false)
				error_message_wrong_input(game, temp, str, NULL);
		}
		free_double_char_arr(temp);
		id++;
	}
	check_number_of_elements(game);
	free_double_char_arr(str);
}

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

void	error_message_wrong_input(t_game *game, char **temp, char **str, char *msg)
{
	free_double_char_arr(temp);
	free_double_char_arr(str);
	//free all
	ft_putendl_fd(msg, 2);// freeler unutma her exittan sonra
	exit(EXIT_FAILURE);
}
