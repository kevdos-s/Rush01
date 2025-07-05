/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevdos-s <kevdos-s@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 22:47:01 by kevdos-s          #+#    #+#             */
/*   Updated: 2025/07/04 22:47:01 by kevdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <io.h>
#include <stdlib.h>

void rush();
int	**ft_create_dummy_map(int p_max_row, int p_max_column);
void ft_print_tableau(int p_row_lenght, int p_column_lenght,int **p_map);
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

	// pour cree une map avec des données pourrie
	int **l_map = ft_create_dummy_map(m_max_row, m_max_column);

	//=========================================================
	// TODO calculer les donnees à mettre dans la map
	//		si possible, de manière à ce que ça marche meme en changeant la taille de la map (genre en 9x9)

	//pour imprimer la map
	ft_print_tableau(m_max_row, m_max_column, l_map);


	//pour liberer la memoire après l'utilisation de la map
	for (int i = 0; i < m_max_row; i++)
	{
		free(l_map[i]);
	}
	free (l_map);
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


	int testDataColumn = 0;
	while (current_row < length_row)
	{
		testDataColumn = 0;
		while(current_column < length_column)
		{
			testDataColumn += 1;
			map[current_row][current_column] = testDataColumn;
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
	write(1, &p_char_to_print, 1);
	//printf("%c", p_char_to_print);
}
void ft_putnb(int p_int_to_print)
{
	printf("%d", p_int_to_print);
}

