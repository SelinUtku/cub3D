/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:27:11 by sutku             #+#    #+#             */
/*   Updated: 2023/08/18 00:01:01 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isspace(char a)
{
	if (a == 32 || a == 9 || a == 10)
		return (1);
	return (0);
}

void    parse_the_map(t_game *game, char *path)
{
    int     fd;
    int     id;
    int     i;
    char    *str;
    char    **input;

    input = malloc(sizeof(char *) * 7);
    fd  = open (path, O_RDONLY);
    if (fd < 0)
        ft_putstr_fd("File can not open\n", 2);
    str = get_next_line(fd);
    if (!str)
        exit(1); // map is empty
    id = 0;
    while (id < 6)
    {
        if (str[0] != '\n')
        {
            i = 0;
            while (ft_isspace(str[i]))
            {

            }
        }
    }
}