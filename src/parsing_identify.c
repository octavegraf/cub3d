/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_identify.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:07:34 by ocgraf            #+#    #+#             */
/*   Updated: 2025/11/19 15:07:34 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	identify(char *line, t_game *game)
{
	int	i;

	i = 0;
	if (ft_strlen(line) < 3)
		return (ft_dprintf(2, "Error\n Wrong line\n"), 1);
	while (!ft_isprint(line[i]) || line[i] == ' ')
		i++;
	if (!ft_strncmp(line + i, "NO", 2) || !ft_strncmp(line + i, "SO", 2)
		|| !ft_strncmp(line + i, "WE", 2) || !ft_strncmp(line + i, "EA", 2))
		return (identify_textures(line + i, game));
	else if ((game->scene.textures[NO] && game->scene.textures[SO]
			&& game->scene.textures[WE] && game->scene.textures[EA])
		&& !ft_strncmp(line + i, "F", 1) || !ft_strncmp(line + i, "C", 1))
		return (identify_colors(line + i, game));
	else if (game->scene.textures[NO] && game->scene.textures[SO]
		&& game->scene.textures[WE] && game->scene.textures[EA]
		&& game->scene.floor_color && game->scene.ceiling_color)
		return (identify_map(line + i, game));
	else
		return (ft_dprintf(2, "Error\n Unknown identifier\n"), 1);
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
		return (ft_dprintf(2, "Error\n Texture file not readable\n"),
			free(line), free(path), 1);
	if (ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 4))
		return (ft_dprintf(2, "Error\n Texture file not .xpm\n"), free(line),
			free(path), 1);
	free(line);
	return (0);
}

int	identify_colors(char *line, t_game *game)
{
	char	*color_str;
	int		color;

	color_str = search_infos(line + 1, 1);
	color = atoi(color_str);
	if (color > 255 || color < 0)
		return (ft_dprintf(2, "Error\n Color value out of range\n"),
			free(line), free(color_str), 1);
	if (!ft_strncmp(line, "F", 1))
		game->scene.floor_color = color;
	else if (!ft_strncmp(line, "C", 1))
		game->scene.ceiling_color = color;
	else
		return (ft_dprintf(2, "Error\n Unknown color identifier\n"),
			free(line), free(color_str), 1);
	free(line);
	free(color_str);
	return (0);
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
			if (map[i][j] == ' ' || map[i][j] == '\f' || map[i][j] == '\n'
				|| map[i][j] == '\r' || map[i][j] == '\t' || map[i][j] == '\v')
				map[i][j] = '1';
			else if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				p++;
			else if (map[i][j] != '0' && map[i][j] != '1')
				return (ft_dprintf(2, "Error\n Invalid map character\n"), 1);
		}
	}
	return (0);
}

char	*search_infos(char *line, int info_type)
{
	int	i;
	int	j;

	i = 0;
	while ((info_type < 6) && line[i] && !ft_isprint(line[i]) || line[i] == ' ')
		i++;
	j = i;
	while (line[j] && ft_isprint(line[j]) && line[j] != ' ')
		j++;
	return (ft_substr(line, i, j - i));
}
