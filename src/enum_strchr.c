/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum_strchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocgraf <ocgraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:32:03 by ocgraf            #+#    #+#             */
/*   Updated: 2025/12/16 13:58:37 by rchan-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#ifdef BONUS

int	e_chr_white(unsigned int c)
{
	if (c == empty || c == o_l || c == o_u || c == t)
		return (1);
	return (0);
}

int	e_chr_hit_open(unsigned int c)
{
	if ((c & d_u_l) == d_u_l || (c & d_u_r) == d_u_r || (c & d_l_u) == d_l_u
		|| (c & d_l_d) == d_l_d)
		return (1);
	return (0);
}

int	e_chr_available(unsigned int c)
{
	if (c == empty || c == c_l || c == c_u || c == o_l || c == o_u || c == t)
		return (1);
	return (0);
}

#endif
