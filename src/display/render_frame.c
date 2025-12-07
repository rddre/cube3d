/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaracut <asaracut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 23:43:17 by asaracut          #+#    #+#             */
/*   Updated: 2025/12/07 03:25:41 by asaracut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"
#include <math.h>

// Step 1: declare raycasting variables
static void rf_declare_vars(int *img_w, int *img_h)
{
    *img_w = 800;
    *img_h = 600;
}

// Step 2: loop columns
static void rf_loop_columns(t_cub *cub, int img_w, int img_h, void *mlx, void *win);

// Step 3: compute ray direction for column
static void rf_compute_ray(int x, int img_w, t_cub *cub, double *ray_dir_x, double *ray_dir_y)
{
    double camera_x;

    camera_x = 2.0 * x / (double)img_w - 1.0;
    *ray_dir_x = cub->player.dir_x + cub->player.plane_x * camera_x;
    *ray_dir_y = cub->player.dir_y + cub->player.plane_y * camera_x;
}

// Step 4: DDA to find wall hit
static int rf_dda_hit(t_cub *cub, double ray_dir_x, double ray_dir_y, int *side, double *perp_wall_dist)
{
    int map_x;
    int map_y;
    double side_dist_x;
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    int step_x;
    int step_y;
    int hit;

    map_x = cub->player.x;
    map_y = cub->player.y;
    hit = 0;
    delta_dist_x = (ray_dir_x == 0.0) ? 1e30 : fabs(1.0 / ray_dir_x);
    delta_dist_y = (ray_dir_y == 0.0) ? 1e30 : fabs(1.0 / ray_dir_y);
    if (ray_dir_x < 0)
    {
        step_x = -1;
        side_dist_x = (cub->player.x - map_x) * delta_dist_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - cub->player.x) * delta_dist_x;
    }
    if (ray_dir_y < 0)
    {
        step_y = -1;
        side_dist_y = (cub->player.y - map_y) * delta_dist_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - cub->player.y) * delta_dist_y;
    }
    while (!hit)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            *side = 0;
        }
        else
        {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            *side = 1;
        }
        if (map_y < 0 || map_y >= cub->map.height_map || map_x < 0 || map_x >= (int)ft_strlen(cub->map.map[map_y]))
            return 0;
        if (cub->map.map[map_y][map_x] == '1')
            hit = 1;
    }
    if (*side == 0)
        *perp_wall_dist = (side_dist_x - delta_dist_x);
    else
        *perp_wall_dist = (side_dist_y - delta_dist_y);
    return 1;
}

int get_tex_color(t_tex *tex, int tex_x, int tex_y)
{
    char *dst;

    if (tex_x < 0)
        tex_x = 0;
    if (tex_x >= tex->width)
        tex_x = tex->width - 1;
    if (tex_y < 0)
        tex_y = 0;
    if (tex_y >= tex->height)
        tex_y = tex->height - 1;
    dst = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
    return (*(int *)dst);
}

// Step 5: draw wall column with texture
static void rf_draw_column(t_cub *cub, int x, int img_h, int line_h, int side, double wall_x, double ray_dir_x, double ray_dir_y)
{
    int start;
    int end;
    int y;
    t_tex *tex;
    int tex_x;
    double step;
    double tex_pos;
    int tex_y;
    int color;

    // choose texture based on side / direction
    if (side == 0 && ray_dir_x > 0)
        tex = &cub->tex_we;
    else if (side == 0 && ray_dir_x < 0)
        tex = &cub->tex_ea;
    else if (side == 1 && ray_dir_y > 0)
        tex = &cub->tex_no;
    else
        tex = &cub->tex_so;

    start = -line_h / 2 + img_h / 2;
    if (start < 0)
        start = 0;
    end = line_h / 2 + img_h / 2;
    if (end >= img_h)
        end = img_h - 1;

    tex_x = (int)(wall_x * (double)tex->width);
    if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
        tex_x = tex->width - tex_x - 1;
    step = 1.0 * tex->height / line_h;
    tex_pos = (start - img_h / 2 + line_h / 2) * step;
    y = start;
    while (y <= end)
    {
        tex_y = (int)tex_pos;
        if (tex_y < 0)
            tex_y = 0;
        if (tex_y >= tex->height)
            tex_y = tex->height - 1;
        tex_pos += step;
        color = get_tex_color(tex, tex_x, tex_y);
        put_pixel(&cub->img, x, y, color);
        y++;
    }
}

// Paint background: top = sky, bottom = floor
static void rf_paint_bg(t_cub *cub, int img_w, int img_h)
{
    int x;
    int y;

    y = 0;
    while (y < img_h)
    {
        int color = (y < img_h / 2) ? cub->map.sky_color : cub->map.floor_color;
        x = 0;
        while (x < img_w)
        {
            put_pixel(&cub->img, x, y, color);
            x++;
        }
        y++;
    }
}

static void rf_loop_columns(t_cub *cub, int img_w, int img_h, void *mlx, void *win)
{
    int x;

    (void)win;
    for (x = 0; x < img_w; x++)
    {
        double ray_dir_x;
        double ray_dir_y;
        int side;
        double perp_wall_dist;
        int line_h;
        double wall_x;

        rf_compute_ray(x, img_w, cub, &ray_dir_x, &ray_dir_y);
        if (!rf_dda_hit(cub, ray_dir_x, ray_dir_y, &side, &perp_wall_dist))
            continue;
        if (perp_wall_dist <= 0.0001)
            perp_wall_dist = 0.0001;
        line_h = (int)(img_h / perp_wall_dist);
        // calculate exact wall hit position for texture mapping
        if (side == 0)
            wall_x = cub->player.y + perp_wall_dist * ray_dir_y;
        else
            wall_x = cub->player.x + perp_wall_dist * ray_dir_x;
        wall_x -= floor(wall_x);
        rf_draw_column(cub, x, img_h, line_h, side, wall_x, ray_dir_x, ray_dir_y);
    }
    mlx_put_image_to_window(mlx, win, cub->img.img, 0, 0);
}

void render_frame(t_cub *cub, void *mlx, void *win)
{
    int img_w;
    int img_h;

    rf_declare_vars(&img_w, &img_h);
    // destroy previous frame image if it exists to avoid leaks when re-rendering
    if (cub->img.img)
        mlx_destroy_image(mlx, cub->img.img);
    cub->img.img = mlx_new_image(mlx, img_w, img_h);
    cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bpp,
            &cub->img.line_len, &cub->img.endian);
    rf_paint_bg(cub, img_w, img_h);
    rf_loop_columns(cub, img_w, img_h, mlx, win);
}