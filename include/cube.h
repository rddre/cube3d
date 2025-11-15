/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaracut <asaracut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 20:58:19 by asaracut          #+#    #+#             */
/*   Updated: 2025/11/15 23:17:43 by asaracut         ###   ########.fr       */
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

/*--- Define your structs here ---*/
typedef struct s_map
{
    char **map;         // La carte en 2D, chaque ligne = une rangée
    int width_map;          // Largeur de la carte
    int height_map;         // Hauteur de la carte
    char *north_texture;   // Chemin de la texture Nord
    char *south_texture;   // Chemin de la texture Sud
    char *west_texture;   // Chemin de la texture Ouest
    char *east_texture;   // Chemin de la texture Est
    int floor_color;    // Couleur du sol (RGB combiné en int)
    int sky_color;  // Couleur du plafond (RGB combiné en int)
    int player_x;       // Position X du joueur (float si tu veux précision)
    int player_y;       // Position Y du joueur
    char player_dir;    // Orientation du joueur ('N','S','E','W')
} t_map;
/*
typedef struct s_player
{
    double x;           // Position X
    double y;           // Position Y
    double plane_x;     // Plan de la caméra (pour le FOV)
    double plane_y;
} t_player;

typedef struct s_mlx // je sais pas encore que ca fait tout ca
{
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    char *addr;        // adresse de l’image
    int bpp;           // bits par pixel
    int line_length;
    int endian;
    int width;
    int height;
} t_mlx;

typedef struct s_texture
{
    void *img;
    int *data;        // tableau des pixels
    int width;
    int height;
} t_texture;*/

typedef struct s_cub
{
    t_map map;
    /*t_player player;
    t_mlx mlx;
    t_texture textures[4]; // NO SO WE EA*/
} t_cub;

/*--- error_exit.c ---*/
void	exit_error(char *message);

/*--- utils_lib.c ---*/
size_t	ft_strlen(const char *s);

#endif