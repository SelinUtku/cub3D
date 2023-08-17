/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 17:11:57 by Cutku             #+#    #+#             */
/*   Updated: 2023/08/17 21:23:49 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_hook(void *param);
int ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void	init_struct(t_game *game);
void	player_position(t_game *game);
void	draw_map(t_game *game);


int map[18][24] = {
				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1},
				{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1},
				{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

void ft_hook(void *param)
{
	t_game *game = param;
	double rot_speed = 0.0174533;
	double move_speed = 0.1;

	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
    	if (map[(int)(game->player->x + game->player->dir_x * move_speed)][(int)game->player->y] != 1) 
	  		game->player->x += game->player->dir_x * move_speed;
      	if(map[(int)game->player->x][(int)(game->player->y + game->player->dir_y * move_speed)] != 1)
	  		game->player->y += game->player->dir_y * move_speed;
		// draw_map(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
    	if (map[(int)(game->player->x - game->player->dir_x * move_speed)][(int)game->player->y] != 1) 
	  		game->player->x -= game->player->dir_x * move_speed;
    	if(map[(int)game->player->x][(int)(game->player->y - game->player->dir_y * move_speed)] != 1)
	  		game->player->y -= game->player->dir_y * move_speed;
		// draw_map(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
    	if (map[(int)(game->player->x + game->player->dir_y * move_speed)][(int)game->player->y] != 1) 
	  		game->player->x += game->player->dir_y * move_speed;
    	if(map[(int)game->player->x][(int)(game->player->y - game->player->dir_x * move_speed)] != 1)
	  		game->player->y -= game->player->dir_x * move_speed;

		// draw_map(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		if (map[(int)(game->player->x - game->player->dir_y * move_speed)][(int)game->player->y] != 1) 
	  		game->player->x -= game->player->dir_y * move_speed;
    	if(map[(int)game->player->x][(int)(game->player->y + game->player->dir_x * move_speed)] != 1)
	  		game->player->y += game->player->dir_x * move_speed;
		// draw_map(game);
	}

	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		double oldDirX = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(rot_speed) - game->player->dir_y * sin(rot_speed);
		game->player->dir_y = oldDirX * sin(rot_speed) + game->player->dir_y * cos(rot_speed);
		double oldPlaneX = game->plane_x;
		game->plane_x = game->plane_x * cos(rot_speed) - game->plane_y * sin(rot_speed);
		game->plane_y = oldPlaneX * sin(rot_speed) + game->plane_y * cos(rot_speed);
		// draw_map(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		double oldDirX = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(-rot_speed) - game->player->dir_y * sin(-rot_speed);
		game->player->dir_y = oldDirX * sin(-rot_speed) + game->player->dir_y * cos(-rot_speed);
		double oldPlaneX = game->plane_x;
		game->plane_x = game->plane_x * cos(-rot_speed) - game->plane_y * sin(-rot_speed);
		game->plane_y = oldPlaneX * sin(-rot_speed) + game->plane_y * cos(-rot_speed);
		// draw_map(game);
	}
	draw_map(game);
}

int	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	init_player_direction(t_game *game)
{
	if (game->dir == WE || game->dir == EA)
	{
		if (game->dir == WE)
		{
			game->player->dir_x = -1;
			game->player->dir_y = 0;
		}
		else
		{
			game->player->dir_x = 1;
			game->player->dir_y = 0;
		}
		game->plane_x = 0.0;
		game->plane_y = 0.66;
	}
	if (game->dir == NO || game->dir == SO)
	{
		if (game->dir == NO)
		{
			game->player->dir_x = 0.0;
			game->player->dir_y = -1.0;
		}
		else
		{
			game->player->dir_x = 0.0;
			game->player->dir_y = 1.0;
		}
		game->plane_x = 0.66;
		game->plane_y = 0.0;
	}
}

void	init_struct(t_game *game)
{
	game->mlx = NULL;
	game->player = malloc (sizeof(t_object));
	game->dir = NO;
	init_player_direction(game);
	// game->player->angle = PI;
}

void	player_position(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < 18)
	{
		x = -1;
		while (++x < 24)
		{
			if (map[y][x] == 2)
			{
				game->player->x = x;
				game->player->y = y;
				return ;
			}
		}
	}
}

void	draw_map(t_game *game)
{
	int		i;
	double	delta_x;
	double	delta_y;
	double	ray_x;
	double	ray_y;
	double	camera_x;
	int		map_x;
	int		map_y;
	mlx_texture_t texture;

	mlx_texture_t texture1 = mlx_load_xpm42("/Users/sutku/Projects/cub3d/wall.xpm42")->texture;
	mlx_texture_t texture2 = mlx_load_xpm42("/Users/sutku/Projects/cub3d/ruby.xpm42")->texture;
	mlx_texture_t texture3 = mlx_load_xpm42("/Users/sutku/Projects/cub3d/box3.xpm42")->texture;
	mlx_texture_t texture4 = mlx_load_xpm42("/Users/sutku/Projects/cub3d/door.xpm42")->texture;

		// game->texture = convert_to_image(game, "/Users/sutku/Projects/cub3d/wall.xpm42");
	i = -1;
	while(++i < SCREEN_WIDTH)
	{
		camera_x = 2 * i / (double)SCREEN_WIDTH - 1;
		ray_x = game->player->dir_x + game->plane_x * camera_x;
		ray_y = game->player->dir_y + game->plane_y * camera_x;
		map_x = (int)(game->player->x);
		map_y = (int)(game->player->y);
		double sideDistX;
		double sideDistY;
		if (ray_x == 0)
			delta_x = 1e30;
		else
			delta_x = fabs(1 / ray_x);
		if (ray_y == 0)
			delta_y = 1e30;
		else
			delta_y = fabs(1 / ray_y);
		double perpWallDist;
		int stepX;
		int stepY;

		int hit = 0;
		int side;
		if (ray_x < 0)
		{
			stepX = -1;
			sideDistX = (game->player->x - map_x) * delta_x;
		}
		else
		{
			stepX = 1;
			sideDistX = (map_x + 1.0 - game->player->x) * delta_x;
		}
		if (ray_y < 0)
		{
			stepY = -1;
			sideDistY = (game->player->y - map_y) * delta_y;
		}
		else
		{
			stepY = 1;
			sideDistY = (map_y + 1.0 - game->player->y) * delta_y;
		}
		while(hit == 0)
		{
			if(sideDistX < sideDistY)
			{
				sideDistX += delta_x;
				map_x += stepX;
				if (ray_x > 0)
					side = 0;
				else
					side = 2;
			}
			else
			{
				sideDistY += delta_y;
				map_y += stepY;
				if (ray_y > 0)
					side = 1;
				else
					side = 3;
			}
			if(map[map_x][map_y] == 1)
				hit = 1;
		}
		if (side == 0)
			texture = texture1;
		else if (side == 1)
			texture = texture2;
		else if (side == 2)
			texture = texture3;
		else
			texture = texture4;

		if(side == 0 || side == 2)
			perpWallDist = (sideDistX - delta_x);
		else if (side == 1 || side == 3)
			perpWallDist = (sideDistY - delta_y);
		int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2+ SCREEN_HEIGHT / 2;
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		double wall_x;
		if (side == 0 || side == 2)
			wall_x = game->player->y + perpWallDist * ray_y;
		else
			wall_x = game->player->x + perpWallDist * ray_x;
		wall_x -= floor(wall_x);
		double tex_x;
		tex_x = wall_x * (double)texture.width;
		if((side == 0 || side == 2) && ray_x > 0)
			tex_x = (double)texture.width - tex_x - 1.0;
      	if((side == 1 || side == 3) && ray_y < 0)
			tex_x = (double)texture.width - tex_x - 1.0;
		double tex_step = (double)texture.height / (double)lineHeight;
		double tex_y;
		if (drawStart < 0)
			tex_y = fabs((double)drawStart) * tex_step;
		else
			tex_y = 0;
		unsigned int color;
		int t = 0;
		uint8_t *pixel;
		while (t < SCREEN_HEIGHT)
		{
			// if ((int)tex_y * texture.width * 4 + (int)tex_x * 4 < 80 * 80 * 4)
			if (t >= drawStart && t <= drawEnd)
			{
				pixel = &texture.pixels[(int)tex_y * texture.width * 4  + (int)tex_x * 4];
				color = ft_pixel(*(pixel), *(pixel + 1), *(pixel + 2), *(pixel + 3));
					mlx_put_pixel(game->img, i, t, color);
				tex_y+=tex_step;
			}
			else if (t < drawStart)
				mlx_put_pixel(game->img, i, t, ft_pixel(153, 255, 255, 255));
			else if (t > drawEnd)
				mlx_put_pixel(game->img, i, t, ft_pixel(160, 160, 160, 255));
			t++;
		}
	}
}


int	main(int argc, char **argv)
{
	t_game	*game;
	
	game = malloc(sizeof(t_game));
	if (!game)
		return (EXIT_FAILURE);
	init_struct(game);
	if (!(game->mlx = mlx_init(1600, 800, "cub3D", true)))
	{
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(game->img = mlx_new_image(game->mlx, 1600, 800)))
	{
		mlx_close_window(game->mlx);
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) == -1)
	{
		mlx_close_window(game->mlx);
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	player_position(game);
	draw_map(game);
	mlx_loop_hook(game->mlx, ft_hook, game);
	// mlx_key_hook(game->mlx, ft_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}

