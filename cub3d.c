/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 02:00:56 by sutku             #+#    #+#             */
/*   Updated: 2023/08/09 01:40:17 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void drawWallColumn(t_game *game, int col, int len, u_int32_t color);
int isWall(t_game *game, int x, int y);
void castRays(t_game *game);
void	draw_map(t_game *game);
void	draw_floor_ceiling(t_game *game);
u_int32_t color_decider(double angle);

int map[8][16] ={{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
				 {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				 {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				 {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				 {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				 {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				 {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
				};

void ft_hook(void *param)
{
	t_game *game = param;

	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP) && game->player->x > 0)
	{
		game->player->x -= 5;
		draw_map(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN) && game->player->x < MAP_HEIGHT)
	{
		game->player->x += 5;
		draw_map(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT) && game->player->y > 0)
	{
		game->player->y -= 5;
		draw_map(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT) && game->player->y < MAP_WIDTH)
	{
		game->player->y += 5;
		draw_map(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A) && game->player->x < MAP_WIDTH)
	{
		game->player->angle += 0.01;
		if (game->player->angle > 2 * PI)
			game->player->angle -= 2 * PI; 
		draw_map(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D) && game->player->x < MAP_WIDTH)
	{
		game->player->angle -= 0.01;
		if (game->player->angle < 0)
			game->player->angle += 2 * PI; 
		draw_map(game);
	}
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void one_unit_draw(t_game *game, uint32_t color, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < 20)
	{
		j = 0;
		while (j < 20)
		{
			mlx_put_pixel(game->player->img, i + (y * 20), j + (x * 20), color);
			if (i == 19)
				mlx_put_pixel(game->player->img, i + (y * 20), j + (x * 20), ft_pixel(1,1,1,255));
			if (j == 19)
				mlx_put_pixel(game->player->img, i + (y * 20), j + (x * 20), ft_pixel(1,1,1,255));
			j++;
		}
		i++;

	}
}

void	draw_floor_ceiling(t_game *game)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < MAP_HEIGHT / 2)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			mlx_put_pixel(game->player->img, j , i, ft_pixel(153,255,255,255));
			j++;
		}
		i++;
	}
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			mlx_put_pixel(game->player->img, j , i, ft_pixel(160,160,160,255));
			j++;
		}
		i++;
	}
}

void	draw_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	uint32_t color_wall = ft_pixel(204, 153, 255, 255);
	uint32_t color_space = ft_pixel(255, 255, 255, 255);
	draw_floor_ceiling(game);
	while (i < 8)
	{
		j = 0;
		while (j < 16)
		{
			if (map[i][j] == 1)
				one_unit_draw(game, color_wall, i, j);
			else
				one_unit_draw(game, color_space, i, j);
			j++;
		}
		i++;
	}
	// castRays(game);
}

void	init_struct(t_game *game)
{
	game->mlx = NULL;
	game->player = malloc (sizeof(t_object));
	game->player->x = 400.0;
	game->player->y = 400.0;
	game->player->angle = PI / 2;
}

void	player_position(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 8)
	{
		j = -1;
		while (++j < 16)
		{
			if (map[i][j] == 2)
			{
				game->player->x =  (j * (MAP_WIDTH / row)) + (MAP_WIDTH / row) / 2;
				game->player->y =  (i * (MAP_WIDTH / column)) + (MAP_WIDTH / column) / 2;
				return ;
			}
		}
	}
}

int32_t	main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (EXIT_FAILURE);
	init_struct(game);
	game->mlx = mlx_init(1600, 800, "cub3D", true);
	game->player->img = mlx_new_image(game->mlx, 1600, 800);
	mlx_image_to_window(game->mlx, game->player->img, 0, 0);
	player_position(game);
	printf("x = %f y = %f", game->player->x, game->player->y);
	draw_map(game);
	mlx_loop_hook(game->mlx, ft_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}
