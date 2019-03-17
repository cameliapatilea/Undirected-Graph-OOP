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
    int **matrice_drumuri();


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
Nod* GrafNeorientat::parcurgere_bfs(int s)
{
    int i, prim, ultim, nr = 0, j = 0, indice;

    Nod *rezultat = new Nod[nr_noduri + 1];
    int *coada = new int[nr_noduri + 1];
    bool *viz  = new bool[nr_noduri + 1];
    for(j = 0; j < nr_noduri + 1; j++)
        viz[j] = false;

    viz[s] = true;
    indice = cauta_nod(s);
    rezultat[++nr] = lista_noduri[indice];
    //initializez coada cu nodul de start
    coada[0] = s;
    prim = ultim = 0;
    //cat timp coada nu e vida
    while(prim <= ultim)
    {
        //extragem un element din coada
        s = coada[prim++];

        for(i = 1; i <= nr_noduri ; i++)
            //daca nodul i nu a mai fost vizitat
            if(viz[i] == false && matrice_adiacenta[s][i] == 1)
            {
                viz[i] = true;
                indice = cauta_nod(i);
                rezultat[++nr] = lista_noduri[indice];
                coada[++ultim] = i;
            }
    }
    return rezultat;

}
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
int** GrafNeorientat::matrice_drumuri()
{
    int i, prim, ultim,  j = 0, s = 1, k, contor_comp_conexe = 0, p = 0;

    int *coada = new int[nr_noduri + 1];
    int *viz  = new int[nr_noduri + 1];
    for(j = 0; j < nr_noduri + 1; j++)
        viz[j] = 0;
    int** MatriceDrumuri = new int*[nr_noduri + 1];
    for(i = 0 ; i <=nr_noduri; i++)
        MatriceDrumuri[i] = new int[nr_noduri + 1];
    for(i = 0; i <= nr_noduri; i++)
        for(j = 0; j <= nr_noduri; j++)
            MatriceDrumuri[i][j] = 0;

    for(k = 1; k <= nr_noduri; k++)
    {
        if(viz[k] == 0)
        {
            contor_comp_conexe++;
            s = k;
            viz[s] = contor_comp_conexe;

            coada[0] = s;
            prim = ultim = 0;

            //cat timp coada nu e vida
            while(prim <= ultim)
            {
                //extragem un element din coada
                s = coada[prim++];

                for(i = 1; i <= nr_noduri ; i++)
                    //daca nodul i nu a mai fost vizitat
                    if(matrice_adiacenta[s][i] == 1 && viz[i] == 0 )
                    {
                        MatriceDrumuri[i][s] = MatriceDrumuri[s][i] = 1;
                        viz[i] = contor_comp_conexe;
                        coada[++ultim] = i;

                    }

            }
            for(j = 0; j <= ultim - 1 ; j++)
                for(p = j + 1; p <= ultim ; p++)
                    MatriceDrumuri[coada[j]][coada[p]] = MatriceDrumuri[coada[p]][coada[j]] = 1;

        }

    }


    return MatriceDrumuri;
}
#endif