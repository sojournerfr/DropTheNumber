/*
** SOJOURNER PROJECT, 2025
** add_number.c
** File description:
** add_number
*/

#ifndef ADD_NUMBER
    #define ADD_NUMBER

typedef struct block_s {
    bool DOWN;
    bool RIGHT;
    bool LEFT;
    int nb;
} block_t;

void add_number
(unsigned int ***matrix, unsigned int number, unsigned int offset);

void handle_blocks
(unsigned int ***matrix, unsigned int i, unsigned int j);

void handle_spaces(unsigned int ***matrix);

#endif
