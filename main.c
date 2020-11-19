#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int w = 0, h = 0;
char* board = NULL;
char* temp_board = NULL;

void loadTab(const char* filename, short int* w, short int* h, char** tab)
{
    FILE *input;
    short int _w, _h;
    input = fopen(filename, "r");

    if(input == NULL)
    {
        printf("Error opening file!");
        exit(1);
    }

    fscanf(input, "%hd %hd", &_w, &_h);
    *w = _w;
    *h = _h;

    *tab = malloc(_w * _h * sizeof(char));

    short int helper = 0;
    for (unsigned short int i = 0; i < _h; ++i)
    {
        for (unsigned short int j = 0; j < _w; ++j)
        {
            fscanf(input, "%hd ", &helper);
            (*tab)[i * _w + j] = helper == 1 ? '*' : ' ';
        }
    }

    fclose(input);
}

void printTab(int w, int h, char* tab)
{
    for (unsigned short int i = 0; i < h; ++i)
    {
        for (unsigned short int j = 0; j < w; ++j)
        {
            printf("%c ", tab[i * w + j]);
        }

        printf("\n");
    }
}

void start(int _w, int _h, char* tab)
{
    board = tab;
    w = _w;
    h = _h;

    temp_board = malloc(_w * _h * sizeof(char));

    for (unsigned int i = 0; i < _w * _h; ++i)
    {
        temp_board[i] = board[i];
    }
}

unsigned short int checkNeighbours(unsigned short int i, unsigned short int j)
{
    unsigned short int count = 0;
    unsigned int left_index = (i * w) + j - 1;
    unsigned int right_index = (i * w) + j + 1;
    unsigned int top_index = ((i - 1) * w) + j;
    unsigned int bottom_index = ((i + 1) * w) + j;
    unsigned int left_top_index = ((i - 1) * w) + j - 1;
    unsigned int left_bottom_index = ((i + 1) * w) + j - 1;
    unsigned int right_top_index = ((i - 1) * w) + j + 1;
    unsigned int right_bottom_index = ((i + 1) * w) + j + 1;

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
    for (unsigned short int i = 0; i < h; ++i)
    {
        for (unsigned short int j = 0; j < w; ++j)
        {
            unsigned short int living_neighbours = checkNeighbours(i, j);
            unsigned int index = i * w + j;
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

    for (unsigned short int i = 0; i < h; ++i)
    {
        for (unsigned short int j = 0; j < w; ++j)
        {
            unsigned int index = i * w + j;
            temp_board[index] = board[index];
        }
    }
}

int main(int argc, char** argv)
{
    char* tab;
    short int _w = 0, _h = 0;

    if (argc == 2)
    {
        loadTab(argv[1], &_w, &_h, &tab);
        start(_w, _h, tab);

        for (int i = 0; i < 100000; ++i)
        {
            printf("---------------\n");
            printTab(w, h, temp_board);
            runOnce();
            usleep(100000);
        }

        free(tab);
    }
    else
    {
        printf("Usage: ./game <file_path>\n");
        printf("Example: ./game tests/glider.txt\n\n");
    }

    
    return 0;
}