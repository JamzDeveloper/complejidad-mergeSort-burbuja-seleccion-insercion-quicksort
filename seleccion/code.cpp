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
		cout << array[i] << endl;
}

void seleccion(string *lista, int cantidad)
{

	string temporal;
	int min;
	for (int i = 0; i < cantidad; i++)
	{
		min = i;
		for (int j = i + 1; j < cantidad; j++)
		{
			if (lista[j] < lista[min])
			{
				min = j;
			}
		}
		temporal = lista[i];
		lista[i] = lista[min];
		lista[min] = temporal;
	}
}
float leer()
{

	string lista[15000];
	int cantidad = 0;
	float tiempoEjecucion;
	char k = 0;
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

	
	
	// CODIGO DE SELECCION
	seleccion(lista, cantidad);

	//TERMINAMOS DE CONTROLAR EL TIEMPO
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<float, std::milli> duration = end - start;

	tiempoEjecucion = duration.count();
	tiempoEjecucion /= 1000;

	///MOSTRAMOS EN PANTALLA
	char resp[3];
	cout << "¿desea ver la lista ordenada? si/no\n";
	fflush(stdin);
	cin.getline(resp, 3, '\n');
	if (strcmp(resp, "si") == 0)
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
		cout << "1.leer\n2.salir\nopcion: ";
		cin >> opt;
		switch (opt)
		{
		case 1:
			tiempo = leer();
			cout << "ALGORITMO DE SELCCION\n";
			cout << "tiempo de ejecucion: " << tiempo << " segundo" << endl;
			break;
		case 2:
			break;
		}
	} while (opt != 2);
	return 0;
}
