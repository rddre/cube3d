/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaracut <asaracut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 20:58:16 by asaracut          #+#    #+#             */
/*   Updated: 2025/11/22 01:57:59 by asaracut         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_cub cub;

	if (ac != 2)
		return (exit_error("Invalid number of arguments"), 1);
	if (!check_extension(av[1]))
		return (exit_error("Map file must be a *.cub"), 1);

	init_cub(&cub);

	if (parsing(av[1], &cub))
		return (write(2, "Parsing failed\n", 15), 1);

	return (0);
}
