#include <iostream>
#include <string.h>
#include <stdio.h>
#include <chrono>
#include <locale.h>
using namespace std;
FILE *fd;

///IMPRIME
void display(string *array, int size)
{

	for (int i = 0; i <= size; i++)
		cout << array[i]<<endl;
}

void Quicksort(string *arr, int izquierda, int derecha)
{

    string tmp;
    int izq = izquierda, der = derecha;
    string pivote = arr[(izquierda + derecha) / 2];

    while (izq <= der)
    {
        while (arr[izq] < pivote)
            izq++;
        while (arr[der] > pivote)
            der--;
        if (izq <= der)
        {
            tmp = arr[izq];
            arr[izq] = arr[der];
            arr[der] = tmp;
            izq++;
            der--;
        }
    }

    if (izquierda < der)
        Quicksort(arr, izquierda, der);
    if (izq < derecha)
        Quicksort(arr, izq, derecha);
}

float leer()
{

    string lista[15000];
    int cantidad = 0;
    float tiempoEjecucion;
    char k = 0;

    //PASAMOS DATOS A UN ARREGLO

    if ((fd = fopen("palabras.txt", "rt")) != NULL)
    {

        while (!feof(fd))
        {

            k = fgetc(fd);
            //comprobamos si el caractar esta en mayuscula 
			//y esta entre el rango de las letras mayusculas y minusculas

            if (isupper(k) && (int(k) < 128))
            {
                lista[cantidad] += tolower(k);
            }
            else
            {
                lista[cantidad] += k;
            }

            if (k == '\n')
            {
                cantidad += 1;
            }
        }
    }
    cantidad += 1;

    //EMPESAMOS A CONROLAR EL TIEMPO
    auto start = std::chrono::system_clock::now();

    // ALGORITMO QUICKSORT

    Quicksort(lista, 0, cantidad);

    //TERMINAMOS DE CONTROLAR EL TIEMPO

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<float, std::milli> duration = end - start;

    tiempoEjecucion = duration.count();
    tiempoEjecucion /= 1000;

    //MOSTRAMOS DATOS DEL ARREGLO ORDENADO

   char resp[3];
	cout<<"¿desea ver la lista ordenada? si/no\n";
		fflush(stdin);
	cin.getline(resp, 3, '\n');
	if (strcmp(resp, "si")==0)
	{
		display(lista, cantidad);
	}

    return tiempoEjecucion;
}

int main()
{
    setlocale(LC_CTYPE, "Spanish");

    int opt;
    float tiempo;
    do
    {
        cout << "1.leer\n2.salir ";
        cin >> opt;
        switch (opt)
        {
        case 1:
            tiempo = leer();
            cout << "ALGORITMO QUICKSHORT\n";
            cout << "tiempo de ejecucion: " << tiempo << " segundo" << endl;
            break;
        case 2:
            break;
        }
    } while (opt != 2);
    return 0;
}
