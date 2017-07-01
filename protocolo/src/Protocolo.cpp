#include "Protocolo.h"
#include <NTL/ZZ.h>
#include "GA.h"
#include <vector>
using namespace NTL;
ZZ raiz_primitiva(ZZ p)
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
string numberToString(int numero){
    stringstream ss;
	ss << numero;
	return ss.str();
}
void Protocolo::generar_claves(int bits)
{
    q = des(bits);
    g = raiz_primitiva(q);
    while(q < g)
    {
        g = raiz_primitiva(q);
    }
    cout<<"q " <<q<<endl;
    cout<<g<<endl;
    p1 = des(bits);
    p2 = des(bits);
    n = p1 * p2;
    ZZ phi_N =(p1-1)*(p2-1);
    e = ga(bits/2,bits,sqrt(bits),11);
    while(e > phi_N || euclides(e, phi_N) != 1)
    {
        e = ga(bits/2,bits,sqrt(bits),11);
    }
    d = inversa(e, phi_N);
    a = ga(11,bits,5,10);
    while(a>q)
    {
        a = ga(11,bits,5,10);
    }
    cout<<"a:  "<<a<<endl;
    cout<<"e:  "<<e<<endl;
    cout<<"n:  "<<n<<endl;
    cout<<"k:  "<<k<<endl;
}
Protocolo::Protocolo(int bits)
{
    generar_claves(bits);

}

Protocolo::Protocolo(ZZ e,ZZ n)
{
    this->e = e;
    this->n = n;
}


string Protocolo::cifrar(string mensaje)
{

    long alfL = this->alfabeto.size();
	string leng = zzToString(this->q), c, original, tmp, alfLeng =zzToString(NTL::to_ZZ(alfL));
	long k = leng.size() - 1, modd, lengP, lengAlf = alfLeng.size()-1; ///k = digitos de N - 1s
	long i, found;
	NTL::ZZ result, temp, ten, ten2, ka, Ca;
	ka = potencia(this->g, this->a, this->q);
	Ca = potencia(this->a, this->e, this->n);
	ten = potenciacion(NTL::to_ZZ(10), NTL::to_ZZ(lengAlf));
	for (i = 0; i < mensaje.size(); i++){ ///llenando los bloques con 2 digitos (tam de la letra mas grande)
		found = this->alfabeto.find(mensaje[i]);
		ten2 = ten;
		if (found < ten2){ ///si es menor a 10, le metemos un 0 al comienzo
			original += "0";
			ten2 /= 10;
		}
		original += zzToString(NTL::to_ZZ(found));
	}
	modd = moduloo(original.size(), k);
	while(modd != 0){ ///agrega "26" (espacio) mientras la long del texto
		original += "26"; ///en numeros no sea divisible entre la long de N
		modd = moduloo(original.size(), k);
	}
	ten = potenciacion(NTL::to_ZZ(10), NTL::to_ZZ(k)); ///10^(k) para saber si result tiene tantos digitos como k
	for(i = 0; i < original.size(); i+=k){
		tmp.clear();
		ten2 = ten;
		tmp = original.substr(i, k);
		temp = stringTozz(tmp);
		result = modulo((ka * temp), this->q);
		while (result  < ten2){ ///si result es menor a 10^k, se le agrega 0 y se divide entre 10 a 10^k (10^{k-1})
			c += "0";
			ten2 /= 10;
		}
		c += zzToString(result);
	}
	string ca = zzToString(Ca), c0;
	k = ca.size();
	leng = zzToString(this->n);
	while(k < leng.size()){
		c0 += "0";
		k++;
	}
	c0 += ca;
	c += c0;
	return c;
}

string Protocolo::descifrar(string mensaje)
{
	long alfL = this->alfabeto.size();
	string leng = zzToString(this->n), d, ret, tmp, ca, alfLeng = zzToString(NTL::to_ZZ(alfL));
	long k = leng.size(), lengAlf = alfLeng.size(); ///P Digitos
	long i, found;
	NTL::ZZ result, temp, ten, ten2, invKM, A, caN, ka;
	//ca(c.begin() + c.size()-this->N, this->N);
	ca = mensaje.substr(mensaje.size()-k, k);
	leng = zzToString(this->q);
	k = leng.size();
	caN = stringTozz(ca);
	A = potencia(caN, this->d, this->n);
	ka = potencia(this->g, A, this->q);
	invKM = inversa(ka, this->q);
	ten = potenciacion(NTL::to_ZZ(10), k-NTL::to_ZZ(2)); ///10^{N-2} para ver si el numero es menor a eso
	for(i = 0; i < (mensaje.size() - k); i+=k){
		tmp.clear(); ///borrando datos del string
		ten2 = ten;
		tmp = mensaje.substr(i, k);
		temp = stringTozz(tmp);
		result = modulo((temp * invKM), this->q);
		cout << "Result: " << result << endl;
		ostringstream conv;
		conv << result;
		while (result < ten2){ ///guardando en bloques N-1
			d += "0";
			ten2 /= 10;
		}
		d += conv.str();
	}
	for(i = 0; i < d.size(); i+=lengAlf){
		tmp.clear();
		tmp = d.substr(i, lengAlf);
		found = NTL::to_long(stringTozz(tmp));
		ret += this->alfabeto[found];
	}
	return ret;
}




