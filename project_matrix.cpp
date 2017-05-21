#include "matrix.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
//#define nDim 4

using namespace std;

int main( int argc, char* argv[] )
{
	//============================================================================================
	
	if( argc != 2 )
	{
		printf("Usage: Dane, size ");
	}


	FILE *plik;

	plik = fopen(argv[1], "r"); // otwieram plik z macierza

	if ( !plik )
	{
		printf("I can't open the file!\n");
		return 0;
	}

	//==================wczytanie rozmiaru tablicy================================================
	int nDim;
	fscanf( plik, "%d", &nDim ); // czytam znak ze strumienia "plik"

	//==================wykreowanie tablicy 2D====================================================
	double **myMatrix = NULL; // tworze macierz
	CreateMatrix( &myMatrix, nDim );
	PrintMatrix( myMatrix, nDim );
	
	//===================wczytanie z pliku do macierzy============================================
	ReadMatrix( plik, myMatrix, nDim );
	PrintMatrix( myMatrix, nDim );

	double **pInv = NULL; // dodatkowa tablica do odwracania
	CreateMatrix( &pInv, nDim );

	//===================obliczenie macierzy odwrotnej=============================================
	InverseMatrix( myMatrix, pInv, nDim, Determinant( myMatrix, nDim ) );
	PrintMatrix( pInv, nDim );

	//==================wpisanie wyniku macierzy do pliku txt======================================
	FILE *wynik;
	wynik = fopen("MatrixResult.txt", "w");

	if ( !wynik )
	{
		printf("I can't open the file!\n");
		return 0;
	}

	WriteMatrix( pInv, nDim, wynik );

	//=================usuniecie macierzy==========================================================
	DeleteMatrix( &myMatrix, nDim );
	DeleteMatrix( &pInv, nDim );

	return 0;
}