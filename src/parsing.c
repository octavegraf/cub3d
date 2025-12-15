/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:41:16 by ocgraf            #+#    #+#             */
/*   Updated: 2025/12/15 15:14:18 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	read_cub_file2(t_game *game, char *buff, int fd);
static int	read_cub_file3(t_game *game, char *buff, int fd, char **map);

int	readable_file(char *file_path)
{
	int	fd;

	fd = -1;
	if (!file_path || !*file_path)
		return (fd);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (fd);
	if (read(fd, NULL, 0) < 0)
		return (close(fd), -1);
	return (fd);
}

int	read_cub_file(char *cub_path, t_game *game, int id)
{
	int		fd;
	char	*buff;

	if (ft_strncmp(cub_path + ft_strlen(cub_path) - 4, ".cub", 4))
		return (ft_dprintf(2, ERR_CUB_EXTENSION), 1);
	fd = readable_file(cub_path);
	if (fd == -1)
		return (1);
	buff = NULL;
	while (true)
	{
		if (buff)
			free(buff);
		buff = get_next_line(fd);
		if (!buff)
			return (close(fd), ft_dprintf(2, ERR_WRONG_LINE), 1);
		ft_printf("parsing: %s\n", buff);
		if (!ft_wstrlen(buff))
			continue ;
		id = identify(buff, game);
		if (id == 2)
			break ;
		if (id == 1)
			return (free(buff), close(fd), 1);
	}
	return (read_cub_file2(game, buff, fd));
}

static int	read_cub_file2(t_game *game, char *buff, int fd)
{
	char	**map;
	char	*temp;

	if (game->scene.ceiling_color == -1 || game->scene.floor_color == -1
		|| !game->scene.textures[NO] || !game->scene.textures[SO]
		|| !game->scene.textures[WE] || !game->scene.textures[EA])
		return (free(buff), close(fd), ft_dprintf(2, ERR_UNKNOWN_ID), 1);
	map = NULL;
	while (ft_wstrlen(buff))
	{
		if (buff[ft_strlen(buff) - 1] == '\n')
		{
			temp = ft_substr(buff, 0, ft_strlen(buff) - 1);
			if (!temp)
				return (double_free(map), free(buff), close(fd), 1);
			free(buff);
			buff = temp;
		}
		map = ft_array_add_row(map, buff);
		if (!map)
			return (free(buff), close(fd), ft_dprintf(2, ERR_MALLOC), 1);
		free(buff);
		buff = get_next_line(fd);
	}
	return (read_cub_file3(game, buff, fd, map));
}

static int	read_cub_file3(t_game *game, char *buff, int fd, char **map)
{
	map = ft_array_add_row(map, "");
	if (!map)
		return (free(buff), close(fd), ft_dprintf(2, ERR_MALLOC), 1);
	while (buff)
	{
		free(buff);
		buff = get_next_line(fd);
		if (ft_wstrlen(buff))
			return (double_free(map), free(buff), close(fd),
				ft_dprintf(2, ERR_WRONG_LINE), 1);
	}
	return (close(fd), free(buff), identify_map(map, game));
}
