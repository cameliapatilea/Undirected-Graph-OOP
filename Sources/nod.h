#ifndef NOD_H
#define NOD_H

#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>

using namespace std;

class Nod{
private:
    int indice;
    int informatie;
public:
    Nod()
    {
        indice = NULL;
        informatie = NULL;
    }
    Nod(int indice, int informatie)
    {
        this->indice = indice;
        this->informatie = informatie;
    }
    void setIndice(int);
    void setInformatie(int);

    int getIndice();
    int getInformatie();

    friend istream &operator>>(istream &input, Nod &N){
      input >> N.indice >> N.informatie;
        return input;
    }
    friend ostream &operator<<(ostream &output, const Nod &N)
    {
       output << N.indice <<" "<< N.informatie ;
        return output;

    }
};

void Nod::setIndice(int n)
{
    indice = n;
}
void Nod::setInformatie(int n)
{
    informatie = n;
}
int Nod::getIndice() {
    return indice;
}
int Nod::getInformatie() {
    return informatie;
}

#endif
