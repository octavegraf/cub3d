/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_replace_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:43:43 by ocgraf            #+#    #+#             */
/*   Updated: 2025/12/16 14:46:53 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#ifdef BONUS

void	replace_char(t_game *game)
{
	char	**map;
	int		i;
	int		j;

	map = game->scene.map;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0')
				map[i][j] = empty;
			else if (map[i][j] == '1')
				map[i][j] = wall;
			else if (map[i][j] == 'T')
				map[i][j] = t;
		}
	}
}

#else

void	replace_char(t_game *game)
{
	char	**map;
	int		i;
	int		j;

	map = game->scene.map;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0')
				map[i][j] = empty;
			else if (map[i][j] == '1')
				map[i][j] = wall;
		}
	}
}

#endif