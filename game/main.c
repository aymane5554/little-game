/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:45:58 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/01/09 11:14:41 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_close(t_arg *arg)
{
	free_images(arg);
	free_animation_images(arg);
	mlx_destroy_display(arg->game.mlx);
	mlx_destroy_window(arg->game.mlx, arg->game.win);
	free(arg->game.mlx);
	free(arg->game.enemies);
	free_map(arg->game.map);
	free(arg->game.width_height);
	arg->game.mlx = NULL;
	arg->game.win = NULL;
	arg->game.width_height = NULL;
	exit(0);
	return (0);
}

int	getkey(int keycode, t_arg *arg)
{
	if (keycode == 65307)
		ft_close(arg);
	else if (keycode == 100)
		moveright(&(arg->game), &(arg->player));
	else if (keycode == 97)
		moveleft(&(arg->game), &(arg->player));
	else if (keycode == 119)
		moveup(&(arg->game), &(arg->player));
	else if (keycode == 115)
		movedown(&(arg->game), &(arg->player));
	return (0);
}

void	load_animation_images(t_player *player, t_game *game)
{
	int	i;

	player->door_img = mlx_xpm_file_to_image(
			game->mlx, "textures/playerindoor.xpm", &i, &i);
	player->animations = malloc(9 * sizeof(void *));
	player->animations[0] = mlx_xpm_file_to_image(
			game->mlx, "textures/animation/anime0.xpm", &i, &i);
	player->animations[1] = mlx_xpm_file_to_image(
			game->mlx, "textures/animation/anime1.xpm", &i, &i);
	player->animations[2] = mlx_xpm_file_to_image(
			game->mlx, "textures/animation/anime2.xpm", &i, &i);
	player->animations[3] = mlx_xpm_file_to_image(
			game->mlx, "textures/animation/anime3.xpm", &i, &i);
	player->animations[4] = mlx_xpm_file_to_image(
			game->mlx, "textures/animation/anime4.xpm", &i, &i);
	player->animations[5] = mlx_xpm_file_to_image(
			game->mlx, "textures/animation/anime5.xpm", &i, &i);
	player->animations[6] = mlx_xpm_file_to_image(
			game->mlx, "textures/animation/anime6.xpm", &i, &i);
	player->animations[7] = mlx_xpm_file_to_image(
			game->mlx, "textures/animation/anime7.xpm", &i, &i);
	player->animations[8] = NULL;
	game->e_img_r = mlx_xpm_file_to_image(
			game->mlx, "textures/enemy_right.xpm", &i, &i);
}

void	load_ranimation_images(t_player *player, t_game *game)
{
	int	i;

	game->wimg = mlx_xpm_file_to_image(game->mlx, "textures/won.xpm", &i, &i);
	player->rev_animations = malloc(9 * sizeof(void *));
	player->rev_animations[0] = mlx_xpm_file_to_image(
			game->mlx, "textures/animation/ranime0.xpm", &i, &i);
	player->rev_animations[1] = mlx_xpm_file_to_image(
			game->mlx, "textures/animation/ranime1.xpm", &i, &i);
	player->rev_animations[2] = mlx_xpm_file_to_image(
			game->mlx, "textures/animation/ranime2.xpm", &i, &i);
	player->rev_animations[3] = mlx_xpm_file_to_image(
			game->mlx, "textures/animation/ranime3.xpm", &i, &i);
	player->rev_animations[4] = mlx_xpm_file_to_image(
			game->mlx, "textures/animation/ranime4.xpm", &i, &i);
	player->rev_animations[5] = mlx_xpm_file_to_image(
			game->mlx, "textures/animation/ranime5.xpm", &i, &i);
	player->rev_animations[6] = mlx_xpm_file_to_image(
			game->mlx, "textures/animation/ranime6.xpm", &i, &i);
	player->rev_animations[7] = mlx_xpm_file_to_image(
			game->mlx, "textures/animation/ranime7.xpm", &i, &i);
	player->rev_animations[8] = NULL;
	game->e_img_l = mlx_xpm_file_to_image(
			game->mlx, "textures/enemy_left.xpm", &i, &i);
	game->limg = mlx_xpm_file_to_image(
			game->mlx, "textures/lost.xpm", &i, &i);
}



int	main()
{
	t_game		game;
	t_player	player;
	t_arg		arg;
	char		*mapfile;

	mapfile = map_check(0);
	game.map = load_map(mapfile);
	game.width_height = map_dimension(game.map);
	if (game.width_height == NULL)
		return (perror("\e[31mError\nInvalid Map"), 1);
	display_errors(&game, &player);
	game.mlx = mlx_init();
	game_init(&game, &player);
	load_ranimation_images(&player, &game);
	load_animation_images(&player, &game);
	display_map(&game);
	mlx_put_image_to_window(game.mlx, game.win,
		player.img, player.x * 32, player.y * 32);
	arg.game = game;
	arg.player = player;
	mlx_hook(game.win, 2, 1L << 0, getkey, &arg);
	mlx_hook(game.win, 17, 0, ft_close, &arg);
	mlx_loop_hook(game.mlx, display_moves, &arg);
	mlx_loop(game.mlx);
}
