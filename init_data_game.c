/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:24:55 by inaranjo          #+#    #+#             */
/*   Updated: 2023/03/01 18:10:58 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*La longueur de la fenêtre est déterminée en multipliant
  le nombre de lignes de la carte
 *(data->map.line_count) par la taille d'une image (IMG_SIZE).
 *La largeur de la fenêtre est déterminée en multipliant la longueur
  de la première ligne de la carte - 1
 *(ft_strlen(data->map.map[0]) - 1) par la taille d'une image (IMG_SIZE).
 *Les dimensions de l'image sont également définies à IMG_SIZE.
 *L'utilisation de [0] est pour accéder au premier élément
  de la première ligne dans la matrice 2D map.
 *Cela est utilisé pour déterminer la longueur de la première ligne,
 *qui peut être utilisée pour déterminer la largeur de la fenêtre.
 *Les dimensions de la fenêtre sont en fonction de la longueur
  de la première ligne carelles sont considérées comme étant représentatives
  de la longueur de toutes les autres lignes.*/
void	init_map(t_engine_game *game)
{
	game->x = 0;
	game->y = 0;
	game->map.player = 0;
	game->map.exit = 0;
	game->map.items = 0;
	game->map.nbr_item_collected = 0;
	game->map.nbr_item = 0;
	game->map.nbr_player = 0;
	game->map.you_can_exit = 0;
	game->map.total_item_to_collect = 3;
	game->nbr_pas = 0;
	game->window_largeur = (ft_strlen(game->map.map[0]) - 1) * IMG_SIZE;
	game->window_hauteur = game->map.nbr_lines * IMG_SIZE;
	game->img.img_h = IMG_SIZE;
	game->img.img_l = IMG_SIZE;
}

/*but initialiser la position du jouer,
 * sans cela il est impossible de definir sa position
 * afin de le faire bouger. 
 * pos_y et pos_x va enregistrer la position du jouer
 * avec ces informations on va pour donner une action au player*/
void	init_player(t_engine_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (game->map.map[y])
	{
		while (game->map.map[y][x])
		{
			if (game->map.map[y][x] == 'P')
			{
				game->pos_y = y;
				game->pos_x = x;
			}
			x++;
		}
		x = 0;
		y++;
	}
}
