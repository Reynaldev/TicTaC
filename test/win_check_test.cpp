/*
* A test to see which condition check is faster between loop-based (iterate every winPatterns) and
* condition-based (check certain specified index).
*/

#include <iostream>
#include <cstring>
#include <cmath>
#include <chrono>

#define CLR_SCR "\033[2J"

// Loop-based or Condition-based
// #define LOOP_CHCK
#define COND_CHCK

// Pick one or uncomment all
// #define VERTICAL_TEST
// #define HORIZONTAL_TEST
#define DIAGONAL_TEST

char grid[] = {
    ' ', ' ', ' ',
    ' ', ' ', ' ',
    ' ', ' ', ' '
};

int winPatterns[] = {
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

// Loop based winning checker
#ifdef LOOP_CHCK
bool isWinning(char c)
{
    for (int i = 0; i < (sizeof(winPatterns) / sizeof(int)); i += 3)
    {
        if ((grid[winPatterns[i]] == c) 
            && (grid[winPatterns[i + 1]] == c) 
            && (grid[winPatterns[i + 2]] == c)) 
        {
            return true;
        }
    }

    return false;
}
#endif

// Condition based winning checker
#ifdef COND_CHCK
bool isWinning(char c, int i)
{
    // Diagonal right
    if (grid[0] == c 
        && grid[4] == c 
        && grid[8] == c)
            return true;

    // Diagonal left
    if (grid[2] == c
        && grid[4] == c
        && grid[6] == c)
            return true;

    // Vertical
    if (grid[i] == c 
        && grid[(i + 3) % 9] == c 
        && grid[(i + 6) % 9] == c)
            return true;

    // Horizontal
    // Get first index of the row
    int row = floor(i / 3) * 3;
    if (grid[row] == c 
        && grid[row + 1] == c
        && grid[row + 2] == c)
            return true;

    return false;
}
#endif

int main()
{
    int gridLength = sizeof(grid) / sizeof(char);
    char sym = 'X';

#ifdef VERTICAL_TEST
    for (int i = 0; i < 3; i++) 
    {
        printf("\nVertical test %d\n", i + 1);

        memset(grid, ' ', sizeof(grid));
        grid[i] = sym;
        grid[i + 3] = sym;
        grid[i + 6] = sym;

        for (int j = 1; j <= gridLength; j++)
        {
            printf("|%c", grid[j - 1]);

            if (j % 3 == 0)
            {
                printf("|\n");

                for (int k = 0; k < 7; k++) 
                    putchar('-');

                printf("\n");
            }
        }

        auto t1 = std::chrono::high_resolution_clock::now();
        
#ifdef LOOP_CHCK
        if (isWinning(sym))
        {
            puts("Win\n");
        }
#endif

#ifdef COND_CHCK
        if (isWinning(sym, i))
        {
            puts("Win\n");
        }
#endif
        
        auto t2 = std::chrono::high_resolution_clock::now();

        auto d = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

        printf("Vertical test %d time:\n%d microseconds", i + 1, d);

        putchar('\n');
    }
#endif // VERTICAL_TEST

#ifdef HORIZONTAL_TEST
    for (int i = 0; i < 3; i++) 
    {
        printf("\nHorizontal test %d\n", i + 1);

        int row = i * 3;
        
        memset(grid, ' ', sizeof(grid));
        grid[row] = sym;
        grid[row + 1] = sym;
        grid[row + 2] = sym;

        for (int j = 1; j <= gridLength; j++)
        {
            printf("|%c", grid[j - 1]);

            if (j % 3 == 0)
            {
                printf("|\n");

                for (int k = 0; k < 7; k++) 
                    putchar('-');

                printf("\n");
            }
        }

        auto t1 = std::chrono::high_resolution_clock::now();
        
#ifdef LOOP_CHCK
        if (isWinning(sym))
        {
            puts("Win\n");
        }
#endif

#ifdef COND_CHCK
        if (isWinning(sym, row))
        {
            puts("Win\n");
        }
#endif
        
        auto t2 = std::chrono::high_resolution_clock::now();

        auto d = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

        printf("Horizontal test %d time:\n%d microseconds", i + 1, d);

        putchar('\n');
    }
#endif // HORIZONTAL_TEST

#ifdef DIAGONAL_TEST
    for (int i = 1; i <= 2; i++) 
    {
        printf("\nHorizontal test %d\n", i);
        
        memset(grid, ' ', sizeof(grid));
        grid[(i % 2 == 0) ? 0 : 2] = sym;
        grid[4] = sym;
        grid[(i % 2 == 0) ? 8 : 6] = sym;

        for (int j = 1; j <= gridLength; j++)
        {
            printf("|%c", grid[j - 1]);

            if (j % 3 == 0)
            {
                printf("|\n");

                for (int k = 0; k < 7; k++) 
                    putchar('-');

                printf("\n");
            }
        }

        auto t1 = std::chrono::high_resolution_clock::now();
        
#ifdef LOOP_CHCK
        if (isWinning(sym))
        {
            puts("Win\n");
        }
#endif

#ifdef COND_CHCK
        if (isWinning(sym, 4))
        {
            puts("Win\n");
        }
#endif
        
        auto t2 = std::chrono::high_resolution_clock::now();

        auto d = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

        printf("Horizontal test %d time:\n%d microseconds", i + 1, d);

        putchar('\n');
    }
#endif // DIAGONAL_TEST

    return 0;
}