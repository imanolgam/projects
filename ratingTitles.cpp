//pelicula=film
//
#include <stdlib.h>
#include <ctime> 
#include <iostream>

using namespace std;
#pragma once

class Video
{
protected:
    int ID;
    string nombre;
    string genero;
    float calificacion;
public:
    Video(int,string,string,float);
    virtual void mostrar();
    virtual void calificar();
};

class Pelicula : public Video
{
protected:
    string duracion;
public:
    Pelicula(int,string,string,float,string);
    void mostrar();
    void calificar();
};

class Serie : public Video
{
protected: 
    int num_temporadas;
public:
    Serie(int,string,string,float,int);
    void mostrar();
    void calificar();
};

class Temporadas : public Serie
{
protected: 
    int num_temporada;
    int num_capitulos;
    string capitulos;
public:
    Temporadas(int,string,string,float,int,int,int,string);
    void mostrar();
    void calificar();
};

Video::Video(int _ID,string _nombre, string _genero, float _calificacion){
    ID = _ID;
    nombre = _nombre;
    genero= _genero;
    calificacion= _calificacion;
}
void Video::mostrar(){
    cout<<"ID: "<<ID<<endl;
    cout<<"Nombre: "<<nombre<<endl;
    cout<<"Género: "<<genero<<endl;
    cout<<"Calificación: "<<calificacion<<" de 5"<<endl;
}

void Video::calificar(){
    float estrellas=0;
    cout<<"What qualification do you giive to this title? Being 1 the min and 5 the max number"<<endl;
    cin>>estrellas; 
    calificacion=estrellas;
}

Pelicula::Pelicula(int _ID,string _nombre,string _genero, float _calificacion, string _duracion) : Video(_ID,_nombre,_genero,_calificacion)
{
    duracion = _duracion;
}
void Pelicula::mostrar()
{
    Video::mostrar();
    cout<<"Duracion: "<<duracion<<endl;
}
void Pelicula::calificar()
{
    Video::calificar();
}

Serie::Serie(int _ID,string _nombre,string _genero, float _calificacion, int _num_temporadas) : Video(_ID,_nombre,_genero,_calificacion)
{
    num_temporadas = _num_temporadas;
}
void Serie::mostrar()
{
    Video::mostrar();
    cout<<"Número de temporadas: "<<num_temporadas<<endl;
}
void Serie::calificar()
{
    Video::calificar();
}

Temporadas::Temporadas(int _ID,string _nombre,string _genero, float _calificacion, int _num_temporadas, int _num_temporada, int _num_capitulos,string _capitulos) : Serie(_ID,_nombre,_genero,_calificacion,_num_temporadas)
{
    num_temporada = _num_temporada;
    num_capitulos = _num_capitulos;
    capitulos = _capitulos;
}
void Temporadas::mostrar()
{
    Serie::mostrar();
    cout<<"Temporada número: "<<num_temporada<<endl;
    cout<<"Número de capitulos de la temporada: "<<num_capitulos<<endl;
    cout<<"Nombre de los capitulos: "<<capitulos<<endl;
}
void Temporadas::calificar()
{
    Video::calificar();
}

int main()
{
    string respuesta;
    int answer;
    string n="si";
    Video *vector[3];
    vector[0]=new Pelicula (2564,"Fight Club","action",4.5,"1:33");
    vector[1]=new Pelicula (2324,"Avengers:Endgame","superheroes, adventure",5,"2:55");
    vector [2]=new Temporadas (2323,"Suits","business",4.8,1,1,3,"\n 1. Back to the future \n 2. Zane vs Zane \n 3. Specter came back");
    vector [3]=new Temporadas (4545,"The Good Doctor","science, research",4.6,1,1,4,"\n 1. The big find\n 2. You won't be able with him\n 3. The Great Pain\n 4. The great catastrophe");
    cout<<"List of movies:\n1. Fight club\n2. Avengers:Endgame\n\nList of series: series:\n3. Suits\n4. The Good Doctor"<<endl;
    cout<<"\n";
    cout<<"Would you like to rate some of this litles? Escribe si o no"<<endl;
    cin>>respuesta;
    while (n=="si")
    {
        if (respuesta=="si")
        {
            cout<<"Write the number of the title you would like to rate according to the printed list"<<endl;
            cin>>answer;
            if (answer ==1)
            {
                vector[0]->calificar();
            }
            else if (answer==2)
            {
                vector[1]->calificar();
            }
            else if (answer==3)
            {
                vector[2]->calificar();
            }
            else if (answer==4)
            {   
                vector[3]->calificar();
            }
        }
        cout<<"Would you like to rate more titles? si/no"<<endl;
        cin>>n;
    }
    vector [0]->mostrar();
    cout<<"\n";
    vector [1]->mostrar();
    cout<<"\n";
    vector[2]->mostrar();
    cout<<"\n";
    vector [3]->mostrar();
    delete [] vector[3];
    return 0;
}
