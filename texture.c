/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:27:11 by sutku             #+#    #+#             */
/*   Updated: 2023/08/26 20:55:09 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_column(t_game *game, t_draw *draw, int col);

void	draw_lineof_texture(t_game *game, int col, double wall_distance)
{
	t_draw	draw;

	draw.line_height = (int)(SCREEN_HEIGHT / wall_distance);
	draw.start = (SCREEN_HEIGHT / 2) - (draw.line_height / 2);
	draw.end = (draw.line_height / 2) + (SCREEN_HEIGHT / 2);
	if (game->wall.side == WE || game->wall.side == EA)
		draw.wall_x = game->player->y + wall_distance * game->ray.y;
	else
		draw.wall_x = game->player->x + wall_distance * game->ray.x;
	draw.wall_x -= floor(draw.wall_x);
	draw.text_x = (int)(draw.wall_x * \
	(double)game->wall.texture[game->wall.side].width);
	draw.text_y = 0;
	draw.text_step = (double)game->wall.texture[game->wall.side].height / \
	(double)draw.line_height;
	if (draw.start < 0)
		draw.text_y = fabs((double)draw.start) * draw.text_step;
	draw_column(game, &draw, col);
}

void	draw_column(t_game *game, t_draw *draw, int col)
{
	unsigned int	color;
	int				t;
	uint8_t			*pixel;
	int				num;

	t = 0;
	while (t < SCREEN_HEIGHT)
	{
		if (t >= draw->start && t <= draw->end)
		{
			num = game->wall.texture[game->wall.side].width * 4 * \
			(int)draw->text_y + (int)draw->text_x * 4;
			pixel = &game->wall.texture[game->wall.side].pixels[num];
			color = ft_pixel(pixel[0], pixel[1], pixel[2], pixel[3]);
			mlx_put_pixel(game->img, col, t, color);
			draw->text_y += draw->text_step;
		}
		else if (t < draw->start)
			mlx_put_pixel(game->img, col, t, \
			ft_pixel(game->c_color.r, game->c_color.g, game->c_color.b, 255));
		else if (t > draw->end)
			mlx_put_pixel(game->img, col, t, \
			ft_pixel(game->f_color.r, game->f_color.g, game->f_color.b, 255));
		t++;
	}
}
