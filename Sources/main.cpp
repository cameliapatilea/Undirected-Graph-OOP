#include<iostream>
#include<fstream>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include "graf.h"
using namespace std;

ifstream f("input.in");
void parcurgere_dfs()
{
    GrafNeorientat G;
    cin >> G;
    cout << "Parcurgere dfs: \n";
    Nod *vector_dfs = G.parcurgere_dfs(2);
    int i = 1;
    while(i <= G.get_nr_noduri() && vector_dfs[i].getIndice()!= 0)
    {
        cout << vector_dfs[i] <<'\n';
        i++;
    }
}
void parcurgere_bfs()
{
    GrafNeorientat G;
    cin >> G;
    cout << "Parcurgere bfs: \n";
    Nod *vector_bfs = G.parcurgere_bfs(1);
    int i = 1;
    while(i <= G.get_nr_noduri() && vector_bfs[i].getIndice() != 0)
    {
        cout <<vector_bfs[i] << '\n';
        i++;
    }
}
void matricea_drumurilor()
{
    GrafNeorientat G;
    int i;
    cin >> G;
    cout << "Matricea drumurilor grafului G este: \n";
    int** MatriceDrumuri = G.matrice_drumuri();
    for(i = 1; i <= G.get_nr_noduri(); i++) {
        for (int j = 1; j <= G.get_nr_noduri(); j++)
            cout << MatriceDrumuri[i][j] << " ";
        cout << endl;
    }
}
void componente_conexe()
{
    GrafNeorientat G;
    int i;
    cin >> G;
    Nod** rezultat = G.componente_conexe();
     cout << "Graful are " << rezultat[0][0].getIndice() << " componente conexe \n";
   for(i = 1; i <= rezultat[0][0].getIndice(); i++)
   {
       cout << "Componenta conexa nr " << i << ":"<<'\n';
       for(int j = 1; j <= rezultat[0][i].getIndice(); j++)
           cout << rezultat[i][j].getInformatie() << " ";
       cout << '\n';
   }
    // G.componente_conexe(cout);
}
void graf_conex()
{
    GrafNeorientat G;
    cin >> G;
    bool ok = G.graf_conex();
    if(ok == true)
        cout << "Graful G este conex \n";
    else cout << "Graful G nu este conex \n";
}
void adunare_grafuri()
{
    GrafNeorientat G1;
    GrafNeorientat G2;

    cin >> G1 ;
    cin >> G2;
    cout << G1 + G2 << endl;
}
void sortare_vector_obiecte()
{
    int n;
    cin >> n;
    /* GrafNeorientat* vector_obiecte = new GrafNeorientat[n + 1];
     for(int i = 1; i <= n; i++)
    {
        cin >> vector_obiecte[i];
        cout << vector_obiecte[i] << endl;
     }
    if( G1 < G2)
        cout <<"da";
    else cout << "nu";*/
    GrafNeorientat G1;
    GrafNeorientat *vector_obiecte = new GrafNeorientat[n + 1];
    GrafNeorientat auxiliar;
    for (int i = 1; i <= n; i++) {
        cin >> vector_obiecte[i];
        // cout << vector_obiecte[i] << endl;
    }

    /*for(int i = 1; i < n; i++)
        for(int j = i +1; j <= n; j++)
            if(vector_obiecte[i] > vector_obiecte[j])
            {
                auxiliar = vector_obiecte[i];
                vector_obiecte[i] = vector_obiecte[j];
                vector_obiecte[j] = auxiliar;
            }
    */
    sort(vector_obiecte + 1, vector_obiecte + n + 1);
    cout << "Sortare a n obiecte de tip GrafNeorientat \n";
    for (int i = 1; i <= n; i++)
        cout << vector_obiecte[i] << endl;
}
int main()
{
    int x;
    cin >> x;
    switch(x)
    {
        case 1:
            parcurgere_dfs();
            break;
        case 2:
            parcurgere_bfs();
            break;
        case 3:
            matricea_drumurilor();
            break;
        case 4:
            componente_conexe();
            break;
        case 5:
            graf_conex();
            break;
        case 6:
            adunare_grafuri();
            break;
        case 7:
            sortare_vector_obiecte();
            break;
        default :
            cout  << "Numarul introdus nu este o comanda valida";

    }
    return 0;

}
