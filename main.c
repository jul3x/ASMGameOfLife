#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
            printf("%c", tab[i * w + j]);
        }

        printf("\n");
    }
}

extern void start(int, int, char*);
extern void run(int steps);


int main(int argc, char** argv)
{
    char* tab;
    int w = 0, h = 0;

    if (argc == 2)
    {
        loadTab(argv[1], &w, &h, &tab);
        start(w, h, tab);
        for (int i = 0; i < 100000; ++i)
        {
            printf("---------------\n");
            printTab(w, h, tab);
            run(1);
            usleep(200000);
        }
    }
    else
    {
        printf("Usage: ./game <file_path>\n");
        printf("Example: ./game tests/glider.txt\n\n");
    }


    return 0;
}