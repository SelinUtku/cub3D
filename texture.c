/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:27:11 by sutku             #+#    #+#             */
/*   Updated: 2023/08/25 23:59:37 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	draw_lineof_texture(t_game *game, int col, double perpWallDist)
{
	int lineHeight;
	int drawStart;
	int drawEnd;
	double wall_x;
	double tex_y;
	double tex_step;
	int tex_x;

	lineHeight =  (int)(SCREEN_HEIGHT / perpWallDist);
	drawStart = (SCREEN_HEIGHT / 2) - (lineHeight / 2);
	// if(drawStart < 0)
	// 	drawStart = 0;
	drawEnd  = (lineHeight / 2) + (SCREEN_HEIGHT / 2);
	// if (drawEnd >= SCREEN_HEIGHT)
	// 	drawEnd = SCREEN_HEIGHT - 1;
	if (game->wall.side % 2 == 0)
		wall_x = game->player->y + perpWallDist * game->ray.y;
	else
		wall_x = game->player->x + perpWallDist * game->ray.x;
	wall_x -= floor(wall_x);
	// if((game->wall.side == 0 || game->wall.side == 2)  && game->ray.x > 0)
	// 	tex_x = (double)game->wall.texture[game->wall.side].width - tex_x - 1.0;
	// if((game->wall.side == 1 || game->wall.side == 3) && game->ray.y < 0)
	// 	tex_x = (double)game->wall.texture[game->wall.side].width - tex_x - 1.0;
	tex_x = (int)(wall_x * (double)game->wall.texture[game->wall.side].width);
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
			mlx_put_pixel(game->img, col, t, ft_pixel(game->c_color.r, game->c_color.g, game->c_color.b, 255));
		else if (t > drawEnd)
			mlx_put_pixel(game->img, col, t, ft_pixel(game->f_color.r, game->f_color.g, game->f_color.b, 255));
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
