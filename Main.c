#include "stdio.h"
#define N 8
typedef struct
{
    int x;
    int y;
    int distance; // steps covered
} Node;

int row[] = {-2, -1, 1, 2, -2, -1, 1, 2};
int col[] = {-1, -2, -2, -1, 1, 2, 2, 1};

int visit[N + 1][N + 1] = {{0}};

Node q[1000]; // array of structure is used to simulate the Queue

int front = -1;
int rear = -1;
int top = -1;

int mapCoordsToIndex(int x, int y)
{
    return 8 * y + x;
}

int isValid(int x, int y) // check whether we are inside the board
{
    if ((x >= 1 && x <= N) && (y >= 1 && y <= N))
        return 1;
    return 0;
}

void enqueue(int x, int y, int distance)
{
    if (front == -1)
        front = 0;
    rear++;
    q[rear].x = x;
    q[rear].y = y;
    q[rear].distance = distance;
}

void dequeue()
{
    if (front == rear)
        rear = front = -1;
    else
        front++;
}
 
int qisempty() // Check Q is empty
{
    if (rear == -1 && front == -1)
        return 1;
    return 0;
}

void push(int index, int *stack) 
{
    top++;
    stack[top] = index;
}

void pop() 
{
    top--;
}

int getX(int index)
{
    return (index % 8) + 1;
}

int getY(int index) 
{
    return (index / 8) + 1;
}

void bfs(int sx, int sy, int dx, int dy)
{
    Node t;
    int x, y;
    enqueue(sx, sy, 0);

    visit[sx][sy] = 1;
    int map[64] = {0};

    while (!qisempty())
    {
        t = q[front];
        dequeue();
        if (t.x == dx && t.y == dy)
        {
            printf("Total Moves Needed to be taken : %d\n", t.distance);
            int stack[1000];
            push(mapCoordsToIndex(t.x-1,t.y-1), stack);

            if (t.distance != 0)
            { // when src and destinations are  the same
                for (int i = mapCoordsToIndex(t.x - 1, t.y - 1); ; i = mapCoordsToIndex(t.x - 1, t.y - 1))
                {
                    if (!(getX(map[i]) == sx && getY(map[i]) == sy))
                    {
                        t.x = getX(map[i]);
                        t.y = getY(map[i]);
                        push(mapCoordsToIndex(t.x - 1, t.y - 1), stack);
                    }
                    else
                        break;
                }
            }
            printf("path : (%d, %d)", sx, sy);
            for (; top != -1; pop())
                printf(" -> (%d,%d)", getX(stack[top]), getY(stack[top]));
            printf("\n\n");
            return;
        }

        for (int i = 0; i < 8; i++)
        {
            x = t.x + row[i];
            y = t.y + col[i];
            if (isValid(x, y) && !visit[x][y])
            {
                visit[x][y] = 1;
                enqueue(x, y, t.distance + 1);
                map[mapCoordsToIndex(x - 1, y - 1)] = mapCoordsToIndex(t.x - 1, t.y - 1);
            }
        }
    }
}

int main()
{
    int dx, dy;
    int sx, sy;
    printf("\nEnter  the   source   Coordinates (x,y), where x & y are numbers between 1 & 8: ");
    scanf("%d%d", &sx, &sy);
    printf("\nEnter the destination Coordinates (x,y), where x & y are numbers between 1 & 8: ");
    scanf("%d%d", &dx, &dy);
    printf("\n");
    if (isValid(sx, sy) && isValid(dx, dy))
        bfs(sx, sy, dx, dy);
    else
        printf("wrong input!\n");
    return 0;
}
