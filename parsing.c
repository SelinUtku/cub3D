/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:19:07 by sutku             #+#    #+#             */
/*   Updated: 2023/08/24 05:11:21 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

char	**parse_the_map(t_game *game, char *path);
bool	floor_and_ceiling_color(t_game *game, char *str, t_color *color);
void	load_direction_texture(t_game *game, char *str, t_dir dir);
void	check_validity_of_input(t_game *game, char **str);
bool	is_valid_rgb(char *str);
bool 	is_it_direction_or_color(t_game *game, char *str);
bool	is_valid_direction(t_game *game, char *str);
void	check_direction_exist(t_game *game, t_dir dir, char *path);



bool	is_valid_rgb(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != ' ')
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

char	**parse_the_map(t_game *game, char *path)
{
	int		fd;
	int		id;
	int		i;
	char	*str;
	char	**input;

	input = malloc(sizeof(char *) * 7);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("FILE", 2);
		exit (EXIT_FAILURE);	
	}
	id = 0;
	str = get_next_line(fd);
	if (!str)
		exit (EXIT_FAILURE); // map is empty
	while (str && id < 6)
	{
		i = 0;
		while (ft_isspace(str[i]))
			i++;
		if (str[i] != '\n')
		{
			input[id] = delete_slash_n(str);
			id++;
		}
		else
			free(str);
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
	read_the_map(game, fd);//sonra
	return (input);
}

bool	r_g_b_control(char *s1, char *s2, char *s3, t_color *color)
{
	if (is_valid_rgb(s1) && is_valid_rgb(s2) && is_valid_rgb(s3))
	{
		color->r = ft_atoi(s1);
		color->g = ft_atoi(s2);
		color->b = ft_atoi(s3);
		// printf("r = %d g = %d b = %d\n", color->r, color->g , color->b);
		return (true);
	}
	return (false);
}

bool	floor_and_ceiling_color(t_game *game, char *str, t_color *color)
{
	char	**temp;

	temp = ft_split(str, ',');
	if (!temp)
		return (ft_putendl_fd("Error", 2), false);
	if (len_of_double_array(temp) != 3)
		return (ft_putendl_fd(RGB_COLOR, 2), free_double_char_arr(temp), false);
	if (!r_g_b_control(temp[0], temp[1], temp[2], color))
		return (free_double_char_arr(temp), false);
	return (free_double_char_arr(temp), true);
}


void	check_number_of_elements(t_game *game)
{
	int	i;

	while (i < 4)
	{
		if (game->wall.num_texture[i] == 0)
		{
			ft_putendl_fd("Missing texture of direction !", 2);
			exit(EXIT_FAILURE);
		}
		i++;
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

	id = 0;
	while (str[id])
	{
		if (is_it_direction_or_color(game, str[id]) == false)
		{
			ft_putendl_fd("Direction or color element is missing ! ", 2);
			free_double_char_arr(str);
			exit(EXIT_FAILURE);
		}
		id++;
	}
	check_number_of_elements(game);
	free_double_char_arr(str);
}

bool	is_floor_or_ceiling(t_game *game, char *str)
{
	int		i;
	int		start;
	char 	*temp;
	t_color	*color;
	int 	len;

	i = 0;
	if (str[i] == 'F')
	{
		color = &game->f_color;
		game->f++;
	}
	else if (str[i] == 'C')
	{
		color = &game->c_color;
		game->c++;
	}
	i++;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] != '\0')
	{
		len = ft_strlen(str + i);
		temp = ft_substr(str, i, len);
		if (floor_and_ceiling_color(game, temp, color) == true)// free str
			return (true);
	}
	return (false);
}

bool	is_it_direction_or_color(t_game *game, char *str)
{
	int	start;
	int	len;

	start = 0;
	while (ft_isspace(str[start]))
		start++;
	len = 0;
	while (str[len + start] != ' ' && str[len + start] != '\0')
		len++;
	if (len == 2)
		return (is_valid_direction(game, str + start));
	else if (len == 1 && (str[start] == 'F' || str[start] == 'C'))
		return (is_floor_or_ceiling(game, str + start));
	return (false);
}

bool	is_valid_direction(t_game *game, char *str)
{
	if (ft_strncmp(str, "NO", 2) == 0)
	{
		game->wall.num_texture[NO]++;
		return (load_direction_texture(game, str + 2, NO), true);
	}
	else if (ft_strncmp(str, "SO", 2) == 0)
	{
		game->wall.num_texture[SO]++;
		return (load_direction_texture(game, str + 2, SO), true);
	}
	else if (ft_strncmp(str, "EA", 2) == 0)
	{
		game->wall.num_texture[EA]++;
		return (load_direction_texture(game, str + 2, EA), true);
	}
	else if (ft_strncmp(str, "WE", 2) == 0)
	{
		game->wall.num_texture[WE]++;
		return (load_direction_texture(game, str + 2, WE), true);
	}
	else
		return (false);
}

void	load_direction_texture(t_game *game, char *str, t_dir dir)
{
	int		fd;
	int		i;
	int		len;
	char	*path;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	len = 0;
	while (str[len + i] != '\0' && str[len + i] != ' ')
		len++;
	path = ft_substr(str, i, len);
	if (!path || len < 6)
	{
		ft_putendl_fd("Wrong texture path", 2);
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(path + len - 6, ".xpm42"))
	{
		ft_putendl_fd("Texture type is not .xpm42 !", 2);
		exit(EXIT_FAILURE);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("Texture file can not open", 2);
		exit(EXIT_FAILURE);
	}
	check_direction_exist(game, dir, path);
}

void	check_direction_exist(t_game *game, t_dir dir, char *path)
{
	if (game->wall.num_texture[dir] == 1)
		game->wall.texture[dir] = mlx_load_xpm42(path)->texture;
	else if (game->wall.num_texture[dir] > 1)
	{
		ft_putendl_fd("Multiple texture of direction !", 2);
		exit (EXIT_FAILURE);
	}
}
