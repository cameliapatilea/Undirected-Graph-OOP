#ifndef GRAF_H
#define GRAF_H

#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include "nod.h"


class GrafNeorientat{
private:

    int nr_noduri;
    int nr_muchii;
    Nod *lista_noduri;
    int **matrice_adiacenta;
    int cauta_nod(int);



public:
    GrafNeorientat()
    {
        nr_noduri = 0;
        nr_muchii = 0;
        lista_noduri = NULL;
        matrice_adiacenta = NULL;
    }

    int get_nr_noduri()
    {
        return nr_noduri;
    }

    Nod *parcurgere_dfs(int);
    Nod *parcurgere_bfs(int);


    friend istream &operator>>(istream &input, GrafNeorientat &G){
        input >>  G.nr_noduri;
        G.lista_noduri = new Nod[G.nr_noduri + 1];
        for(int i = 1; i <= G.nr_noduri; i++)
            input >> G.lista_noduri[i];

        input >> G.nr_muchii;
        G.matrice_adiacenta = new int*[G.nr_noduri + 1];
        for(int i = 0; i <= G.nr_noduri; i++)
            G.matrice_adiacenta[i] = new int[G.nr_noduri + 1];

        int x, y;
        for(int i = 0; i < G.nr_muchii; i++)
        {
            input >> x >> y;
            G.matrice_adiacenta[x][y] = G.matrice_adiacenta[y][x] = 1;
        }
        return input;
    }
    friend ostream &operator<<(ostream &output, const GrafNeorientat &G)
    {
        output << G.nr_noduri <<'\n';
        for(int i = 1; i <= G.nr_noduri; i++)
            output << G.lista_noduri[i] << '\n';
        output << G.nr_muchii << '\n';
        for(int i = 1; i <= G.nr_noduri; i++) {
            for(int j = i; j <= G.nr_noduri; j++)
                if (G.matrice_adiacenta[i][j] == 1)
                    output << i << " "<< j << endl;
        }
        return output;

    }
};

int GrafNeorientat::cauta_nod(int indice) {
    for (int i = 1; i <= nr_noduri; i++)
        if (lista_noduri[i].getIndice() == indice)
            return i;
    return -1;
}
/*Nod* GrafNeorientat::parcurgere_bfs(int s)
{



}*/
Nod* GrafNeorientat::parcurgere_dfs(int s)
{
    int i = 0, nr = 0, j = 0, indice;
    Nod *rezultat = new Nod[nr_noduri + 1];
    int *stiva = new int[nr_noduri + 1];
    bool *viz  = new bool[nr_noduri + 1];
    for(j = 0; j < nr_noduri + 1; j++)
        viz[j] = false;

    stiva[++i] = s;

    while(i > 0)
    {
        s = stiva[i];
        i--;
        if(viz[s] == false)
        {
            viz[s] = true;
            indice = cauta_nod(s);
            rezultat[++nr] = lista_noduri[indice];
        }
        for(j = 1; j <= nr_noduri; j++)
            if(matrice_adiacenta[s][j] == 1 && viz[j] == false)
                stiva[++i] = j;
    }
    return rezultat;
}
#endif