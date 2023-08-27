/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 02:59:30 by sutku             #+#    #+#             */
/*   Updated: 2023/08/27 00:59:27 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	is_valid_direction(t_game *game, char *str)
{
	if (ft_strncmp(str, "NO", 2) == 0)
	{
		game->wall.num_texture[NO]++;
		load_direction_texture(game, str + 2, NO);
	}
	else if (ft_strncmp(str, "SO", 2) == 0)
	{
		game->wall.num_texture[SO]++;
		load_direction_texture(game, str + 2, SO);
	}
	else if (ft_strncmp(str, "EA", 2) == 0)
	{
		game->wall.num_texture[EA]++;
		load_direction_texture(game, str + 2, EA);
	}
	else if (ft_strncmp(str, "WE", 2) == 0)
	{
		game->wall.num_texture[WE]++;
		load_direction_texture(game, str + 2, WE);
	}
	else
	{
		free_elements(game);
		error_handler(game, W_DIRECTION);
	}
}

void	check_texture_path(t_game *game, char *path, int len)
{
	int	fd;

	if (!path || len < 6)
	{
		if (path)
			free(path);
		error_handler(game, TEXT_PATH);
	}
	if (ft_strcmp(path + len - 6, ".xpm42"))
	{
		free(path);
		error_handler(game, NO_XPM42);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(path);
		error_handler(game, TEXT_FILE);
	}
	close(fd);
}

void	load_direction_texture(t_game *game, char *str, t_dir dir)
{
	int		i;
	int		len;
	char	*path;

	i = 0;
	skip_spaces(str, &i);
	len = 0;
	while (str[len + i] != '\0' && str[len + i] != ' ')
		len++;
	path = ft_substr(str, i, len);
	check_texture_path(game, path, len);
	check_direction_exist(game, dir, path);
}

void	check_direction_exist(t_game *game, t_dir dir, char *path)
{
	if (game->wall.num_texture[dir] == 1)
	{
		game->wall.xpm[dir] = mlx_load_xpm42(path);
		game->wall.texture[dir] = game->wall.xpm[dir]->texture;
	}
	else if (game->wall.num_texture[dir] > 1)
	{
		free(path);
		error_handler(game, MULTI_TEXT);
	}
	free(path);
}
