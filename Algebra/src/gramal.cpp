#include "gramal.h"
#include "GA.h"
#include <iostream>
#include <stdlib.h>
#include <NTL/ZZ.h>
#include <sstream>
#include "Funciones Matematicas.h"
using namespace NTL;
using namespace std;

gamal::gamal(ZZ e_1,ZZ e_2,ZZ p_0)
{
    e1 = e_1;
    e2 = e_2;
    p = p_0;
}


gamal::gamal(int bits)
{
    generar_claves(bits);
}
ZZ gamal::raiz_primitiva(ZZ p)
{
    ZZ q, g;
    q = (p - 1)/2;
    for(int i = 1; i < p - 1; i++)
    {
        g = p - i;
        if((potencia(g, to_ZZ(2), p) != 1) && (potencia(g, q, p) != 1))
        {
            break;
        }
    }
    return q;
}

void gamal::generar_claves(int bits)
{
    ZZ a,r_0;
    a = ga(11,bits,5,10);
    while(ProbPrime(a,10)!=1){
        a = ga(11,bits,5,10);
    }
    p=a;
    e1 = raiz_primitiva(p);
    d = ga(11,bits,5,10);
    r_0 = ga(11,bits,5,10);
    while(d<1 && d>p-2 && r_0<1 && r_0>p-2){
        d = ga(11,bits,5,10);
        r_0 = ga(11,bits,5,10);
    }
    r=r_0;
    e2 = potencia(e1,d,p);
    cout<<"e1: "<<e1<<endl;
    cout<<"e2: "<<e2<<endl;
    cout<<"p: "<<p<<endl;
}
string numberToString(int numero){
    stringstream ss;
	ss << numero;
	return ss.str();
}
string gamal::cifrar(string mensaje)
{
    string res,lString,mensajeC,c1_string;
    int c1_temp;
    ZZ c1;
    ZZ N,Km;
    N=p;
    c1= potencia(e1,r,p);
    Km = potencia(e2,r,p);
    c1_string =zzToString(c1);
    c1_temp = c1_string.length();
    int lenMaxString = numberToString(longitud).length();
    int lenN = zzToString(N).length();
    int k = lenN-1;

    int numOfZeros;
    int l;
    ZZ numGroups;
    for(int i = 0;i<mensaje.length();i++){
        l = alfabeto.find(mensaje[i]);
        lString = numberToString(l);
        numOfZeros = lenMaxString-lString.length();
        string temp(numOfZeros,'0');
        temp.append(lString);
        res.append(temp);
    }
    string posW = numberToString(alfabeto.find('w'));
    while(moduloo(res.length(),k)!=0){
        res.append(posW);
    }
    numGroups = to_ZZ(res.length()/k);
    long long i;
    int ini = 0;
    int fin = k;
    for(i=0;i<numGroups;i++){
        ZZ numCifrar(INIT_VAL,res.substr(ini,fin).c_str());
        //numCifrar = m.modularExpo(numCifrar,clavePublica,N);
        numCifrar = modulo(numCifrar*Km,p);
        string t = zzToString(numCifrar);
        int diff = (lenN)-t.length();
        string actualString = t;
        if(diff!=0){
            string temp(diff,'0');
            temp.append(t);
            actualString = temp;
        }
        mensajeC+=actualString;
        ini+=k;
    }
    if(c1_temp<lenN){
        int tempo = lenN-c1_temp;
        string temp(tempo,'0');
        temp+=c1_string;
        temp+=mensajeC;
        mensajeC=temp;
            cout<<mensajeC;
    }else{
        c1_string+=mensajeC;
        mensajeC = c1_string;
    }
    return mensajeC;
}


 string gamal::descifrar(string mensaje)
{
    ZZ Km;
    ZZ N;
    N = p;
    int lenP = zzToString(p).length();
    ZZ c1(INIT_VAL,mensaje.substr(0,lenP).c_str());
    Km=potencia(c1,d,p);
    Km=inversa(Km,p);
    string grupo,res,MensajeDes;
    int numMaxofChars = numberToString(longitud).length();
    ZZ nLen,menLen,numGrupos,dp,dq,D,c,numLetras;
    nLen = to_ZZ(zzToString(N).length());
    menLen = to_ZZ(mensaje.length());
    numGrupos = menLen/nLen;
    long long i;
    int inicio = lenP;
    c=0;
    for(i=1;i<numGrupos;i++){
        grupo = mensaje.substr(inicio,to_int(nLen));
        ZZ valGrupo(INIT_VAL,grupo.c_str());
        D=modulo(valGrupo*Km,p);
        if(zzToString(D).length() < to_int(nLen)){
            string temp((to_int(nLen)-zzToString(D).length())-1,'0');
            temp.append(zzToString(D));
            res+=temp;
        }else{
           res+=zzToString(D);
        }

        c++;
        inicio+=to_int(nLen);
    }
    inicio = 0;
    numLetras = to_ZZ(res.length())/to_ZZ(numberToString(longitud).length());
    for(i=0;i<numLetras;i++){
        ZZ temp(INIT_VAL,res.substr(inicio,numMaxofChars).c_str());
        if(alfabeto[to_int(temp)]=='w'){
            break;
        }
        MensajeDes+=alfabeto[to_int(temp)];
        inicio+=numMaxofChars;
    }
    return MensajeDes;
}
void gamal::set_e1(ZZ e1)
{
    this->e1 = e1;
}
void gamal::set_e2(ZZ e2)
{
    this->e2 = e2;
}
void gamal::set_d(ZZ d)
{
    this->d = d;
}
