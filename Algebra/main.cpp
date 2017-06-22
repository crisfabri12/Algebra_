#include <iostream>
#include <NTL/ZZ.h>
#include <string>
#include <Cesar.h>
#include <Afin.h>
#include "RSA.h"
#include <fstream>
#include "GA.h"
#include "gramal.h"
#include <time.h>
#include "Funciones Matematicas.h"
using namespace std;
using namespace NTL;
void implementElGamal(){
//////    int opcion;
//////    string mensaje="Nos movemos entre las sombras para servir a la luz somos asesinos";
//////    string e1,e2,p;
//////    string c2;
//////    gamal receptor(128);
//    while(true){
//        cout<<"Quiere decifrar presione 1: "<<endl;
//        cout<<"Quiere cifrar presione 2: "<<endl;
//        cin>>opcion;
//        if(opcion==1){
//            cout<<"Ingrese el c2: "<<endl;
//            cin>>c2;
//            cout<<"Mensaje decifrado: "<<receptor.descifrar(c2)<<endl;
//            cout<<"preciones 0 para continuar"<<endl;
//            cin>>opcion;
//        }else if(opcion==2){
//            cout<<"Ingrese e1: "<<endl;
//            cin>>e1;
//            cout<<"Ingrese e2: "<<endl;
//            cin>>e2;
//            cout<<"Ingrese p: "<<endl;
//            cin>>p;
//            gamal emisor(stringTozz(e1),stringTozz(e2),stringTozz(p));
//            emisor.cifrar(mensaje);
//            cout<<"preciones 0 para continuar"<<endl;
//            cin>>opcion;
//        }else{
//            cout<<"Ingrese una opcion valida"<<endl;
//            cout<<"preciones 0 para continuar"<<endl;
//            cin>>opcion;
//        }
//    }

    string mensaje="Nos movemos entre las sombras para servir a la luz somos asesinos";
    string e1,e2,p;
    string c2;
    gamal receptor(128);
while(true){
    int opcion;
    cout<<"Quiere decifrar presione 1: "<<endl;
    cout<<"Quiere cifrar presione 2: "<<endl;
    cin>>opcion;
    switch (opcion)
    {
    case 1:
        cout<<"Ingrese el c2: "<<endl;
        cin>>c2;
        cout<<"Mensaje decifrado: "<<receptor.descifrar(c2)<<endl;
        cout<<"preciones 0 para continuar"<<endl;
        cin>>opcion;
    case 2:
        cout<<"Ingrese e1: "<<endl;
        cin>>e1;
        cout<<"Ingrese e2: "<<endl;
        cin>>e2;
        cout<<"Ingrese p: "<<endl;
        cin>>p;
        gamal emisor(stringTozz(e1),stringTozz(e2),stringTozz(p));
        emisor.cifrar(mensaje);
        cout<<"preciones 0 para continuar"<<endl;
        cin>>opcion;

    }

    }
}
main()
{
    srand(time(NULL));
    ifstream ficheroEntrada;
    string mensaje;
    ficheroEntrada.open ("entrada.txt",ios::out | ios::binary);
    getline(ficheroEntrada,mensaje);
    ficheroEntrada.close();
    RSA s(16);
    s.set_e2(stringTozz("19"));
    s.set_n2(stringTozz("1961"));
    s.set_d2(stringTozz("1675"));
//    s.set_clavepublica(stringTozz("253"));
//    s.set_N(stringTozz("34393"));
//    s.set_claveprivada(stringTozz("2017"));
    string encriptado = s.cifrar(mensaje,"g");
    cout<<encriptado<<endl;
    cout<<"----------------------------------"<<endl;

    string original = s.descifrar(encriptado);
    cout<<original;
    ofstream ficherosalida;
    ficherosalida.open ("salida.txt");
    ficherosalida << original;
    ficherosalida.close();
//    implementElGamal();
//    gamal r(512);
//    ZZ e_1,e_2,p,c;
//    e_1 = stringTozz("4123341997156703662481795929193273818156341704419873643684407880196374387953658668324927087005164878736873139715900902329806186136192910784175959299237068");
//    e_2 = stringTozz("5772106229734278558933290561620091903222030418429026399712885064895227123102841659337611265435432352577264064758017831430676714624204057741472980116566210");
//    p = stringTozz("8246683994313407324963591858386547636312683408839747287368815760392748775907317336649854174010329757473746279431801804659612372272385821568351918598474137");
//    gamal s(e_1,e_2,p);
//    string cifrado = s.cifrar("hola que tal");
//    cout<<cifrado<<endl;
//    string original = r.descifrar(cifrado);
//    cout<<original;


};
