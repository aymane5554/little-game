/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:45:30 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/01/09 10:26:15 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void next_level(t_player *player, t_game *game);

void	end(t_player *player, t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win,
		game->images[2], player->x * 32, player->y * 32);
	player->moves++;
	if (player->coins == game->coins)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->wimg,
			((game->width_height[0] * 32) / 2) - 64,
			((game->width_height[1] * 32) / 2) - 32);
		player->state = 'F';
		next_level(player, game);
	}
	else
	{
		mlx_put_image_to_window(game->mlx, game->win,
			player->door_img, x * 32, y * 32);
		player->x = x;
		player->y = y;
	}
}

void	free_animation_images(t_arg *arg)
{
	int		i;

	i = 0;
	while (arg->player.animations[i] != NULL)
	{
		mlx_destroy_image(arg->game.mlx, arg->player.animations[i]);
		i++;
	}
	free(arg->player.animations);
	arg->player.animations = NULL;
	i = 0;
	while (arg->player.rev_animations[i] != NULL)
	{
		mlx_destroy_image(arg->game.mlx, arg->player.rev_animations[i]);
		i++;
	}
	free(arg->player.rev_animations);
	arg->player.rev_animations = NULL;
}

void	free_map(char **map)
{
	int		i;

	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}

void	free_images(t_arg *arg)
{
	int		i;

	i = 0;
	mlx_destroy_image(arg->game.mlx, arg->player.img);
	mlx_destroy_image(arg->game.mlx, arg->player.left_img);
	mlx_destroy_image(arg->game.mlx, arg->player.door_img);
	mlx_destroy_image(arg->game.mlx, arg->game.wimg);
	mlx_destroy_image(arg->game.mlx, arg->game.limg);
	mlx_destroy_image(arg->game.mlx, arg->game.e_img_l);
	mlx_destroy_image(arg->game.mlx, arg->game.e_img_r);
	while (arg->game.images[i] != NULL)
	{
		mlx_destroy_image(arg->game.mlx, arg->game.images[i]);
		i++;
	}
	free(arg->game.images);
}

void next_level(t_player *player, t_game *game)
{
	char *mapfile;

	player->moves = 0;
	player->coins = 0;
	game->coins = 0;
	player->state = 'P';
	player->level++;
	free(game->enemies);
	free_map(game->map);
	free(game->width_height);
	mapfile = map_check(player->level);
	game->map = load_map(mapfile);
	game->width_height = map_dimension(game->map);
	if (game->width_height == NULL)
	{
		perror("\e[31mError\nInvalid Map"); 
		exit(1);
	}
	display_errors(game, player);
	display_map(game);
	mlx_put_image_to_window(game->mlx, game->win,
		player->img, player->x * 32, player->y * 32);
}