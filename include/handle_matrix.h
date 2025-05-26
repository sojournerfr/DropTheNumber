/*
** EPITECH PROJECT, 2025
** handle_matrix.h
** File description:
** handle_matrix
*/

#ifndef HANDLE_MATRIX_H_
    #define HANDLE_MATRIX_H_

    #include "drop_the_number.h"

    #define ROWS 6
    #define COLS 4

unsigned int **init_matrix(void);
void free_matrix(unsigned int **matrix, int row);
void display_matrix(unsigned int **matrix);

#endif
