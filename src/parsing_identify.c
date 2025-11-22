/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_identify.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:07:34 by ocgraf            #+#    #+#             */
/*   Updated: 2025/11/22 20:10:30 by ocgraf           ###   ########.fr       */
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

static int	identify_colors2(char *color, int *rgb)
{
	char	*temp;
	int		i;

	temp = color;
	i = 0;
	while (i < 3)
	{
		while (*temp && (*temp == ' ' || *temp == '\t'))
			temp++;
		if (!*temp || !ft_isdigit(*temp))
			return (1);
		rgb[i] = ft_atoi(temp);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (1);
		while (*temp && ft_isdigit(*temp))
			temp++;
		while (*temp && (*temp == ' ' || *temp == '\t'))
			temp++;
		if (i < 2)
		{
			if (*temp != ',')
				return (1);
			temp++;
		}
		i++;
	}
	while (*temp && (*temp == ' ' || *temp == '\t'))
		temp++;
	if (*temp)
		return (1);
	return (0);
}

static void	identify_colors3(char *line, int *rgb, t_game *game)
{
	if (line[0] == 'F')
		game->scene.floor_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	else
		game->scene.ceiling_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
}

int	identify_colors(char *line, t_game *game)
{
	int		rgb[3];
	char	*color;

	color = search_infos(line + 1, 1);
	if (!color)
		return (ft_dprintf(2, ERR_COLOR_OUT_OF_RANGE), 1);
	if (!*color)
		return (free(color), ft_dprintf(2, ERR_COLOR_OUT_OF_RANGE), 1);
	if (identify_colors2(color, rgb))
		return (free(color), ft_dprintf(2, ERR_COLOR_OUT_OF_RANGE), 1);
	identify_colors3(line, rgb, game);
	return (free(color), 0);
}

