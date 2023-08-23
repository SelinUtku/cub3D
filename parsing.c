/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:19:07 by sutku             #+#    #+#             */
/*   Updated: 2023/08/23 00:49:51 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

char	**parse_the_map(t_game *game, char *path);
bool	floor_and_ceiling_color(t_game *game, char *str, t_color *color);
void	match_direction_and_texture(t_game *game, char *str, char *path);
void	check_validity_of_input(t_game *game, char **str);
bool	is_valid_rgb(char *str);
bool 	is_it_direction_or_color(t_game *game, char *str);





bool	is_valid_rgb(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n' && str[i] != ' ')
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
			input[id] = str;
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
	read_the_map(game, fd);
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
	while (ft_isspace(str[i]))
		i++;
	start = i;
	if (!ft_strncmp(str + i, "F", 1))
	{
		color = &game->f_color;
		game->f++;
	}
	else if (!ft_strncmp(str + i, "C", 1))
	{
		color = &game->c_color;
		game->c++;
	}
	else
		return (ft_putendl_fd(F_C, 2), false);
	i++;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] != '\0' && str[i] != '\n')
	{
		len = my_strlen(str + i);
		temp = ft_substr(str, i, len);
		if (floor_and_ceiling_color(game, temp, color) == true)// free str
			return (true);
	}
	return (false);
}

void	direction_operations(t_game *game, char *str, char *dir)
{
	int		i;
	int		len;
	int		fd;
	char	*path;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	len = 0;
	while (str[len + i] != '\0' && str[len + i] != '\n' && str[len + i] != ' ')
		len++;
	path = ft_substr(str, i, len);
	if (!path)
	{
		ft_putendl_fd("no texture path", 2);
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
		ft_putendl_fd("File can not open", 2);
		exit(EXIT_FAILURE);
	}
	match_direction_and_texture(game, dir, path);
}

bool is_it_direction_or_color(t_game *game, char *str)
{
	int	i;
	int	start;
	int	len;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	start = i;
	len = 0;
	while (str[len + i] != ' ' && str[len + i] != '\n' && str[len + i] != '\0')
		len++;
	if (len == 2 && !ft_strncmp(str + start, "NO", 2))
	{
		direction_operations(game, str + start + 2, "NO");
		return (true);
	}
	else if (len == 2 && !ft_strncmp(str + start, "SO", 2))
	{
		direction_operations(game, str + start + 2, "SO");
		return (true);
	}
	else if (len == 2 && !ft_strncmp(str + start, "WE", 2))
	{
		direction_operations(game, str + start + 2, "WE");
		return (true);
	}
	else if (len == 2 && !ft_strncmp(str + start, "EA", 2))
	{
		direction_operations(game, str + start + 2, "EA");
		return (true);
	}
	else if (len == 1)
	{
		if (is_floor_or_ceiling(game, str) == true)
			return (true);
	}
	return (false);
}
