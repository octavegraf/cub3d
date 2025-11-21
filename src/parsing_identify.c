/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_identify.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:07:34 by ocgraf            #+#    #+#             */
/*   Updated: 2025/11/21 19:32:24 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	identify_map2(t_game *game, char *set);

int	identify(char *line, t_game *game)
{
	int	i;

	i = 0;
	if (ft_strlen(line) < 3)
		return (ft_dprintf(2, ERR_WRONG_LINE), 1);
	while (!ft_isprint(line[i]) || line[i] == ' ')
		i++;
	if (!ft_strncmp(line + i, "NO", 2) || !ft_strncmp(line + i, "SO", 2)
		|| !ft_strncmp(line + i, "WE", 2) || !ft_strncmp(line + i, "EA", 2))
		return (identify_textures(line + i, game));
	else if (!ft_strncmp(line + i, "F", 1) || !ft_strncmp(line + i, "C", 1))
		return (identify_colors(line + i, game));
	else
		return (ft_dprintf(2, ERR_UNKNOWN_ID), 1);
}

int	identify_textures(char *line, t_game *game)
{
	char	*path;

	path = search_infos(line + 2, 0);
	if (!ft_strncmp(line, "NO", 2))
		game->scene.textures[NO] = path;
	else if (!ft_strncmp(line, "SO", 2))
		game->scene.textures[SO] = path;
	else if (!ft_strncmp(line, "WE", 2))
		game->scene.textures[WE] = path;
	else if (!ft_strncmp(line, "EA", 2))
		game->scene.textures[EA] = path;
	if (readable_file(path) == 1)
		return (ft_dprintf(2, ERR_TEXTURE_NOT_READABLE), 1);
	if (ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 4))
		return (ft_dprintf(2, ERR_TEXTURE_NOT_XPM), 1);
	return (0);
}

int	identify_colors(char *line, t_game *game)
{
	int		rgb[3];
	int		i;
	char	*color;
	char	*temp;

	if (ft_strlen(line) < 1 || (line[0] != 'F' && line[0] != 'C'))
		return (ft_dprintf(2, ERR_UNKNOWN_COLOR_ID), 1);
	color = search_infos(line + 1, 1);
	if (!color || !*color)
		return (free(color), ft_dprintf(2, ERR_COLOR_OUT_OF_RANGE), 1);
	temp = color;
	i = -1;
	while (++i < 3 && ft_wstrlen(temp))
	{
		rgb[i] = ft_atoi(temp);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (free(color), ft_dprintf(2, ERR_COLOR_OUT_OF_RANGE), 1);
		if (i < 2)
		{
			temp = ft_strchr(temp, ',');
			if (!temp)
				return (free(color), ft_dprintf(2, ERR_COLOR_OUT_OF_RANGE), 1);
			temp++;
		}
		i++;
	}
	if (i != 4)
		return (free(color), ft_dprintf(2, ERR_COLOR_OUT_OF_RANGE), 1);
	if (line[0] == 'F')
		game->scene.floor_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	else
		game->scene.ceiling_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (free(color), 0);
}

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
				&& map[i][j] != '\v')
				return (ft_dprintf(2, ERR_INVALID_MAP_CHAR), 1);
		}
	}
	if (p != 1)
		return (ft_dprintf(2, ERR_INVALID_PLAYER_COUNT), 1);
	return (identify_map2(game, "10NSEW"));
}

static int	identify_map2(t_game *game, char *set)
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
			if (ft_strchr(set + 1, map[i][j]))
			{
				if (!i || !j || ft_strlen(map[i - 1]) <= j
					|| ft_strlen(map[i + 1]) <= j
					|| !ft_strchr(set, map[i - 1][j])
					|| !ft_strchr(set, map[i + 1][j])
					|| !ft_strchr(set, map[i][j - 1])
					|| !ft_strchr(set, map[i][j + 1]))
					return (ft_dprintf(2, ERR_MAP_OPEN, i, j), 1);
			}
		}
	}
	return (map_remove_whitespaces(game));
}
