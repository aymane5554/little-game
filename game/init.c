/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:45:53 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/01/09 10:25:03 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	*map_dimension(char **map)
{
	int	x;
	int	y;
	int	*dimension;
	int	w;

	y = 0;
	dimension = malloc(2 * sizeof(int));
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0' && map[y][x] != '\n')
			x++;
		if (y != 0 && x != w)
			return (free(dimension), free_map(map), NULL);
		w = x;
		y++;
	}
	dimension[0] = x;
	dimension[1] = y;
	if (map[y - 1][x] == '\n' || x * 32 > 3800 || y * 32 > 2100)
		return (free(dimension), free_map(map), NULL);
	return (dimension);
}

char	**load_map(char *file)
{
	int		fd;
	char	**map;
	int		i;
	int		size;

	size = file_line(file);
	map = malloc((size + 1) * sizeof(char *));
	fd = open(file, O_RDONLY);
	i = 0;
	while (i < size)
	{
		map[i] = get_next_line(fd);
		i++;
	}
	close(fd);
	map[i] = NULL;
	if (map[0] == NULL)
	{
		perror("\e[31mError\nInvalid map");
		exit(1);
	}
	return (map);
}

void	display_tile(t_game *game, int i, int j)
{
	if (game->map[i][j] == '1'
		&& (i == game->width_height[1] -1 || game->map[i + 1][j] == '1'))
		mlx_put_image_to_window(game->mlx,
			game->win, game->images[0], j * 32, i * 32);
	else if (game->map[i][j] == '1')
		mlx_put_image_to_window(game->mlx,
			game->win, game->images[1], j * 32, i * 32);
	else if (game->map[i][j] == '0')
		mlx_put_image_to_window(game->mlx,
			game->win, game->images[2], j * 32, i * 32);
	else if (game->map[i][j] == 'E')
		mlx_put_image_to_window(game->mlx,
			game->win, game->images[3], j * 32, i * 32);
	else if (game->map[i][j] == 'C')
		mlx_put_image_to_window(game->mlx,
			game->win, game->images[4], j * 32, i * 32);
}

void	display_map(t_game *game)
{
	int		i;
	int		j;
	int		e;

	i = 0;
	e = 0;
	game->number_of_enemies = count_enemies(game);
	game->enemies = malloc(game->number_of_enemies * sizeof(t_enemy));
	while (i < game->width_height[1])
	{
		j = 0;
		while (j < game->width_height[0])
		{
			display_tile(game, i, j);
			if (game->map[i][j] == 'A')
			{
				game->enemies[e].x = j * 32;
				game->enemies[e].y = i * 32;
				game->enemies[e].velocity = 1;
				e++;
			}
			j++;
		}
		i++;
	}
}

int	game_init(t_game	*game, t_player *player)
{
	int			i;

	player->level = 0;
	player->state = 'P';
	player->img = mlx_xpm_file_to_image(
			game->mlx, "textures/player.xpm", &i, &i);
	player->left_img = mlx_xpm_file_to_image(
			game->mlx, "textures/player_left.xpm", &i, &i);
	player->moves = 0;
	player->coins = 0;
	game->win = mlx_new_window(
			game->mlx, game->width_height[0] * 32,
			game->width_height[1] * 32, "So Long");
	game->images = malloc(6 * sizeof(void *));
	game->images[0] = mlx_xpm_file_to_image(
			game->mlx, "textures/wall.xpm", &i, &i);
	game->images[1] = mlx_xpm_file_to_image(
			game->mlx, "textures/wall01.xpm", &i, &i);
	game->images[2] = mlx_xpm_file_to_image(
			game->mlx, "textures/ground.xpm", &i, &i);
	game->images[3] = mlx_xpm_file_to_image(
			game->mlx, "textures/door.xpm", &i, &i);
	game->images[4] = mlx_xpm_file_to_image(
			game->mlx, "textures/coin.xpm", &i, &i);
	game->images[5] = NULL;
	return (1);
}
