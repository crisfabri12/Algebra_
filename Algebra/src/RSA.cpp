#include "RSA.h"
#include "GA.h"
#include <iostream>
#include <stdlib.h>
#include <NTL/ZZ.h>
#include <sstream>
#include "Funciones Matematicas.h"
using namespace NTL;
using namespace std;


void RSA::generar_claves(int bits)
{
    ZZ p = ga(bits/2,bits,sqrt(bits),11);
    ZZ q = ga(bits/2,bits,sqrt(bits),11);
    while(ProbPrime(p,10)!=1)
    {
        p = ga(bits/2,bits,sqrt(bits),11);
    }
    while(ProbPrime(q,10)!=1)
    {
        q = ga(bits/2,bits,sqrt(bits),1);
    }
    N = p * q;
    this->p = p;
    this->q = q;
    this->N = N;
    ZZ phi_N =(p-1)*(q-1);
    ZZ e = ga(bits/2,bits,sqrt(bits),11);
    while(e > phi_N || euclides(e, phi_N) != 1)
    {
        e = ga(bits/2,bits,sqrt(bits),11);
    }
    cout <<"Clave publica: " << e << endl;
    this->e = e;
    this->d = inversa(e, phi_N);
    cout << "Clave privada: " << d << endl;
    cout <<"N: " << N << endl;
}
RSA::RSA(ZZ e, ZZ n) //EMISOR
{
    e = e;
    N = n;
    alfabeto = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 *#";
}
RSA::RSA(int bits) //RECEPTOR
{
    generar_claves(bits);
    alfabeto = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 *#";
}
ZZ RSA::get_N()
{
    return N;
}
ZZ RSA::get_clave_publica()
{
    return e;
}
string RSA::cifrar(string mensaje,string firma)
{
    string mensaje_cifrado;
    string digito;
    string temp;
    string aux;
    int pos;
    ZZ aux_2;
    for(int i = 0;i<mensaje.size();i++)
    {
        pos = alfabeto.find(mensaje[i]);
        if(pos<10)
            digito+="0";
        digito+= zzToString(to_ZZ(pos));
    }
    ZZ tam = to_ZZ(digito.size());
    ZZ part = to_ZZ((zzToString(N).size())-1);
    while(modulo(tam,part)!=0){
        pos = alfabeto.find("*");
        digito+= zzToString(to_ZZ(pos));
        tam = to_ZZ(digito.size());
    }
    for(int i=0;i<digito.size();i+=to_int(part))
    {
        int j=0;
        while(j<to_int(part))
        {
            aux+=digito[i+j];
            ++j;
        }
        aux_2 = stringTozz(aux);
        aux_2 = potenciaMod(aux_2,e,N);
        aux = zzToString(aux_2);
        int a = aux.size();
        while(to_ZZ(a)<part+1)
        {
            a++;
            temp+="0";

        }
        temp+= aux;
        mensaje_cifrado+=temp;
        aux = "";
        temp = "";
     }
     string firmazz = "";
      firmazz+=zzToString(to_ZZ(alfabeto.find("#")));
      cout<<"........"<<firmazz<<endl;
     for(int i=0;i<firma.size();i++)
     {
         ZZ temp;
         temp = to_ZZ(alfabeto.find(firma[i]));
         temp = potencia(temp,d,N);
         string letra;
         if(modulo(temp,part)!= 1)
         {
             letra += "0";
         }
         letra += zzToString(temp);
         firmazz += letra;
     }
     cout<<firmazz<<endl;;
     part = zzToString(n2).size()-1;
    for(int i=0;i<firmazz.size();i+=to_int(part))
    {
        int j=0;
        while(j<to_int(part))
        {
            aux+=firmazz[i+j];
            ++j;
        }
        aux_2 = stringTozz(aux);
        aux_2 = potencia(aux_2,e2,n2);
        aux = zzToString(aux_2);
        int a = aux.size();
        while(a < zzToString(n2).size())
        {
            a++;
            temp+="0";

        }
        temp+= aux;
        cout<<temp<<endl;
        mensaje_cifrado+=temp;
        aux = "";
        temp = "";
     }
     cout<<temp<<endl;;
    return mensaje_cifrado;
}


 string RSA::descifrar(string cifrado)
{
    string original;
    ZZ aux_2;
    string aux;
    string digitos;
    int pos = 0;
    ZZ part = to_ZZ((zzToString(N).size()));
    for(int i=0;i<cifrado.size();i+=to_int(part))
    {
        int j=0;
        while(j<to_int(part))
        {
            aux+=cifrado[i+j];
            ++j;
        }

        aux_2 = stringTozz(aux);
        aux_2 = resto_chino(aux_2);
        aux = zzToString(aux_2);
        int a = aux.size();
        while(to_ZZ(a)<part-1)
        {
            a++;
            digitos+="0";

        }
        digitos+= aux;
        aux = "";
     }
    aux= "";
    for(int i = 0;i<digitos.size();i+=2)
    {
        int j=0;
        while(j<2)
        {
            aux+=digitos[i+j];
            ++j;
        }
        aux_2 = stringTozz(aux);
        pos = to_int(aux_2);
        cout<<alfabeto[pos]<<aux_2<<endl;
        if(alfabeto[pos]=='#')
        {
            i = digitos.size();
            break;
        }
        original+= alfabeto[pos];
        aux = "";

    }
//    aux = "";
//    part = zzToString(n2).size()-1;
//    int part_2 = zzToString(N).size()-1;
//    string firma2 = "";
//    cout<<original.size()-part_2<<endl;
//    for(int i =original.size()-part_2;i<original.size();i+=to_int(part))
//    {
//
//        int j=0;
//        while(j<part)
//        {
//            aux += cifrado[i+j];
//            ++j;
//        }
//        aux_2 = stringTozz(aux);
//        aux_2 = potencia(aux_2,d2,n2);
//        if(zzToString(aux_2).length() < part - 1)
//        {
//            for(int i = 0; i < part - zzToString(aux_2).length() - 1; i++)
//            {
//                firma2 += "0";
//            }
//        firma2 += zzToString(aux_2);
//        }
//        else
//            firma2 += zzToString(aux_2);
//        aux = "";
//        aux_2 = 0;
//    }
//    cout<<firma2<<endl;
//
//
//    part = zzToString(n2).size()-1;
//    aux_2 = 0;
//    aux = "";
//    for(int i =0;i<firma2.size();i+=2)
//    {
//        int j=0;
//        while(j<2)
//        {
//            aux += cifrado[i+j];
//            ++j;
//        }
//
//        aux_2 = stringTozz(aux);
//        pos = to_int(aux_2);
//        cout<<pos<<endl;
//        original+= alfabeto[pos];
//        cout<<alfabeto[pos]<<endl;
//        aux = "";
//    }

    return original;
}
void RSA::set_clavepublica(ZZ x)
{
    this->e = x;
}
void RSA::set_claveprivada(ZZ x){
    this->d = x;
}
void RSA::set_N(ZZ x){
    this->N = x;
}

ZZ RSA::resto_chino(ZZ c){
    ZZ x;
    ZZ d_1 = modulo(this->d,this->p -1);
    ZZ d_2 = modulo(this->d,this->q -1);
    ZZ a_1 = potenciaMod(c,d_1,p);
    ZZ a_2 = potenciaMod(c,d_2,q);
    ZZ q_1 = inversa(q,p);
    ZZ q_2 = inversa(p,q);
    x = modulo(a_1 * q * q_1,this->N);
    x+= modulo(a_2 * p * q_2,this->N);
    return modulo(x,this->N);
}

void RSA::set_e2(ZZ x)
{
    this->e2 = x;
}
void RSA::set_n2(ZZ x){
    this->n2 = x;
}
void RSA::set_d2(ZZ x){
    this->d2 = x;
}
