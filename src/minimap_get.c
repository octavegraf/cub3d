/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:11:12 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/16 14:02:18 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "cub3d.h"

static unsigned int	tab_size(char	**tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

static int	init_minimap(t_game *game, int radius_map)
{
	int		i;

	game->scene.minimap = malloc(sizeof(char *) * ((radius_map * 2) + 1));
	if (game->scene.minimap == NULL)
		return (ft_dprintf(2, ERR_MALLOC), 0);
	i = 0;
	while (i < (radius_map * 2) + 1)
	{
		game->scene.minimap[i] = malloc(sizeof(char) * ((radius_map * 2) + 1));
		if (game->scene.minimap[i] == NULL)
			return (minimap_free(&(game->scene.minimap), i, radius_map), 0);
		i++;
	}
	return (1);
}

static void	minimap_get_j(t_game *game, int i, int radius_map, int map_size_x)
{
	int	map_size_y;
	int	j;

	if (i + ((int)(game->player.pos_x)) - radius_map >= 0
			&& i + ((int)(game->player.pos_x)) - radius_map < map_size_x)
		map_size_y = ft_strlen(game->scene.map
			[i + ((int)(game->player.pos_x)) - radius_map]);
	else
		map_size_y = -1;
	j = 0;
	while (j < (radius_map * 2) + 1)
	{
		if (i + ((int)(game->player.pos_x)) - radius_map < 0
			|| i + ((int)(game->player.pos_x)) - radius_map >= map_size_x
			|| j + ((int)(game->player.pos_y)) - radius_map < 0
			|| j + ((int)(game->player.pos_y)) - radius_map >= map_size_y)
			game->scene.minimap[i][j] = wall;
		else
			game->scene.minimap[i][j] = game->scene.map[i
				+ ((int)(game->player.pos_x)) - radius_map][j
				+ ((int)(game->player.pos_y)) - radius_map];
		j++;
	}
}

int	minimap_get(t_game *game, int radius_map)
{
	int		i;
	int		map_size_x;

	if (init_minimap(game, radius_map) == 0)
		return (0);
	i = 0;
	map_size_x = tab_size(game->scene.map);
	while (i < (radius_map * 2) + 1)
	{
		minimap_get_j(game, i, radius_map, map_size_x);
		i++;
	}
	return (1);
}
#endif
