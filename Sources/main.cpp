#include<iostream>
#include<fstream>
#include "graf.h"
using namespace std;

ifstream f("date.in");

int main()
{
    GrafNeorientat G;
    f >> G;
    Nod *vector_dfs = G.parcurgere_dfs(2);
    Nod *vector_bfs = G.parcurgere_bfs(1);
   // cout << G;
  //  cout << endl << endl;
    int i = 1;
    while(i <= G.get_nr_noduri() && vector_dfs[i].getIndice()!= 0)
    {
       // cout << vector_dfs[i] <<'\n';
        i++;
    }
    i = 1;
   // cout << endl;
    while(i <= G.get_nr_noduri() && vector_bfs[i].getIndice() != 0)
    {
      //  cout <<vector_bfs[i] << '\n';
        i++;
    }
    int** MatriceDrumuri = G.matrice_drumuri();
    for(i = 1; i <= G.get_nr_noduri(); i++)
    {
        for(int j = 1; j <= G.get_nr_noduri(); j++)
            cout << MatriceDrumuri[i][j] << " ";
        cout << endl;
    }

    return 0;
}
