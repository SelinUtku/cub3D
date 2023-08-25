/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 20:53:24 by sutku             #+#    #+#             */
/*   Updated: 2023/08/25 03:53:21 by sutku            ###   ########.fr       */
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

//CONSTANTS
# define PI 3.14159265359
# define SCREEN_WIDTH 1600
# define SCREEN_HEIGHT 800
# define ROT_SPEED 0.0174533
# define MOVE_SPEED 0.1
//FILE ERRORS
# define FILE "File could not open !"
# define W_FILE "Incomplete file !"
# define TEXT_FILE "Texture file can not open !"
//ELEMENT ERRORS
# define W_ELEMENT "Element id is not valid !"
# define W_DIRECTION "Direction identifier is not valid !"
# define MISS_TEXT "Missing texture of one of the directions !"
# define W_FLOOR "Duplicate or missing floor argument !"
# define W_CEILING "Duplicate or missing ceiling argument !"
# define TEXT_PATH "There is no texture path !"
# define NO_XPM42 "Texture type is not .xpm42 !"
# define MULTI_TEXT "Multiple texture of one of the directions !"
//COLOR ERRORS
# define RGB_NO_COLOR "RGB color is missing or more than valid !"
# define RGB_NO_NUM "Rgb colors are not number !"
# define RGB_RANGE "Rgb colors are not 0-255 !"
# define F_C_NO_ARG "F or C does not have proper arguments !"
//MAP ERRORS
# define NO_MAP "Map does not exist !"
# define INV_CHAR "Invalid character !"
# define EMPTY_LINE "Empty line in map !"
# define NO_PLAY_DIR "There is no player direction !"
# define MULTI_DIR "Multiple player direction !"

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
	int				num_texture[4];
	int				side;
}t_wall;

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
}t_map;

typedef struct s_game
{
	mlx_image_t	*img;
	char		*elements[7];
	int			num_elements;
	t_map		map;
	t_wall		wall;
	t_color		f_color;
	t_color		c_color;
	int			f;
	int			c;
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
int		len_of_double_array(char **str);
void	draw_map(t_game *game);
void	read_the_map(t_game *game, int fd);
void	is_valid_map(t_game *game);
char	*delete_slash_n(char *str);

//parsing.c
void	open_map_file(t_game *game, char *path);
void	parse_the_elements(t_game *game, int fd);
bool	check_number_of_elements(t_game *game);
void	check_validity_of_elements(t_game *game);
void	direction_or_color(t_game *game, char *str);

//help functions
int		ft_isspace(char a);
int		ft_strcmp(char *str1, char *str2);
void	free_double_char_arr(char **str);
int		len_of_double_array(char **str);
void	free_elements(t_game *game);
void	error_handler(t_game *game, char *str);
void	skip_spaces(char *str, int *i);

//wall_check.c
void	left_wall_check(t_game *game);
void	right_wall_check(t_game *game);
void	top_wall_check(t_game *game);
void	bottom_wall_check(t_game *game);

//wall_textures.c
void	is_valid_direction(t_game *game, char *str);
void	check_direction_exist(t_game *game, t_dir dir, char *path);
void	load_direction_texture(t_game *game, char *str, t_dir dir);

//floor_ceiling.c
void	floor_or_ceiling(t_game *game, char *str);
void	control_f_c_args(t_game *game, char *str, t_color *color);
void	is_valid_rgb(t_game *game, char **str);
void	put_rgb_colors(t_color *color, char **str);

void	ft_key_hook(void *param);
void	init_struct(t_game *game);
void	player_position(t_game *game);


void	print_map(t_game *game);
#endif