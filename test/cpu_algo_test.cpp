/*
* A script to do algorithm test for the CPU to win the game.
*/

#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <ctime>
#include <chrono>

#define CLR_SCR "\033[2J"

#define GRID_LEN        (sizeof(grid) / sizeof(char))
#define PATTERN_LEN     (sizeof(winPatterns) / sizeof(int))

char grid[] = {
    ' ', ' ', ' ',
    ' ', 'O', ' ',
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

enum CPUMode { DEFFENSIVE, OFFENSIVE };

void wait(int ms)
{
    while (true) {
        static clock_t t = clock();
        int d = (clock() - t);

        if (d != 0 && d % ms == 0) 
            break;

        // printf("\n%d", d % 3);
    }
}

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

bool hasEmptyGrid(int &pos)
{
    printf("Checking empty col at pattern %d\n", pos);
    int tPos = pos;
    while (tPos < (pos + 3)) 
    {
        printf("%d - Col %d\n", tPos, winPatterns[tPos]);

        if (grid[winPatterns[tPos]] == ' ')
        {
            printf("Empty Col at %d\n", winPatterns[tPos]);
            pos = tPos;
            return true;
        }

        tPos = (tPos + 1) % PATTERN_LEN;
    }

    printf("No empty col at %d row\n", pos);
    return false;
}

int main(int argc, char **argv)
{
    char symbol = 'X';
    char oppSym = 'O';

    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            int index = std::atoi((char*)argv[i]);
            grid[index] = 'O';
        }
    }

    while (true)
    {
        static char nextSym = ' ';
        static int nextSymIndex = -1;

        // printf("%s\n", CLR_SCR);
        for (int i = 1; i <= GRID_LEN; i++)
        {
            printf("|%c", grid[i - 1]);

            if (i % 3 == 0)
            {
                printf("|\n");

                for (int j = 0; j < 7; j++) 
                    putchar('-');

                printf("\n");
            }
        }

        if (nextSymIndex != -1)
        {
            if (nextSym == symbol && isWinning(symbol, nextSymIndex))
            {
                printf("\nCPU won the game!\n");
                return 0;
            }
        }

        puts("CPU is thinking!\n");

        auto t1 = std::chrono::high_resolution_clock::now();

        CPUMode mode = CPUMode::OFFENSIVE;

        int nextPos = -1;
        int defPos = -1;
        int offPos = -1;

        int offScore = 0;
        int defScore = 0;
        
        for (int i = 0; i < PATTERN_LEN; i += 3)
        {
            int tempScore = 0;

            printf("Row %d, index: %d\n", i / 3, i);

            // Empty col checking
            tempScore = (grid[winPatterns[i]] == ' ') ? tempScore + 1 : tempScore;
            tempScore = (grid[winPatterns[i + 1]] == ' ') ? tempScore + 1 : tempScore;
            tempScore = (grid[winPatterns[i + 2]] == ' ') ? tempScore + 1 : tempScore;

            if (tempScore <= 0)
            {
                printf("No empty col at pattern row %d", i / 3);
                continue;
            }

            tempScore = 0;

            // Offensive checking
            tempScore = (grid[winPatterns[i]] == symbol) ? tempScore + 1 : tempScore;
            tempScore = (grid[winPatterns[i + 1]] == symbol) ? tempScore + 1 : tempScore;
            tempScore = (grid[winPatterns[i + 2]] == symbol) ? tempScore + 1 : tempScore;

            if (tempScore >= 1 && offScore < 2)
            {          
                offScore = tempScore;  
                offPos = i;
            }

            if (tempScore >= 2)
            {
                printf("Win at pattern row %d\n", i / 3);
            }

            tempScore = 0;

            // Deffense checking
            tempScore = (grid[winPatterns[i]] == oppSym) ? tempScore + 1 : tempScore;
            tempScore = (grid[winPatterns[i + 1]] == oppSym) ? tempScore + 1 : tempScore;
            tempScore = (grid[winPatterns[i + 2]] == oppSym) ? tempScore + 1 : tempScore;

            if (tempScore == 2)
            {
                printf("Danger at pattern row %d\n", i / 3);
                defScore = tempScore;
                defPos = i;
            }
        }

        printf(
            "Off Score: %d\n"
            "Off Position: %d\n",
            offScore, offPos
        );

        printf(
            "Def Score: %d\n"
            "Def Position: %d\n",
            defScore, defPos
        );

        if (offScore >= 2 && hasEmptyGrid(offPos))
        {
            nextPos = winPatterns[offPos];
            defScore = 0;
        }

        if (defScore >= 2 && hasEmptyGrid(defPos))
        {
            nextPos = winPatterns[defPos];
        }

        if (nextPos == -1)
        {
            nextPos = 0;
            // while (grid[winPatterns[nextPos]] != ' ') nextPos = (nextPos + 1) % PATTERN_LEN;
            while (nextPos < GRID_LEN) 
            {
                if (grid[nextPos] == ' ')
                    printf("Empty col at index %d\n", nextPos);

                if (nextPos % 2 == 0)
                    printf("Even col at %d\n\n", nextPos);

                nextPos++;
            }

            putchar('\n');

            nextPos = winPatterns[nextPos];
        }

        auto t2 = std::chrono::high_resolution_clock::now();
        
        grid[nextPos] = symbol;
        nextSym = symbol;
        nextSymIndex = nextPos;

        auto d = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

        printf("I filled the %d column\n", nextPos);
        printf("It took me %d microseconds to think\n", d);

        wait(3000);
    } 

    return 0;
}