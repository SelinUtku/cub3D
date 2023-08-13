/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_deneme.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 05:33:16 by sutku             #+#    #+#             */
/*   Updated: 2023/08/09 01:13:38 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void drawWallColumn(t_game *game, int col, int len, u_int32_t color);
int iswall(t_game *game, int x, int y);
void castrays(t_game *game);
void	draw_map(t_game *game);
void	draw_floor_ceiling(t_game *game);
u_int32_t color_decider(double angle);
t_ray	check_horizontal_intersection(t_game *game, double angle);
t_ray	check_vertical_intersection(t_game *game, double angle);
void	dda(t_game *game, t_ray ray);
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);


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
				{1,0,0,0,0,0,0,1},//5
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
	mlx_put_pixel(game->player->img, game->player->x / 4, game->player->y / 4, ft_pixel(1, 1, 1, 255));
	castrays(game);
}
double	pythagoras(double start_x, double start_y, double end_x, double end_y, double cast_angle)
{
	double	len;
	double	x;
	double	y;

	x = end_x - start_x;
	y = end_y - start_y;
	// x = pow(x, 2);
	// y = pow(y, 2);
	len = sqrtf(pow(x, 2) + pow(y, 2));
	// 	return ((int)round(y));
	// return ((int)round(x));
	return (len);
}

void castrays(t_game *game) 
{
	int		i;
	double	fov_ang;
	double	cast_angle;
	t_ray		ray_x;
	t_ray		ray_y;
	double		len;

	fov_ang = -(PI / 6.0);
	i = 0;
	while (i < MAP_WIDTH)
	{
		cast_angle = game->player->angle + fov_ang;
		if (cast_angle < 0)
			cast_angle += 2 * PI;
		else if (cast_angle > 2 * PI)
			cast_angle -= 2 * PI;
			// isWall(game ,mapX, mapY);
		ray_x = check_horizontal_intersection(game, cast_angle);
		// printf("x = %d  y = %d len = %d\n", ray_x.x , ray_x.y, ray_x.len);
		ray_y = check_vertical_intersection(game, cast_angle);
		// printf ("x = %d y = %d len = %d\n", ray_x.x, ray_x.y, ray_x.len);
		// if (ray_x.len < ray_y.len)
		// 	printf("ray_x x = %d y = %d len = %d\n",ray_x.x, ray_x.y, ray_x.len);
		// else
			// printf("ray_y x = %d y = %d len = %d\n",ray_y.x, ray_y.y, ray_y.len);
		if (ray_x.len < ray_y.len)
		{
			len = ray_x.len;
			printf("ray x = %f\n", len);

			// printf("x = %d y = %d len =%f\n", ray_x.x, ray_x.len, len);
			// dda(game, ray_x);
		}
		else
		{
			len = ray_y.len;
			printf("ray y = %f\n", len);
			// printf("x = %d y = %d len =%f\n", ray_y.x, ray_y.len, len);
			// dda(game, ray_y);
		}
		len *= cos(fov_ang);
		// printf("%d\n", len);
		// drawWallColumn(game, i, len, ft_pixel(255, 153, 255, 255));
			// if(map[(int)(mapX/100.0)][(int)(mapY/100.0)] == 1)
			// {
				// if (fov_ang < 0)
				// 	fov_ang += 2 * PI;
				// else if (fov_ang > 2 * PI)
				// 	fov_ang -= 2 * PI;
				// color = color_decider(cast_angle);
				// drawWallColumn(game, bla, pythagoras(game->player->x, game->player->y, rayX, rayY, fov_ang), color);
				// bla++;
			// }
		fov_ang += (PI / 3.0) / 800.0;
		i++;
	}
}

void	dda(t_game *game, t_ray ray)
{
	int dx;
	int	dy;
	int	step;
	int	i;
	float	x;
	float	y;

	dx = ray.x - game->player->x;
	dy = ray.y - game->player->y;
	x = game->player->x;
	y = game->player->y;
	if (abs(dx) > abs(dy))
		step = abs(dx);
	else
		step = abs(dy);
	i = 0;
	while (i < step)
	{
		mlx_put_pixel(game->player->img, x / 4, y / 4, ft_pixel(255, 128, 0, 255));
		x += (dx / step);
		y += (dy /step);
		i++;
	}
	
}

t_ray	check_horizontal_intersection(t_game *game, double angle)
{
	t_ray	ray;
	int		delta_y;
	int		delta_x;

	if (0.0 < angle && angle < PI)
	{
		delta_y = -100;
		ray.y = ((int)(game->player->y / 100) * 100) - 1;
		if (angle == PI / 2)
		{
			ray.x = game->player->x;
			delta_x = 0;
		}
		else
		{
			ray.x = game->player->x + (int)((game->player->y - ray.y) / tan(angle));
			delta_x = 100 / tan(angle);
		}
	}
	else
	{
		delta_y = 100;
		ray.y = ((int)(game->player->y / 100) * 100) + 100;
		if (angle == (PI / 2) * 3)
		{
			ray.x = game->player->x;
			delta_x = 0;
		}
		else
		{
			ray.x = game->player->x + (int)((game->player->y - ray.y) / tan(angle));
			delta_x = 100 / tan(angle);
		}
	}
	while ((ray.x < MAP_WIDTH && ray.y < MAP_HEIGHT && ray.x > 0 && ray.y > 0) && iswall(game, ray.x, ray.y) != 1)
	{
		ray.y += delta_y;
		ray.x += delta_x;
	}
	if (!(ray.x < MAP_WIDTH && ray.y < MAP_HEIGHT && ray.x > 0 && ray.y > 0))
	{
		ray.len = INT32_MAX;
		return (ray);
	}
	ray.len = pythagoras(game->player->x, game->player->y, ray.x, ray.y, angle);
	return (ray);
}

t_ray	check_vertical_intersection(t_game *game, double angle)
{
	t_ray	ray;
	int		delta_y;
	int		delta_x;

	if (angle == PI / 2 || angle == (PI / 2) * 3)
	{
		ray.x = game->player->x;
		ray.y = game->player->y;
		ray.len = INT32_MAX;
		return (ray);
	}
	if (angle < PI / 2 || angle > (PI / 2) * 3)
	{
		delta_x = 100;
		ray.x = ((int)(game->player->x / 100) * 100) + 100;
		if (angle == 0.0)
		{
			delta_y = 0;
			ray.y = game->player->y;
		}
		else
		{
			delta_y = 100 * tan(angle);
			ray.y = game->player->y + (int)(game->player->x - ray.x) * tan(angle);
		}
	}
	else
	{
		delta_x = -100;
		ray.x = ((int)(game->player->x / 100) * 100) - 1;
		if (angle == PI)
		{
			delta_y = 0;
			ray.y = game->player->y;			
		}
		else
		{
			delta_y = 100 * tan(angle);
			ray.y = game->player->y + (int)(game->player->x - ray.x) * tan(angle);
		}
	}
	while (ray.x < MAP_WIDTH && ray.y < MAP_HEIGHT && ray.x > 0 && ray.y > 0 && iswall(game, ray.x, ray.y) != 1)
	{
		ray.y += delta_y;
		ray.x += delta_x;
	}
	if (!(ray.x < MAP_WIDTH && ray.y < MAP_HEIGHT && ray.x > 0 && ray.y > 0))
	{
		ray.len = INT32_MAX;
		return (ray);
	}
	ray.len = pythagoras(game->player->x, game->player->y, ray.x, ray.y, angle);
	return (ray);
}

int iswall(t_game *game, int x, int y) {
	
	// mlx_put_pixel(game->player->img, y / 4, x / 4, ft_pixel(255, 128, 0, 255));
	// printf("\nmap_x = %d, map_y = %d\n", x, y);
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
	int h;
	double angle;
	int wall_top;
	int	wall_bottom;

	// angle = 1.0;
	// while (len > 0)
	// {
	// 	angle += (9.0 / 800);
	// 	len--;
	// }
	// n_len = 400.0 / angle;
	h = (800 / len) * 100;
	// printf("%d\n", h);
	j = 0;
	wall_top = (MAP_HEIGHT - h) / 2;
	if (wall_top > 800)
		h = 800;
	// wall_bottom = (MAP_HEIGHT - wall_top);
	while (j < 800)
	{
		if (j >= wall_top && j <= wall_bottom)
			mlx_put_pixel(game->player->img, col, j, color);
		// mlx_put_pixel(game->player->img, col, (MAP_HEIGHT / 2) - j, color);
		// mlx_put_pixel(game->player->img, col, (MAP_HEIGHT / 2) + j, color);
		j++;
	}
}

void	init_struct(t_game *game)
{
	game->mlx = NULL;
	game->player = malloc (sizeof(t_object));
	game->player->x = 400;
	game->player->y = 400;
	game->player->angle = PI;
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
	// printf("x = %f y = %f", game->player->x, game->player->y);
	draw_map(game);
	mlx_loop_hook(game->mlx, ft_hook, game);

	// mlx_key_hook(game->mlx, ft_hook, game);
	// mlx_loop_hook(game->mlx, ft_randomize, game->player->img);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}
