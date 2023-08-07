/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_deneme.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 05:33:16 by sutku             #+#    #+#             */
/*   Updated: 2023/08/07 05:13:22 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void drawWallColumn(t_game *game, int col, int len, u_int32_t color);
int isWall(t_game *game, int x, int y);
void castRays(t_game *game);
void	draw_map(t_game *game);
void	draw_floor_ceiling(t_game *game);
u_int32_t color_decider(double angle);


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



int map[8][8] = {{1,1,1,1,1,1,1,1},//0
				{1,0,0,0,0,0,0,1},//1
				{1,0,0,0,0,0,0,1},//2
				{1,0,0,0,0,0,0,1},//3
				{1,0,0,0,2,0,0,1},//4
				{1,0,0,1,0,0,0,1},//5
				{1,0,0,0,0,1,0,1},//6
				{1,1,1,1,1,1,1,1},//7
			//   0 1 2 3 4 5 6 7
};


int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void one_unit_draw(t_game *game, uint32_t color, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < 25)
	{
		j = 0;
		while (j < 25)
		{
			mlx_put_pixel(game->player->img, i + (y * 25), j + (x * 25), color);
			if (i == 24)
				mlx_put_pixel(game->player->img, i + (y * 25), j + (x * 25), ft_pixel(1,1,1,255));
			if (j == 24)
				mlx_put_pixel(game->player->img, i + (y * 25), j + (x * 25), ft_pixel(1,1,1,255));
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
		while (j < 8)
		{
			if (map[i][j] == 1)
				one_unit_draw(game, color_wall, i, j);
			else
				one_unit_draw(game, color_space, i, j);
			j++;
		}
		i++;
	}
	castRays(game);
}
double	pythagoras(double start_x, double start_y, double end_x, double end_y, double cast_angle)
{
	double	len;
	double	x;
	double	y;

	x = fabs(end_x - start_x);
	y = fabs(end_y - start_y);
	x = pow(x, 2);
	y = pow(y, 2);
	printf("%f, %f\t", x, y);
	len = sqrtf(x + y);
	printf("%f\n", len);
	len *= cos(cast_angle);
	// 	return ((int)round(y));
	// return ((int)round(x));
	return (len);
}


void castRays(t_game *game) 
{
    // Number of screen columns (rays)
    int screenWidth = 800;
	int		i = 0;
	double	fov_ang;
	double	cast_angle;
	double	len;
	double	x_dir;
	double	y_dir;
	u_int32_t color;

        double rayX = game->player->x;
        double rayY = game->player->y;
		fov_ang = -(PI / 6.0);
		int bla= 0;
		bla = 0;
		while (i < 800)
		{
			cast_angle = game->player->angle + fov_ang;
			// if (cast_angle < 0)
			// 	cast_angle += 2 * PI;
			// else if (cast_angle > 2 * PI)
			// 	cast_angle -= 2 * PI;
			// cast_angle = 0;
			rayX = game->player->x;
       		rayY = game->player->y;
			while (1)
			{
				rayX += cos(cast_angle);
				rayY += sin(cast_angle);
				int mapX = (int)(rayX/100);
				int mapY = (int)(rayY/100);
				mapX*=100;
				mapY*=100;
				// isWall(game ,mapX, mapY);
				// if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT || isWall(game ,mapX, mapY))
				// {
					if(map[(int)(mapX/100.0)][(int)(mapY/100.0)] == 1)
					{
						// if (fov_ang < 0)
						// 	fov_ang += 2 * PI;
						// else if (fov_ang > 2 * PI)
						// 	fov_ang -= 2 * PI;
						// color = color_decider(cast_angle);
						color = 0xFF000040;
						drawWallColumn(game, bla, pythagoras(game->player->x, game->player->y, mapX, rayY, fov_ang), color);
						bla++;
					break;
					}
				// }
			}
			fov_ang += (PI / 3.0) / 800.0;
			i++;
		}
}

int isWall(t_game *game, int x, int y) {
	
	mlx_put_pixel(game->player->img, y / 4, x / 4, ft_pixel(255, 128, 0, 255));
	if(map[x / 100][y / 100] == 1)
		return (1);
    return 0;
}

u_int32_t color_decider(double angle)
{
	u_int32_t color;

	if ((angle >= 0) && angle <= PI / 2)
		color = ft_pixel(51, 153, 255, 255);
	else if ((angle >= PI) && angle <= 3 * PI / 2)
		color = ft_pixel(102, 102, 255, 255);
	else if ((angle >= 3 * PI / 2) && (angle <= 2 * PI))
		color = ft_pixel(255, 255, 102, 255);
	else
		color = ft_pixel(255, 153, 153, 255);
	return (color);
}

void drawWallColumn(t_game *game, int col, int len, u_int32_t color)
{
    int	i;
	int j;
	double n_len;
	double angle;

	// angle = 1.0;
	// while (len > 0)
	// {
	// 	angle += (9.0 / 800);
	// 	len--;
	// }
	// n_len = 800 / angle;
	n_len = 800.0 / (len / 100.0);
		j = 0;
	while (j < 800)
	{
		if (j > (800 / 2) - (n_len / 2) && j < (800 / 2) + (n_len / 2))
			mlx_put_pixel(game->player->img, col, j, color);
		// if ((MAP_HEIGHT / 2) > j)
			// mlx_put_pixel(game->player->img, col, (MAP_HEIGHT / 2) + j, color);
		j++;
	}
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
		while (++j < 8)
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

	if (!(game->mlx = mlx_init(800, 800, "cub3D", true)))
	{
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(game->player->img = mlx_new_image(game->mlx, 800, 800)))
	{
		mlx_close_window(game->mlx);
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(game->mlx, game->player->img, 0, 0) == -1)
	{
		mlx_close_window(game->mlx);
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	player_position(game);
	printf("x = %f y = %f", game->player->x, game->player->y);
	draw_map(game);
	mlx_loop_hook(game->mlx, ft_hook, game);

	// mlx_key_hook(game->mlx, ft_hook, game);
	// mlx_loop_hook(game->mlx, ft_randomize, game->player->img);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}
