//
// Created by fedemeister on 13/03/18.
//

#ifndef ABIN_E_S_H
#define ABIN_E_S_H

#include <cassert>
#include <iostream>
#include <fstream>

using std::istream;
using std::ostream;
using std::cin;
using std::cout;
using std::endl;

template<typename T>
void rellenarDescendientes(typename Abin<T>::nodo r, Abin<T> &A, const T &fin)
// Pre: r es un nodo hoja de A.
// Post: Lee de la entrada estándar y en preorden los descendientes de r,
//       usando fin para introducir nodos nulos.
{
    T ehi, ehd;

    assert(A.hijoIzqdoB(r) == Abin<T>::NODO_NULO &&
           A.hijoDrchoB(r) == Abin<T>::NODO_NULO);
    cout << "Hijo izqdo. de " << A.elemento(r) <<
         " (Fin = " << fin << "): ";
    cin >> ehi;
    if (ehi != fin) {
        A.insertarHijoIzqdoB(r, ehi);
        rellenarDescendientes(A.hijoIzqdoB(r), A, fin);
    }
    cout << "Hijo drcho. de " << A.elemento(r) <<
         " (Fin = " << fin << "): ";
    cin >> ehd;
    if (ehd != fin) {
        A.insertarHijoDrchoB(r, ehd);
        rellenarDescendientes(A.hijoDrchoB(r), A, fin);
    }
}

template<typename T>
void rellenarAbin(Abin<T> &A, const T &fin)
// Pre: A está vacío.
// Post: Rellena el árbol A con la estructura y elementos
//       leídos en preorden de la entrada estándar, usando
//       fin como elemento especial para introducir nodos nulos.
{
    T e;

    assert(A.arbolVacioB());
    cout << "Raiz (Fin = " << fin << "): ";
    cin >> e;
    if (e != fin) {
        A.insertarRaizB(e);
        rellenarDescendientes(A.raizB(), A, fin);
    }
}

template<typename T>
void rellenarAbin(istream &is, Abin<T> &A)
// Pre: A está vacío.
// Post: Extrae los nodos de A del flujo de entrada is,
//       que contendrá el elemento especial que denota
//       un nodo nulo seguido de los elementos en preorden,
//       incluyendo los correspondientes a nodos nulos.
{
    T e, fin;

    assert(A.arbolVacioB());
    if (is >> fin && is >> e && e != fin) {
        A.insertarRaizB(e);
        rellenarDescendientes(is, A.raizB(), A, fin);
    }
}

template<typename T>
void rellenarDescendientes(istream &is, typename Abin<T>::nodo r, Abin<T> &A, const T &fin)
// Pre: r es un nodo hoja de A.
// Post: Lee del flujo de entrada is y en preorden los descendientes de r,
//       usando fin para los nodos nulos.
{
    T ehi, ehd;

    assert(A.hijoIzqdoB(r) == Abin<T>::NODO_NULO &&
           A.hijoDrchoB(r) == Abin<T>::NODO_NULO);
    if (is >> ehi && ehi != fin) {
        A.insertarHijoIzqdoB(r, ehi);
        rellenarDescendientes(is, A.hijoIzqdoB(r), A, fin);
    }
    if (is >> ehd && ehd != fin) {
        A.insertarHijoDrchoB(r, ehd);
        rellenarDescendientes(is, A.hijoDrchoB(r), A, fin);
    }
}

template<typename T>
void imprimirDescendientes(typename Abin<T>::nodo r, const Abin<T> &A)
// Post: Muestra los descendientes de r en la salida estándar.
{
    if (A.hijoIzqdoB(r) != Abin<T>::NODO_NULO) {
        cout << "Hijo izqdo de " << A.elemento(r) << ": "
             << A.elemento(A.hijoIzqdoB(r)) << endl;
        imprimirDescendientes(A.hijoIzqdoB(r), A);
    }
    if (A.hijoDrchoB(r) != Abin<T>::NODO_NULO) {
        cout << "Hijo derecho de " << A.elemento(r) << ": "
             << A.elemento(A.hijoDrchoB(r)) << endl;
        imprimirDescendientes(A.hijoDrchoB(r), A);
    }
}


template<typename T>
void imprimirAbin(const Abin<T> &A)
// Post: Muestra los nodos de A en la salida estándar
{
    if (!A.arbolVacioB()) {
        cout << "Raíz del árbol: "
             << A.elemento(A.raizB()) << endl;
        imprimirDescendientes(A.raizB(), A);
    } else
        cout << "Árbol vacío\n";
}

template<typename T>
void imprimirAbin(ostream &os, const Abin<T> &A, const T &fin)
// Post: Inserta en el flujo de salida os los nodos de A en preorden,
//       precedidos del elemento especial usado para denotar un nodo nulo.
{
    if (!A.arbolVacioB()) {
        os << fin << endl
           << A.elemento(A.raizB()) << ' ';
        imprimirDescendientes(os, A.raizB(), A, fin);
        os << endl;
    }
}

template<typename T>
void imprimirDescendientes(ostream &os, typename Abin<T>::nodo r, const Abin<T> &A, const T &fin)
// Post: Inserta en el flujo de salida os y en preorden
//       los descendientes de r, usando fin como nodo nulo.
{
    if (A.hijoIzqdoB(r) != Abin<T>::NODO_NULO) {
        os << A.elemento(A.hijoIzqdoB(r)) << ' ';
        imprimirDescendientes(os, A.hijoIzqdoB(r), A, fin);
    } else
        os << fin << ' ';
    if (A.hijoDrchoB(r) != Abin<T>::NODO_NULO) {
        os << A.elemento(A.hijoDrchoB(r)) << ' ';
        imprimirDescendientes(os, A.hijoDrchoB(r), A, fin);
    } else
        os << fin << ' ';
}

#endif   // ABIN_E_S_H