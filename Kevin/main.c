/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevdos-s <kevdos-s@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 22:47:01 by kevdos-s          #+#    #+#             */
/*   Updated: 2025/07/05 22:02:07 by kevdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
//#include <io.h>
#include <stdlib.h>

void rush();
int	**ft_create_dummy_map(int p_max_row, int p_max_column);
void ft_fill_map(int **p_map, int *p_up, int *p_down, int *p_left, int *p_right);
void ft_print_tableau(int p_row_lenght, int p_column_lenght,int **p_map);
int ft_get_all_nb_added(int p_nb);
void ft_putchar(char p_char_to_print);
void ft_putnb(int p_int_to_print);
const int m_max_row = 4;
const int m_max_column = 4;

int main()
{
	// TODO
	//chopper les arguments et les mettre dans des tableaux
	//		ex: int asked_column_up[4]; int asked_column_down[4]; int asked_row_left[4]; int asked_row_right[4];
	//faire une fonction atoi du coup

	rush();
}

void rush()
{

	int map[4][4];
	// pour cree une map avec des données pourrie
	int **l_map = ft_create_dummy_map(m_max_row, m_max_column);

	//=========================================================
	// TODO calculer les donnees à mettre dans la map
	//		si possible, de manière à ce que ça marche meme en changeant la taille de la map (genre en 9x9)

	int l_up[4] = {4, 3, 2, 1};
	int l_down[4] = {1, 2, 2, 2};
	int l_left[4] = {4, 3, 2, 1};
	int l_right[4] = {1, 2, 2, 2};

	ft_fill_map(l_map, l_up, l_down, l_left, l_right);

	//pour imprimer la map
	ft_print_tableau(m_max_row, m_max_column, l_map);


	//pour liberer la memoire après l'utilisation de la map
	for (int i = 0; i < m_max_row; i++)
	{
		free(l_map[i]);
	}
	free (l_map);
}
void ft_fill_map(int **p_map, int *p_up, int *p_down, int *p_left, int *p_right)
{
	int l_row_possibility_added = ft_get_all_nb_added(m_max_row);
	int l_column_possibility_added = ft_get_all_nb_added(m_max_column);
	int current_row = 0;
	int current_column = 0;

	while(current_row < m_max_row)
	{
		//d'abord les column
		while (current_column < m_max_column)
		{
			//point de vue du haut
			//		si c'est le minimum donc 1
			if(p_up[current_column] == 1 && p_map[0][current_column] != m_max_column)
			{
				p_map[0][current_column] = m_max_column;
			}
			//		si on demande le max, ecrira la colonne
			if(p_up[current_column] == m_max_column)
			{
				p_map[current_row][current_column] = current_row + 1;
			}

			//point de vue du bas
			//		si c'est le minimum donc 1
			if(p_down[current_column] == 1 && p_map[m_max_row - 1][current_column] != m_max_column)
			{
				p_map[m_max_row - 1][current_column] = m_max_column;
			}
			//		si c'est le max, ecrira la colonne
			if(p_down[current_column] == m_max_column)
			{
				p_map[current_row][current_column] = m_max_column - current_row;
			}


			//Point de vue de gauche
			//		si on demande le max, ecrira la ligne
			if(p_left[current_row] == m_max_row)
			{
				p_map[current_row][current_column] = current_column + 1;
			}


			//Point de vue de droite
			//		si on demande le max, ecrira la ligne
			if(p_right[current_row] == m_max_row)
			{
				p_map[current_row][current_column] = m_max_column - current_column;
			}


			current_column++;
		}


		//point de vue de gauche
		//		si c'est le minimum donc 1
		if(p_left[current_row] == 1 && p_map[current_row][0] != m_max_row)
		{
			p_map[current_row][0] = m_max_row;
		}


		//point de vue de droite
		//		si c'est le minimum donc 1
		if(p_right[current_row] == 1 && p_map[current_row][m_max_column - 1] != m_max_row)
		{
			p_map[current_row][m_max_column - 1] = m_max_row;
		}





		current_column = 0;
		current_row++;
	}


}

int ft_get_all_nb_added(int p_nb)
{
	int result;

	result = 0;

	while(p_nb > 0)
	{
		result += p_nb;
		p_nb--;
	}
	return result;
}
int	**ft_create_dummy_map(int p_max_row, int p_max_column)
{
	//int l_tableau[4][4] = malloc(sizeof(int[4][4]));
	int	**map;
	map = (int **)malloc(sizeof(int *) * p_max_row);
	//map = (int*)malloc(p_max_row * sizeof(int));
	int i;
	for (i = 0; i< p_max_row; i++)
	{
		map[i] = (int *)malloc(p_max_column * sizeof(int));
	}

	int length_row = p_max_row;
	int length_column = p_max_column;

	int current_row = 0;
	int current_column = 0;


	while (current_row < length_row)
	{

		while(current_column < length_column)
		{

			map[current_row][current_column] = 0;
			current_column++;
		}
		current_column = 0;
		current_row++;
	}

	return (map);
}

void ft_print_tableau(int p_row_lenght, int p_column_lenght,int **p_map)
{

	//int length_row = sizeof(p_map) / sizeof(p_map[0]);
	//int length_column = sizeof(p_map[0]) / sizeof(p_map[0][0]);

	int current_row = 0;
	int current_column = 0;

	while (current_row < p_row_lenght)
	{

		while(current_column < p_column_lenght)
		{
			ft_putnb(p_map[current_row][current_column]);
			ft_putchar('\t');
			current_column++;
		}
		ft_putchar('\n');
		current_column = 0;
		current_row++;
	}
}
void ft_putchar(char p_char_to_print)
{
	//write(1, &p_char_to_print, 1);
	printf("%c", p_char_to_print);
}
void ft_putnb(int p_int_to_print)
{
	printf("%d", p_int_to_print);
}

