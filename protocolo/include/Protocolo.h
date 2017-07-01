#ifndef PROTOCOLO_H
#define PROTOCOLO_H
using namespace std;
#include "GA.h"
#include "Funciones Matematicas.h"
#include <NTL/ZZ.h>
#include <string>
using namespace NTL;
class Protocolo
{
    public:
        Protocolo(int bits);
        Protocolo(ZZ e,ZZ n);
        void generar_claves(int bits);
        string cifrar(std::string mensaje);
        string descifrar(string mensaje);
    private:
        ZZ p1,p2,q,n,e,d,g,a,k;
        string alfabeto="abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
        int longitud = alfabeto.length();
};

#endif // PROTOCOLO_H
