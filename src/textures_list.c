/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:31:38 by ocgraf            #+#    #+#             */
/*   Updated: 2025/12/01 14:23:28 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	add_texture(t_game *game, char *file_path)
{
	int		cardinal;
	t_list	*lst;

	if (!file_path || is_readable_file(file_path + 2) == -1)
		return (ft_dprintf(2, ERR_TEXTURE_NOT_READABLE), 1);
	if (!ft_strncmp(file_path, "NO", 2))
		cardinal = NO;
	else if (!ft_strncmp(file_path, "SO", 2))
		cardinal = SO;
	else if (!ft_strncmp(file_path, "WE", 2))
		cardinal = WE;
	else if (!ft_strncmp(file_path, "EA", 2))
		cardinal = EA;
	else
		return (ft_dprintf(2, ERR_INVALID_CARDINAL), 1);
	lst = ft_lstnew(file_path + 2);
	if (!lst)
		return (1);
	if (!game->scene.textures[cardinal])
		game->scene.textures[cardinal] = lst;
	else
		ft_lstadd_back(&game->scene.textures[cardinal], lst);
	return (0);
}
