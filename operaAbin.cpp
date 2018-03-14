//
// Created by fedemeister on 13/03/18.
//


#include "abin_celdas.h"
#include "abin_E-S.h"
using namespace std;
typedef char tElto;
const tElto fin = '#';   // fin de lectura


int num_nodos(const Abin<tElto> &A);
int num_nodos_rec(const Abin<tElto> &A, Abin<tElto>::nodo);


int num_nodos(const Abin<tElto> &A)
{
    return num_nodos_rec(A, A.raizB());
}

int num_nodos_rec(const Abin<tElto> &A, Abin<tElto>::nodo n)
{
    if (n == Abin<tElto>::NODO_NULO)
        return 0;
    else
        return 1 + num_nodos_rec(A, A.hijoIzqdoB(n)) + num_nodos_rec(A, A.hijoDrchoB(n));
}



int main()
{
    Abin<tElto> A, B;
    //cout << "*** Lectura del árbol binario A ***\n";
    //rellenarAbin(A, fin);      // desde std::cin
    //ofstream fs("abin.dat");   // abrir fichero de salida
    //        imprimirAbin(fs, A, fin);  // en fichero
    //fs.close();
    //cout << "\n*** Árbol A guardado en fichero abin.dat ***\n";
    cout << "\n*** Lectura de árbol binario B de abin.dat ***\n";
    ifstream fe("abin.dat");   // abrir fichero de entrada
            rellenarAbin(fe, B);       // desde fichero
    fe.close();
    cout << "\n*** Mostrar árbol binario B ***\n";
    imprimirAbin(B);           // en std::cout

    int n = num_nodos(B);
    cout << n;
    return 0;
}