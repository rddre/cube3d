/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaracut <asaracut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 02:18:07 by asaracut          #+#    #+#             */
/*   Updated: 2025/11/24 22:00:57 by asaracut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

int stock_map(char *line, t_cub *cub)
{
    size_t  len;
    int     i;
    char    *dup;

    // replace trailing newline length
    len = line_len_no_nl(line);
    if ((int)len > cub->map.width_map)
        cub->map.width_map = (int)len;
    cub->map.height_map++;
    // validate and normalize
    i = 0;
    while (line[i] && line[i] != '\n')
    {
        if (line[i] == '\t')
            line[i] = ' ';
        if (line[i] != ' ' && line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
        {
            write(1, "wrong caractere in map\n", 23);
            return (-1);
        }
        if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
        {
            if (cub->map.player_dir == 0)
            {
                cub->map.player_dir = line[i];
                cub->map.player_x = i;
                cub->map.player_y = cub->map.height_map - 1;
            }
            cub->map.nombre_player++;
        }
        i++;
    }
    // duplicate line up to len
    dup = (char *)malloc(len + 1);
    if (!dup)
        return (-1);
    ft_memcpy(dup, line, len);
    dup[len] = '\0';
    // reallocate matrix and store
    cub->map.map = ft_realloc_matrix(cub->map.map, cub->map.height_map - 1, cub->map.height_map);
    if (!cub->map.map)
    {
        free(dup);
        return (-1);
    }
    cub->map.map[cub->map.height_map - 1] = dup;
    return (0);
}