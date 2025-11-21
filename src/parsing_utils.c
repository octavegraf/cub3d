/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:06:40 by ocgraf            #+#    #+#             */
/*   Updated: 2025/11/21 16:56:48 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_wstrlen(char *str)
{
	int	i;

	i = 0;
	while (str && *str)
	{
		if (ft_isalnum(*str))
			i++;
		str++;
	}
	return (i);
}

char	*search_infos(char *line, int info_type)
{
	int	i;
	int	j;

	i = 0;
	while ((info_type < 6) && line[i]
		&& (!ft_isprint(line[i]) || line[i] == ' '))
		i++;
	j = i;
	while (line[j] && ft_isprint(line[j]) && line[j] != ' ')
		j++;
	return (ft_substr(line, i, j - i));
}

int	map_remove_whitespaces(t_game *game)
{
	size_t	min_white;
	size_t	i;
	char	*temp;

	i = -1;
	min_white = INT_MAX;
	while (game->scene.map[++i])
	{
		if (min_white > ft_strlen(game->scene.map[i])
			- ft_wstrlen(game->scene.map[i]))
			min_white = ft_strlen(game->scene.map[i])
				- ft_wstrlen(game->scene.map[i]);
	}
	i = -1;
	while (game->scene.map[++i])
	{
		temp = ft_substr(game->scene.map[i], min_white,
				ft_strlen(game->scene.map[i]) - min_white);
		if (!temp)
			return (1);
		free(game->scene.map[i]);
		game->scene.map[i] = temp;
	}
	return (0);
}
