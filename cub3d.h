/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 20:53:24 by sutku             #+#    #+#             */
/*   Updated: 2023/08/21 18:15:51 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <sys/time.h>
# include <fcntl.h>

# define PI 3.14159265359
# define SCREEN_WIDTH 1600
# define SCREEN_HEIGHT 800
# define MORE_ELEMENT "It is not two element in one line !"
# define FILE "File can not open !"
# define D_C "Direction or color element is not valid !"
# define F_C "F or C is not exist !"
# define RGB_COLOR "RGB color is missing or more than valid !"
# define ROT_SPEED 0.0174533
# define MOVE_SPEED 0.1
# define MAP_CONTENT "10NSWE"

typedef struct s_object
{
	double		x;
	double		y;
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

typedef struct s_coord
{
	double	x;
	double	y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
}t_coord;

typedef	struct s_color
{
	int	r;
	int	g;
	int	b;
}t_color;

typedef struct s_ray
{
	double		x;
	double		delta_x;
	double		y;
	double		delta_y;
	int			len;
}t_ray;

typedef struct s_wall
{
	mlx_texture_t	texture[4];
	int				no;
	int				so;
	int				we;
	int				ea;
	int				side;
}t_wall;

typedef struct s_game
{
	mlx_image_t	*img;
	char		**map;
	t_wall		wall;
	t_color		f_color;
	int				f;
	t_color		c_color;
	int				c;
	t_ray		ray;
	mlx_t		*mlx;
	t_object	*player;
	t_dir		dir;
	double		plane_x;
	double		plane_y;
	mlx_image_t	*texture;
}t_game;

void	open_image(char *str, t_game *game);
void	draw_lineof_texture(t_game *game, int col, double perpWallDist);
int		ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
t_coord	dda(t_game *game);
char    **parse_the_map(t_game *game, char *path);
int		len_of_double_array(char **str);
void	check_validity_of_input(t_game *game, char **str);
void	draw_map(t_game *game);
bool	is_floor_or_ceiling(t_game *game, char *str);
void	read_the_map(t_game *game, int fd);
void	is_valid_map(t_game *game);

//help functions
int		ft_isspace(char a);
int		ft_strcmp(char *str1, char *str2);
void	free_double_char_arr(char **str);
int		len_of_double_array(char **str);
int		my_strlen(char *str);
#endif