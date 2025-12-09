/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_scene_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan-re <rchan-re@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:19:13 by rchan-re          #+#    #+#             */
/*   Updated: 2025/12/09 12:23:00 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef BONUS

void	t_scene_free(t_scene *scene)
{
	int	i;

	if (scene->map != NULL)
	{
		i = 0;
		while (scene->map[i] != NULL)
		{
			free(scene->map[i]);
			i++;
		}
		free(scene->map);
	}
	i = 0;
	while (i < 4)
	{
		ft_lstclear(&(scene->textures[i]), free);
		i++;
	}
	if (scene->minimap != NULL)
		minimap_free(&(scene->minimap), (scene->minimap_radius_map * 2) + 1,
			scene->minimap_radius_map);
}

#else

void	t_scene_free(t_scene *scene)
{
	int	i;

	if (scene->map != NULL)
	{
		i = 0;
		while (scene->map[i] != NULL)
		{
			free(scene->map[i]);
			i++;
		}
		free(scene->map);
	}
	i = 0;
	while (i < 4)
	{
		ft_lstclear(&(scene->textures[i]), free);
		i++;
	}
}
#endif
