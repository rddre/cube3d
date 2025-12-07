/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaracut <asaracut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 20:58:19 by asaracut          #+#    #+#             */
/*   Updated: 2025/12/07 02:54:09 by asaracut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "../minilibx-linux/mlx.h"

# define speed 0.1
# define ROT_SPEED 0.05
# define M_PI 3.14159265358979323846

/*--- Define your structs here ---*/
typedef struct s_map
{
    char **map;         // La carte en 2D, chaque ligne = une rangée

    char *no_texture;   // Chemin de la texture Nord
    char *so_texture;   // Chemin de la texture Sud
    char *we_texture;   // Chemin de la texture Ouest
    char *ea_texture;   // Chemin de la texture Est

    int floor_color;    // Couleur du sol (RGB combiné en int)
    int sky_color;  // Couleur du plafond (RGB combiné en int)

    int player_x;       // Position X du joueur (float si tu veux précision)
    int player_y;       // Position Y du joueur
    char player_dir;    // Orientation du joueur ('N','S','E','W')

    int width_map;          // Largeur de la carte
    int height_map;         // Hauteur de la carte

	int parsing_step; // Indicateur de l'étape de parsing en cours
	int nombre_player; // Nombre de joueurs trouvés dans la carte
} t_map;

typedef struct s_player
{
    double x;
    double y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
} t_player;

typedef struct s_img
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}   t_img;

typedef struct s_move
{
    double nx;
    double ny;
    int    mx;
    int    my;
} t_move;

typedef struct s_tex
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
} t_tex;

typedef struct s_cub
{
    t_map		map;
    t_player	player;
	t_img		img;
    t_move		move;
	// textures loaded from XPM
	t_tex		tex_no;
	t_tex		tex_so;
	t_tex		tex_we;
	t_tex		tex_ea;
} t_cub;

/*--- display ---*/
int		start_game(t_cub *cub);
int		handle_key(int key, t_cub *cub);
int		handle_exit(t_cub *cub);
void	render_frame(t_cub *cub, void *mlx, void *win);
void	put_pixel(t_img *img, int x, int y, int color);
int		get_tex_color(t_tex *tex, int tex_x, int tex_y);
void	load_textures(t_cub *cub);

/*--- movement ---*/
void	rotation(int direction, t_cub *cub);
void	move_player_w(t_cub *cub);
void	move_player_s(t_cub *cub);
void	move_player_a(t_cub *cub);
void	move_player_d(t_cub *cub);
void	move_valid_or_no(t_cub *cub);

/*--- parsing.c ---*/
int		parsing(char *map, t_cub *cub);
int		empty_line(char *line);
int		skip_spaces(char **line);
size_t	line_len_no_nl(char *line);
int		stock_info(char *line, t_cub *cub);
int		stock_map(char *line, t_cub *cub);
int		stock_texture(char *line, t_cub *cub);
int		stock_color(char *line, t_cub *cub);
void	parse_map(t_cub *cub);

/*--- error_exit.c ---*/
void	exit_error(char *message, int code);
void	free_textures(t_cub *cub);
void	free_texture_exit(t_cub *cub, char *message);
void	free_map(t_cub *cub);
void	free_all(t_cub *cub);
void	free_all_exit(t_cub *cub, char *message);

/*--- utils_lib.c ---*/
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*get_next_line(int fd);
int		ft_atoi(const char *str);
char	**ft_realloc_matrix(char **old, int old_size, int new_size);

/*--- init.c ---*/
void	init_cub(t_cub *cub);
void	init_player(t_cub *cub, char direction);

#endif