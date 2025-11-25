/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaracut <asaracut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 03:02:59 by asaracut          #+#    #+#             */
/*   Updated: 2025/11/25 03:03:23 by asaracut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

void init_cub(t_cub *cub)
{
	ft_memset(cub, 0, sizeof(t_cub));
}

void    init_player(t_cub *cub, char orientation)
{
    if (orientation == 'N')
    {
        cub->player.dir_x = 0;
        cub->player.dir_y = -1;
        cub->player.plane_x = 0.66;
        cub->player.plane_y = 0;
    }
    else if (orientation == 'S')
    {
        cub->player.dir_x = 0;
        cub->player.dir_y = 1;
        cub->player.plane_x = -0.66;
        cub->player.plane_y = 0;
    }
    else if (orientation == 'E')
    {
        cub->player.dir_x = 1;
        cub->player.dir_y = 0;
        cub->player.plane_x = 0;
        cub->player.plane_y = 0.66;
    }
    else if (orientation == 'W')
    {
        cub->player.dir_x = -1;
        cub->player.dir_y = 0;
        cub->player.plane_x = 0;
        cub->player.plane_y = -0.66;
    }
}
