#include<iostream>
#include<fstream>
#include "graf.h"
using namespace std;

ifstream f("date.in");

int main()
{
    GrafNeorientat G;
    cin >> G;
    Nod *vector_dfs = G.parcurgere_dfs(2);
    cout << G;
    cout << endl << endl;
    int i = 1;
    while(i <= G.get_nr_noduri() && vector_dfs[i].getIndice()!= 0)
    {
        cout << vector_dfs[i] <<'\n';
        i++;
    }
return 0;
}
