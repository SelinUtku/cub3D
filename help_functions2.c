/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 22:19:37 by sutku             #+#    #+#             */
/*   Updated: 2023/08/27 03:58:04 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
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

void	free_elements(t_game *game)
{
	while (game->num_elements >= 0)
	{
		free(game->elements[game->num_elements]);
		game->num_elements--;
	}
}

char	*delete_slash_n(char *str)
{
	char	*temp;

	temp = ft_strrchr(str, '\n');
	if (temp)
		*temp = '\0';
	return (str);
}

void	free_all(t_game *game)
{
	free_double_char_arr(game->map.map);
	mlx_delete_image(game->mlx, game->img);
	mlx_delete_xpm42(game->wall.xpm[0]);
	mlx_delete_xpm42(game->wall.xpm[1]);
	mlx_delete_xpm42(game->wall.xpm[2]);
	mlx_delete_xpm42(game->wall.xpm[3]);
}
