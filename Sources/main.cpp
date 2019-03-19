#include<iostream>
#include<fstream>
#include "graf.h"
using namespace std;

ifstream f("date.in");

int main()
{
    GrafNeorientat G;
    //f >> G;
    //Nod *vector_dfs = G.parcurgere_dfs(2);
    //Nod *vector_bfs = G.parcurgere_bfs(1);
   // cout << G;
  //  cout << endl << endl;
 //   int i = 1;
    //parcurgere in adancime
   // while(i <= G.get_nr_noduri() && vector_dfs[i].getIndice()!= 0)
  //  {
       // cout << vector_dfs[i] <<'\n';
    //    i++;
   // }
  //  i = 1;
   // cout << endl;
   //parcurgere in latime
  //  while(i <= G.get_nr_noduri() && vector_bfs[i].getIndice() != 0)
   // {
      //  cout <<vector_bfs[i] << '\n';
   //     i++;
   // }
   // int** MatriceDrumuri = G.matrice_drumuri();
  /*  for(i = 1; i <= G.get_nr_noduri(); i++)
    {
        for(int j = 1; j <= G.get_nr_noduri(); j++)
            cout << MatriceDrumuri[i][j] << " ";
       cout << endl;
    }*/
 // Nod** rezultat = G.componente_conexe();
   /* cout << "Graful are " << rezultat[0][0].getIndice() << " componente conexe \n";
  for(i = 1; i <= rezultat[0][0].getIndice(); i++)
  {
      cout << "Componenta conexa nr " << i << ":"<<'\n';
      for(int j = 1; j <= rezultat[0][i].getIndice(); j++)
          cout << rezultat[i][j].getInformatie() << " ";
      cout << '\n';
  }*/
   // G.componente_conexe(cout);

   //bool ok = G.graf_conex();
    //if(ok == true)
   //     cout << "Graful este conex \n";
   // else cout << "Graful nu este conex \n";

   GrafNeorientat G1;
   GrafNeorientat G2;
   GrafNeorientat G3;
   f >> G1 >> G2;
   G3 = G1 + G2;
   cout << G3;
  int n;
  //citire, memorare si afisare a n obiecte
  /*f >> n;
  GrafNeorientat* vector_obiecte = new GrafNeorientat[n + 1];
  for(int i = 1; i <= n; i++)
  {
      f >> vector_obiecte[i];
      cout << vector_obiecte[i] << endl;
  }
*/
    return 0;
}
