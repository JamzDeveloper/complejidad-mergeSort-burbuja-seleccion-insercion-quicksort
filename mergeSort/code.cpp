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


void merge(string *array, int inicio, int media, int fin)
{
	int i, j, k, tamDerecho, tamIzquierdo;

	tamIzquierdo = media - inicio + 1;
	tamDerecho = fin - media;
	string arrIzquierdo[tamIzquierdo], arrDerecho[tamDerecho];


	for (i = 0; i < tamIzquierdo; i++)
		arrIzquierdo[i] = array[inicio + i];

	for (j = 0; j < tamDerecho; j++)
		arrDerecho[j] = array[media + 1 + j];
	i = 0;
	j = 0;
	k = inicio;


	while (i < tamIzquierdo && j < tamDerecho)
	{
		if (arrIzquierdo[i] <= arrDerecho[j])
		{
			array[k] = arrIzquierdo[i];
			i++;
		}
		else
		{
			array[k] = arrDerecho[j];
			j++;
		}
		k++;
	}
	while (i < tamIzquierdo)
	{
		array[k] = arrIzquierdo[i];
		i++;
		k++;
	}
	while (j < tamDerecho)
	{
		array[k] = arrDerecho[j];
		j++;
		k++;
	}
}

void mergeSort(string *array, int inicio, int fin)
{
	int media;
	if (inicio < fin)
	{
		int media = inicio + (fin - inicio) / 2;
		
		mergeSort(array, inicio, media);
		mergeSort(array, media + 1, fin);
		merge(array, inicio, media, fin);
	}
}

float leer()
{

	string lista[15000];
	int cantidad = 0;
	char k = 0;
	float tiempoEjecucion;

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

	///METODO NERGESORT
	mergeSort(lista, 0, cantidad);

	//TERMINAMOS DE CONTROLAR EL TIEMPO
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<float, std::milli> duration = end - start;

	tiempoEjecucion = duration.count();
	tiempoEjecucion /= 1000;

	///MOSTRAMOS EN PANTALLA

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
	float tiempo;
	int opt;
	do
	{
		cout << "\n1.leer\n2.salir\nopcion: ";
		cin >> opt;
		switch (opt)
		{
		case 1:
			tiempo = leer();
			cout << "ALGORITMO MERGESORT\n";
			cout << "tiempo de ejecucion: " << tiempo << " segundo" << endl;
			break;
		case 2:
			break;
		}
	} while (opt != 2);
	return 0;
}