/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaracut <asaracut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 02:18:07 by asaracut          #+#    #+#             */
/*   Updated: 2025/11/24 00:14:55 by asaracut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

int stock_map(char *line, t_cub *cub)
{
	(void)line;

	if (line_len_no_nl(line) > (size_t)cub->map.width_map)
		cub->map.width_map = line_len_no_nl(line);
	cub->map.height_map += 1;

	cub->map.map = ft_realloc_matrix(cub->map.map, cub->map.height_map - 1, cub->map.height_map);
	if (!cub->map.map)
		return (-1);
	cub->map.map[cub->map.height_map - 1] = line;
	return (0);
}