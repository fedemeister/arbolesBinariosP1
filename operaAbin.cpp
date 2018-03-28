//
// Created by fedemeister on 13/03/18.
//


#include "abin_celdas.h"
#include "abin_E-S.h"

using namespace std;
typedef char tElto;
const tElto fin = '#';   // fin de lectura


template<typename T>
bool similares_rec(const Abin<T> &A, typename Abin<T>::nodo a,
                   const Abin<T> &B, typename Abin<T>::nodo b);


template<typename T>
Abin<T> reflejado_rec(Abin<T>::nodo n, Abin<T> A, Abin<T>::nodo n2, Abin<T> Arbol_Imagen);


//PRACTICA 1

/*
 * Implemente un subprograma que calcule el numero de nodos de un arbol binario
 */
int num_nodos_rec(const Abin<tElto> &A, Abin<tElto>::nodo n) {
    if (n == Abin<tElto>::NODO_NULO)
        return 0;
    else
        return 1 + num_nodos_rec(A, A.hijoIzqdoB(n)) + num_nodos_rec(A, A.hijoDrchoB(n));
}

int num_nodos(const Abin<tElto> &A) {
    return num_nodos_rec(A, A.raizB());
}

/*
 * Implemente un subprograma que calcule la altura de un arbol binario
 */

template<typename T>
int alturaAbin(typename Abin<T>::nodo n, Abin<T> A) {   // recorrido en postorden
    if (n == Abin<T>::NODO_NULO)
        return -1;
    else
        return 1 + max(alturaAbin(A.hijoIzqdoB(n), A),
                       alturaAbin(A.hijoDrchoB(n), A)
        );
}

template<typename T>
int altura(const Abin<T> &a) {
    return alturaAbin(a.raizB(), a);
}



/*
 * Implemente un subprograma que, dados un arbol binario y un nodo del mismo,
 * determine la profundidad de este nodo en dicho arbol
 */

template<typename T>
int profundidad(typename Abin<T>::nodo n, const Abin<T> &A) {   // si n es la raiz
    if (n == Abin<T>::NODO_NULO)
        return -1;
    else if (A.raizB() == n)
        return 0;
    else
        return profundidad(A.padreB(n), A) + 1;
}


/*
 * Implemente un subprograma que determine el nuvel de desequilibrio de un arbol binario,
 * definido como el maximo desequilibrio de todos sus nodos. El desequilibrio de un nodo se
 * define como la diferencia entre las alturas de los subarboles del mismo
 */

template <typename T>
int desequilibrio(typename Abin<T>::nodo n, const Abin<T>& a)
{
    if (n == Abin<T>::NODO_NULO)
        return -1;
    return abs(alturaAbin(a.hijoIzqdoB(n),a)
               - (alturaAbin(a.hijoDrchoB(n),a))
    );
}

// recorrido en postorden
template <typename T>
int desequilibrioSubarbol(typename Abin<T>::nodo n,const Abin<T>& a)
{
    int des_rama_izq, des_rama_der, des_n;

    if (n == Abin<T>::NODO_NULO)
        return desequilibrio(n, a);
    else
    {   // desequilibrio de la rama izquierda de n:
        des_rama_izq = desequilibrioSubarbol(a.hijoIzqdoB(n), a);
        // desequilibrio de la rama derecha de n:
        des_rama_der = desequilibrioSubarbol(a.hijoDrchoB(n), a);
        // desequilibrio del nodo actual n:
        des_n = desequilibrio(n, a);
        // evaluar maximo desequilibrio del nodo actual
        // y los subarboles del nodo n
        return max(des_n, max(des_rama_izq, des_rama_der));
    }
}

template <typename T>
int nivelDesequilibrio(const Abin<T>& a)
{
    return desequilibrioSubarbol(a.raizB(), a);
}


/*
 * Implementa un subprograma que determine si un arbol binario es o no pseudocompleto. En este
 * problema entenderemos que un arbol es pseudocompleto, si en el penultimo nivel del mismo
 * cada uno de los nodos tiene dos hijos o ninguno.
 */


template <typename T>
bool tieneCeroDosHijos(typename Abin<T>::nodo n, const Abin<T>& a)
{
    return ( a.hijoIzqdoB(n) != Abin<T>::NODO_NULO
             && a.hijoDrchoB(n) != Abin<T>::NODO_NULO )
           || ( a.hijoIzqdoB(n) == Abin<T>::NODO_NULO
                && a.hijoDrchoB(n) == Abin<T>::NODO_NULO );
}

//  h = altura maxima del arbol a
template <typename T>
bool checkPseudocompleto(typename Abin<T>::nodo n, const Abin<T>& a, int h)
{
    if ( profundidad(n, a) == (h - 1) )
        return tieneCeroDosHijos(n, a);
    else if ( n == Abin<T>::NODO_NULO )
        return true;
    else
        return checkPseudocompleto(a.hijoIzqdoB(n), a, h)
               && checkPseudocompleto(a.hijoDrchoB(n), a, h);
}

template <typename T>
bool esPseudocompleto(const Abin<T> a)
{
    return checkPseudocompleto(
            a.raizB(), a, altura(a));
}





// PRACTICA 2
template<typename T>
bool similares(const Abin<T> &A, const Abin<T> &B) {
    return similares_rec(A, A.raizB(), B, B.raizB());
}

template<typename T>
bool similares_rec(const Abin<T> &A, typename Abin<T>::nodo a,
                   const Abin<T> &B, typename Abin<T>::nodo b) {
    if (a == Abin<T>::NODO_NULO && b == Abin<T>::NODO_NULO)
        return true;
    else if ((a == Abin<T>::NODO_NULO && b != Abin<T>::NODO_NULO)
             || (a != Abin<T>::NODO_NULO && b == Abin<T>::NODO_NULO))
        return false;
    else if (a != Abin<T>::NODO_NULO && b != Abin<T>::NODO_NULO)
        return similares_rec(A, A.hijoIzqdoB(a), B, B.hijoIzqdoB(b))
               && similares_rec(A, A.hijoDrchoB(a), B, B.hijoDrchoB(b));
}

template<typename T>
Abin<T> reflejado(Abin<T> A) {
    Abin<T> Arbol_Reflejado;
    Arbol_Reflejado.insertarRaizB(A.raizB());

    return reflejado_rec(A.raizB(), A, Arbol_Reflejado.raizB(), Arbol_Reflejado);
}

template<typename T>
Abin<T> reflejado_rec(Abin<T>::nodo n, Abin<T> A, Abin<T>::nodo n2, Abin<T> *Arbol_Reflejado) {

    if (A.hijoIzqdoB(n) && A.hijoDrchoB(n) == Abin<T>::NODO_NULO)
        return;
    else
        return Abin<T>();
}

int main() {
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