/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 20:53:24 by sutku             #+#    #+#             */
/*   Updated: 2023/08/09 01:35:12 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# define PI 3.14159265359
# define MAP_WIDTH 800
# define MAP_HEIGHT 800
# define row 8
# define column 8
# define max_row 8
# define max_column 8

typedef struct s_object
{
	mlx_image_t	*img;
	int			x;
	int			y;
	double		angle;
	double		delta_x;
	double		delta_y;
}t_object;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_t		*ray_mlx;
	t_object	*player;
}t_game;

typedef struct s_ray
{
	int		x;
	int		y;
	int		len;
	double	angle;
}t_ray;

#endif