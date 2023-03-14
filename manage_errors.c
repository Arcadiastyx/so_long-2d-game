/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:50:49 by inaranjo          #+#    #+#             */
/*   Updated: 2023/03/02 13:28:05 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*But de la fonction : verifier que l argument fournis
 * au terminal correspond bien : 
 * a un fichier .ber si non error*/
int	check_arg(char *map_file)
{
	size_t	len;
	int		fd;

	len = ft_strlen(map_file);
	if (open(map_file, O_DIRECTORY) > 0)
	{
		fd = open(map_file, O_DIRECTORY);
		close(fd);
		return (1);
	}
	else
	{
		fd = open (map_file, O_RDONLY);
		close(fd);
		if ((map_file[len - 3] != 'b' && map_file[len - 2] != 'e'
				&& map_file[len -1] != 'r'
				&& map_file[len - 4] != '.') || fd < 0)
			return (1);
		else
			return (0);
	}
}	

/*Il compte le nombre de 'P', 'E' et 'C' dans la carte en utilisant
  une double boucle while pour parcourir chaque caractère de la carte. 
* Ensuite, il vérifie si le nombre de chaque caractère est supérieur à zéro. 
* Si le nombre de l'un de ces caractères est égal à zéro, cela signifie
  qu'il manque un élément essentiel pour jouer au jeu (joueur, sortie ou objet),
  donc la fonction renvoie 1 pour indiquer une erreur. 
  Sinon, la fonction renvoie 0 pour indiquer que tout est correct
  et que le jeu peut commencer.*/
int	check_nbr_of_char(t_engine_game *game)
{
	while (game->map.map[game->y])
	{
		while (game->map.map[game->y][game->x])
		{
			if (game->map.map[game->y][game->x] == 'P')
				game->map.nbr_player++;
			else if (game->map.map[game->y][game->x] == 'E')
				game->map.nbr_exit++;
			else if (game->map.map[game->y][game->x] == 'C')
				game->map.nbr_item++;
			game->x++;
		}
		game->x = 0;
		game->y++;
	}
	if (!game->map.nbr_player || game->map.nbr_exit > 2
		|| game->map.nbr_item != 3)
		return (1);
	else
		return (0);
}

/*but : verifier si la carte du jeu est rectangle, c est a dire : 
 * que chaque ligne de la carte possede bien la meme longueur
 * Pour cela il parcout chaque ligne de la carte delimite par '\n'
   (qui est gere das le gnl) et stocke la longueur de la premier ligne
   dans la variable "row_len".Si une ligne a une longueur diff;rente de "row_len"
   cela signigie que la carte n est pas rectangulaire
   donc la fonction renvoie 1 si = toutes les lignes ont la meme longueur
   si non la fonction renvoie 0
   1.Initialisation des variables
   2.Calcul de la longueur de la première ligne de la map et stockage
     dans game->map.row_len
   3.Tant que la ligne courante n'est pas terminée et qu'on n'a pas rencontré 
     de saut de ligne, on avance dans la ligne courante
   4.Si la longueur de la ligne courante est différente de game->map.row_len
     La map n'est pas rectangulaire, on retourne 1
	 Réinitialisation de la variable x à 0
	 On passe à la ligne suivante
	La map est rectangulaire, on retourne 0*/
int	check_if_map_is_rec(t_engine_game *game)
{
	int		y;
	size_t	x;

	y = 0;
	x = 0;
	game->map.row_len = ft_strlen(game->map.map[y]) - 1;
	while (game->map.map[y])
	{
		while (game->map.map[y][x] && game->map.map[y][x] != '\n')
		x++;
		if (x != game->map.row_len)
			return (1);
		x = 0;
		y++;
	}
	return (0);
}

/*but : verifier si la map est bien 
bordee par des murs La fonction itère
sur chaque caractère de la ligne,
en vérifiant si chaque caractère est égal à '1'. 
Si un caractère autre que '1' est trouvé, la fonction renvoie 1,
indiquant que la ligne n'est pas correctement bordée par des murs.
Sinon, si la boucle se termine 
sans trouver d'autres caractères que '1', 
la fonction renvoie 0, indiquant que la ligne
est correctement bordée par des murs.*/
int	check_walls_top_bot(int row, char **map)
{
	int	y;

	y = 0;
	while (map[row][y] && map[row][y] != '\n')
	{
		if (map[row][y] != '1')
			return (1);
		y++;
	}
	return (0);
}

/* but :vérifie si la carte
(représentée par la variable map) 
a des murs sur les côtés gauche et droit.
1.On commence à la ligne 1 car la ligne 0 est vérifiée dans check_walls_top_bot()
2.On vérifie si la première et la dernière ligne sont des murs
3.La boucle while vérifie si la première colonne et la dernière colonne 
de chaque ligne sont des murs, pour toutes les lignes de la carte, 
sauf la première et la dernière.
4.Si une des vérifications échoue, la fonction renvoie 1 
(ce qui signifie qu'il n'y a pas de mur sur un côté),
sinon elle renvoie 0 (ce qui signifie que tous les côtés sont des murs).*/
int	check_walls_left_right(int nbr_lines, char **map)
{
	int	y;

	y = 1;
	if (check_walls_top_bot(0, map) == 1
		|| check_walls_top_bot(nbr_lines, map) == 1)
		return (1);
	while (y < nbr_lines)
	{
		if (map[y][0] != '1' || map[y][ft_strlen(map[0]) - 2] != '1')
			return (1);
			y++;
	}
	return (0);
}
