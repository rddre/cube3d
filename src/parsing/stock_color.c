/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaracut <asaracut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 23:17:56 by asaracut          #+#    #+#             */
/*   Updated: 2025/11/23 23:45:23 by asaracut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

int stock_color(char *line, t_cub *cub)
{
    int r;
    int g;
    int b;

    skip_spaces(&line);
    if (*line < '0' || *line > '9')
		free_texture_exit(cub, "Invalid color format");
    r = ft_atoi(line);
    while (*line >= '0' && *line <= '9')
        line++;
    skip_spaces(&line);
    if (*line != ',')
		free_texture_exit(cub, "Invalid color format");
    line++;
    skip_spaces(&line);
    if (*line < '0' || *line > '9')
		free_texture_exit(cub, "Invalid color format");
    g = ft_atoi(line);
    while (*line >= '0' && *line <= '9')
        line++;
    skip_spaces(&line);
    if (*line != ',')
		free_texture_exit(cub, "Invalid color format");
    line++;
    skip_spaces(&line);
    if (*line < '0' || *line > '9')
		free_texture_exit(cub, "Invalid color format");
    b = ft_atoi(line);
    while (*line >= '0' && *line <= '9')
        line++;
    skip_spaces(&line);
    if (*line != '\0' && *line != '\n')
		free_texture_exit(cub, "Invalid color format");
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		free_texture_exit(cub, "Color values must be between 0 and 255");
    if (cub->map.parsing_step == 4)
        cub->map.floor_color = (r << 16) | (g << 8) | b;
    else if (cub->map.parsing_step == 5)
        cub->map.sky_color = (r << 16) | (g << 8) | b;
    return (0);
}
