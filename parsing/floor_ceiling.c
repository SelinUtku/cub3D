/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 01:50:33 by sutku             #+#    #+#             */
/*   Updated: 2023/08/25 03:46:15 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	is_valid_rgb(t_game *game, char **str)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		j = 0;
		while (str[i][j] != '\0' && str[i][j] != ' ')
		{
			if (str[i][j] < '0' || str[i][j] > '9')
			{
				free_double_char_arr(str);
				error_handler(game, RGB_NO_NUM);
			}
			j++;
		}
		j = ft_atoi(str[i]);
		if (j < 0 || j > 255)
		{
			free_double_char_arr(str);
			error_handler(game, RGB_RANGE);
		}
	}
}

void	put_rgb_colors(t_color *color, char **str)
{
	color->r = ft_atoi(str[0]);
	color->g = ft_atoi(str[1]);
	color->b = ft_atoi(str[2]);
	free_double_char_arr(str);
}

void	control_f_c_args(t_game *game, char *str, t_color *color)
{
	char	**temp;

	temp = ft_split(str, ',');
	if (!temp)
		return (ft_putendl_fd("Error", 2));
	if (len_of_double_array(temp) != 3)
	{
		free_double_char_arr(temp);
		error_handler(game, RGB_NO_COLOR);
	}
	is_valid_rgb(game, temp);
	put_rgb_colors(color, temp);
}

void	floor_or_ceiling(t_game *game, char *str)
{
	int		i;
	t_color	*color;

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
	skip_spaces(str, &i);
	if (str[i] != '\0')
		control_f_c_args(game, str + i, color);
	else
		error_handler(game, F_C_NO_ARG);
}
