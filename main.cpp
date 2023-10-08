#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace chrono;

char grid[6][6] = {
    { ' ', '|', ' ', '|', ' ' },
    { '-', '-', '-', '-', '-' },
    { ' ', '|', ' ', '|', ' ' },
    { '-', '-', '-', '-', '-' },
    { ' ', '|', ' ', '|', ' ' }
};

void insertSymbol(int input)
{
    // printf("\nSymbol: %s\n", input);

    switch (input)
    {
        case 0:
            grid[0][0] = 'X';
            break;
        case 1:
            grid[0][2] = 'X';
            break;
        case 2:
            grid[0][4] = 'X';
            break;
        case 3:
            grid[2][0] = 'X';
            break;
        case 4:
            grid[2][2] = 'X';
            break;
        case 5:
            grid[2][4] = 'X';
            break;
        case 6:
            grid[4][0] = 'X';
            break;
        case 7:
            grid[4][2] = 'X';
            break;
        case 8:
            grid[4][4] = 'X';
            break;
        default:
            printf("Invalid input. Only 0 to 8\n");
            break;
    }
}

int main()
{
    uint input;

    printf("Welcome to TicTac++\n");
    printf("1) Play\n");
    printf("0) Exit\n");
    printf(">> ");
    scanf("%i", &input);

    if (input == 0)
    {
        return 0;
    }
    else if (input == 1)
    {
        int gridX = 5;
        int gridY = 5;

        bool quit = false;
        while (!quit)
        {
            for (int i = 0; i < gridY; i++)
            {
                for (int j = 0; j < gridX; j++)
                {
                    printf("%c", grid[i][j]);
                }

                putchar('\n');
            }

            printf("Your turn\n>> ");
            scanf("%i", &input);

            insertSymbol(input);
        }
    }
    else
    {
        printf("Invalid input");
    }

    printf("Exiting...");

    return 0;
}