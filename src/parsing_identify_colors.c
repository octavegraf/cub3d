/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_identify_colors.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:07:34 by ocgraf            #+#    #+#             */
/*   Updated: 2025/11/24 15:38:27 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	identify_colors2(char *color, int *rgb);
static int	identify_colors3(char **temp, int *rgb);
static void	identify_colors_set(char *line, int *rgb, t_game *game);

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
	identify_colors_set(line, rgb, game);
	return (free(color), 0);
}

static int	identify_colors2(char *color, int *rgb)
{
	int		i;
	char	*temp;

	i = -1;
	temp = color;
	while (*temp)
	{
		if (ft_isprint(*temp) && *temp != ',' && *temp != ' '
			&& (*temp < '0' || *temp > '9'))
			return (1);
		temp++;
	}
	temp = color;
	return (identify_colors3(&temp, rgb));
}

static int	identify_colors3(char **temp, int *rgb)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		rgb[i] = ft_atoi(*temp);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (1);
		*temp = ft_strchr(*temp, ',');
		if (!*temp && i < 2)
			return (1);
		if (*temp)
			(*temp)++;
	}
	if (*temp && ft_wstrlen(*temp))
		return (1);
	return (0);
}

static void	identify_colors_set(char *line, int *rgb, t_game *game)
{
	if (line[0] == 'F')
		game->scene.floor_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	else
		game->scene.ceiling_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
}
