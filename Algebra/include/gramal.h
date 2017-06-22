#ifndef GRAMAL_H
#define GRAMAL_H
#include <string>
#include <NTL/ZZ.h>
#include <vector>
#include "Funciones Matematicas.h"
using namespace NTL;
using namespace std;
class gamal
{
    public:
        void generar_claves(int bits);
        gamal(int bits);
        gamal(ZZ e_1,ZZ e_2,ZZ p_0);
        string cifrar(std::string mensaje);
        string descifrar(string mensaje);
        ZZ raiz_primitiva(ZZ p);
        void set_e1(ZZ e1);
        void set_e2(ZZ e2);
        void set_d(ZZ d);
    private:
        ZZ p,d,e1,e2,r;
        string alfabeto="abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
        int longitud = alfabeto.length();

};

#endif // GRAMAL_H
