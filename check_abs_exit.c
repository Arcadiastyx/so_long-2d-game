/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_abs_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:03:57 by inaranjo          #+#    #+#             */
/*   Updated: 2023/03/02 13:41:12 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*parcourt chaque chaîne de caractères du tableau avec une boucle while
tant qu'elle n'a pas atteint la fin du tableau
(c'est-à-dire la valeur nulle). */
void	print_new_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		printf("%s", map[i]);
	printf("\n");
}

/*alloue de la mémoire pour une nouvelle copie de la carte de jeu.
Elle parcourt ensuite chaque ligne de la carte originale
et alloue de la mémoire pour une copie de chaque ligne
dans la nouvelle carte.
La nouvelle carte est marquée avec une valeur nulle
à la fin pour indiquer la fin du tableau.
La fonction renvoie un pointeur vers la nouvelle carte
copiée ou NULL en cas d'échec de l'allocation de mémoire.*/
char	**copy_of_the_original_map(t_engine_game *game)
{
	int		i;
	char	**new_map;
	int		line_length;

	i = 0;
	new_map = malloc((game->map.nbr_lines + 1) * sizeof(char *));
	if (!new_map)
		return (NULL);
	while (i < game->map.nbr_lines)
	{
		line_length = ft_strlen(game->map.map[i]);
		new_map[i] = (char *)malloc((line_length + 1) * sizeof(char));
		if (!new_map[i])
		{
			ft_free(new_map);
			return (NULL);
		}
		ft_memcpy(new_map[i], game->map.map[i], line_length);
		new_map[i][line_length] = '\0';
		i++;
	}
	new_map[game->map.nbr_lines] = NULL;
	return (new_map);
}

/*flood_fill est une implémentation récursive
de l'algorithme de remplissage par diffusion.
Elle prend en entrée un point de départ (x, y) 
et une copie de la carte de jeu map ainsi
que l'objet "game" qui contient les informations du jeu.
La fonction vérifie si x/y est à l'intérieur de la carte
et s'il correspond à un élément de la carte que l'on peut remplir
a savoir P-C-E-0
si c'est le cas, la fonction marque cette case comme 
remplie en la changeant en 'X'et rappelle la fonction flood_fill 
sur les voisins de cette case
((x-1, y), (x+1, y), (x, y-1) et (x, y+1)).*/
void	flood_fill(t_engine_game *game, char **map, int x, int y)
{
	if (x < 0 || y < 0 || y >= game->map.nbr_lines
		|| x >= game->window_largeur / IMG_SIZE)
		return ;
	if (map[y][x] == 'P' || map[y][x] == 'C'
		|| map[y][x] == 'E' || map[y][x] == '0')
	{
		map[y][x] = 'X';
		flood_fill(game, map, x - 1, y);
		flood_fill(game, map, x + 1, y);
		flood_fill(game, map, x, y - 1);
		flood_fill(game, map, x, y + 1);
	}
}

/*permet de compter le nombre de C qui son remplace*/
int	count_collectibles(char **map)
{
	int	x;
	int	y;
	int	count;

	x = 0;
	y = 0;
	count = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == 'C')
				count++;
			x++;
		}
		x = 0;
		y++;
	}
	return (count);
}

/*1.La fonction commence par appeler copy_of_the_original_map
 pour créer une copie de la carte de jeu. 
 Si la copie ne peut pas être créée, la fonction renvoie 0
2.La fonction appelle ensuite print_new_map
 pour afficher la carte copiée.
 Elle compte également le nombre de collectibles
 sur la carte à l'aide de count_collectibles
3.Ensuite, la fonction appelle flood_fill
 pour remplir les espaces vides avec des 'X'
à partir de la position du joueur.
La fonction affiche à nouveau la carte après cela.
4.Si la position de sortie (exit)
 n'est pas marquée comme accessible (marquée avec un 'X'),
 la fonction libère la mémoire allouée
 pour la carte copiée avec ft_free et retourne 0.
5. Si le nombre de collectibles restants sur la carte 
 est inférieur de 3 ou plus par rapport 
 au nombre initial de collectibles, 
 la fonction libère la mémoire allouée
pour la carte copiée avec ft_free et retourne.*/
int	check_path(t_engine_game *game)
{
	char	**map_cpy;
	int		collectibles;

	map_cpy = copy_of_the_original_map(game);
	if (!map_cpy)
		return (0);
	collectibles = count_collectibles(map_cpy);
	flood_fill(game, map_cpy, game->pos_x, game->pos_y);
	printf("\n");
	if (map_cpy[game->map.exit_y][game->map.exit_x] != 'X')
	{
		ft_free(map_cpy);
		return (0);
	}
	if (collectibles - count_collectibles(map_cpy) >= 3)
	{
		ft_free(map_cpy);
		return (1);
	}
	ft_free(map_cpy);
	return (0);
}
