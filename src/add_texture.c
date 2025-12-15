/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:31:38 by ocgraf            #+#    #+#             */
/*   Updated: 2025/12/15 14:20:39 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef BONUS

int	add_texture2(t_game *game, int fd, int cardinal, t_list *lst);

int	add_texture(t_game *game, char *line, char *file_path)
{
	int		cardinal;
	int		fd;
	t_list	*lst;

	fd = readable_file(file_path);
	if (!file_path || fd == -1)
		return (ft_dprintf(2, ERR_TEXTURE_NOT_READABLE), 1);
	if (!ft_strncmp(line, "NO", 2))
		cardinal = NO;
	else if (!ft_strncmp(line, "SO", 2))
		cardinal = SO;
	else if (!ft_strncmp(line, "WE", 2))
		cardinal = WE;
	else if (!ft_strncmp(line, "EA", 2))
		cardinal = EA;
	else if (!ft_strncmp(line, "D", 1))
		cardinal = D;
	else if (!ft_strncmp(line, "T", 1))
		cardinal = T;
	else
		return (ft_dprintf(2, ERR_INVALID_CARDINAL), close(fd), 1);
	lst = ft_lstnew(file_path);
	if (!lst)
		return (close(fd), 1);
	return (add_texture2(game, fd, cardinal, lst));
}

int	add_texture2(t_game *game, int fd, int cardinal, t_list *lst)
{
	ft_lstadd_back(&game->scene.textures[cardinal], lst);
	close(fd);
	return (0);
}

#else

int	add_texture(t_game *game, char *line, char *file_path)
{
	int		cardinal;
	int		fd;
	t_list	*lst;

	fd = readable_file(file_path);
	if (!file_path || fd == -1)
		return (ft_dprintf(2, ERR_TEXTURE_NOT_READABLE), 1);
	if (!ft_strncmp(line, "NO", 2) && !game->scene.textures[NO])
		cardinal = NO;
	else if (!ft_strncmp(line, "SO", 2) && !game->scene.textures[SO])
		cardinal = SO;
	else if (!ft_strncmp(line, "WE", 2) && !game->scene.textures[WE])
		cardinal = WE;
	else if (!ft_strncmp(line, "EA", 2) && !game->scene.textures[EA])
		cardinal = EA;
	else
		return (ft_dprintf(2, ERR_INVALID_CARDINAL), close(fd), 1);
	lst = ft_lstnew(file_path);
	if (!lst)
		return (close(fd), 1);
	if (!game->scene.textures[cardinal])
		game->scene.textures[cardinal] = lst;
	else
		ft_lstadd_back(&game->scene.textures[cardinal], lst);
	return (close(fd), 0);
}
#endif
