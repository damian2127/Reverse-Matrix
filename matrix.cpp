#include "matrix.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

//====================  KREOWANIE MACIERZY   ========================================================================
void CreateMatrix( double*** pMatrix, int size )
{
	double **p = *pMatrix = ( double** )malloc( size * ( sizeof(double *) )); // uzyc calloca

	if ( *pMatrix )                                             // jesli pamiec jest dobrze zaalokowana
	{
		for ( int i = 0; i < size; i++,p++ )
		{                                                      
			*p = ( double* )malloc( ( sizeof(double) ) *size); 
			memset( *p, 0, sizeof( double ) * size );          // zainicjuj element wiersza
		}
	}
	else
	{
		printf("No memory! \n");
	}
}

//============  WYPISANIE MACIERZY  ================================================================================

void PrintMatrix( double** pMatrix, int size )
{
	printf("\n");

	double **w = pMatrix;

	for ( int i = 0; i < size; i++, w++ )
	{
		double *p = *w; // *p to pierwsze element wiersza **w ( wskazuje na poczatek tablicy w ktorej jest size elementow tego wiersza )

		for ( int j = 0; j < size; j++)
		{
		
			printf( "%.2lf ", *p++ );	// wypisuje dany element wiersza **w
		                 // zwiekszam element wiersza **w
		}
		printf("\n");
	}
}

//=================  WPISANIE ZAWARTOSCI PLIKU DO MACIERZY  ==========================================================================

void ReadMatrix( FILE *plik , double **pMatrix, int size )
{
	fgetc( plik );                                  //Funkcja odczytuje jeden znak ze wskazanego strumienia. Zwraca kod odczytanego znaku w przypadku sukcesu.

	double **p = pMatrix;

	for ( int i = 0; i < size; i++, p++)
	{
		double *v = *p;                             // *v to wsk na element wiersza **p

		for ( int j = 0; j < size; j++, v++)
		{
			fscanf( plik, "%lf", v );               // czytam kolejny znak z pliku i zapisuje pod adresem ( v )
		}
	}

	fclose( plik ); // zamykam plik bo dane zostaly zapisane w macierzy
}

//===================   OBLICZAM WYZNACZNIK MACIERZY   ==============================================================================

double Determinant( double **pMatrix, int size )
{
	if ( size == 1 )                 // jesli jest macierz 1x1
	{
		return pMatrix[0][0];
	}
	else if ( size == 2 )            // jesli jest macierz 2x2
	{
		return ( ( pMatrix[0][0] * pMatrix[1][1] ) - ( pMatrix[0][1] * pMatrix[1][0] ) );
	}

	double **temp = NULL;           // tablica pomocnicza 2D

	CreateMatrix( &temp, size - 1 ); // o rozmiarze size - 1
	
	double res = 0;
	double x = 1;
	double **p = pMatrix;            // **p wskazuje na pierwszy element danego wiersza

	for ( int i = 0; i < size; i++, p++ )
	{	
		double *v = *p;              // pierwszy znak wiersza           
		Complement( temp, pMatrix, i, 0, size );    // rozwiniecie La'Place
		res = res + (*v) * (x) * ( Determinant( temp, size - 1 ) );     //rekurencyjne wywolanie
		x = -x;
	}

	DeleteMatrix( &temp, size - 1 ); // usuwam pomocnicza tablice
	
	return res; // zwracam wartosc wyznacznika
}

//=====================  TWORZY MACIERZ PO WYKRESLENIU ODPOWIEDNIEJ KOLUMNY I WIERSZA ( potrzebne do wyznacznika )   =========================

void Complement( double **pTab, double **pMatrix, int nRow, int nCol, int size )
{
	double **p1 = pMatrix;               // **p1 wskazuje na pierwszy element pierwszego wiersza macierzy odwracanej
	double **p2 = pTab;                  // **p2 wskazuje na pierwszy element macierzy pomocniczej po wykresleniu wiersza i kolumny

	for ( int i = 0; i < size; i++, p1++ )
	{
		if ( i == nRow )                // pominiemy wykonywanie petli for gdy trafimy na wykreslony wiersz
		{
			continue;
		}
		
		double *v1 = *p1;               // v1 i v2 wskazuja na odpowiednie elementy wierszy pMatrix i pTab
		double *v2 = *p2;

		for ( int j = 0; j < size; j++, v1++ )
		{
			if ( j == nCol )              //pominiemy wykonywanie petli for gdy trafimy na wykreslona kolumne
			{
				continue;
			}
			
			*v2 = *v1;               //przypisuje do pTab odpowiedni element macierzy

			v2++;                    // przechodze do kolejnego elementu
		}

		p2++;                           // przechodzimy do kolejnego wiersza gdy wypelnimy poprzedni	
	}
}

//==============  TRANSPONOWANIE MACIERZY   ===================================================================

void TransponseMatrix( double** pMatrix, int size )
{
	double **p = pMatrix;               // **p wskazuje na pierwsze elementy kazdego z wierszy

	for ( int i = 0; i < size; i++, p++)
	{
		double *v = (*p + i + 1);       // tu bedzie kolejny element danego wiersza

		for ( int j = i + 1; j < size; j++, v++)
		{
			double temp = *v;           // podmieniam odpowiednie elementy
			*v = pMatrix[j][i];
			pMatrix[j][i] = temp;
		}
	}
}

//==============    USUWANIE MACIERZY    ==================================================================================

void DeleteMatrix(double ***pMatrix, int size)
{
	double **w = *pMatrix;               // wsk na pierwszy element wiersza
	
	if ( w )                             // jesli jest jeszcze jakis wiersz
	{
		for ( int i = 0; i < size; i++, w++ )
		{
			free( *w );
		}

		free( *pMatrix );
		*pMatrix = NULL;
	}
	else
	{
		printf(" Matrix is empty! \n");
	}
}

//=============		OBLICZENIE MACIERZY DOPELNIEN ALGEBRAICZNYCH   ====================================================================================

void ComplMatrix( double **pTabI, double **pTabD, int size )
{
	double **pTemp = NULL;          // pomocnicza tablica 2D

	CreateMatrix( &pTemp, size - 1);

	double **p = pTabD;             // macierz dla ktorej elementow bede liczyl dopelnienia

	for ( int i = 0; i < size; i++, p++ )
	{
		double *v = *p;            // bedzie wskazywac na element wiersza
		
		double temp = (!(i % 2)) ? 1 : -1;     // zbadac parzystosc wiersza!!!!!
		
		for ( int j = 0; j < size; j++, v++ )
		{
			Complement( pTemp, pTabI, i, j, size ); //macierz pomocnicza po wykresleniu odpowiedniej kolumny i wiersza
			*v= temp * Determinant( pTemp, size - 1 ); // przypisuje odpowiednia wartosc do v
			temp = -temp;
		}
	}

	DeleteMatrix( &pTemp, size - 1  );               // usuwam macierz pomocnicza
}

//===============  MACIERZ ODWROTNA    ====================================================================================
void InverseMatrix( double **pMatrix, double **pTab, int size, double det )
{
	//double temp = ( 1 / det );
	
	ComplMatrix( pMatrix, pTab, size );  // obliczam macierz dopelnien algebraicznych
	TransponseMatrix( pTab, size );      // transponuje

	double **p = pTab;
	for ( int i = 0; i < size; i++) // wpisuje macierz odwrotna do nowej macierzy
	{
		double *v = *p;

		for ( int j = 0; j < size; j++)
		{
			*v++ /=  det;
		}
	}
	p++;                          // przechodze do kolejnego wiersza
}

//============  WPISANIE WYNIKU MACIERZY DO PLIKU    ========================================================================

void WriteMatrix( double **pMatrix, int size, FILE *plik )
{
	double **p = pMatrix;

	fprintf(plik,"To macierz odwrotna: \n\n");

	for ( int i = 0; i < size; i++, p++ )
	{
		double *w = *p;     // wsk na odpowiedni element danego wiersza

		for ( int j = 0; j < size; j++, w++)
		{
			fprintf( plik, "%.4lf ", *w );// wpisanie odpowiedniej wartosci do pliku
		}

		fprintf( plik, "\n" ); // wypisuje nowa linie
	}

	fclose( plik ); // zamykam plik w ktorym zapisuje nowa macierz
}