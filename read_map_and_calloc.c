/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_and_calloc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:07:43 by inaranjo          #+#    #+#             */
/*   Updated: 2023/03/02 13:30:29 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* but de la fontion : lire le nombre de ligne dans le fichier .ber
 1.  ouvrir le fichier en mode lecture seulement
 2.  si le descripteur de fichier est égal à -1,
	 il y a eu une erreur lors de l'ouverture du fichier
 3. lire la première ligne du fichier
 4. tant que la variable temporaire est non nulle
	-incrémenter le compteur de 1
    -libérer la mémoire allouée pour la ligne lue
	-lire la prochaine ligne du fichier
 5. ferme le fichier avant de renvoyer le nbr de lignes	*/
int	get_nbr_lines(char	*map_file)
{
	int		fd;
	char	*tmp_line;
	int		nbr_of_line;

	nbr_of_line = 0;
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (1);
	else
	{
		tmp_line = get_next_line(fd);
		if (!tmp_line)
		{
			perror("ERROR : Empty file");
			exit(EXIT_FAILURE);
		}
		while (tmp_line)
		{
			nbr_of_line++;
			free(tmp_line);
			tmp_line = get_next_line(fd);
		}
		close(fd);
	}
	return (nbr_of_line);
}

/*But de la fonction : 
 - Allouer de la memoire dyna. a notre map.
 - Initialiser la variable nbr_lines. (dans struct)
 - Initialiser la variable map_file. (dans struct)
 - Initialiser la variable map. (dans struct)
*Il stocke le nom du fichier dans game->map.map_file.
*Il alloue de la mémoire pour un tableau de chaines de caractères
 en utilisant ft_calloc et stocke ce tableau dans game->map.map.
*Il ouvre le fichie .ber en utilisant open et stocke le descripteur
 de fichier dans game->map.fd. Si le descripteur de fichier n'est pas valide,
 il affiche une erreur et quitte le programme.
*Il appelle la fonction memset_map pour mettre en mémoire 
 les lignes du fichier dans le tableau game->map.map.
Il ferme le descripteur de fichier en utilisant close. */
void	map_setup(char *map_file, t_engine_game *game)
{
	int		row;
	int		i;
	size_t	column;

	i = 0;
	row = 0;
	column = 0;
	game->map.nbr_lines = get_nbr_lines(map_file);
	game->map.map_file = map_file;
	game->map.map = ft_calloc(game->map.nbr_lines + 1, sizeof (char *));
	if (!(game->map.map))
		return ;
	game->map.fd = open(map_file, O_RDONLY);
	if (game->map.fd == -1)
	{
		perror("ERROR : impossible d'ouvrir le fichier\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		memset_map_row_line(row, column, i, game);
		close(game->map.fd);
	}
}

/*but de la fonction : set up la memoire dynamique
  de notre matrix en 2d (.ber) a savoir axe x et axe y avec ces chars
 1.Déclaration d'une variable
   pour stocker la ligne actuelle lue dans le fichier
 2.Lire la première ligne dans le fichier
 3.Boucle pour lire toutes les lignes dans le fichier jusqu'à
   ce que toutes les lignes aient été lues
 4.Allouer de la mémoire pour stocker chaque
   ligne dans une case de tableau
 5.Vérifier si l'allocation de mémoire a échoué
 6.Boucle pour copier chaque caractère
   de la ligne actuelle dans le tableau
 7.Mettre à jour les valeurs de la ligne et
   de la colonne pour la prochaine itération
 8.Libérer la mémoire utilisée pour stocker la ligne actuelle
 9.Lire la ligne suivante
 10.Marquer la fin du tableau avec une valeur nulle
 A chaque tour de boucle, le caractère courant de "line" est copié
   dans la case correspondante de la matrice "map",
   et les compteurs "i" et "column" sont incrémentés.

   L'incrémentation de "column" sert à déplacer la position dans la colonne
de la matrice "map"où sera copié le prochain caractère*/
void	memset_map_row_line(int row, int column, int i, t_engine_game *game)
{
	char	*line;

	line = get_next_line(game->map.fd);
	while (line)
	{
		game->map.map[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!game->map.map[row])
			return (ft_free(game->map.map));
		while (line[i] != '\0')
			game->map.map[row][column++] = line[i++];
		game->map.map[row++][column] = '\0';
		column = 0;
		i = 0;
		free(line);
		line = get_next_line(game->map.fd);
	}
	game->map.map[row] = NULL;
}
