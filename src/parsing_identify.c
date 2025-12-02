/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_identify.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 20:10:33 by ocgraf            #+#    #+#             */
/*   Updated: 2025/12/02 15:21:47 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	identify_map2(t_game *game, char *set);

int	identify(char *line, t_game *game)
{
	char	*temp;

	if (ft_strlen(line) < 7)
		return (ft_dprintf(2, ERR_WRONG_LINE), 1);
	temp = skip_whitespaces(line);
	if (!ft_strncmp(temp, "NO", 2) || !ft_strncmp(temp, "SO", 2)
		|| !ft_strncmp(temp, "WE", 2) || !ft_strncmp(temp, "EA", 2))
		return (identify_textures(temp, game));
	else if (!ft_strncmp(temp, "F", 1) || !ft_strncmp(temp, "C", 1))
		return (identify_colors(temp, game));
	else
		return (2);
}

int	identify_textures(char *line, t_game *game)
{
	char	*path;
	char	*temp;
	int		fd;

	path = skip_whitespaces(line + 2);
	temp = path;
	while (temp && ft_isprint(*temp) && *temp != ' ')
		temp++;
	if (ft_wstrlen(temp))
		return (ft_dprintf(2, ERR_TEXTURE_NOT_READABLE), 1);
	path = ft_substr(path, 0, temp - path);
	if (!path)
		return (ft_dprintf(2, ERR_TEXTURE_NOT_READABLE), 1);
	fd = readable_file(path);
	if (fd == -1)
		return (ft_dprintf(2, ERR_TEXTURE_NOT_READABLE), free(path), 1);
	if (ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 4))
		return (ft_dprintf(2, ERR_TEXTURE_NOT_XPM), free(path), close(fd), 1);
	if (add_texture(game, line, path))
		return (ft_dprintf(2, ERR_TEXTURE_NOT_READABLE), free(path), close(fd),
			1);
	return (close(fd), 0);
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
	return (identify_map2(game, MAP_ELEMENTS));
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

int	identify_colors(char *line, t_game *game)
{
	int		rgb[3];
	char	*temp;
	int		i;

	i = -1;
	temp = skip_whitespaces(line + 1);
	while (++i < 3)
	{
		rgb[i] = ft_atoi(temp);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (ft_dprintf(2, ERR_COLOR_OUT_OF_RANGE), 1);
		temp = skip_whitespaces(skip_numbers(temp));
		if (i < 2 && *temp++ != ',')
			return (ft_dprintf(2, ERR_COLOR_OUT_OF_RANGE), 1);
		temp = skip_whitespaces(temp);
	}
	if (*temp)
		return (ft_dprintf(2, ERR_COLOR_OUT_OF_RANGE), 1);
	if (!ft_strncmp(line, "F", 1) && game->scene.floor_color == -1)
		game->scene.floor_color = (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
	else if (!ft_strncmp(line, "C", 1) && game->scene.ceiling_color == -1)
		game->scene.ceiling_color = (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
	else
		return (ft_dprintf(2, ERR_COLOR_OUT_OF_RANGE), 1);
	return (0);
}
