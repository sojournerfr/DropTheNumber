/*
** SOJOURNER PROJECT, 2025
** handle_game.c
** File description:
** This file contains functions to handle the game logic
** such as associating blocks, handling spaces, and adding numbers.
*/

#include "drop_the_number.h"

static void associate_blocks
(unsigned int ***matrix, block_t block, unsigned int i, unsigned int j)
{
    unsigned int **current = *matrix;

    current[i][j] *= (block.nb > 0) ? (1U << block.nb) : current[i][j];
    if (block.LEFT && j > 0)
        current[i][j - 1] = 0;
    if (block.RIGHT && j + 1 < COLS)
        current[i][j + 1] = 0;
    if (block.DOWN && i + 1 < ROWS) {
        current[i + 1][j] = current[i][j];
        current[i][j] = 0;
        handle_blocks(matrix, i + 1, j);
    } else
        handle_blocks(matrix, i, j);
    if (block.LEFT && j > 0)
        handle_blocks(matrix, i, j - 1);
    if (block.RIGHT && j + 1 < COLS)
        handle_blocks(matrix, i, j + 1);
    handle_spaces(matrix);
}

void handle_blocks(unsigned int ***matrix, unsigned int i, unsigned int j)
{
    unsigned int **current = *matrix;
    block_t block = {0, 0, 0, 0};

    if (current[i][j] == 0)
        return;
    if (i + 1 < ROWS && current[i][j] == current[i + 1][j])
        block.DOWN = true;
    if (j > 0 && current[i][j] == current[i][j - 1])
        block.LEFT = true;
    if (j + 1 < COLS && current[i][j] == current[i][j + 1])
        block.RIGHT = true;
    block.nb = block.DOWN + block.LEFT + block.RIGHT;
    if (block.nb != 0)
        associate_blocks(matrix, block, i, j);
    if (block.LEFT && j > 0 && current[i][j - 1] != 0)
        handle_blocks(matrix, i, j - 1);
    if (block.RIGHT && j + 1 < COLS && current[i][j + 1] != 0)
        handle_blocks(matrix, i, j + 1);
    if (i + 1 < ROWS && current[i + 1][j] != 0)
        handle_blocks(matrix, i + 1, j);
}

static void handle_spaces_bis
(unsigned int ***matrix, unsigned int j, unsigned int i)
{
    unsigned int **current = *matrix;

    if (i + 1 >= ROWS)
        return;
    if (current[i][j] != 0 && current[i + 1][j] == 0) {
        current[i + 1][j] = current[i][j];
        current[i][j] = 0;
        handle_spaces(matrix);
    }
}

void handle_spaces(unsigned int ***matrix)
{
    for (int j = 0; j < COLS; j++)
        for (int i = ROWS - 2; i >= 0; i--)
            handle_spaces_bis(matrix, j, i);
}

static unsigned int get_offset(unsigned int cols)
{
    if (cols == 1)
        return 0;
    if (cols == COLS)
        return COLS - 1;
    return cols - 1;
}

void add_number(unsigned int ***matrix, unsigned int number, unsigned int cols)
{
    unsigned int **current = *matrix;
    unsigned int index = 1;
    unsigned int offset = get_offset(cols);

    if (cols <= 0 || cols > COLS)
        return;
    while (current[ROWS - index][offset] != 0 && index < ROWS)
        index++;
    current[ROWS - index][offset] = number;
    handle_blocks(matrix, ROWS - index, offset);
}
