/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaracut <asaracut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 03:35:38 by asaracut          #+#    #+#             */
/*   Updated: 2025/11/25 03:36:53 by asaracut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

int start_game()
{
    void *mlx;
    void *win;

    mlx = mlx_init();                     // Initialise la minilibx
    if (!mlx)
        return (1);

    win = mlx_new_window(mlx, 800, 600, "Test MLX");  // Create window
    if (!win)
        return (1);

    mlx_loop(mlx);                        // Start event loop
    return (0);
}
