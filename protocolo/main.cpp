#include <iostream>
#include "GA.h"
#include "Protocolo.h"
#include <time.h>
#include "Funciones Matematicas.h"
using namespace std;

int main()
{
    srand(time(NULL));
    Protocolo r(64);
    string cifrado = r.cifrar("hola");
    cout<<cifrado<<endl;
    string original = r.descifrar(cifrado);
    cout<<original<<endl;

}
