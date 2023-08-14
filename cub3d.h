/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 20:53:24 by sutku             #+#    #+#             */
/*   Updated: 2023/08/14 20:51:02 by sutku            ###   ########.fr       */
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

typedef struct s_game
{
	mlx_image_t	*img;
	mlx_t		*mlx;
	mlx_t		*ray_mlx;
	t_object	*player;
	double		plane_x;
	double		plane_y;
	double		time;
	double		old_time;
}t_game;

typedef struct s_ray
{
	int		x;
	int		y;
	int		len;
	double	angle;
}t_ray;

#endif