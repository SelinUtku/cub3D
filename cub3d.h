/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 20:53:24 by sutku             #+#    #+#             */
/*   Updated: 2023/08/15 19:41:00 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <sys/time.h>
# include <fcntl.h>
# define PI 3.14159265359
# define SCREEN_WIDTH 1600
# define SCREEN_HEIGHT 800

typedef struct s_object
{
	double			x;
	double			y;
	double		dir_x;
	double		dir_y;
}t_object;

typedef enum e_dir
{
	NO,
	SO,
	WE,
	EA,
}t_dir;

typedef struct s_game
{
	mlx_image_t	*img;
	mlx_t		*mlx;
	mlx_t		*ray_mlx;
	t_object	*player;
	t_dir		dir;
	double		plane_x;
	double		plane_y;
	mlx_image_t	*texture;
}t_game;

typedef struct s_ray
{
	int		x;
	int		y;
	int		len;
	double	angle;
}t_ray;

void	open_image(char *str, t_game *game);
mlx_image_t	*convert_to_image(t_game *game, char *path);


#endif