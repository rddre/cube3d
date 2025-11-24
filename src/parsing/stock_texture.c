/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaracut <asaracut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 02:35:54 by asaracut          #+#    #+#             */
/*   Updated: 2025/11/23 23:06:48 by asaracut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

int stock_texture(char *line, t_cub *cub)
{
    size_t  i;
    size_t  start;
    size_t  end;
    int     fd;
    char    *texture_path;

    // skip leading spaces
    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    start = i;
    // path until space/tab/newline or end
    while (line[i] && line[i] != '\n' && line[i] != ' ' && line[i] != '\t')
        i++;
    end = i; // exclusive end of path
    if (end == start)
    {
        free_textures(cub);
        exit_error("Empty texture path", 1);
    }
    // allocate path
    texture_path = (char *)malloc(end - start + 1);
    if (!texture_path)
    {
        free_textures(cub);
        exit_error("Memory allocation failed for texture path", 1);
    }
    ft_memcpy(texture_path, line + start, end - start);
    texture_path[end - start] = '\0';
    // extension check
    if (ft_strlen(texture_path) < 5 || ft_strcmp(texture_path + ft_strlen(texture_path) - 4, ".xpm") != 0)
    {
        free(texture_path);
        free_textures(cub);
        exit_error("Texture must end with .xpm", 1);
    }
    // after path: only spaces/tabs until optional newline/end
    while (line[i] && line[i] != '\n')
    {
        if (line[i] != ' ' && line[i] != '\t')
        {
            free(texture_path);
            free_textures(cub);
            exit_error("Invalid characters after .xpm", 1);
        }
        i++;
    }
    // verify file readable
    fd = open(texture_path, O_RDONLY);
    if (fd < 0)
    {
        free(texture_path);
        free_textures(cub);
        exit_error("Cannot open texture file", 1);
    }
    close(fd);
    // store based on step
    if (cub->map.parsing_step == 0)
        cub->map.no_texture = texture_path;
    else if (cub->map.parsing_step == 1)
        cub->map.so_texture = texture_path;
    else if (cub->map.parsing_step == 2)
        cub->map.we_texture = texture_path;
    else if (cub->map.parsing_step == 3)
        cub->map.ea_texture = texture_path;
    else
    {
        free(texture_path);
        free_textures(cub);
        exit_error("Invalid parsing step for texture", 1);
    }
    return (0);
}
