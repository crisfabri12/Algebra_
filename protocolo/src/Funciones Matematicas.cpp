#include "Funciones Matematicas.h"
#include <NTL/ZZ.h>
#include "GA.h"
#include <vector>
using namespace NTL;
using namespace std;
string zzToString(ZZ z) {
    stringstream buffer;
    buffer << z;
    return buffer.str();
}
ZZ stringTozz(string str){
    ZZ number(INIT_VAL, str.c_str());
    return number;
}
vector<bool> ZZtoBinary(ZZ num){
    vector<bool> binario;
    while(num>0){
        binario.push_back(to_int(modulo(num,to_ZZ(2))));
        num=num>>1;
    }
    return binario;
}
ZZ potenciaMod(ZZ n, ZZ m, ZZ mod){
    if(n>mod)
        n=modulo(n,mod);
    vector<bool> b=ZZtoBinary(m);
    ZZ d=to_ZZ(1);
	for(int i=b.size();i>0;i--){
        d=modulo(d*d,mod);
        if(b[i-1]==1)
            d=modulo(d*n,mod);
	}
	return d;
}

ZZ modulo(ZZ a, ZZ n)
{
    ZZ q, r;
	q = a / n;
	r = a - (q*n);
	if (r < 0)
		r += n;
	return r;
}

ZZ euclides(ZZ a, ZZ b)
{
     ZZ residuo = modulo(a,b);
     while(residuo!=0)
     {
         a = b;
         b = residuo;
         residuo = modulo(a,b);
     }
     return b;
}
ZZ mcd(ZZ a, ZZ b)
{
    ZZ resultado;
    resultado = 1;
    ZZ i;
    for(i=1;i<=a;i++)
    {
        if((modulo(a,i)==0)&&(modulo(b,i)==0))
        {
            resultado = i;
        }
    }
    return resultado;
}
std::vector <ZZ> euclides_extendido(ZZ a, ZZ b)
{
    std::vector <ZZ> resultados;
    ZZ r1,s1,t1,r2,s2,t2,q,r;
    r1 = a;
    r2 = b;
    s1 = 1;
    s2 = 0;
    t1 = 0;
    t2 = 1;
    while(r2>0)
    {
        q = r1/r2;

        ZZ r = r1 - q * r2;
        r1 = r2;
        r2 = r;

        ZZ s = s1 - q * s2;
        s1 = s2;
        s2 = s;

        ZZ t = t1 - q * t2;
        t1 = t2;
        t2 = t;

    }
    resultados.push_back(r1);
    resultados.push_back(s1);
    resultados.push_back(t1);
    return resultados;
}
ZZ inversa(ZZ a, ZZ alfabeto)
{
    ZZ x = euclides_extendido(a,alfabeto)[1];
    if(x<0)
    {
        return modulo(x,alfabeto);
    }
    return x;
}

ZZ potencia(ZZ a, ZZ b, ZZ modu)
{
    ZZ result = to_ZZ(1);
    ZZ n = to_ZZ(2);
    while(b != to_ZZ(0)){
        if(modulo(b,n)==1){
            result = modulo((result * a),modu);
        }
        a = modulo((a * a),modu);
        b = b/2;
    }
    return result;
}


bool fermat(ZZ p){
    ZZ a;
    a=to_ZZ(3);
    while(true){
        a=ga(4,1024,2,3);
        if(mcd(p,a)==1){
            break;
        }
    }
    if(potencia(a,p-1,p)==1){
        return 1;
    }
    return 0;
}
int moduloo(int a, int n)
{
    int q, r;
	q = a / n;
	r = a - (q*n);
	if (r < 0)
		r += n;
	return r;
}
ZZ potenciacion(ZZ a, ZZ b){
	ZZ m, temp;
	ZZ res;
	res = to_ZZ("1");
	m = b;
	while(m != 0){
		if (m == b) temp = a;
		else temp *= temp;
		if (modulo(m, to_ZZ(2)) == 1)
			res *= temp;
		m/=2;
	}
	return res;
}
std::vector<int> criba_Eratostenes(int intervalo_mayor, int intervalo_menor)
{
    std::vector<int>lista(intervalo_mayor,1);
    int j=0,k=0,pivote;//j[0]=2,j[1]=3,...

    while(j<intervalo_mayor){
        while(lista[j]==0){//0 es falso
            j++;
        }
        pivote=j+2;
        k=j+3;j++;
        while(k<intervalo_mayor){
            if(lista[k]==1&&moduloo(k,pivote)==0){
                lista[k]=0;//cout<<k<<endl;
            }
            k++;
        }
    }
    std::vector<int>res;
    for(int i=intervalo_menor;i<intervalo_mayor;i++)
    {
        if(lista[i]==1)
        {
            res.push_back(i);
        }
    }
    return res;
}
int PHI_euler(int num){
    int factorPrimo=2, exp=0,resultado=1;/////////////////////////CALCULAMOS LOS FACTORES
    std::vector<int>exp_factores;
    while(factorPrimo<=num){
        if(moduloo(num,factorPrimo)==0){
            num=num/factorPrimo;
            exp++;
        }
        else{
            factorPrimo++;
            exp_factores.push_back(exp);
            exp=0;
        }
    }
    exp_factores.push_back(exp);
    for(int i=0;i<exp_factores.size();i++){//////////////////////////EMPEZAMOS A CALCULAR EL PHI DE EULER
        if(exp_factores[i]==0)//i[0]=2;i[1]=3... i[n]=n+2
            continue;
        if(exp_factores[i]==1){
            resultado*=i+1;
        }
        else {
            resultado*=(pow((i+2),exp_factores[i])- pow((i+2),exp_factores[i]-1));
        }
    }
    return resultado;
}


vector<bool> permu56(vector<bool> bits){
    vector<bool> respuesta;
    int tabla_predefinida[56] = {57,49,41,33,25,17,9,1,57,50,42,34,26,18,10,2,59,57,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4};
    for(int i = 0; i < 56; i++){
        respuesta.push_back(bits[tabla_predefinida[i]-1]);
    }
    return respuesta;
}

vector<bool> permu48(vector<bool> bits){
    vector<bool> respuesta;
    int tabla_predefinida[48] = {14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,41,33,48,44,49,39,56,34,53,46,42,50,36,29,32};
    for(int i = 0; i < 48; i++){
        respuesta.push_back(bits[tabla_predefinida[i]-1]);
    }
    return respuesta;
}

vector<bool> rotarizquierda(vector<bool> num, int vueltas)
{
    bool temp;
    for(int j = vueltas; j > 0; j--)
    {
        for(int i = 0; i < num.size() - 1; i++)
        {
            temp = num[i];
            num[i] = num[i + 1];
            num[i + 1] = temp;
        }
    }
    return num;
}

vector<bool> subvec(vector<bool> numero,int posicion, int numeros){
    vector <bool> resultado;
    for(int i = 0; i < numeros; i++){
        resultado.push_back(numero[posicion]);
        posicion++;
    }
    return resultado;
}

vector<bool> unir(vector<bool> A, vector<bool> B){
    vector<bool>C;
    for(int i = 0; i < A.size(); i++){
        C.push_back(A[i]);
    }
    for(int j = 0; j < B.size(); j++){
        C.push_back(B[j]);
    }
    return C;
}

ZZ des(int bits){
    vector<bool> digitos = ga2(bits/2,bits,sqrt(bits),11);
    int vueltas[] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
    vector<bool> actual;
    for(int j = 0; j < bits; j+=64){
        vector<bool> temp;
        temp = (permu56(subvec(digitos,j,64)));
        actual = unir(actual,temp);
    }
    for(int k = 0; k < 16; k++){
        vector<bool> vec_56bits;
        vector<bool> vec_48bits;
        for(int l = 0; l < actual.size(); l+=56){
            vector<bool> c = rotarizquierda(subvec(actual,l,28),vueltas[k]);
            vector<bool> d = rotarizquierda(subvec(actual,l+28,28),vueltas[k]);
            vec_56bits = unir(vec_56bits, unir(c,d));
            vec_48bits = unir(vec_48bits,permu48(unir(c,d)));
        }
        if(vec_48bits[vec_48bits.size()-1] == 0){
            vec_48bits[vec_48bits.size()-1] = 1;
        }
        ZZ resultado = convertir_decimal(vec_48bits,vec_48bits.size());
        if(ProbPrime(resultado,10)){
            return resultado;
        }
        actual = vec_56bits;
    }
    return des(bits);
}


