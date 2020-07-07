
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


    init(ohd);

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

 
    mind = dijkstra_distance(ohd);

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

int* dijkstra_distance(int ohd[NV][NV])
{
    bool* connected;
    connected = new bool[NV];
    connected[0] = true;

    int i;
    for (i = 1; i < NV; i++)
    {
        connected[i] = false;
    }

    int md;
    int* mind;
    int mv;
    mind = new int[NV];
    for (i = 1; i < NV; i++)
    {
        mind[i] = ohd[1][i];
    }


    int step;
    for (step = 1; step < NV; step++)
    {
        find_nearest(mind, connected, &md, &mv);

        if (mv == -1)
        {
            cout << "\n";
            cout << "Warning! Graph not be connected\n";
            break;
        }
        connected[mv] = true;

        update_mind(mv, connected, ohd, mind);
    }
    delete[] connected;
    return mind;
}


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
