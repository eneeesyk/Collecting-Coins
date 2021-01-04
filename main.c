#include <stdio.h>
#define N 8

int board[N][N] =
        {
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 1},
            {0, 0, 0, 1, 0, 1, 0, 0},
            {0, 0, 1, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 0},
      };

int coins()
{
    int i,j;
    int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j]==1)
                count++;
        }
    }
    return count;
}

int distance(int fromx, int fromy, int tox, int toy)
{
    return (tox - fromx) + (toy - fromy);
}

int find_closest(int *x, int *y)
{
    int i,j;
    int closest_distance = N * 2; /* choose the most far corner and update later */
    int closest_x = N-1;
    int closest_y = N-1;
    int tmp;

    for(i=*x; i<N; i++)
    {
        for(j=*y; j<N; j++)
        {
            if(board[i][j] == 1) /* calculate if coin exist */
            {
                tmp = distance(*x, *y, i, j);
                if(tmp < closest_distance)
                {
                    closest_x = i;
                    closest_y = j;
                    closest_distance = tmp;
                }
            }
        }
    }

    *x = closest_x;
    *y = closest_y;

    return closest_distance;
}

int main() {
    int robot_count = 0;
    int robot_x, robot_y;
    int coin_count = coins();

    while (coin_count > 0)
    {
        robot_count++; /* use a robot */
        robot_x = 0;   /* every robot starts from 0,0 (upper left corner) */
        robot_y = 0;

        printf("Robot#%d starts: [%d,%d]\n", robot_count, robot_x, robot_y);

        while(robot_x < (N-1) || robot_y < (N-1))
        {
            find_closest(&robot_x, &robot_y);
            printf("\tRobot#%d moves: [%d,%d]\n", robot_count, robot_x, robot_y);

            if(board[robot_x][robot_y] == 1)
            {
                printf("\tRobot#%d collected the coin: [%d,%d]\n", robot_count, robot_x, robot_y);
                board[robot_x][robot_y] = 0;
                coin_count--;
            }
        }

        printf("\tRobot#%d finished: [%d,%d]\n", robot_count, robot_x, robot_y);
    }

    printf("Finished using %d robots!\n", robot_count);
    return 0;
}
