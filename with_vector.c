/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   with_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 17:11:57 by Cutku             #+#    #+#             */
/*   Updated: 2023/08/19 22:26:09 by sutku            ###   ########.fr       */
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
	// game->f_color = malloc (sizeof(t_color));
	// game->c_color = malloc (sizeof(t_color));
	game->wall.no = 0;
	game->wall.so = 0;
	game->wall.we = 0;
	game->wall.ea = 0;
	game->f = 0;
	game->c = 0;
	init_player_direction(game);
	// load_textures(game);
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
	double	camera_x;
	t_coord	distance;

	i = -1;
	while(++i < SCREEN_WIDTH)
	{
		camera_x = 2 * i / (double)SCREEN_WIDTH - 1;
		game->ray.x = game->player->dir_x + game->plane_x * camera_x;
		game->ray.y = game->player->dir_y + game->plane_y * camera_x;
		if (game->ray.x == 0)
			game->ray.delta_x = 1e30;
		else
			game->ray.delta_x = fabs(1 / game->ray.x);
		if (game->ray.y == 0)
			game->ray.delta_y = 1e30;
		else
			game->ray.delta_y = fabs(1 / game->ray.y);
		distance = dda(game);
		if(game->wall.side % 2 == 0)
			draw_lineof_texture(game, i, distance.x - game->ray.delta_x);
		else if (game->wall.side % 2 != 0)
			draw_lineof_texture(game, i, distance.y - game->ray.delta_y);
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
	char **str = parse_the_map(game, "./map.cub");
	check_validity_of_input(game, str);
	draw_map(game);
	mlx_loop_hook(game->mlx, ft_hook, game);
	// mlx_key_hook(game->mlx, ft_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}

