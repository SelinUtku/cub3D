/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 00:39:04 by sutku             #+#    #+#             */
/*   Updated: 2023/08/27 01:54:26 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	skip_spaces(char *str, int *i)
{
	while (ft_isspace(str[*i]))
		(*i)++;
}

int	len_of_double_array(char **str)
{
	int	len;

	len = 0;
	while (str[len] != NULL)
		len++;
	return (len);
}

void	error_handler(t_game *game, char *str)
{
	ft_putendl_fd(str, 2);
	if (game->map.map)
		free_double_char_arr(game->map.map);
	exit(EXIT_FAILURE);
}
