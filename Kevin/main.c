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

void rush();
void test(int p_row_lenght, int p_column_lenght,int p_tableau[p_row_lenght][p_column_lenght]);
void ft_putchar(char p_char_to_print);
void ft_putnb(int p_int_to_print);

int main()
{
	rush();
}

void rush()
{
	const int max_row = 4;
	const int max_column = 4;
	int l_tableau[4][4];

	int length_row = sizeof(l_tableau) / sizeof(l_tableau[0]);
	int length_column = sizeof(l_tableau[0]) / sizeof(l_tableau[0][0]);

	int current_row = 0;
	int current_column = 0;


	int testDataColumn = 0;
	int testDataRow = 60;
	while (current_row < length_row)
	{
		testDataColumn = 0;
		while(current_column < length_column)
		{
			testDataColumn += 1;
			l_tableau[current_row][current_column] = testDataColumn;
			current_column++;
		}
		current_column = 0;
		current_row++;
	}

	test(length_row, length_column, l_tableau);
}

void test(int p_row_lenght, int p_column_lenght,int p_tableau[p_row_lenght][p_column_lenght])
{

	//int length_row = sizeof(p_tableau) / sizeof(p_tableau[0]);
	//int length_column = sizeof(p_tableau[0]) / sizeof(p_tableau[0][0]);

	int current_row = 0;
	int current_column = 0;

	while (current_row < p_row_lenght)
	{

		while(current_column < p_column_lenght)
		{
			ft_putnb(p_tableau[current_row][current_column]);
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

