/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 17:11:57 by Cutku             #+#    #+#             */
/*   Updated: 2023/08/14 00:19:19 by Cutku            ###   ########.fr       */
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
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

void ft_hook(void *param)
{
	t_game *game = param;
	double rot_speed = 0.0174533;
	double move_speed = 0.1;

	rot_speed *= 2;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
	{
    	if (map[(int)(game->player->x + game->player->dir_x * move_speed)][(int)game->player->y] != 1) 
	  		game->player->x += game->player->dir_x * move_speed;
      	if(map[(int)game->player->x][(int)(game->player->y + game->player->dir_y * move_speed)] != 1)
	  		game->player->y += game->player->dir_y * move_speed;
		draw_map(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
	{
    	if (map[(int)(game->player->x - game->player->dir_x * move_speed)][(int)game->player->y] != 1) 
	  		game->player->x -= game->player->dir_x * move_speed;
    	if(map[(int)game->player->x][(int)(game->player->y - game->player->dir_y * move_speed)] != 1)
	  		game->player->y -= game->player->dir_y * move_speed;
		draw_map(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
    	if (map[(int)(game->player->x - game->player->dir_y * move_speed)][(int)game->player->y] != 1) 
	  		game->player->x -= game->player->dir_y * move_speed;
    	if(map[(int)game->player->x][(int)(game->player->y + game->player->dir_x * move_speed)] != 1)
	  		game->player->y += game->player->dir_x * move_speed;
		draw_map(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
    	if (map[(int)(game->player->x + game->player->dir_y * move_speed)][(int)game->player->y] != 1) 
	  		game->player->x += game->player->dir_y * move_speed;
    	if(map[(int)game->player->x][(int)(game->player->y - game->player->dir_x * move_speed)] != 1)
	  		game->player->y -= game->player->dir_x * move_speed;
		draw_map(game);
	}

	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		double oldDirX = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(rot_speed) - game->player->dir_y * sin(rot_speed);
		game->player->dir_y = oldDirX * sin(rot_speed) + game->player->dir_y * cos(rot_speed);
		double oldPlaneX = game->plane_x;
		game->plane_x = game->plane_x * cos(rot_speed) - game->plane_y * sin(rot_speed);
		game->plane_y = oldPlaneX * sin(rot_speed) + game->plane_y * cos(rot_speed);
		draw_map(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		double oldDirX = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(-rot_speed) - game->player->dir_y * sin(-rot_speed);
		game->player->dir_y = oldDirX * sin(-rot_speed) + game->player->dir_y * cos(-rot_speed);
		double oldPlaneX = game->plane_x;
		game->plane_x = game->plane_x * cos(-rot_speed) - game->plane_y * sin(-rot_speed);
		game->plane_y = oldPlaneX * sin(-rot_speed) + game->plane_y * cos(-rot_speed);
		draw_map(game);
	}

}

int ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	init_struct(t_game *game)
{
	game->mlx = NULL;
	game->player = malloc (sizeof(t_object));
	game->player->dir_x = -1;
	game->player->dir_y = 0;
	// game->player->angle = PI;
	game->time = 0;
	game->old_time = 0;
	game->plane_x = 0.0;
	game->plane_y = 0.66;
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
				printf("x = %d y = %d \n", game->player->x, game->player->y);
				return ;
			}
		}
	}
}

void	draw_map(t_game *game)
{
	int	i;
	double deltaDistX;
	double deltaDistY;

	i = -1;
	while(++i < SCREEN_WIDTH)
	{
		double cameraX = 2 * i / (double)SCREEN_WIDTH - 1;
		double rayDirX = game->player->dir_x + game->plane_x * cameraX;
		double rayDirY = game->player->dir_y + game->plane_y * cameraX;
		int mapX = (int)(game->player->x);
		int mapY = (int)(game->player->y);
		double sideDistX;
		double sideDistY;
		if (rayDirX == 0)
			deltaDistX = 1e30;
		else
			deltaDistX = fabs(1 / rayDirX);
		if (rayDirY == 0)
			deltaDistY = 1e30;
		else
			deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		int stepX;
		int stepY;

		int hit = 0;
		int side;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->player->x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player->x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->player->y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player->y) * deltaDistY;
		}
		while(hit == 0)
		{
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if(map[mapX][mapY] == 1)
				hit = 1;
			if(side == 0)
				perpWallDist = (sideDistX - deltaDistX);
			else
				perpWallDist = (sideDistY - deltaDistY);
			int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
			int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
			if(drawStart < 0) 
				drawStart = 0;
			int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
			if(drawEnd >= SCREEN_HEIGHT) 
				drawEnd = SCREEN_HEIGHT - 1;
			unsigned int color = ft_pixel(102, 102, 255, 255);
			if(side == 1) 
				color = color / 2;
			int t = 0;
			while (t < SCREEN_HEIGHT)
			{
				if (t >= drawStart && t <= drawEnd)
					mlx_put_pixel(game->img, i, t, color);
				else if (t < drawStart)
					mlx_put_pixel(game->img, i, t, ft_pixel(153,255,255,255));
				else
					mlx_put_pixel(game->img, i, t, ft_pixel(160,160,160,255));
				t++;
			}
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
	// mlx_loop_hook(game->mlx, ft_randomize, game->player->img);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}

