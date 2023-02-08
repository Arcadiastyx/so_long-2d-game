/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:05:19 by inaranjo          #+#    #+#             */
/*   Updated: 2023/02/08 15:44:26 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"



/* va liber l espace allouer pour les mallocs*/
void ft_free(char **tab)
{
	size_t	i;

	i = 0;
	while(tab[i])
	{
		free(tab[i]); 
		i++;
	} 
	free(tab);
	tab = NULL;
	return ;
}

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
	int fd;
	char *tmp_line; 
	int	nbr_of_line;

	nbr_of_line = 0;
	fd = open(map_file, O_RDONLY);
	if(fd == -1) 
	{
		perror("ERROR : FD non compatible\n");
		exit(EXIT_FAILURE);
	}
	else 
	{
		tmp_line = get_next_line(fd);
		while(tmp_line)
		{
			nbr_of_line++;
			free(tmp_line);
			tmp_line = get_next_line(fd);
		}
		close(fd);
	}
	return(nbr_of_line);
} 

/*but de la fonction : set up la memoire dynamique de notre matrix en 2d (.ber) avec ces char
 1.Déclaration d'une variable pour stocker la ligne actuelle lue dans le fichier
 2.Lire la première ligne dans le fichier
 3.Boucle pour lire toutes les lignes dans le fichier jusqu'à ce que toutes les lignes aient été lues
 4.Allouer de la mémoire pour stocker chaque ligne dans une case de tableau
 5.Vérifier si l'allocation de mémoire a échoué
 6.Boucle pour copier chaque caractère de la ligne actuelle dans le tableau
 7.Mettre à jour les valeurs de la ligne et de la colonne pour la prochaine itération
 8.Libérer la mémoire utilisée pour stocker la ligne actuelle
 9.Lire la ligne suivante
 10.Marquer la fin du tableau avec une valeur nulle
 A chaque tour de boucle, le caractère courant de "line" est copié dans la case correspondante de la matrice "map", et les compteurs "i" et "column" sont incrémentés.

L'incrémentation de "column" sert à déplacer la position dans la colonne
de la matrice "map"où sera copié le prochain caractère*/
void memset_map_row_line(int row,int column, int i,t_engine_game *game)
{
	char *line;

	line = get_next_line(game->map.fd);
	while(line)
	{
		game->map.map[row] = ft_calloc(ft_strlen(line) + 1,sizeof(char));
		if(!game->map.map[row]) 
			return(ft_free(game->map.map));
		while(line[i] != '\0')
			game->map.map[row][column++] = line[i++];
		game->map.map[row++][column] = '\0';
		column = 0;
		i = 0;
		free(line);
		line = get_next_line(game->map.fd);	
	}
	game->map.map[row] = NULL;
}

/*Il appelle la fonction get_nbr_lines qui retourne le nombre de lignes dans le fichier, puis il stocke ce nombre dans game->map.nbr_lines.
Il stocke le nom du fichier dans game->map.map_file.
Il alloue de la mémoire pour un tableau de chaines de caractères en utilisant ft_calloc et stocke ce tableau dans game->map.map.
Il ouvre le fichie:r en utilisant open et stocke le descripteur de fichier dans game->map.fd. Si le descripteur de fichier n'est pas valide, il affiche une erreur et quitte le programme.
Il appelle la fonction memset_map pour mettre en mémoire les lignes du fichier dans le tableau game->map.map.
Il ferme le descripteur de fichier en utilisant close. */

void map_setup(char *map_file,t_engine_game *game)
{
	int row; 
	int i;
	size_t column;

	i = 0;
	row = 0;
	column = 0;
	game->map.nbr_lines = get_nbr_lines(map_file);
	game->map.map_file = map_file;
	game->map.map = ft_calloc(game->map.nbr_lines + 1,sizeof (char *));
	if(!(game->map.map))
		return ;
	game->map.fd = open(map_file, O_RDONLY);
	if(game->map.fd == -1) 
	{
		perror("ERROR : impossible d'ouvrir le fichier\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		memset_map_row_line(row,column,i,game);
		close(game->map.fd);
	}
}


/*La longueur de la fenêtre est déterminée en multipliant le nombre de lignes de la carte
 *  (data->map.line_count) par la taille d'une image (IMG_SIZE).
 *   La largeur de la fenêtre est déterminée en multipliant la longueur de la première ligne de la carte moins 1
 *    (ft_strlen(data->map.map[0]) - 1) par la taille d'une image (IMG_SIZE).
 *    Les dimensions de l'image sont également définies à IMG_SIZE.
 *    L'utilisation de [0] est pour accéder au premier élément de la première ligne dans la matrice 2D map.
 *    Cela est utilisé pour déterminer la longueur de la première ligne,
 *    qui peut être utilisée pour déterminer la largeur de la fenêtre.
 *    Les dimensions de la fenêtre sont en fonction de la longueur de la première ligne car
 *    elles sont considérées comme étant représentatives de la longueur de toutes les autres lignes.*/
void init_map(t_engine_game *game)
{
	game->x = 0;
	game->y = 0;
	game->map.player = 0;
	game->map.exit = 0; 
	game->map.items = 0;
	game->window_largeur = (ft_strlen(game->map.map[0]) - 1) * IMG_SIZE;
	game->window_hauteur = game->map.nbr_lines * IMG_SIZE;
	game->img.img_h = IMG_SIZE;
	game->img.img_l = IMG_SIZE;
}

/*but de la fonction :  initialise la position du joueur (représenté par le caractère 'P') sur la carte.
 *  Il parcourt les lignes et les colonnes de la carte (stockée dans un tableau 2D map)
 *  pour trouver le premier caractère 'P' et stocker ses coordonnées y et x respectivement dans les variables pos_y et pos_x*/

/*void	init_player(t_engine_game *game)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while(game->map.map[y])
	{
		while(game->map.map[y][x])
		{
			if(game->map.map[y][x] == 'P')
			{
				game->pos_y = y; 
				game_>pas_x = x;
			}
			x++;
		}
		x = 0;
		y++;
	}
}*/

/*Prend les images dans le repertoire a image pour les mettre dans les variables qui leurs sont destinee
 * le chemin absolu pour prendre l image est gerer via une macro dans le .h */
void init_img(t_engine_game *game)
{
	game->img.wall = mlx_xpm_file_to_image(game->mlx_start,WALL,&game->img.img_l,&game->img.img_h);
	game->img.floor = mlx_xpm_file_to_image(game->mlx_start,GROUND,&game->img.img_l,&game->img.img_h);
	game->img.exit = mlx_xpm_file_to_image(game->mlx_start,EXIT,&game->img.img_l,&game->img.img_h);
	game->img.items = mlx_xpm_file_to_image(game->mlx_start,ITEM,&game->img.img_l,&game->img.img_h);
	game->img.player = mlx_xpm_file_to_image(game->mlx_start,PLAYER,&game->img.img_l,&game->img.img_h);
}

/*Des que nous avons en memoire les images, on veut les appeler pour les afficher a la fenetre
 * chaque valeur devra etre remplacer par l image qui lui correspond*/
void put_img_to_win(t_engine_game *game, int width,int y,int x)
{
	if(game->map.map[y][x] == '1')
		mlx_put_image_to_window(game->mlx_start,game->window_param,game->img.wall,width, y * IMG_SIZE);
	else if(game->map.map[y][x] == '0')
		mlx_put_image_to_window(game->mlx_start,game->window_param,game->img.floor,width, y * IMG_SIZE);
	else if(game->map.map[y][x] == 'E') 
		 mlx_put_image_to_window(game->mlx_start,game->window_param,game->img.exit,width, y * IMG_SIZE);
	else if(game->map.map[y][x] == 'C')
		 mlx_put_image_to_window(game->mlx_start,game->window_param,game->img.items,width, y * IMG_SIZE);
	else if(game->map.map[y][x] == 'P')
		 mlx_put_image_to_window(game->mlx_start,game->window_param,game->img.player,width, y * IMG_SIZE);
}


/* comment definir la largeur et la hauteur de la fenetre ? */ 
int init_window(t_engine_game *game)
{
	game->mlx_start = mlx_init();
	if(game->mlx_start == NULL)
		return (1);
	game->window_param = mlx_new_window(game->mlx_start,game->window_largeur,game->window_hauteur, "so_long");
	if(game->window_param == NULL)
	{
		free(game->window_param);
		return(1);
	}
	return(1);
}

/* but de la fonction afficher les spritres*/
int create_map(t_engine_game *game)
{
   int y;
   size_t x;
   int width;

   if(game->window_param == NULL)
	   return(-1);
   y = 0;
   x = 0;
   width = 0;
   while(game->map.map[y])
   {
	   while(game->map.map[y][x] && game->map.map[y][x] != '\n')
	   {
		   put_img_to_win(game,width,y,x);
		   width += IMG_SIZE;
		   x++;
	   }
	   x = 0;
	   width = 0;
	   y++;
   }
   return(0);
}

int check_arg(char *map_file)
{
	size_t len;
	int fd;

	len = ft_strlen(map_file);
	if(open(map_file, O_DIRECTORY) > 0)
	{
		fd = open(map_file, O_DIRECTORY);
		close(fd);
		return(1);
	}
	else 
	{
		fd =open(map_file,O_RDONLY);
		close(fd);
		if((map_file[len - 3] != 'b' && map_file[len - 2] != 'e' && map_file[len -1] != 'r' && map_file[len - 4] != '.') || fd < 0)
			return (1);
		else
			return(0);
	}

}	

int main(int ac,char **av)
{
	t_engine_game game;

	if(ac == 2)
	{
		if(check_arg(av[1]) == 1)
		{
			perror("ERROR: l'arguement fournis ne correspond pas a un .ber\n");
			exit(EXIT_FAILURE);
		}
		map_setup(av[1],&game);
		init_map(&game);
		init_window(&game);
		init_img(&game);
		create_map(&game);
		mlx_loop(game.mlx_start);
		free(game.mlx_start);
		if(game.map.map)
			ft_free(game.map.map);
	}
}
