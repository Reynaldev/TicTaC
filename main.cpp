#include <iostream>
#include <string>
#include <cstring>
#include <ctime>

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

int main()
{
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

        printf("\033[2J");
        printf("Insert your name\n>> ");
        scanf("%s", playerName);

        player.init(playerName, randPick);
        cpu.init("CPU", randPick + 1);

        printf("\033[2J");
        printf(
            "Hello %s\n"
            "Your symbol is '%c'\n",
            player.name,
            player.sym
        );

        switch (turnState)
        {
        case TurnState::PLAYER:
            printf("\n\nPlayer go first\n\n");
            break;
        case TurnState::CPU:
            printf("\n\nCPU go first\n\n");
            break;
        }
        
        while (true) {
            static clock_t time;
            time = clock();

            if (time % 3000 == 0) 
                break;
        }
        

        // Gameplay loop
        bool quit = false;
        while (!quit)
        {
            char *strEmptyCol;

            printf("\033[2J");
            for (int i = 1; i <= gridLength; i++)
            {
                printf("|%c", grid[i - 1]);

                if (grid[i - 1] == ' ') 
                {
                    strcat(strEmptyCol, std::to_string(i).c_str());
                }

                if (i % 3 == 0)
                {
                    printf("|\n");

                    for (int j = 0; j < 7; j++) 
                    {
                        putchar('-');
                    }

                    printf("\n");
                }
            }

            printf("Empty column(s): %s\n\n", strEmptyCol);

            switch (turnState)
            {
            case TurnState::PLAYER:
                printf("Your turn\n>> ");
                scanf("%d", &input);

                if (input > gridLength || input < 1) {
                    printf("Invalid input!\n");
                    continue;
                }

                grid[input - 1] = player.sym;
                turnState = TurnState::CPU;
                break;
            case TurnState::CPU:
                printf("\n\nCPU's turn");
                
                while (true) {
                    static clock_t time;
                    time = clock();

                    if (time % 3000 == 0) 
                        break;
                }


                int symPlace = rand() % gridLength;
                grid[symPlace] = cpu.sym;
                
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