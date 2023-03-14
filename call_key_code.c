/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_key_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:40:10 by inaranjo          #+#    #+#             */
/*   Updated: 2023/03/02 13:16:50 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*but : appele les key_actions pour faire bouger le player en gerant 
   les events lies aux touches du clavier. 
 * gere egalement la prise d items
 * gere egalement l apparition de la sortie
 * gere egalement la condition desortie
Elle prend en entrée le code de la touche appuyée et un pointeur
vers une structure de données t_engine_game qui contient les informations
sur l'état du jeu. En fonction de la touche appuyée,
elle appelle d'autres fonctions pour gérer les actions correspondantes.
Les touches sont identifiées à l'aide de constantes définies dans le .h,
comme KEY_W, KEY_A, KEY_S et KEY_D.
Après avoir géré l'action de la touche,
la fonction appelle d'autres fonctions pour mettre à jour les éléments du jeu,
vérifier si le joueur a gagné ou perdu, et gérer la sortie du jeu.
Enfin, la fonction retourne 0 pour indiquer que tout s'est bien passé. */
int	press_key_code_action(int key_code, t_engine_game *game)
{
	if (key_code == KEY_ESC)
		press_key_code_esc(game);
	else if (key_code == KEY_W)
		press_key_code_w(game);
	else if (key_code == KEY_A)
		press_key_code_a(game);
	else if (key_code == KEY_S)
		press_key_code_s(game);
	else if (key_code == KEY_D)
		press_key_code_d(game);
	item_update(game);
	manage_exit(game);
	win_condition(game);
	return (0);
}

/*but : vérifie si le joueur a ramassé tous les objets et
 *  est sur la case de fin.
 *  Si c'est le cas, le jeu affiche "YOU WIN" à l'écran et
 *  se termine en appelant la fonction exit.
 *  il est indispensable d enregistrer la position de E, afin
 *  de pouvoir ajouter des events */
void	win_condition(t_engine_game *game)
{
	if (game->map.nbr_item_collected == 3
		&& game->map.map[game->pos_y][game->pos_x] == 'E')
	{
		printf("YOU WIN\n");
		exit(EXIT_SUCCESS);
	}
}

/*but : collecte les items, les detruits et transforme la case courante
 * en char 0 ex: C = item C -> Floor = 0*/
void	item_update(t_engine_game *game)
{
	if (game->map.map[game->pos_y][game->pos_x] == 'C')
	{
		mlx_put_image_to_window(game->mlx_start, game->window_param,
			game->img.floor, game->pos_x * IMG_SIZE, game->pos_y * IMG_SIZE);
		game->map.nbr_item_collected++;
		game->map.map[game->pos_y][game->pos_x] = '0';
		mlx_put_image_to_window(game->mlx_start, game->window_param,
			game->img.player_down,
			game->pos_x * IMG_SIZE, game->pos_y * IMG_SIZE);
		printf("Nombre d'item collecté :%d\n", game->map.nbr_item_collected);
	}
}

/*but: vérifie si le joueur a collecté tous les objets dans la carte
 *  en comparant le nombre total d'objets à collecter
 *  avec le nombre d'objets collectés par le joueur.
 *  Si tous les objets ont été collectés, la variable you_can_exit
 *  dans la structure map est mise à 1 pour indiquer que le joueur
 *  peut maintenant sortir de la carte. La fonction met également 
 *  à jour l'affichage de la sortie en appelant la fonction
 *  mlx_put_image_to_window avec l'image de sortie correspondante.*/
void	manage_exit(t_engine_game *game)
{
	if (game->map.nbr_item_collected == game->map.total_item_to_collect)
	{
		game->map.you_can_exit = 1;
		mlx_put_image_to_window(game->mlx_start, game->window_param,
			game->img.exit,
			game->map.exit_x * IMG_SIZE, game->map.exit_y * IMG_SIZE);
	}
}
