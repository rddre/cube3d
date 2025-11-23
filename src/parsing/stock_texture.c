/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaracut <asaracut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 02:35:54 by asaracut          #+#    #+#             */
/*   Updated: 2025/11/23 03:39:47 by asaracut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

int stock_texture(char *line, t_cub *cub)
{
	char *texture_path;
	size_t i;
	int fd;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	texture_path = (char *)malloc(i + 1);
	if (!texture_path)
	{
		free_textures(cub);
		exit_error("Memory allocation failed for texture path", 1);
	}
	ft_memcpy(texture_path, line, i);
	texture_path[i] = '\0';

	// verify extension .xpm
	if (ft_strlen(texture_path) < 4 || ft_strcmp(texture_path + ft_strlen(texture_path) - 4, ".xpm") != 0)
	{
		free(texture_path);
		free_textures(cub);
		exit_error("Texture must be a .xpm file", 1);
	}

	// verify file is readable
	fd = open(texture_path, O_RDONLY);
	if (fd < 0)
	{
		free(texture_path);
		free_textures(cub);
		exit_error("Cannot open texture file", 1);
	}
	close(fd);

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
		exit_error("Invalid parsing step for texture, how did you get here?", 1);
	}
	return (0);
}
