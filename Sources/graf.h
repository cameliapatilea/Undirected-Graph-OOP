#ifndef GRAF_H
#define GRAF_H

#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include "nod.h"


class GrafNeorientat{
private:


    int nr_muchii;
    Nod *lista_noduri;
    int **matrice_adiacenta;
    int cauta_nod(int);
    int nr_noduri;
    int nr_noduri2;



public:
    //constructor
    GrafNeorientat()
    {
        nr_noduri = 0;
        nr_muchii = 0;
        lista_noduri = NULL;
        matrice_adiacenta = NULL;

    }
    GrafNeorientat(int nr_noduri)
    {
        nr_noduri2 = nr_noduri;
        nr_muchii = 0;
        lista_noduri = NULL;
        matrice_adiacenta = NULL;
    }
    //destructor
   ~GrafNeorientat()
   {
        delete[] lista_noduri;

       for(int i = 1; i <= nr_noduri2; i++)
           delete[] matrice_adiacenta[i];
       delete[] matrice_adiacenta;
   }

    //constructor copiere
    GrafNeorientat(const GrafNeorientat &Graf)
    {
         nr_noduri = Graf.nr_noduri ;
         nr_muchii = Graf.nr_muchii;
         lista_noduri = new Nod[Graf.nr_noduri + 1];
         for(int i = 1; i <= Graf.nr_noduri; i++)
             lista_noduri[i] = Graf.lista_noduri[i];

         matrice_adiacenta = new int*[Graf.nr_noduri + 1];
         for(int i = 1; i <= Graf.nr_noduri; i++)
             matrice_adiacenta[i] = new int[Graf.nr_noduri + 1];

         for(int i = 1; i <= Graf.nr_noduri; i++)
             for(int j = 1; j <= Graf.nr_noduri; j++)
                 matrice_adiacenta[i] = Graf.matrice_adiacenta[i];
    }

    int get_nr_noduri()
    {
        return nr_noduri;
    }

    Nod *parcurgere_dfs(int);
    Nod *parcurgere_bfs(int);
    int **matrice_drumuri();
    Nod **componente_conexe();
    ostream& componente_conexe(ostream&);
    bool graf_conex();


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
  GrafNeorientat operator=(GrafNeorientat graf);
  friend  GrafNeorientat operator+(const GrafNeorientat& G1, const GrafNeorientat& G2)
    {
       GrafNeorientat G3 ;
        G3.nr_noduri = G1.nr_noduri;
        G3.nr_muchii = 0;

        G3.lista_noduri = new Nod[G1.nr_noduri + 1];
        for(int i = 1; i <= G1.nr_noduri; i++)
        G3.lista_noduri[i] = G1.lista_noduri[i];

        G3.matrice_adiacenta = new int*[G1.nr_noduri ];
        for(int i = 1; i <= G1.nr_noduri ; i++)
            G3.matrice_adiacenta[i] = new int[G1.nr_noduri ];
        for(int i = 1; i <= G3.nr_noduri; i++)
            for(int j = 1; j <= G3.nr_noduri; j++)
                G3.matrice_adiacenta[i][j] = 0;

        for(int i = 1; i <= G3.nr_noduri; i++)
            for(int j = i+1; j <= G3.nr_noduri; j++)
                if((G1.matrice_adiacenta[i][j] == 1  || G2.matrice_adiacenta[i][j] == 1) )
                {
                    G3.matrice_adiacenta[i][j] = G3.matrice_adiacenta[j][i] = 1;
                    G3.nr_muchii++;
                }

         return G3;

    }
};
GrafNeorientat GrafNeorientat::operator=(GrafNeorientat graf)
{
    nr_noduri = graf.nr_noduri;
    nr_muchii = graf.nr_muchii;
    lista_noduri = new Nod[graf.nr_noduri + 1];
    for(int i = 1; i <= graf.nr_noduri; i++)
        lista_noduri[i] = graf.lista_noduri[i];

    matrice_adiacenta = new int*[graf.nr_noduri + 1];
    for(int i = 1; i <= graf.nr_noduri; i++)
        matrice_adiacenta[i] = new int[graf.nr_noduri + 1];

    for(int i = 1; i <= graf.nr_noduri; i++)
        for(int j = 1; j <= graf.nr_noduri; j++)
            matrice_adiacenta[i] = graf.matrice_adiacenta[i];
     return *this;
}
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

    //parcurg toate nodurile si calculez toate drumurile, de la fiecare nod la toate celelalte
    for(k = 1; k <= nr_noduri; k++)
    {
        // daca dam peste un nod nevizitat
        if(viz[k] == 0)
        {
            //maresc nr de componente conexe
            contor_comp_conexe++;
            s = k;
            //in vectorul viz voi pune nr componentei conexe
            viz[s] = contor_comp_conexe;

            //initializez primul element al cozii cu nodul pe care ma aflu
            coada[0] = s;
            prim = ultim = 0;

            //cat timp coada nu e vida
            while(prim <= ultim)
            {
                //extragem un element din coada
                s = coada[prim++];

                for(i = 1; i <= nr_noduri ; i++)
                    //daca nodul i nu a mai fost vizitat si exista drum de la i la s
                    if(matrice_adiacenta[s][i] == 1 && viz[i] == 0 )
                    {
                        //marchez in matricea de drumuri
                        MatriceDrumuri[i][s] = MatriceDrumuri[s][i] = 1;
                        viz[i] = contor_comp_conexe;
                        //inserez in coada nodul i
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
Nod** GrafNeorientat::componente_conexe() {
    int comp = 0;
    int i, prim, ultim,  j = 0, s = 1, k;

    int *coada = new int[nr_noduri + 1];
    int *viz  = new int[nr_noduri + 1];
    Nod **rezultat = new Nod*[nr_noduri + 1];
    rezultat[0] = new Nod[nr_noduri + 1];

    for(j = 0; j < nr_noduri + 1; j++)
        viz[j] = 0;

    for(k = 1; k <= nr_noduri; k++) {
        // daca dam peste un nod nevizitat
        if (viz[k] == 0) {
            //maresc nr de componente conexe
            comp++;
            s = k;
            //in vectorul viz voi pune nr componentei conexe
            viz[s] = comp;
            prim = ultim = 1;
            coada[ultim] = s;

            while (prim <= ultim) {
                for (i = 1; i <= nr_noduri; i++) {
                    if (matrice_adiacenta[coada[prim]][i] == 1 && viz[i] == 0)
                    {
                        viz[i] = 1;
                        coada[++ultim] = i;
                    }
                }
                prim++;
            }
            rezultat[comp] = new Nod[ultim + 1];
            //retin pe linia 0 dimensiunea pentru fiecare linie in parte, care contine nodurile fiecarei componente conexe in parte
            rezultat[0][comp] = Nod(ultim, ultim);
            for(j = 1; j <= ultim; j++)
                rezultat[comp][j] = lista_noduri[cauta_nod(coada[j])];

        }

    }
    rezultat[0][0] = Nod(comp, comp);
    return rezultat;
}

ostream& GrafNeorientat::componente_conexe(ostream& output) {
    int comp = 0;
    int i, prim, ultim,  j = 0, s = 1, k;

    int *coada = new int[nr_noduri + 1];
    int *viz  = new int[nr_noduri + 1];
    Nod **rezultat = new Nod*[nr_noduri + 1];
    rezultat[0] = new Nod[nr_noduri + 1];

    for(j = 0; j < nr_noduri + 1; j++)
        viz[j] = 0;

    for(k = 1; k <= nr_noduri; k++) {
        // daca dam peste un nod nevizitat
        if (viz[k] == 0) {
            //maresc nr de componente conexe
            comp++;
            s = k;
            //in vectorul viz voi pune nr componentei conexe
            viz[s] = comp;
            prim = ultim = 1;
            coada[ultim] = s;

            while (prim <= ultim) {
                for (i = 1; i <= nr_noduri; i++) {
                    if (matrice_adiacenta[coada[prim]][i] == 1 && viz[i] == 0)
                    {
                        viz[i] = 1;
                        coada[++ultim] = i;
                    }
                }
                prim++;
            }
            rezultat[comp] = new Nod[ultim + 1];
            //retin pe linia 0 dimensiunea pentru fiecare linie in parte, care contine nodurile fiecarei componente conexe in parte
            rezultat[0][comp] = Nod(ultim, ultim);
            for(j = 1; j <= ultim; j++)
                rezultat[comp][j] = lista_noduri[cauta_nod(coada[j])];

        }

    }
    rezultat[0][0] = Nod(comp, comp);
    output << "Graful are " << rezultat[0][0].getIndice() << " componente conexe \n";
    for(i = 1; i <= rezultat[0][0].getIndice(); i++)
    {
        output << "Componenta conexa nr " << i << ":"<<'\n';
        for(int j = 1; j <= rezultat[0][i].getIndice(); j++)
            output << rezultat[i][j].getInformatie() << " ";
        output<< '\n';
    }
    return output;
}

bool GrafNeorientat::graf_conex() {
    int i = 0, nr = 0, j = 0, indice;
    int s = 1;

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

        }
        for(j = 1; j <= nr_noduri; j++)
            if(matrice_adiacenta[s][j] == 1 && viz[j] == false)
                stiva[++i] = j;
    }

    for(i = 1; i <= nr_noduri; i++)
        if(viz[i] == false)
            return false;
     return true;
}
#endif