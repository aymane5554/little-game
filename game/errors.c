/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 14:48:35 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/01/09 10:27:59 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	loop(t_game *game, t_player *player, int arr[])
{
	int		j;

	j = 0;
	while (j < game->width_height[0])
	{
		if (game->map[arr[0]][j] == 'E')
			arr[1]++;
		else if (game->map[arr[0]][j] == 'P')
		{
			arr[2]++;
			player->x = j;
			player->y = arr[0];
		}
		else if (game->map[arr[0]][j] == 'C')
			game->coins++;
		else if (game->map[arr[0]][j] != '0'
			&& game->map[arr[0]][j] != '1' && game->map[arr[0]][j] != 'A')
		{
			perror("\e[31mError\nInvalid Component");
			return (free_map(game->map), free(game->width_height), -1);
		}
		j++;
	}
	return (1);
}

int	check_items(t_game *game, t_player *player)
{
	int	arr[3];

	arr[0] = 0;
	arr[1] = 0;
	arr[2] = 0;
	game->coins = 0;
	while (arr[0] < game->width_height[1])
	{
		if (loop(game, player, arr) == -1)
			exit(1);
		arr[0]++;
	}
	if (arr[1] != 1 || arr[2] != 1 || game->coins < 1)
	{
		free_map(game->map);
		free(game->width_height);
		perror("\e[31mError\nThe map must contain 1 exit, at"
			"least 1 collectible, and 1 starting position to be valid.");
		exit(1);
	}
	return (1);
}

void	free_and_exit(char *err, t_game *game)
{
	free_map(game->map);
	perror(err);
	exit(1);
}

int	find(int x, int y, char **map, int *wh)
{
	map[y][x] = 'X';
	if (map[y - 1][x] == 'E' || map[y + 1][x] == 'E'
		|| map[y][x + 1] == 'E' || map[y][x - 1] == 'E')
		return (1);
	if ((map[y - 1][x] == '0' || map[y - 1][x] == 'C'))
	{
		if (find(x, y - 1, map, wh) == 1)
			return (1);
	}
	if ((map[y + 1][x] == '0' || map[y + 1][x] == 'C'))
	{
		if (find(x, y + 1, map, wh) == 1)
			return (1);
	}
	if ((map[y][x + 1] == '0' || map[y][x + 1] == 'C'))
	{
		if (find(x + 1, y, map, wh) == 1)
			return (1);
	}
	if ((map[y][x - 1] == '0' || map[y][x - 1] == 'C'))
	{
		if (find(x - 1, y, map, wh) == 1)
			return (1);
	}
	return (-1);
}

void	display_errors(t_game *game, t_player *player)
{
	char	**map;
	int		i = 0;

	check_items(game, player);
	if (map_horizontal_borders(*game) == -1
		|| map_vertical_borders(*game) == -1)
		free_and_exit("\e[31mError\nThe map must be surrounded by walls", game);
	map = mapdup(game);
	if (find(player->x, player->y, map, game->width_height) != 1)
		free_and_exit("\e[31mError\nThere is no valid path to E", game);
	free_map(map);
	map = mapdup(game);
	if (find_coins(player->x, player->y, map,
			game->width_height, &i) != game->coins)
		free_and_exit("\e[31mError\nThere is no valid path to C", game);
	free_map(map);
}
