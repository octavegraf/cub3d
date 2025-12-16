/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_identify_map_extra.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 11:59:57 by ocgraf            #+#    #+#             */
/*   Updated: 2025/12/15 16:07:18 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#ifdef BONUS

static int	identify_map2(t_game *game);
static int	identify_map_doors(t_game *game);
static int	identify_map_sprites(t_game *game);

int	identify_map(char **map, t_game *game)
{
	int	i;
	int	j;
	int	p;

	i = -1;
	p = 0;
	game->scene.map = map;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				p++;
			else if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' '
				&& map[i][j] != '\f' && map[i][j] != '\r' && map[i][j] != '\t'
				&& map[i][j] != '\v' && map[i][j] != 'D' && map[i][j] != 'T')
				return (ft_dprintf(2, ERR_INVALID_MAP_CHAR), 1);
		}
	}
	if (p != 1)
		return (ft_dprintf(2, ERR_INVALID_PLAYER_COUNT), 1);
	return (identify_map2(game));
}

static int	identify_map2(t_game *game)
{
	size_t	i;
	size_t	j;
	char	**map;

	map = game->scene.map;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (ft_strchr(&MAP_ELEMENTS[1], map[i][j]))
			{
				if (!i || !j || !map[i][j + 1] || ft_strlen(map[i - 1]) <= j
					|| ft_strlen(map[i + 1]) <= j
					|| !ft_strchr(MAP_ELEMENTS, map[i - 1][j])
					|| !ft_strchr(MAP_ELEMENTS, map[i + 1][j])
					|| !ft_strchr(MAP_ELEMENTS, map[i][j - 1])
					|| !ft_strchr(MAP_ELEMENTS, map[i][j + 1]))
					return (ft_dprintf(2, ERR_MAP_OPEN, i, j), 1);
			}
		}
	}
	return (identify_map_doors(game));
}

static int	identify_map_doors(t_game *game)
{
	size_t	i;
	size_t	j;
	char	**map;

	map = game->scene.map;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'D')
			{
				if (!i || !j || ft_strlen(map[i - 1]) <= j || ft_strlen(map[i
							+ 1]) <= j || ((map[i][j - 1] != '1' || map[i][j
						+ 1] != '1') && (map[i - 1][j] != '1' || map[i + 1]
									[j] != '1')) || !game->scene.textures[D])
					return (ft_dprintf(2, ERR_DOOR_MISS_WALLS), 1);
				map[i][j] = c_l;
				if (map[i][j - 1] == '1' && map[i][j + 1] == '1')
					map[i][j] = c_u;
			}
		}
	}
	return (identify_map_sprites(game));
}

static int	identify_map_sprites(t_game *game)
{
	size_t	i;
	size_t	j;
	char	**map;

	map = game->scene.map;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'T')
			{
				if (!game->scene.textures[T])
					return (ft_dprintf(2, ERR_SPRITE_TEXTURES), 1);
			}
		}
	}
	return (map_remove_whitespaces(game));
}

#endif
