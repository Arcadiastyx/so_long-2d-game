/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_img_to_window.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:38:21 by inaranjo          #+#    #+#             */
/*   Updated: 2023/02/28 17:51:42 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*Prend les images dans le repertoire a image pour les mettre
  dans les variables qui leurs sont destinee
*le chemin absolu pour prendre l image est gerer via une macro dans le .h */
void	init_img(t_engine_game *game)
{
	game->img.wall = mlx_xpm_file_to_image(game->mlx_start,
			WALL, &game->img.img_l, &game->img.img_h);
	game->img.exit = mlx_xpm_file_to_image(game->mlx_start,
			EXIT, &game->img.img_l, &game->img.img_h);
	game->img.items = mlx_xpm_file_to_image(game->mlx_start,
			ITEM, &game->img.img_l, &game->img.img_h);
	game->img.player_right = mlx_xpm_file_to_image(game->mlx_start,
			PLAYER_RIGHT, &game->img.img_l, &game->img.img_h);
	game->img.player_left = mlx_xpm_file_to_image(game->mlx_start,
			PLAYER_LEFT, &game->img.img_l, &game->img.img_h);
	game->img.player_up = mlx_xpm_file_to_image(game->mlx_start,
			PLAYER_UP, &game->img.img_l, &game->img.img_h);
	game->img.player_down = mlx_xpm_file_to_image(game->mlx_start,
			PLAYER_DOWN, &game->img.img_l, &game->img.img_h);
	game->img.floor = mlx_xpm_file_to_image(game->mlx_start,
			GROUND, &game->img.img_l, &game->img.img_h);
}

/*Des que nous avons en memoire les images, on veut les appeler
 *  pour les afficher a la fenetre
 * chaque valeur devra etre remplacer par l image qui lui correspond*/
void	put_img_to_win(t_engine_game *game, int width, int y, int x)
{
	if (game->map.map[y][x] == 'P')
		mlx_put_image_to_window(game->mlx_start,
			game->window_param, game->img.player_right, width, y * IMG_SIZE);
	else if (game->map.map[y][x] == 'E'
		&& game->map.nbr_item_collected == game->map.total_item_to_collect)
		mlx_put_image_to_window(game->mlx_start, game->window_param,
			game->img.exit, width, y * IMG_SIZE);
	else if (game->map.map[y][x] == 'C')
		mlx_put_image_to_window(game->mlx_start,
			game->window_param, game->img.items, width, y * IMG_SIZE);
	else if (game->map.map[y][x] == '0')
		mlx_put_image_to_window(game->mlx_start,
			game->window_param, game->img.floor, width, y * IMG_SIZE);
	else if (game->map.map[y][x] == '1')
		mlx_put_image_to_window(game->mlx_start,
			game->window_param, game->img.wall, width, y * IMG_SIZE);
}

/* But definir la taille de la fenetre selon la taille 
 * de la carte et les settings aproprie
 * + gestions d erreur  */
int	init_window(t_engine_game *game)
{
	game->mlx_start = mlx_init();
	if (game->mlx_start == NULL)
		return (1);
	game->window_param = mlx_new_window(game->mlx_start,
			game->window_largeur, game->window_hauteur, "so_long");
	if (game->window_param == NULL)
	{
		free(game->window_param);
		return (1);
	}
	return (0);
}

/* but de la fonction afficher les sprites
 * selon les emplacements predefinies dans la map*/
int	create_map_base_on_data(t_engine_game *game)
{
	int			y;
	size_t		x;
	int			width;

	if (game->mlx_start == NULL)
		return (1);
	y = 0;
	x = 0;
	width = 0;
	while (game->map.map[y])
	{
		while (game->map.map[y][x] && game->map.map[y][x] != '\n')
		{
			set_exit(game, x, y);
			put_img_to_win(game, width, y, x);
			width += IMG_SIZE;
			x++;
		}
		x = 0;
		width = 0;
		y++;
	}
	return (0);
}

/* extention pour avoir les 25lignes dans create_map..*/
void	set_exit(t_engine_game *game, int x, int y)
{
	if (game->map.map[y][x] == 'E')
	{
		game->map.exit_x = x;
		game->map.exit_y = y;
	}
}
