#ifndef _MATRIX_
#define _MATRIX_
#include <stdio.h>

void CreateMatrix( double ***pMatrix, int size ); //tworzenie macierzy kwadratowej size x size
void PrintMatrix( double **pMatrix, int size );   // wypisanie macierzy
void ReadMatrix( FILE* plik, double **pMatrix, int size ); // odczytanie macierzy z pliku i wpisanie do tablicy 2D
void TransponseMatrix( double **pMatrix, int size ); // transponowanie macierzy
void DeleteMatrix( double ***pMatrix, int size ); // usuwanie macierzy
double Determinant( double **pMatrix, int size ); // obliczenie wyznacznika
void InverseMatrix( double **pMatrix, double **pTab, int size, double det ); // obliczenie macierzy odwrotnej
void Complement( double **pTab, double **pMatrix, int nRow, int nCol, int size ); // wypisanie macierzy po wykresleniu odpowiedniego wiersza i kolumny
void ComplMatrix( double **pTabI, double **pTabD, int size ); // obliczenie macierzy dopelnien algebraicznych
void WriteMatrix( double **pMatrix, int size, FILE *plik ); // wpisanie wyniku macierzy odw do pliku

#endif