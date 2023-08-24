/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:27:11 by sutku             #+#    #+#             */
/*   Updated: 2023/08/24 03:48:09 by sutku            ###   ########.fr       */
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


void	draw_lineof_texture(t_game *game, int col, double perpWallDist)
{
	int lineHeight;
	int drawStart;
	int drawEnd;
	double wall_x;
	double tex_y;
	double tex_step;
	double tex_x;

	lineHeight =  (int)(SCREEN_HEIGHT / perpWallDist);
	drawStart = (SCREEN_HEIGHT - lineHeight) / 2;
	drawEnd  = (lineHeight + SCREEN_HEIGHT) / 2;
	if (game->wall.side % 2 == 0)
		wall_x = game->player->y + perpWallDist * game->ray.y;
	else
		wall_x = game->player->x + perpWallDist * game->ray.x;
	wall_x -= floor(wall_x);
	if((game->wall.side == 0 || game->wall.side == 2)  && game->ray.x > 0)
		tex_x = (double)game->wall.texture[game->wall.side].width - tex_x - 1.0;
	if((game->wall.side == 1 || game->wall.side == 3) && game->ray.y < 0)
		tex_x = (double)game->wall.texture[game->wall.side].width - tex_x - 1.0;
	tex_x = wall_x * (double)game->wall.texture[game->wall.side].width;
	tex_y = 0;
	tex_step = (double)game->wall.texture[game->wall.side].height / (double)lineHeight;
	if (drawStart < 0)
		tex_y = fabs((double)drawStart) * tex_step;

	unsigned int color;
	int t = 0;
	uint8_t *pixel;
	while (t < SCREEN_HEIGHT)
	{
		// if ((int)tex_y * texture.width * 4 + (int)tex_x * 4 < 80 * 80 * 4)
		if (t >= drawStart && t <= drawEnd)
		{
			pixel = &game->wall.texture[game->wall.side].pixels[(int)tex_y * game->wall.texture[game->wall.side].width * 4  + (int)tex_x * 4];
			color = ft_pixel(*(pixel), *(pixel + 1), *(pixel + 2), *(pixel + 3));
				mlx_put_pixel(game->img, col, t, color);
			tex_y += tex_step;
		}
		else if (t < drawStart)
			mlx_put_pixel(game->img, col, t, ft_pixel(153, 255, 255, 255));
		else if (t > drawEnd)
			mlx_put_pixel(game->img, col, t, ft_pixel(160, 160, 160, 255));
		t++;
	}
}

// void	put_textures_to_img()
// {
// 	unsigned int color;
// 	int t;
// 	uint8_t *pixel;

// 	t = 0;
// 	while (t < SCREEN_HEIGHT)
// 	{
// 		// if ((int)tex_y * texture.width * 4 + (int)tex_x * 4 < 80 * 80 * 4)
// 		if (t >= drawStart && t <= drawEnd)
// 		{
// 			pixel = &game->wall.texture[game->wall.side].pixels[(int)tex_y * game->wall.texture[game->wall.side].width * 4  + (int)tex_x * 4];
// 			color = ft_pixel(*(pixel), *(pixel + 1), *(pixel + 2), *(pixel + 3));
// 				mlx_put_pixel(game->img, col, t, color);
// 			tex_y+=tex_step;
// 		}
// 		else if (t < drawStart)
// 			mlx_put_pixel(game->img, col, t, ft_pixel(153, 255, 255, 255));
// 		else if (t > drawEnd)
// 			mlx_put_pixel(game->img, col, t, ft_pixel(160, 160, 160, 255));
// 		t++;
// 	}
// }
