/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:06:40 by ocgraf            #+#    #+#             */
/*   Updated: 2025/12/16 15:17:21 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_wstrlen(char *str)
{
	int	i;

	i = 0;
	while (str && *str)
	{
		if (ft_isprint(*str))
			i++;
		str++;
	}
	return (i);
}

char	*skip_whitespaces(char *str)
{
	while (str && (*str == ' ' || *str == '\t' || *str == '\n'
			|| *str == '\r' || *str == '\v' || *str == '\f'))
		str++;
	return (str);
}

char	*skip_numbers(char *str)
{
	while (str && ft_isdigit(*str))
		str++;
	return (str);
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
		temp = skip_whitespaces(game->scene.map[i]);
		if (ft_strlen(game->scene.map[i]) - ft_strlen(temp) < min_white)
			min_white = ft_strlen(game->scene.map[i]) - ft_strlen(temp);
	}
	if (!min_white)
		return (0);
	i = -1;
	while (game->scene.map[++i])
	{
		temp = game->scene.map[i];
		game->scene.map[i] = ft_substr(temp, min_white,
				ft_strlen(temp) - min_white);
		free(temp);
		if (!game->scene.map[i])
			return (ft_dprintf(2, ERR_MALLOC), 1);
	}
	return (0);
}
