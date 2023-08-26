/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:27:11 by sutku             #+#    #+#             */
/*   Updated: 2023/08/15 20:15:53 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_image(char *str, t_game *game)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
	printf("ERROR\n");
		// error_message(OPEN_IMAGE, game);
	close(fd);
}


mlx_image_t	*convert_to_image(t_game *game, char *path)
{
	xpm_t			*xpm;
	mlx_image_t		*img;

	open_image(path, game);
	xpm = mlx_load_xpm42(path);
	// if (!xpm)
		// error_message(LOAD_XPM, game);
	img = mlx_texture_to_image(game->mlx, &xpm->texture);
	// if (!img)
		// error_message(MLX_TEXTURE, game);
	mlx_delete_xpm42(xpm);
	return (img);
}

