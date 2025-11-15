/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaracut <asaracut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 20:58:16 by asaracut          #+#    #+#             */
/*   Updated: 2025/11/15 22:45:20 by asaracut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int	check_extension(char *map_name)
{
	size_t	i;

	i = 0;
	while (map_name[i])
		i++;
	if (i < 4)
		return (0);
	
	if (map_name[i - 1] != 'r' || map_name[i - 2] != 'e'
		|| map_name[i - 3] != 'b' || map_name[i - 4] != '.')
		return (0);

	return (1);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (exit_error("Invalid number of arguments"), 1);
	if (!check_extension(av[1]))
		return (exit_error("Map file must be a *.cub"), 1);
	
	if (parsing(av[1]))
		return (1);

	return (0);
}
