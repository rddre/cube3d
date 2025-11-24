/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaracut <asaracut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 21:56:05 by asaracut          #+#    #+#             */
/*   Updated: 2025/11/24 21:56:46 by asaracut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

void parse_map(t_cub *cub)
{
	if (cub->map.nombre_player != 1)
	{
		free_textures(cub);
		exit_error("There must be exactly one player in the map", 1);
	}
}
