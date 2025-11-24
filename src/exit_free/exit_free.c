/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaracut <asaracut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 22:44:24 by asaracut          #+#    #+#             */
/*   Updated: 2025/11/23 23:44:06 by asaracut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

void free_textures(t_cub *cub)
{
	if (cub->map.no_texture)
		free(cub->map.no_texture);
	if (cub->map.so_texture)
		free(cub->map.so_texture);
	if (cub->map.we_texture)
		free(cub->map.we_texture);
	if (cub->map.ea_texture)
		free(cub->map.ea_texture);
}

void free_texture_exit(t_cub *cub, char *message)
{
	free_textures(cub);
	exit_error(message, 1);
}
