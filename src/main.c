/*
** EPITECH PROJECT, 2025
** main.c
** File description:
** This is the main file for the Drop The Number game
*/

#include "drop_the_number.h"

static int get_cols(int nb)
{
    char *input = "NULL";
    char *temp = NULL;
    int status = 0;
    size_t len = 0;

    while (status == -1 || atoi(input) <= 0 || atoi(input) > COLS) {
        printf("📍Where do you want to drop the %d? ", nb);
        printf("Select a column (1-4): ");
        status = getline(&input, &len, stdin);
        temp = malloc(sizeof(char) * (strlen(input) + 1));
        if (temp == NULL)
            return -84;
        strcpy(temp, input);
        temp[strlen(temp) - 1] = '\0';
        if (!strcmp(temp, "quit") || !strcmp(temp, "exit"))
            return -84;
        free(temp);
    }
    printf("\n");
    return atoi(input);
}

static unsigned int get_rdnumber(void)
{
    int r = 0;

    srand(time(NULL));
    r = rand() % 100;
    if (r < 30)
        return 2;
    if (r < 60)
        return 4;
    if (r < 80)
        return 8;
    if (r < 90)
        return 16;
    return 32;
}

static bool is_over(unsigned int **matrix)
{
    for (int i = 0; i < COLS; i++)
        if (matrix[0][i] != 0)
            return false;
    return true;
}

int main(void)
{
    unsigned int **matrix = init_matrix();
    unsigned int number = 0;
    int cols = 0;
    bool game = true;

    display_matrix(matrix);
    while (game) {
        number = get_rdnumber();
        printf("\n💡Incoming number: \033[34m%u\033[0m\n", number);
        cols = get_cols(number);
        if (cols == -84)
            break;
        add_number(&matrix, number, cols);
        display_matrix(matrix);
        game = is_over(matrix);
    }
    free_matrix(matrix, ROWS);
    printf("\033[1m\n Game Over !!!\033[0m\n");
    return 0;
}
