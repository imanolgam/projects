#include <stdlib.h>
#include <ctime> 
#include <iostream>

using namespace std;
#pragma once
//clase padre
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
    cout<<"¿Qué calificación le das a este título? Siendo 1 el mínimo y 5 el máximo"<<endl;
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
    vector[0]=new Pelicula (2564,"Club de la Pelea","acción",4.5,"1:33");
    vector[1]=new Pelicula (2324,"Avengers:Endgame","superhéroes, aventura",5,"2:55");
    vector [2]=new Temporadas (2323,"Suits","negocios",4.8,1,1,3,"\n 1. Volviendo al Futuro \n 2. Zane vs Zane \n 3. Specter regresó");
    vector [3]=new Temporadas (4545,"The Good Doctor","ciencia, investigación",4.6,1,1,4,"\n 1. El gran hallazgo\n 2. No podrás con él\n 3. El gran sufrimiento\n 4. La gran catástrofe");
    cout<<"Lista de peliculas:\n1. Club de la Pelea\n2. Avengers:Endgame\n\nLista de series:\n3. Suits\n4. The Good Doctor"<<endl;
    cout<<"\n";
    cout<<"¿Deseas calificar alguno de estos titulos? Escribe si o no"<<endl;
    cin>>respuesta;
    while (n=="si")
    {
        if (respuesta=="si")
        {
            cout<<"Escribe el número de acuerdo a la lista anterior del título que deseas calificar"<<endl;
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
        cout<<"¿Deseas calificar más títulos? si/no"<<endl;
        cin>>n;
    }
    vector [0]->mostrar();
    cout<<"\n";
    vector [1]->mostrar();
    cout<<"\n";
    vector[2]->mostrar();
    cout<<"\n";
    vector [3]->mostrar();
    delete [] vector[3];//Liberar memoria
    return 0;
}