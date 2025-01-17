/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:46:15 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/01/01 14:46:58 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*join(char *s1, char *s2)
{
	int size = 0;
	int i = 0;
	int ii = 0;
	char	*res;

	while (s1[i])
		i++;
	size += i;
	i = 0;
	while (s2[i])
		i++;
	size += i;
	res = malloc((size + 1) * sizeof(char));
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[ii])
	{
		res[i] = s2[ii];
		ii++;
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*map_check(int level)
{
	int	fd;
	char prefix[] = "maps/";
	char *file;

	file = join(prefix, ft_itoa(level));
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("\e[31mError\n");
		exit(1);
	}
	close(fd);
	return (file);
}

int	map_horizontal_borders(t_game game)
{
	int		i;
	char	*s;

	i = 0;
	s = game.map[0];
	while (i < game.width_height[0])
	{
		if (s[i] != '1')
			return (-1);
		i++;
	}
	i = 0;
	s = game.map[game.width_height[1] - 1];
	while (i < game.width_height[0])
	{
		if (s[i] != '1')
			return (-1);
		i++;
	}
	return (1);
}

int	map_vertical_borders(t_game game)
{
	int		i;

	i = 0;
	while (i < game.width_height[1])
	{
		if (game.map[i][0] != '1' ||
			game.map[i][game.width_height[0] - 1] != '1')
			return (-1);
		i++;
	}
	return (1);
}
