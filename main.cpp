#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <cmath>

#define CLR_SCR "\033[2J"

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

int main()
{
    int gridLength = (sizeof(grid) / sizeof(char));

    unsigned int input;

    puts(CLR_SCR);
    printf("Welcome to TicTac++\n");
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
            printf("\n\nCPU go first");
            break;
        }
        
        wait(3000);

        // Gameplay loop
        while (true)
        {
            static char nextSym = ' ';
            static int nextSymIndex = -1;
            char strEmptyCol[8];
            
            memset(strEmptyCol, 0, sizeof(strEmptyCol));

            printf("%s\n", CLR_SCR);
            for (int i = 1; i <= gridLength; i++)
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

            if (nextSym != ' ' && nextSymIndex != -1)
            {
                if (nextSym == player.sym && isWinning(player.sym, nextSymIndex))
                {
                    printf("\nYou won the game!\nCongrats, %s!", player.name);
                    return 0;
                }
                
                if (nextSym == cpu.sym && isWinning(cpu.sym, nextSymIndex))
                {
                    printf("\nCPU won the game!\nToo bad, %s.", player.name);
                    return 0;
                }
            }

            switch (turnState)
            {
            case TurnState::PLAYER:
                printf("Empty column(s): %s\n\n", strEmptyCol);
                printf("Your turn\n>> ");
                scanf("%i", &input);
                
                if (input > gridLength || input < 1)
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

                int symPlace = rand() % gridLength;
                while (grid[symPlace] != ' ') 
                {
                    symPlace = (symPlace + 1) % gridLength;

                    printf("\n%d", symPlace);
                }
                
                // static int strategy = -1;
                // if (strategy < 0) 
                // {
                //     int symPlace = rand() % gridLength;
                //     while (grid[symPlace] != ' ') 
                //     {
                //         symPlace = (symPlace + 3) % gridLength;

                //         printf("\n%d", symPlace);
                //     }
                // }

                grid[symPlace] = cpu.sym;
                nextSym = cpu.sym;
                nextSymIndex = symPlace;

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