/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum_strchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:32:03 by ocgraf            #+#    #+#             */
/*   Updated: 2025/12/15 17:02:05 by ocgraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#ifdef BONUS

int	e_chr_white(int c)
{
	if (c == -1 || c == o_l || c == o_u || c & d_u_l == 1 || c == t
		|| c & d_u_r == 1 || c & d_l_u == 1 || c & d_l_d == 1)
		return (1);
	return (0);
}

int	e_chr_h_open(int c)
{
	if (c & d_u_l == 1 || c & d_u_r == 1 || c & d_l_u == 1 || c & d_l_d == 1)
		return (1);
	return (0);
}

int	e_chr_available(int c)
{
	if (c == -1 || c == c_l || c == c_u || c == o_l || c == o_u)
		return (1);
	return (0);
}

#endif