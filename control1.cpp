#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 

using namespace std;

struct Estacion {
  int id;
  int linea;
  string Abrev;
  string nombre;
  int terminal;
  int combinacion;
  int direccion;
  int direccion1;
};

//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	vector <Estacion> metro;
	string argumento=argv[1];
	string Minicial=argv[2];
	string Mdestino=argv[3];
	int in,fin;

	if(argc==4)
	{
		if(argumento=="-v")
		{
			cout<<"Victor Gomez Espinosa"<<endl;
			cout<<"Fabian Cancino Riquelme"<<endl;

		}
		else
		{
			if(argumento=="-f")
			{
				Llenado(metro);
				if(BusquedaEstaciones(metro,Minicial,Mdestino,&in,&fin)==2)
				{	
					////////////////////////////////////////
					for(int i=0;i<metro.size();i++) // aca buscamos las estaciones Terminales
					{
						if(metro[i].id!=0)
						{
							if(metro[i-1].id==0 || metro[i+1].id==0)
							{
								metro[i].terminal=1;
							}
							else
							{
								metro[i].terminal=0;
							}
						}
					}
				////////////////////////////////////////////
					
					for(int i=0;i<metro.size();i++) // busqueda de direcciones en la que avanza
					{
							if(metro[i].id!=0)
							{
								metro[i].direccion= metro[i+1].id;
								metro[i].direccion1= metro[i-1].id;
							}
					}
				////////////////////////////////////////////
					
					for(int i=0;i<metro.size();i++) // busqueda de combinacioninaciones
					{
						for(int j=0;j<metro.size();j++)
						{
							if(i!=j && metro[i].id!=0 && metro[j].id!=0 )
							{
								if(metro[i].nombre==metro[j].nombre && metro[i].combinacion==0)
								{
									metro[i].combinacion=metro[j].linea;
									metro[j].combinacion=metro[i].linea;
								}
							}
						}
					}
				////////////////////////////////////////////	
					
					string camino=metro[in].nombre; // Usamos para buscar el recorrido
					vector <string> auxiliar;
					vector <int> valores;
					int contAux=0,min=10000,ind;

					if(in==fin)
					{
						cout<<metro[in].nombre<<endl;
					}
					else
					{
						BusquedaSigEst(metro,&contAux,camino,in,fin,auxiliar,valores); // funcion que busca la sigt estacion
						for(int i=0;i<valores.size();i++)
						{
							if(valores[i]<min)
							{
								min=valores[i];
								ind=i;
							}
						}
						cout<<auxiliar[ind]<<endl;
					}
				////////////////////////////////////////////
				}
				else
				{
					cout<<"Codigos de estacion erroneos"<<endl;
				}
			}
			else
			{
				cout<<"Entrada no correspondiente"<<endl;
			}
		}
	}
	else
	{
		cout<<"Los datos ingresados son erroneos"<<endl;
	}
}