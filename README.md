In this project, we will use the algorithm we learned in the Graph Theory course: Dijkstra's Algorithm.
The main purpose of the algorithm is to find the shortest path on Graf. 

As the way of working:
1. Set the starting point.
2. Determine the cost from the starting point to the other points and mark the low cost point.
3. Repeat the same process among other points that can be reached from the point marked in the second step.

The program uses the matrix during the run. The matrix to be used is as follows.

| N| 1 | 2| 3|  4| 5| 6| 7| 8|
| ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ | 
| 1| 	0| 	40| 	15| 	Inf| 	Inf| 	Inf| 	35| 	Inf| 
| 2| 	40	| 0| 	0| 	100| 	Inf| 	Inf| 	25| 	Inf| 
| 3| 	15	| 0	| 0| 	20| 	10| 	50| 	Inf| 	50| 
| 4| 	Inf	| 100| 	20	| 0| 	10	| Inf| 	45| 	Inf| 
| 5| 	Inf	| Inf| 	10| 	10	| 0	| 30	| 50	| 30| 
| 6| 	Inf	| Inf| 	50| 	Inf	| 30| 	0	| Inf| 	0| 
| 7| 	35	| 25| 	Inf| 	45	| 50| 	Inf	| 0	| 0| 
| 8| 	Inf	| Inf| 	50| 	Inf	| 30| 	0	| 0| 	0| 

Creates a tree while the algorithm is running. Initially, a node is selected and calculation is made according to this node.
Connection status is specified with connected [0] = true. Then values are used with mind[i].
The purpose is to produce results using these matrix values in the algorithm.

Necessary libraries for the program.
```sh
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;
# define NV 9
int main(int argc, char** argv);
int* dijkstra_distance(int ohd[NV][NV]);
void find_nearest(int mind[NV], bool connected[NV], int* d, int* v);
void init(int ohd[NV][NV]);
void update_mind(int mv, bool connected[NV], int ohd[NV][NV], int mind[NV]);
```

The main function of the program.
```sh
int main(int argc, char** argv)
{
    int i;
    int i4_huge = 2147483647;
    int j;
    int* mind;
    int ohd[NV][NV];
    cout << "\n";
    cout << "  Finding the minimum distance between nodes by applying the Dijkstra algorithm on the distance matrix.\n";
    cout << "  Prepared by Emre Can TURAL\n\n";

    /*First of all, we need to initialize the  data matrix to be used.
    The matrix to be used is defined by a two-dimensional array in the "init" function.*/
    init(ohd);

    /*The matrix used is printed on the screen as a table with the following codes.
    The values of the two-dimensional array are used for this output.*/
    cout << "\n";
    cout << "  Distance matrix:\n";
    cout << "\n";
    cout << "        1    2     3     4     5     6      7    8";
    cout << "\n";
    cout << "\n";
    for (i = 1; i < NV; i++)
    {
        cout << "  " << i;
        for (j = 1; j < NV; j++)
        {
            if (ohd[i][j] == i4_huge)
            {
                cout << "   Inf";
            }
            else
            {
                cout << "   " << setw(3) << ohd[i][j];
            }
        }
        cout << "\n";
        cout << "\n";
    }
```

The other part of the screen output is the results. Distances must be calculated for the results. For this purpose, the function "dijkstra_distance" is used.
  ```sh
    mind = dijkstra_distance(ohd);
```
The results obtained by calculations are written on the screen in this section.
```sh
    cout << "\n";
    cout << "  Minimum distances from node 1:\n";
    cout << "\n";
    for (i = 1; i < NV; i++)
    {
        cout << "  " << setw(2) << i
            << "  " << setw(2) << mind[i] << "\n";
    }
    cout << "\n";
    cout << "\n";
    delete[] mind;
    system("pause");
    return 0;
}
```
The "init" function uses the matrix we created.There are values that we will use in this matrix. The function uses the two-dimensional array as "int ohd [NV] [NV]". Makes calculations according to the limit value of 2147483647. The purpose of this is to prevent the overflow of int value.

```sh
void init(int ohd[NV][NV])
{
    int i;
    int i4_huge = 2147483647;
    int j;

    for (i = 1; i < NV; i++)
    {
        for (j = 1; j < NV; j++)
        {
            if (i == j)
            {
                ohd[i][i] = 0;
            }
            else
            {
                ohd[i][j] = i4_huge;
            }
        }
    }
    ohd[1][2] = ohd[2][1] = 40;
    ohd[1][3] = ohd[3][1] = 15;
    ohd[1][7] = ohd[7][1] = 35;
    ohd[2][3] = ohd[3][2] = 0;
    ohd[2][4] = ohd[4][2] = 100;
    ohd[2][7] = ohd[7][2] = 25;
    ohd[3][4] = ohd[4][3] = 20;
    ohd[3][5] = ohd[5][3] = 10;
    ohd[3][6] = ohd[6][3] = 50;
    ohd[3][8] = ohd[8][3] = 50;
    ohd[4][5] = ohd[5][4] = 10;
    ohd[4][7] = ohd[7][4] = 45;
    ohd[5][6] = ohd[6][5] = 30;
    ohd[5][7] = ohd[7][5] = 50;
    ohd[5][8] = ohd[8][5] = 30;
    ohd[6][8] = ohd[8][6] = 0;
    ohd[7][8] = ohd[8][7] = 0;
    return;
}
```
Distances between nodes are calculated with the "dijkstra_distance" function. First node must be specified for the startup process. The process of starting the project depends on this node.

```sh
int* dijkstra_distance(int ohd[NV][NV])
{
    //The creation of nodes begins with this step.
    bool* connected;
    connected = new bool[NV];
    connected[0] = true;

    int i;
    for (i = 1; i < NV; i++)
    {
        connected[i] = false;
    }

    //In the next steps, each node is used step by step.
    int md;
    int* mind;
    int mv;
    mind = new int[NV];
    for (i = 1; i < NV; i++)
    {
        mind[i] = ohd[1][i];
    }
```
Continue with iteration. Add one node to each regeneration of the function used.First, find the nearest unconnection node. Mark this node as connected.After determining the minimum distance to the MV node, see if this reduces the minimum distance to other nodes.

```sh
    int step;
    for (step = 1; step < NV; step++)
    {
        //The "find_nearest" function is used for the nearest node.
        find_nearest(mind, connected, &md, &mv);

        //In this section, the connection is checked.
        if (mv == -1)
        {
            cout << "\n";
            cout << "Warning! Graph not be connected\n";
            break;
        }
        connected[mv] = true;

        //The "update_mind" function is used to update the value.
        update_mind(mv, connected, ohd, mind);
    }
    delete[] connected;
    return mind;
}
```
find_nearest finds the nearest unconnected node.Thus, the value to be marked is determined.
```sh
void find_nearest(int mind[NV], bool connected[NV], int* d, int* v)
{
    int i;
    int i4_huge = 2147483647;

    *d = i4_huge;
    *v = -1;
    for (i = 0; i < NV; i++)
    {
        if (!connected[i] && mind[i] < *d)
        {
            *d = mind[i];
            *v = i;
        }
    }
    return;
}
```
update_mind updates the minimum distance vector. This update is done according to the 2147483647 limit.
We use this value for infinity. Because integer values have a limit.
```sh
void update_mind(int mv, bool connected[NV], int ohd[NV][NV], int mind[NV])

{
    int i;
    const int i4_huge = 2147483647;

    for (i = 1; i < NV; i++)
    {
        if (!connected[i])
        {

            if (ohd[mv][i] < i4_huge)
            {
                if (mind[mv] + ohd[mv][i] < mind[i])
                {
                    mind[i] = mind[mv] + ohd[mv][i];
                }
            }
        }
    }
    return;
}
```
