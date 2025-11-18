/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:11:16 by ocgraf            #+#    #+#             */
/*   Updated: 2025/11/18 14:59:05 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	readable_file(char *file_path)
{
	int	fd;

	if (!file_path || !*file_path)
		return (ft_dprintf (2, "Error\n null path\n"), 1);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (ft_dprintf (2, "Error\n open file\n"), 1);
	return (fd);
}

int	read_map(char *map_path)
{
	int	fd;

	fd = readable_file(map_path);
	if (fd == -1)
		return (1);
	get_next_line(fd)
}
