#include <bits/stdc++.h>
//#include <iostream>
//#include <conio.h>
//#include <stdlib.h>

using namespace std;


struct Nodo{
    int dato;
    Nodo *der;
    Nodo *izq;
    Nodo *padre;
};

//Prototipos
void menu();
Nodo *crearNodo(int,Nodo *);
void insertarNodo(Nodo *&,int,Nodo *);
void mostrarArbol(Nodo *, int);
bool busqueda(Nodo *, int);
void preOrden(Nodo *);
void inOrden(Nodo *);
void postOrden(Nodo *);
void eliminar(Nodo *, int);
void eliminarNodo(Nodo *);
Nodo *minimo(Nodo *);
void reemplazar (Nodo *,Nodo *);
void destruirNodo(Nodo *);

//inicializar el arbol
Nodo *arbol = NULL;

//encargado de crear los nodos cuando sea llamado
Nodo *crearNodo (int n,Nodo *padre){
    Nodo *nuevo_nodo = new Nodo();

    nuevo_nodo -> dato = n;
    nuevo_nodo -> der = NULL;
    nuevo_nodo -> izq = NULL;
    nuevo_nodo -> padre = padre;

    return nuevo_nodo;
}

//funcion para insertar los datos en los nodos
void insertarNodo(Nodo *&arbol, int n,Nodo *padre){
    if (arbol == NULL){
        Nodo *nuevo_nodo = crearNodo(n,padre);
        arbol = nuevo_nodo;
    }
    else{
        int valorRaiz = arbol -> dato;
        if(n < valorRaiz){
            insertarNodo(arbol -> izq, n, arbol);
        }
        else{
            insertarNodo(arbol -> der, n, arbol);
        }
    }
}


//Creacion de menu para tener una mejor ejecucion del programa
void menu(){
    int dato, opcion,contador=0;

    do{
        cout << "\t.:MENU:."<<endl;

        cout << "1. Insertar un nuevo nodo\n";

        cout << "2. mostrar el arbol completo\n";

        cout << "3. buscar un elemento en el arbol\n";

        cout << "4. Recorrer Arbol en preOrden\n";

        cout << "5. Recorrer arbol en InOrden\n";

        cout << "6. Recorrer arbol en PostOrden\n";

        cout << "7. Eliminar un nodo del arbol\n";

        cout << "8. Salir\n";

        cout << "Elige una opcion: ";

        cin >> opcion;

        switch(opcion){
            case 1: cout << "\nEscribe un numero: ";
                    cin >> dato;
                    insertarNodo(arbol,dato,NULL);
                    cout << endl;
                    system("pause");
                    break;
            case 2: cout << "\nMostrando el arbol completo:\n\n";
                    mostrarArbol(arbol,contador);
                    cout << '\n';
                    system("pause");
                    break;
            case 3: cout << "\nQue numero quieres buscar? ";
                    cin >> dato;
                    if(busqueda(arbol,dato)==true){
                        cout << "\nElemento " << dato << " a sido encontrado en el arbol\n";
                    }
                    else{
                        cout << "\nElemento no encontrado\n";
                    }
                    cout<<endl;
                    system("pause");
                    break;
            case 4: cout <<"Recorrido en PreOrden: ";
                    preOrden(arbol);
                    cout << endl << endl;
                    system("pause");
                    break;
            case 5: cout << "\nRecorrido en InOrden: ";
                    inOrden(arbol);
                    cout << "\n\n";
                    system("pause");
                    break;
            case 6: cout << "\nRecorrido en PostOrden: ";
                    postOrden(arbol);
                    cout << endl << endl;
                    system("pause");
                    break;
            case 7: cout <<"\nIngresa el numero que quieres eliminar: ";
                    cin >> dato;
                    eliminar(arbol,dato);
                    cout << endl;
                    system("pause");
                    break;

        }
        system("cls");

    }while(opcion != 8);

}

//Funcion para mostrar el arbol completo despues de ser ordenado
void mostrarArbol(Nodo *arbol, int cont){
    if(arbol == NULL){
        return;
    }
    else{
        mostrarArbol(arbol -> der, cont+1);
        for(int i=0;i<cont;++i){
            cout << "   ";
        }
        cout << arbol -> dato << endl;
        mostrarArbol(arbol -> izq,cont+1);
    }
}

//Funcion para buscar un elemento dentro del arbol
bool busqueda(Nodo *arbol, int n){
    if(arbol == NULL){
        return false;
    }
    else if(arbol -> dato == n){
        return true;
    }
    else if(n < arbol -> dato){
        return busqueda(arbol -> izq, n);
    }
    else{
        return busqueda(arbol -> der, n);
    }
}

//Funcion para el ordenamiento en preOrden
void preOrden(Nodo *arbol){
    if(arbol == NULL){
        return;
    }
    else{
        cout << arbol -> dato << " - ";
        preOrden(arbol -> izq);
        preOrden(arbol -> der);
    }
}

//Funcion para el ordenamiento en InOrden
void inOrden(Nodo *arbol){
    if(arbol == NULL){
        return;
    }
    else{
        inOrden(arbol -> izq);
        cout << arbol -> dato << " - ";
        inOrden(arbol -> der);
    }
}


//Funcion para el ordenamiento en postOrden
void postOrden (Nodo *arbol){
    if(arbol == NULL){
        return;
    }
    else{
        postOrden(arbol -> izq);
        postOrden(arbol -> der);
        cout << arbol -> dato <<" - ";
    }
}

void eliminar(Nodo *arbol, int n){
    if(arbol == NULL){
        return;
    }
    else if (n < arbol -> dato){
        eliminar(arbol -> izq, n);
    }
    else if( n> arbol -> dato){
        eliminar(arbol -> der, n);
    }
    else{
        eliminarNodo(arbol);
    }
}

/*Nodo mas izquierdo posible para recorrer
a los hijos despues de eliminar un nodo padre*/
Nodo *minimo(Nodo *arbol){
    if( arbol == NULL){
        return NULL;
    }
    if(arbol -> izq){
        return minimo(arbol -> izq);
    }
    else{
        return arbol;
    }
}

//Funcion para que los hijos apunten a su nuevo padre
void reemplazar(Nodo *arbol, Nodo *nuevoNodo){
    if (arbol -> padre){
        //asignarle nuevo hijo
        if(arbol ->dato == arbol -> padre -> izq -> dato){
            arbol -> padre -> izq = nuevoNodo;
        }
        else if (arbol -> dato == arbol -> padre -> der -> dato){
            arbol -> padre -> der = nuevoNodo;
        }
    }
    if(nuevoNodo){
        //asignarle nuevo padre
        nuevoNodo -> padre = arbol -> padre;
    }
}


//Funcion para destruir el nodo para que sea eliminado correctamente
void destruirNodo(Nodo *nodo){
    nodo -> izq = NULL;
    nodo -> der = NULL;
    delete nodo;

}

//Funcion para eliminar el Nodo segun los hijos que tenga
void eliminarNodo(Nodo *nodoEliminar){
    
    //dos
    if (nodoEliminar -> izq && nodoEliminar->der){
        Nodo *menor = minimo (nodoEliminar ->der);
        nodoEliminar->dato = menor->dato;
        eliminarNodo(menor);
    }

    //uno
    else if( nodoEliminar -> izq ){
        reemplazar(nodoEliminar,nodoEliminar-> izq);
        destruirNodo(nodoEliminar);

    }
    else if(nodoEliminar -> der){
        reemplazar(nodoEliminar,nodoEliminar->der);
        destruirNodo(nodoEliminar);
    }

    //cero
    else{
        reemplazar(nodoEliminar,NULL);
        destruirNodo(nodoEliminar);
    }
}


//Funcion principal en donde uso el menu que cree antes
int main()
{
    menu();
    return 0;

}
