/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaracut <asaracut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 21:52:47 by asaracut          #+#    #+#             */
/*   Updated: 2025/11/22 02:58:20 by asaracut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

int verifi_line(char *line, t_cub *cub)
{
	(void)cub;
	printf("Read line: %s", line);
	return (0);
}

int read_map(int fd, t_cub *cub)
{
	char *line;

	(void)cub;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (verifi_line(line, cub) != 0)
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	return (0);
}

int parsing(char *map, t_cub *cub)
{
	int fd;

	(void)cub;
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (exit_error("Could not open map file"), 1);

	if (read_map(fd, cub) != 0)
		return (exit_error("Could not read map file"), 1);

	close(fd);
	write(1, "Parsing successful\n", 20);
	return (0);
}
