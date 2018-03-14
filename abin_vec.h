//
// Created by fedemeister on 10/03/18.
//

#ifndef ARBOLESBINARIOS_ABIN_VEC_H
#define ARBOLESBINARIOS_ABIN_VEC_H

#include <cassert>
#include <cstdlib>

template<typename T>
class Abin {
public:
    typedef int nodo;   // índice de la matriz
    // entre 0 y maxNodos-1
    static const nodo NODO_NULO;
    explicit Abin(size_t maxNodos); // constructor
    void insertarRaizB(const T &e);
    void insertarHijoIzqdoB(nodo n, const T &e);
    void insertarHijoDrchoB(nodo n, const T &e);
    void eliminarHijoIzqdoB(nodo n);
    void eliminarHijoDrchoB(nodo n);
    void eliminarRaizB();
    ~Abin(); // destructor
    bool arbolVacioB() const;
    const T &elemento(nodo n) const; // acceso a elto, lectura
    T &elemento(nodo n); // acceso a elto, lectura/escritura
    nodo raizB() const;
    nodo padreB(nodo n) const;
    nodo hijoIzqdoB(nodo n) const;
    nodo hijoDrchoB(nodo n) const;
    Abin(const Abin<T> &a); // ctor. de copia
    Abin<T> &operator=(const Abin<T> &a);   // asignación
private:
    struct celda {
        T elto;
        nodo padre, hizq, hder;
    };
    celda *nodos;   // vector de nodos
    int maxNodos;   // tamaño del vector
    int numNodos;   // número de nodos del árbol
};

/* Definición del nodo nulo */
template<typename T>
const typename Abin<T>::nodo Abin<T>::NODO_NULO(nullptr_t);

template<typename T>
inline Abin<T>::Abin(size_t maxNodos) :
        nodos(new celda[maxNodos]),
        maxNodos(maxNodos),
        numNodos(0) {}

template<typename T>
void Abin<T>::insertarRaizB(const T &e) {
    assert(numNodos == 0);  // árbol vacío
    numNodos = 1;
    nodos[0].elto = e;
    nodos[0].padre = NODO_NULO;
    nodos[0].hizq = NODO_NULO;
    nodos[0].hder = NODO_NULO;
}

template<typename T>
void Abin<T>::insertarHijoIzqdoB(Abin<T>::nodo n, const T &e) {
    assert(n >= 0 && n < numNodos); // nodo válido
    assert(nodos[n].hizq == NODO_NULO); // n no tiene hijo izqdo.
    assert(numNodos < maxNodos);    // árbol no lleno
    // añadir el nuevo nodo al final de la secuencia
    nodos[n].hizq = numNodos;
    nodos[numNodos].elto = e;
    nodos[numNodos].padre = n;
    nodos[numNodos].hizq = NODO_NULO;
    nodos[numNodos].hder = NODO_NULO;
    numNodos++;
}

template<typename T>
void Abin<T>::insertarHijoDrchoB(Abin<T>::nodo n, const T &e) {
    assert(n >= 0 && n < numNodos); // nodo válido
    assert(nodos[n].hder == NODO_NULO); // n no tiene hijo drcho.
    assert(numNodos < maxNodos);    // árbol no lleno
    // añadir el nuevo nodo al final de la secuencia
    nodos[n].hder = numNodos;
    nodos[numNodos].elto = e;
    nodos[numNodos].padre = n;
    nodos[numNodos].hizq = NODO_NULO;
    nodos[numNodos].hder = NODO_NULO;
    numNodos++;
}

template<typename T>
void Abin<T>::eliminarHijoIzqdoB(Abin<T>::nodo n) {
    nodo hizqdo;
    assert(n >= 0 && n < numNodos); // nodo válido
    hizqdo = nodos[n].hizq;
    assert(hizqdo != NODO_NULO); // existe hijo izqdo. de n
    assert(nodos[hizqdo].hizq == NODO_NULO // hijo izqdo. de
           && nodos[hizqdo].hder == NODO_NULO);    // n es hoja
    if (hizqdo != numNodos - 1) {
        // Mover el último nodo a la posición del hijo izqdo.
        nodos[hizqdo] = nodos[numNodos - 1];
        // Actualizar la posición del hijo (izquierdo o derecho) en el padre del nodo movido
        if (nodos[nodos[hizqdo].padre].hizq == numNodos - 1)
            nodos[nodos[hizqdo].padre].hizq = hizqdo;
        else
            nodos[nodos[hizqdo].padre].hder = hizqdo;
        // Si el nodo movido tiene hijos, actualizar la posición del padre
        if (nodos[hizqdo].hizq != NODO_NULO)
            nodos[nodos[hizqdo].hizq].padre = hizqdo;
        if (nodos[hizqdo].hder != NODO_NULO)
            nodos[nodos[hizqdo].hder].padre = hizqdo;
    }
    nodos[n].hizq = NODO_NULO;
    numNodos--;
}

template<typename T>
void Abin<T>::eliminarHijoDrchoB(Abin<T>::nodo n) {
    nodo hdrcho;
    assert(n >= 0 && n < numNodos); // nodo válido
    hdrcho = nodos[n].hder;
    assert(hdrcho != NODO_NULO);    // existe hijo drcho. de n
    assert(nodos[hdrcho].hizq == NODO_NULO && // hijo drcho. de
           nodos[hdrcho].hder == NODO_NULO);  // n es hoja
    if (hdrcho != numNodos - 1) {
        // Mover el último nodo a la posición del hijo drcho.
        nodos[hdrcho] = nodos[numNodos - 1];
        // Actualizar la posición del hijo (izquierdo o derecho) en el padre del nodo movido
        if (nodos[nodos[hdrcho].padre].hizq == numNodos - 1)
            nodos[nodos[hdrcho].padre].hizq = hdrcho;
        else
            nodos[nodos[hdrcho].padre].hder = hdrcho;
        // Si el nodo movido tiene hijos, actualizar la posición del padre
        if (nodos[hdrcho].hizq != NODO_NULO)
            nodos[nodos[hdrcho].hizq].padre = hdrcho;
        if (nodos[hdrcho].hder != NODO_NULO)
            nodos[nodos[hdrcho].hder].padre = hdrcho;
    }
    nodos[n].hder = NODO_NULO;
    numNodos--;
}

template<typename T>
inline void Abin<T>::eliminarRaizB() {
    assert(numNodos == 1);
    numNodos = 0;
}

template<typename T>
inline Abin<T>::~Abin() {
    delete[] nodos;
}

template<typename T>
inline bool Abin<T>::arbolVacioB() const {
    return (numNodos == 0);
}

template<typename T>
inline const T &Abin<T>::elemento(Abin<T>::nodo n) const {
    assert(n >= 0 && n < numNodos);
    return nodos[n].elto;
}

template<typename T>
inline T &Abin<T>::elemento(Abin<T>::nodo n) {
    assert(n >= 0 && n < numNodos);
    return nodos[n].elto;
}

template<typename T>
inline typename Abin<T>::nodo Abin<T>::raizB() const {
    return (numNodos > 0) ? 0 : NODO_NULO;
}

template<typename T>
inline
typename Abin<T>::nodo Abin<T>::padreB(Abin<T>::nodo n) const {
    assert(n >= 0 && n < numNodos);
    return nodos[n].padre;
}

template<typename T>
inline
typename Abin<T>::nodo Abin<T>::hijoIzqdoB(Abin<T>::nodo n) const {
    assert(n >= 0 && n < numNodos);
    return nodos[n].hizq;
}

template<typename T>
inline
typename Abin<T>::nodo Abin<T>::hijoDrchoB(Abin<T>::nodo n) const {
    assert(n >= 0 && n < numNodos);
    return nodos[n].hder;
}

template<typename T>
Abin<T>::Abin(const Abin<T> &a) :
        nodos(new celda[a.maxNodos]),
        maxNodos(a.maxNodos),
        numNodos(a.numNodos) {
    // copiar el vector
    for (nodo n = 0; n <= numNodos - 1; n++)
        nodos[n] = a.nodos[n];
}

template<typename T>
Abin<T> &Abin<T>::operator=(const Abin<T> &a) {
    if (this != &a) {
    // Evitar autoasignación.
    // Destruir el vector y crear uno nuevo si es necesario
        if (maxNodos != a.maxNodos) {
            delete[] nodos;
            maxNodos = a.maxNodos;
            nodos = new celda[maxNodos];
        }
    // Copiar el vector
        numNodos = a.numNodos;
        for (nodo n = 0; n <= numNodos - 1; n++)
            nodos[n] = a.nodos[n];
    }
    return *this;
}

#endif //ARBOLESBINARIOS_ABIN_VEC_H
