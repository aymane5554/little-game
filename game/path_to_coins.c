/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_to_coins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:14:57 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/01/09 11:15:54 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	find_coins(int x, int y, char **map, int *wh, int *coins)
{
	if (map[y][x] == 'C')
		(*coins)++;
	map[y][x] = 'X';
	if (map[y - 1][x] == '0' || map[y - 1][x] == 'C' || map[y - 1][x] == 'E')
		find_coins(x, y - 1, map, wh, coins);
	if (map[y + 1][x] == '0' || map[y + 1][x] == 'C' || map[y + 1][x] == 'E')
		find_coins(x, y + 1, map, wh, coins);
	if (map[y][x + 1] == '0' || map[y][x + 1] == 'C' || map[y][x + 1] == 'E')
		find_coins(x + 1, y, map, wh, coins);
	if (map[y][x - 1] == '0' || map[y][x - 1] == 'C' || map[y][x - 1] == 'E')
		find_coins(x - 1, y, map, wh, coins);
	return (*coins);
}
