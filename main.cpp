/*
 * @file
 * @brief A simple Tic-Tac-Toe game
 * where you play with AI. Make your own strategy and try to beat it!
 * @details
 * This is a basic game with Command-Line interface. The game includes win and lose, 
 * and randomly chosen symbol (You can either be O or X).
 * You have to input between 1-9 on empty column, and play again if you lose.
 *
 * @author [Reynaldev](https://github.com/Reynaldev)
 */

#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <cmath>

#define CLR_SCR "\033[2J"

#define GRID_LEN        (sizeof(grid) / sizeof(char))
#define PATTERN_LEN     (sizeof(winPatterns) / sizeof(int))

// Define an empty 3x3 grid
char grid[] = {
    ' ', ' ', ' ',
    ' ', ' ', ' ',
    ' ', ' ', ' '
};

// A pattern for the AI to win the game.
// The AI will use this to check every column of the opponent.
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

// A struct/class to define player and AI.
struct {
    char name[64];
    char sym;

    void init(const char *name, unsigned int choice) {
        strcpy(this->name, name);
        this->sym = (choice % 2 == 0) ? 'X' : 'O';
    }
} player, cpu;

enum TurnState { PLAYER, CPU };

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

/*
 * @brief Check a row if it has empty column to put the next symbol
 */
bool hasEmptyGrid(int &pos)
{
    int tPos = pos;
    while (tPos < (pos + 3)) 
    {
        if (grid[winPatterns[tPos]] == ' ')
        {
            pos = tPos;
            return true;
        }

        tPos = (tPos + 1) % PATTERN_LEN;
    }

    return false;
}

int main()
{
    unsigned int input;

    puts(CLR_SCR);
    printf("Welcome to Tic-Tac-Toe Game\n");
    printf("1) Play\n");
    printf("0) Exit\n");
    printf(">> ");
    scanf("%i", &input);

    if (input == 0)
    {
        printf("\nExiting...");

        return 0;
    }
    else if (input == 1)
    {
        srand(time(0));

        // Initialize
        char playerName[] = "";
        int randPick = rand();
        static bool isCpuGoFirst = false;

        TurnState turnState = (randPick % 2 == 0) ? TurnState::PLAYER : TurnState::CPU;

        puts(CLR_SCR);
        printf("Insert your name\n>> ");
        scanf("%s", playerName);

        player.init(playerName, randPick);
        cpu.init("CPU", randPick + 1);

        puts(CLR_SCR);
        printf(
            "Hello %s\n"
            "Your symbol is '%c'\n",
            player.name,
            player.sym
        );

        switch (turnState)
        {
        case TurnState::PLAYER:
            printf("\n\nPlayer go first");
            break;
        case TurnState::CPU:
            isCpuGoFirst = true;
            printf("\n\nCPU go first");
            break;
        }
        
        wait(3000);

        // Gameplay loop
        while (true)
        {
            static char nextSym = ' ';          // Stores current symbol
            static int nextSymIndex = -1;       // Stores current index
            char strEmptyCol[8];                // Stores an array of empty column
            
            // Set strEmptyCol to empty, this will avoid glitch from previous render
            memset(strEmptyCol, 0, sizeof(strEmptyCol));

            // Draw 3x3 grid
            printf("%s\n", CLR_SCR);
            for (int i = 1; i <= GRID_LEN; i++)
            {
                printf("|%c", grid[i - 1]);

                if (grid[i - 1] == ' ')
                    strcat(strEmptyCol, std::to_string(i).c_str());

                if (i % 3 == 0)
                {
                    printf("|\n");

                    for (int j = 0; j < 7; j++) 
                        putchar('-');

                    printf("\n");
                }
            }

            // Check if current symbol is not empty and...
            // ...index has postive value not bigger than the column
            if (nextSym != ' ' && nextSymIndex != -1)
            {
                if (nextSym == player.sym && isWinning(player.sym, nextSymIndex))
                {
                    printf("\nYou won the game!\nCongrats, %s!", player.name);
                    exit(0);
                }
                
                if (nextSym == cpu.sym && isWinning(cpu.sym, nextSymIndex))
                {
                    printf("\nCPU won the game!\nToo bad, %s.", player.name);
                    exit(0);
                }
            }

            // If there's no empty columns left
            if (strlen(strEmptyCol) == 0)
            {
                puts("It's a DRAW!\n");
                exit(0);
            }

            // Start putting a symbol
            switch (turnState)
            {
            case TurnState::PLAYER:
                printf("Empty column(s): %s\n\n", strEmptyCol);
                printf("Your turn\n>> ");
                scanf("%i", &input);
                
                if (input > GRID_LEN || input < 1)
                {
                    puts("\nInvalid input!\n");
                    wait(3000);
                    break;
                }
                
                if (grid[input - 1] != ' ') 
                {
                    puts("\nThat place is not empty!\n");
                    wait(3000);
                    break;
                }

                grid[input - 1] = player.sym;
                nextSym = player.sym;
                nextSymIndex = input - 1;

                turnState = TurnState::CPU;
                break;
            case TurnState::CPU:
                printf("\n\nCPU's turn");
                
                wait(3000);
                
                // CPU win algorithm
                
                // Start defining some variables to calculate position of each symbol
                int nextPos = -1;
                int defPos = -1;
                int offPos = -1;

                int offScore = 0;
                int defScore = 0;
                
                /*
                 * The AI will start a loop based on matching pattern,
                 * where every matched column will add a score to tempScore variable.
                 */
                for (int i = 0; i < PATTERN_LEN; i += 3)
                {
                    int tempScore = 0;

                    // Empty col checking
                    tempScore = (grid[winPatterns[i]] == ' ') ? tempScore + 1 : tempScore;
                    tempScore = (grid[winPatterns[i + 1]] == ' ') ? tempScore + 1 : tempScore;
                    tempScore = (grid[winPatterns[i + 2]] == ' ') ? tempScore + 1 : tempScore;

                    if (tempScore <= 0)
                        continue;

                    tempScore = 0;

                    // Offensive checking
                    tempScore = (grid[winPatterns[i]] == cpu.sym) ? tempScore + 1 : tempScore;
                    tempScore = (grid[winPatterns[i + 1]] == cpu.sym) ? tempScore + 1 : tempScore;
                    tempScore = (grid[winPatterns[i + 2]] == cpu.sym) ? tempScore + 1 : tempScore;

                    if (tempScore >= 1 && offScore < 2)
                    {             
                        offScore = tempScore;  
                        offPos = i;
                    }

                    tempScore = 0;

                    // Deffense checking
                    tempScore = (grid[winPatterns[i]] == player.sym) ? tempScore + 1 : tempScore;
                    tempScore = (grid[winPatterns[i + 1]] == player.sym) ? tempScore + 1 : tempScore;
                    tempScore = (grid[winPatterns[i + 2]] == player.sym) ? tempScore + 1 : tempScore;

                    if (tempScore == 2)
                    {
                        defScore = tempScore;
                        defPos = i;
                    }
                }

                // If either offScore or defScore is bigger than 2 (The threshold value),
                // then use a pattern based on offPos and defPos.
                
                if (offScore >= 2 && hasEmptyGrid(offPos))
                {
                    nextPos = winPatterns[offPos];
                    defScore = 0;
                }

                if (defScore >= 2 && hasEmptyGrid(defPos))
                {
                    nextPos = winPatterns[defPos];
                }

                // If the score is not sufficient to meet the offScore or defScore,
                // then fill a random column with this priority: 
                // center, diagonal, and then vertical or horizontal
                if (nextPos == -1)
                {
                    int pos = 4;
                    int max = pos + GRID_LEN;

                    while (pos < max) 
                    {
                        if (grid[pos % GRID_LEN] == ' ' && (pos % GRID_LEN) % 2 == 0)
                        {
                            nextPos = pos % GRID_LEN;
                            break;
                        }

                        if (grid[pos % GRID_LEN] == ' ')
                            nextPos = pos % GRID_LEN;

                        pos++;
                    }
                }

                grid[nextPos] = cpu.sym;
                nextSym = cpu.sym;
                nextSymIndex = nextPos;

                turnState = TurnState::PLAYER;
                break;
            }
        }
    }
    else
    {
        printf("Invalid input");
    }
    
    return 0;
}
