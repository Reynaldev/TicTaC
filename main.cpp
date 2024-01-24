#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace chrono;

int patterns[] = {
    // Horizontal
    0, 1, 2,
    3, 4, 5,
    6, 7, 8,

    // Vertical
    0, 3, 6,
    1, 4, 7,
    2, 5, 8,

    // Diagonal
    0, 4, 8,
    2, 4, 6
};

void insertSymbol(int input)
{
    // printf("\nSymbol: %s\n", input);

    // switch (input)
    // {
    //     case 0:
    //         grid[0][0] = 'X';
    //         break;
    //     case 1:
    //         grid[0][2] = 'X';
    //         break;
    //     case 2:
    //         grid[0][4] = 'X';
    //         break;
    //     case 3:
    //         grid[2][0] = 'X';
    //         break;
    //     case 4:
    //         grid[2][2] = 'X';
    //         break;
    //     case 5:
    //         grid[2][4] = 'X';
    //         break;
    //     case 6:
    //         grid[4][0] = 'X';
    //         break;
    //     case 7:
    //         grid[4][2] = 'X';
    //         break;
    //     case 8:
    //         grid[4][4] = 'X';
    //         break;
    //     default:
    //         printf("Invalid input. Only 0 to 8\n");
    //         break;
    // }
}

int main()
{
    char grid[] = {
        '0', '1', '2',
        '3', '4', '5',
        '6', '7', '8'
    };

    int gridLength = (sizeof(grid) / sizeof(char));

    unsigned int input;

    printf("\033[2J");
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
        bool quit = false;
        while (!quit)
        {
            printf("\033[2J");

            for (int i = 1; i <= gridLength; i++)
            {
                printf("|%c", grid[i - 1]);

                if (i % 3 == 0)
                {
                    printf("|\n");
                }
            }

            printf("Your turn\n>> ");
            scanf("%d", &input);

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