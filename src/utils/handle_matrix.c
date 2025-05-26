/*
** SOJOURNER PROJECT, 2025
** handle_matrix.c
** File description:
** This file contains functions to handle the matrix
** such as initializing, displaying, and freeing the matrix.
*/

#include "drop_the_number.h"

static int count_digits(int n)
{
    int count = 0;

    if (n == 0)
        return 1;
    n = abs(n);
    while (n != 0) {
        n /= 10;
        count++;
    }
    return count;
}

static int get_cell_length(unsigned int **matrix)
{
    int size = 0;
    int len = 0;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            len = count_digits(matrix[i][j]);
            size = (len > size) ? len : size;
        }
    }
    return size;
}

void free_matrix(unsigned int **matrix, int row)
{
    if (!matrix)
        return;
    for (int i = 0; i < row; i++)
        free(matrix[i]);
    free(matrix);
}

static int get_ptn(unsigned int **matrix)
{
    int total = 0;

    if (!matrix)
        return 0;
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            total += matrix[i][j];
    return total;
}

static void display_color(int width, unsigned int value)
{
    if (value == 0)
        printf("\033[0;32m %0*d \033[0m", width, value);
    else
        printf("\033[0;31m %0*d \033[0m", width, value);
    printf("|");
}

void display_matrix(unsigned int **matrix)
{
    int width = get_cell_length(matrix);

    system("clear");
    printf("\033[1m DropTheNumber by Sojourner:\033[0m\n\n");
    if (!matrix)
        return;
    for (int i = 0; i < ROWS; i++) {
        printf(" |");
        for (int j = 0; j < COLS; j++)
            display_color(width, matrix[i][j]);
        printf("\n");
    }
    printf("\033[1m\n Total: %d pts\033[0m\n", get_ptn(matrix));
}

unsigned int **init_matrix(void)
{
    unsigned int **matrix = malloc(sizeof(int *) * ROWS);

    if (!matrix)
        return NULL;
    for (int i = 0; i < ROWS; i++) {
        matrix[i] = malloc(sizeof(int) * COLS);
        if (!matrix[i]) {
            free_matrix(matrix, i);
            return NULL;
        }
    }
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            matrix[i][j] = 0;
    return matrix;
}
