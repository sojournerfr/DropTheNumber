/*
** SOJOURNER PROJECT, 2025
** main.c
** File description:
** This is the main file for the Drop The Number game
*/

#include "drop_the_number.h"

static int handle_input(unsigned int ***matrix, char *input, int status)
{
    if (input[status - 1] == '\n')
        input[status - 1] = '\0';
    if (!strcmp(input, "quit") || !strcmp(input, "exit"))
        return -84;
    if (!strcmp(input, "reset"))
        system("rm -f .highscore");
    if (!strcmp(input, "restart") || !strcmp(input, "reset")) {
        free_matrix(*matrix, ROWS);
        *matrix = init_matrix();
        return -1;
    }
    return 0;
}

static int prompt_column(unsigned int ***matrix)
{
    char *input = NULL;
    size_t len = 0;
    int status = 0;
    int res = 0;
    int col = 0;

    status = getline(&input, &len, stdin);
    if (status == -1) {
        free(input);
        return -84;
    }
    res = handle_input(matrix, input, status);
    if (res != 0) {
        free(input);
        return res;
    }
    col = atoi(input);
    free(input);
    return col;
}

static int get_cols(int nb, unsigned int ***matrix)
{
    int col = 0;

    while (col <= 0 || col > COLS) {
        printf("📍Where do you want to drop the ");
        printf("%d? Select a column (1-%d): ", nb, COLS);
        col = prompt_column(matrix);
        if (col == -84 || col == -1)
            return col;
    }
    printf("\n");
    return col;
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
    int i = 0;

    for (i = 0; i < COLS; i++)
        if (matrix[0][i] != 0)
            return false;
    return true;
}

static void play_turn(unsigned int ***matrix)
{
    unsigned int number = 0;
    int cols = 0;

    number = get_rdnumber();
    printf("\n💡Incoming number: \033[34m%u\033[0m\n", number);
    cols = get_cols(number, matrix);
    if (cols == -84) {
        free_matrix(*matrix, ROWS);
        exit(0);
    }
    if (cols == -1) {
        display_matrix(*matrix);
        return;
    }
    add_number(matrix, number, cols);
    display_matrix(*matrix);
}

int main(void)
{
    unsigned int **matrix = NULL;

    matrix = init_matrix();
    display_matrix(matrix);
    while (is_over(matrix)) {
        play_turn(&matrix);
    }
    free_matrix(matrix, ROWS);
    printf("\033[1m\n Game Over !!!\033[0m\n");
    return 0;
}
