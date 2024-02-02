#include <iostream>
#include <string>
#include <cstring>
#include <ctime>

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
            char strEmptyCol[8];

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

            if (nextSym != ' ')
            {
                if (nextSym == player.sym && isWinning(player.sym))
                {
                    printf("\nYou won the game!\nCongrats, %s!", player.name);
                    return 0;
                }
                
                if (nextSym == cpu.sym && isWinning(cpu.sym))
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

                turnState = TurnState::PLAYER;
                break;
            }

            memset(strEmptyCol, 0, sizeof(strEmptyCol));
        }
    }
    else
    {
        printf("Invalid input");
    }
    
    return 0;
}