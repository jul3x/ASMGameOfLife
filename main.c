#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int w = 0, h = 0;
char* board = NULL;
char* temp_board = NULL;

void loadTab(const char* filename, int* w, int* h, char** tab)
{
    FILE *input;
    int _w, _h;
    input = fopen(filename, "r");

    if(input == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    fscanf(input, "%d %d", &_w, &_h);
    *w = _w;
    *h = _h;

    *tab = malloc(_w * _h * sizeof(char));

    int helper = 0;
    for (int i = 0; i < _h; ++i)
    {
        for (int j = 0; j < _w; ++j)
        {
            fscanf(input, "%d ", &helper);
            (*tab)[i * _w + j] = helper == 1 ? '*' : ' ';
        }
    }

    fclose(input);
}

void printTab(int w, int h, char* tab)
{
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            printf("%c ", tab[i * w + j]);
        }

        printf("\n");
    }
}

// void start(int _w, int _h, char* tab)
// {
//     board = tab;
//     w = _w;
//     h = _h;

//     temp_board = malloc(_w * _h * sizeof(char));

//     for (int i = 0; i < _w * _h; ++i)
//     {
//         temp_board[i] = board[i];
//     }
// }

extern int start(int, int, char*);

int checkNeighbours(int i, int j)
{
    int count = 0;
    int left_index = (i * w) + j - 1;
    int right_index = (i * w) + j + 1;
    int top_index = ((i - 1) * w) + j;
    int bottom_index = ((i + 1) * w) + j;
    int left_top_index = ((i - 1) * w) + j - 1;
    int left_bottom_index = ((i + 1) * w) + j - 1;
    int right_top_index = ((i - 1) * w) + j + 1;
    int right_bottom_index = ((i + 1) * w) + j + 1;

    if (j > 0)
        if (temp_board[left_index] == '*')
            ++count;

    if (j < w - 1)
        if (temp_board[right_index] == '*')
            ++count;

    if (i > 0)
        if (temp_board[top_index] == '*')
            ++count;

    if (i < h - 1)
        if (temp_board[bottom_index] == '*')
            ++count;

    if (j > 0)
    {
        if (i > 0)
            if (temp_board[left_top_index] == '*')
                ++count;
        if (i < h - 1)
            if (temp_board[left_bottom_index] == '*')
                ++count;
    }

    if (j < w - 1)
    {
        if (i > 0)
            if (temp_board[right_top_index] == '*')
                ++count;
        if (i < h - 1)
            if (temp_board[right_bottom_index] == '*')
                ++count;
    }

    return count;
}

void runOnce()
{
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            int living_neighbours = checkNeighbours(i, j);
            int index = i * w + j;
            if (living_neighbours == 3)
            {
                board[index] = '*';
            }
            else if (living_neighbours == 2 && temp_board[index] == '*')
            {
                board[index] = '*';
            }
            else
            {
                board[index] = ' ';
            }
        }
    }

    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            int index = i * w + j;
            temp_board[index] = board[index];
        }
    }
}

int main(int argc, char** argv)
{
    char* tab;
    int _w = 0, _h = 0;

    if (argc == 2)
    {
        loadTab(argv[1], &_w, &_h, &tab);
        // printf("%d", start(_w, _h, tab));
        // printf("\n%d", tab);
        char* a = (char*)start(_w, _h, tab);

        printTab(_w, _h, a);
        // for (int i = 0; i < 100000; ++i)
        // {
        //     printf("---------------\n");
        //     printTab(w, h, temp_board);
        //     runOnce();
        //     usleep(100000);
        // }

        // free(tab);
    }
    else
    {
        printf("Usage: ./game <file_path>\n");
        printf("Example: ./game tests/glider.txt\n\n");
    }


    return 0;
}