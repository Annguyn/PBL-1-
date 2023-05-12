#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50

int graph[MAX_SIZE][MAX_SIZE];
int colors[MAX_SIZE];
int degrees[MAX_SIZE];
int vertices[MAX_SIZE];
int n;

void readGraph();
void printGraph();
void calculateDegrees();
void sortVertices();
int chooseColor(int vertex);
void colorGraph();
void printColors();

int main()
{
    readGraph();
    printf("Graph:\n");
    printGraph();
    calculateDegrees();
    sortVertices();
    colorGraph();
    printColors();

    return 0;
}

void readGraph()
{
    int i, j, v1, v2, numEdges;
    FILE *fp;
    fp = fopen("g.txt", "rt");
    if (fp == NULL)
    {
        printf("File does not exist!\n");
        exit(0);
    }
    else
    {
        fscanf(fp, "%d %d", &n, &numEdges);
        for (i = 0; i < numEdges; i++)
        {
            fscanf(fp, "%d %d", &v1, &v2);
            graph[v1-1][v2-1] = 1;
            graph[v2-1][v1-1] = 1;
        }
    }
    fclose(fp);
}

void printGraph()
{
    int i, j;
    char vertex = 'A';
    printf("Number of vertices: %d\n\n", n);
    printf("  ");
    for (i = 0; i < n; i++)
    {
        printf("%c ", vertex++);
    }
    printf("\n");
    vertex = 'A';
    for (i = 0; i < n; i++)
    {
        printf("%c ", vertex++);
        for (j = 0; j < n; j++)
            printf("%d ", graph[i][j]);
        printf("\n");
    }
}

void calculateDegrees()
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        degrees[i] = 0;
        for (j = 0; j < n; j++)
            degrees[i] += graph[i][j];
        vertices[i] = i;
    }
}

void sortVertices()
{
    int i, j, temp1, temp2;
    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
            if (degrees[i] < degrees[j])
            {
                temp1 = degrees[i];
                degrees[i] = degrees[j];
                degrees[j] = temp1;
                temp2 = vertices[i];
                vertices[i] = vertices[j];
                vertices[j] = temp2;
            }
}

int chooseColor(int vertex)
{
    int i, j, color;
    int used[MAX_SIZE] = {0};
    for (i = 0; i < n; i++)
    {
        if (graph[vertex][i] && colors[i])
            used[colors[i] - 1] = 1;
    }
    for (i = 0; i < n; i++)
    {
        if (!used[i])
        {
            color = i + 1;
            break;
        }
    }
    return color;
}

void colorGraph()
{
    int i, j;
    int numColors = 0;
    for (i = 0; i < n; i++)
    {
        int vertex = vertices[i];
        colors[vertex] = chooseColor(vertex);
        if (colors[vertex] > numColors)
            numColors = colors[vertex];
    }
    printf("Number of colors used: %d\n", numColors);
}

void printColors()
{
    int i;
    char vertexNames[MAX_SIZE] = {'A', 'B', 'C', 'D', 'E'};
    printf("Colors:\n");
    for (i = 0; i < n; i++)
    {
        printf("Vertex %c has color ", vertexNames[i]);
        switch (colors[i])
        {
        case 1:
            printf("red\n");
            break;
        case 2:
            printf("green\n");
            break;
        case 3:
            printf("blue\n");
            break;
        case 4:
            printf("yellow\n");
            break;
        case 5:
            printf("pink\n");
            break;
        case 6:
            printf("violet\n");
            break;
        case 7:
            printf("orange\n");
            break;
        case 8:
            printf("black\n");
            break;
        default:
            printf("unknown\n");
            break;
        }
    }
}