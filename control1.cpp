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


void Llenado(vector <Estacion> &metro)
{
	Estacion aux;
	string l,auxStr,auxStr2;
	int posicion,cont=1,lineaAux;
	ifstream fixero("Lineas.csv");
	while(!fixero.eof())
	{
		getline(fixero,l);
		posicion=l.find(" ");
		auxStr = l.substr(0,posicion);
		posicion=l.find(" ")+1;
		auxStr2 =l.substr(posicion);
		posicion=auxStr2.find(" ");
		if(auxStr=="Línea")
		{
			posicion=auxStr2.find(" ");
			auxStr2=auxStr2.substr(0,posicion);
			if(auxStr2=="4a")
			{
				lineaAux=3;
			}
			else
			{
				lineaAux=atoi(auxStr2.c_str());
			}
			aux.id=0;
			aux.linea=0;
			aux.nombre="";
			aux.Abrev="";
			aux.combinacion=0;
			metro.push_back(aux);
		}
		else
		{
			aux.id=cont;
			aux.linea=lineaAux;
			aux.nombre=auxStr2;
			aux.Abrev=auxStr;
			aux.combinacion=0;
			cont++;
			metro.push_back(aux);
		}
	}
	metro.pop_back();
	Estacion aux2;
	aux2.id=0;
	aux2.linea=0;
	aux2.nombre="";
	aux2.Abrev="";
	aux2.combinacion=0;
	metro.push_back(aux2);
}



int BusquedaEstaciones(vector <Estacion> &metro, string Inicio, string Destino, int *inicio, int *final)
{
	int x=0;
	for(int i=0;i<metro.size();i++)
	{
		if(metro[i].id!=0 && metro[i].Abrev==Inicio)
		{
			*inicio=i;
			x++;
		}
		if(metro[i].id!=0 && metro[i].Abrev==Destino)
		{
			*final=i;
			x++;
		}
	}
	return x;
}




void BusquedaSigEst(vector <Estacion> &metro, int *cont, string &cam, int inic, int des, vector <string> &posibles, vector <int> &valores)
{
	int movimiento1,movimiento2,contador1,contador2,aux1=0,aux2=0;
	string recorrido1,recorrido2,can;
	if(*cont>50)
	{
		*cont=1000;
	}
	else
	{
		contador1=*cont;
		recorrido1=cam;
		movimiento1=inic+1;
		while(metro[movimiento1].id!=0 && aux1==0)
		{
			contador1++;
			recorrido1=recorrido1+"->"+metro[movimiento1].nombre;
			if(movimiento1==des)
			{
				aux1=1;
				posibles.push_back(recorrido1);
				valores.push_back(contador1);
			}
			else
			{
				if(metro[movimiento1].combinacion!=0)
				{
					for(int i=0;i<metro.size();i++)
					{
						if(metro[movimiento1].nombre==metro[i].nombre && movimiento1!=i)
						{
							if(metro[i].nombre==metro[des].nombre)
							{
								aux1=1;
								posibles.push_back(recorrido1);
								valores.push_back(contador1);
							}
							else
							{
								BusquedaSigEst(metro,&contador1,recorrido1,i,des,posibles,valores);
							}
						}
					}
				}
			}
			movimiento1++;
		}
		contador2=*cont;
		recorrido2=cam;
		movimiento2=inic-1;
		while(metro[movimiento2].id!=0 && aux2==0)
		{
			contador2++;
			recorrido2=recorrido2+"->"+metro[movimiento2].nombre;
			if(movimiento2==des)
			{
				posibles.push_back(recorrido2);
				valores.push_back(contador2);
				aux2=1;
			}
			else
			{
				if(metro[movimiento2].combinacion!=0)
				{
					for(int i=0;i<metro.size();i++)
					{
						if(metro[movimiento2].nombre==metro[i].nombre && movimiento2!=i)
						{
							if(metro[i].nombre==metro[des].nombre)
							{
								posibles.push_back(recorrido2);
								valores.push_back(contador2);
								aux2=1;
							}
							else
							{
								BusquedaSigEst(metro,&contador2,recorrido2,i,des,posibles,valores);
							}
						}
					}
				}
			}
			movimiento2--;
		}
	}
}



int main(int argc, char* argv[])
{
	vector <Estacion> metro;
	string argumento=argv[1];
	int in,fin;

		if(argumento=="-v")
		{
			cout<<"Victor Gomez Espinosa"<<endl;
			cout<<"Fabian Cancino Riquelme"<<endl;

		}
		else
		{
			if(argumento=="-f")
			{	string Minicial=argv[2];
			 	string Mdestino=argv[3];
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
