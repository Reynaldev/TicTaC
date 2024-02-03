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

char grid[] = {
    ' ', ' ', ' ',
    ' ', 'O', ' ',
    ' ', 'O', ' '
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

int main(int argc, char **argv)
{
    int gridLength = (sizeof(grid) / sizeof(char));
    int patternLength = (sizeof(winPatterns) / sizeof(int)); 
    char symbol = 'X';
    char oppSym = 'O';

    while (true)
    {
        static char nextSym = ' ';
        static int nextSymIndex = -1;

        printf("%s\n", CLR_SCR);
        for (int i = 1; i <= gridLength; i++)
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

        int nextPos = -1;

        int defPos = -1;
        int offPos = -1;

        int offScore = 0;
        bool deffenseMode = false;
        
        for (int i = 0; i < patternLength; i += 3)
        {
            int tempScore = 0;

            printf("Row %d\n", i / 3);

            // Deffense checking
            tempScore = (grid[winPatterns[i]] == oppSym) ? tempScore + 1 : tempScore;
            tempScore = (grid[winPatterns[i + 1]] == oppSym) ? tempScore + 1 : tempScore;
            tempScore = (grid[winPatterns[i + 2]] == oppSym) ? tempScore + 1 : tempScore;
            
            tempScore = (grid[winPatterns[i]] == symbol) ? tempScore + 1 : tempScore;
            tempScore = (grid[winPatterns[i + 1]] == symbol) ? tempScore + 1 : tempScore;
            tempScore = (grid[winPatterns[i + 2]] == symbol) ? tempScore + 1 : tempScore;

            if (tempScore == 2)
            {
                deffenseMode = true;
                defPos = i;
            }

            if (deffenseMode)
                break;

            // Offensive checking
            tempScore = (grid[winPatterns[i]] == ' ' || grid[winPatterns[i]] == symbol) ? tempScore + 1 : tempScore;
            tempScore = (grid[winPatterns[i + 1]] == ' ' || grid[winPatterns[i + 1]] == symbol) ? tempScore + 1 : tempScore;
            tempScore = (grid[winPatterns[i + 2]] == ' ' || grid[winPatterns[i + 2]] == symbol) ? tempScore + 1 : tempScore;

            if (tempScore > offScore)
            {
                offScore = tempScore;
                offPos = i;
            }
        }

        if (deffenseMode)
        {
            while (grid[winPatterns[defPos]] != ' ' && defPos < (defPos + 3)) defPos++;

            nextPos = winPatterns[defPos];
        }
        else
        {
            while (grid[winPatterns[offPos]] != ' ' && offPos < (offPos + 3)) offPos++;

            nextPos = winPatterns[offPos];
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