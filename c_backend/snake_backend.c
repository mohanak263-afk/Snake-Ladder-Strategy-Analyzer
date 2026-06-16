#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define WINNING_POSITION 100
#define SIZE 101

int snakes[] = {17, 52, 57, 62, 88, 95, 97};
int snake_tails[] = {13, 29, 40, 22, 18, 51, 79};

int ladders[] = {3, 8, 28, 58, 75, 80, 90};
int ladder_tops[] = {21, 30, 84, 77, 86, 100, 91};

int board[SIZE];
int parent[SIZE];
int moveFrom[SIZE];
void setupBoard()
{
    for(int i = 0; i < SIZE; i++)
    {
        board[i] = i;
    }

    for(int i = 0; i < 7; i++)
    {
        board[snakes[i]] = snake_tails[i];
    }

    for(int i = 0; i < 7; i++)
    {
        board[ladders[i]] = ladder_tops[i];
    }
}

int minMovesToWin()
{
    int visited[SIZE] = {0};
    int queue[SIZE];
    int distance[SIZE] = {0};

    int front = 0;
    int rear = 0;

    queue[rear++] = 1;
    visited[1] = 1;
    parent[1] = -1;
moveFrom[1] = 1;
    while(front < rear)
    {
        int current = queue[front++];

        if(current == 100)
        {
            return distance[current];
        }

        for(int dice = 1; dice <= 6; dice++)
        {
            int next = current + dice;

            if(next <= 100)
            {
                int finalPos = board[next];
if(!visited[finalPos])
{
    visited[finalPos] = 1;

    parent[finalPos] = current;

    moveFrom[finalPos] = next;

    distance[finalPos] =
        distance[current] + 1;

    queue[rear++] = finalPos;
}           
            }
        }
    }

    return -1;
}
void printShortestPath()
{
    int path[SIZE];

    int count = 0;

    int current = 100;

    while(current != -1)
    {
        path[count++] = current;

        current = parent[current];
    }

    for(int i = count - 1; i > 0; i--)
    {
        int from = path[i];

        int to = path[i - 1];

        int landed = moveFrom[to];

        printf("%d", from);

        if(landed != to)
        {
            int ladder = 0;

            for(int j = 0; j < 7; j++)
            {
                if(ladders[j] == landed &&
                   ladder_tops[j] == to)
                {
                    ladder = 1;
                    break;
                }
            }

            if(ladder)
            {
                printf(
                    " -> %d (Ladder to %d)",
                    landed,
                    to
                );
            }
            else
            {
                printf(
                    " -> %d (Snake to %d)",
                    landed,
                    to
                );
            }
        }
        else
        {
            printf(
                " -> %d",
                to
            );
        }

        if(i != 1)
        {
            printf("\n");
        }
    }
}
int rollDice()
{
    return (rand() % 6) + 1;
}

int main(int argc, char *argv[])
{
    setupBoard();

    

 if(argc == 2 &&
   strcmp(argv[1], "bfs") == 0)
{
    int moves =
    minMovesToWin();

    printf(
        "%d|",
        moves
    );

    printShortestPath();

    printf("\n");

    return 0;
}

    if(argc != 4)
    {
        return 1;
    }

    int player1 = atoi(argv[1]);
    int player2 = atoi(argv[2]);
    int currentPlayer = atoi(argv[3]);

    srand(time(NULL) + player1 + player2);

    int dice = rollDice();
    int winner = 0;
    int nextPlayer;

    char message[500] = "";

    if(currentPlayer == 1)
    {
        int newPos = player1 + dice;

        sprintf(
            message,
            "Player 1 rolled %d",
            dice
        );

        if(newPos <= WINNING_POSITION)
        {
            player1 = newPos;
        }

        for(int i = 0; i < 7; i++)
        {
            if(player1 == ladders[i])
            {
                char temp[120];

                sprintf(
                    temp,
                    " | LANDED ON %d | LADDER! %d -> %d",
                    ladders[i],
                    ladders[i],
                    ladder_tops[i]
                );

                strcat(message, temp);

                player1 = ladder_tops[i];
                break;
            }
        }

        for(int i = 0; i < 7; i++)
        {
            if(player1 == snakes[i])
            {
                char temp[120];

                sprintf(
                    temp,
                    " | LANDED ON %d | SNAKE! %d -> %d",
                    snakes[i],
                    snakes[i],
                    snake_tails[i]
                );

                strcat(message, temp);

                player1 = snake_tails[i];
                break;
            }
        }

        if(player1 == WINNING_POSITION)
        {
            winner = 1;

            strcat(
                message,
                " | PLAYER 1 WINS!"
            );
        }

        if(dice == 6)
        {
            nextPlayer = 1;

            strcat(
                message,
                " | EXTRA TURN!"
            );
        }
        else
        {
            nextPlayer = 2;
        }
    }
    else
    {
        int newPos = player2 + dice;

        sprintf(
            message,
            "Player 2 rolled %d",
            dice
        );

        if(newPos <= WINNING_POSITION)
        {
            player2 = newPos;
        }

        for(int i = 0; i < 7; i++)
        {
            if(player2 == ladders[i])
            {
                char temp[120];

                sprintf(
                    temp,
                    " | LANDED ON %d | LADDER! %d -> %d",
                    ladders[i],
                    ladders[i],
                    ladder_tops[i]
                );

                strcat(message, temp);

                player2 = ladder_tops[i];
                break;
            }
        }

        for(int i = 0; i < 7; i++)
        {
            if(player2 == snakes[i])
            {
                char temp[120];

                sprintf(
                    temp,
                    " | LANDED ON %d | SNAKE! %d -> %d",
                    snakes[i],
                    snakes[i],
                    snake_tails[i]
                );

                strcat(message, temp);

                player2 = snake_tails[i];
                break;
            }
        }

        if(player2 == WINNING_POSITION)
        {
            winner = 2;

            strcat(
                message,
                " | PLAYER 2 WINS!"
            );
        }

        if(dice == 6)
        {
            nextPlayer = 2;

            strcat(
                message,
                " | EXTRA TURN!"
            );
        }
        else
        {
            nextPlayer = 1;
        }
    }

    printf(
        "%d|%d|%d|%d|%d|%d|%s\n",
        player1,
        player2,
        currentPlayer,
        nextPlayer,
        dice,
        winner,
        message
    );

    return 0;
}