/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaracut <asaracut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 20:58:16 by asaracut          #+#    #+#             */
/*   Updated: 2025/11/23 03:29:33 by asaracut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int	check_extension(char *map_name)
{
	size_t	len;
	char	*ext;

	len = ft_strlen(map_name);
	if (len < 4)
		return (0);
	
	ext = map_name + len - 4;
	if (ft_strcmp(ext, ".cub") != 0)
		return (0);

	return (1);
}

void init_cub(t_cub *cub)
{
	ft_memset(cub, 0, sizeof(t_cub));
}

void print_info(t_cub *cub)
{
	printf("NO Texture: %s\n", cub->map.no_texture);
	printf("SO Texture: %s\n", cub->map.so_texture);
	printf("WE Texture: %s\n", cub->map.we_texture);
	printf("EA Texture: %s\n", cub->map.ea_texture);
	printf("Floor Color: %d\n", cub->map.floor_color);
	printf("Sky Color: %d\n", cub->map.sky_color);
	printf("Map Width: %d\n", cub->map.width_map);
	printf("Map Height: %d\n", cub->map.height_map);
	printf("Player Position: (%d, %d)\n", cub->map.player_x, cub->map.player_y);
	printf("Player Direction: %c\n", cub->map.player_dir);
}

int	main(int ac, char **av)
{
	t_cub cub;

	if (ac != 2)
		exit_error("Invalid number of arguments", 1);
	if (!check_extension(av[1]))
		exit_error("Map file must be a *.cub", 1);

	init_cub(&cub);

	if (parsing(av[1], &cub)) // parsing renvoie jamais d'erreur
		return (write(2, "Parsing failed\n", 15), 1); // a effacer
	printf("\n\n\n");
	print_info(&cub);
	return (0);
}
