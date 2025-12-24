/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw_doors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:57:28 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/24 15:02:52 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS

# include "cub3d.h"

static int	e_chr_doors(unsigned int c)
{
	if (c == c_l || c == c_u || c == o_l || c == o_u)
		return (1);
	return (0);
}

static int	draw_open_left(t_game *g, t_quadri *q, int map_char, int radius_map)
{
	int	save;

	if (map_char == o_l)
	{
		save = q->x_start;
		if (q->y_start == 0)
			q->y_end -= g->scene.minimap_scale_screen_map / 2;
		else if (q->y_end - q->y_start >= g->scene.minimap_scale_screen_map / 2)
			q->y_end = q->y_start + g->scene.minimap_scale_screen_map / 2 - 1;
		if (q->x_end != 2 * radius_map * g->scene.minimap_scale_screen_map - 1)
		{
			q->x_start = q->x_end;
			fill_quadri_minimap(g, q);
		}
		if (save != 0)
		{
			q->x_start = save;
			q->x_end = q->x_start;
			fill_quadri_minimap(g, q);
		}
		return (1);
	}
	return (0);
}

static int	draw_open_up(t_game *g, t_quadri *q, int map_char, int radius_map)
{
	int	save;

	if (map_char == o_u)
	{
		save = q->y_start;
		if (q->x_start == 0)
			q->x_end -= g->scene.minimap_scale_screen_map / 2;
		else if (q->x_end - q->x_start >= g->scene.minimap_scale_screen_map / 2)
			q->x_end = q->x_start + g->scene.minimap_scale_screen_map / 2 - 1;
		if (q->y_end != (2 * radius_map * g->minimap_scale_screen_map) - 1)
		{
			q->y_start = q->y_end;
			fill_quadri_minimap(g, q);
		}
		if (save != 0)
		{
			q->y_start = save;
			q->y_end = q->y_start;
			fill_quadri_minimap(g, q);
		}
		return (1);
	}
	return (0);
}

static void	quadri_draw_doors(t_game *game, t_quadri *q, char c, int radius_map)
{
	if (draw_open_left(game, q, c, radius_map))
		;
	else if (draw_open_up(game, q, c, radius_map))
		;
	else if (c == c_l && q->y_start != 0)
	{
		q->y_end = q->y_start;
		fill_quadri_minimap(game, q);
	}
	else if (c == c_u && q->x_start != 0)
	{
		q->x_end = q->x_start;
		fill_quadri_minimap(game, q);
	}
}

void	draw_doors(t_game *g, int radius_map)
{
	int			i;
	int			j;
	t_quadri	q;

	i = 0;
	while (i < (radius_map * 2) + 1)
	{
		j = 0;
		while (j < (radius_map * 2) + 1)
		{
			if (e_chr_doors(g->scene.minimap[i][j]))
			{
				quadri_get_x(g, i, &q, radius_map);
				quadri_get_y(g, j, &q, radius_map);
				q.color = RED;
				quadri_draw_doors(g, &q, g->scene.minimap[i][j], radius_map);
			}
			j++;
		}
		i++;
	}
}

#endif
