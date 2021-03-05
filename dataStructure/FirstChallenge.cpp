/*PRIMER ENTREGABLE 
BERNARDO REYES DÍAZ A01021602
JESÚS IMANOL GARCÍA MENDOZA A01652759*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

/*A CONTINUACIÓN SE CREA LA CLASE DONDE SE GUARDARÁ TODO EL REGISTRO DE DATOS,
SE CREAN ATRIBUTOS POR CADA CATEGORÍA DE DATO
SE CREAN MÉTODOS PARA MANIPULAR ESTOS DATOS*/
using namespace std;
class Record{
	public:
	string fecha;
	string hora;
    string companiaIP;
    string dnsInterno;
	string nombreFuente;
    string destinoIP;
    string puertoDestino;
	string nombreDestino;
    int puertoDestino2;
	
	Record(string f, string h, string cIP, string dnsI, string nF, string desIP, string pD, string nD){
		fecha=f;
		hora=h;
        companiaIP=cIP;
        dnsInterno=dnsI;
		nombreFuente=nF;
        destinoIP=desIP;
        puertoDestino=pD;
		nombreDestino=nD;
        if (pD=="-"){
            puertoDestino2=0;
            
        }
        else {
            puertoDestino2=stoi(pD);
        }
	}
	
	void imprimirRecordFuente(){
		cout<<nombreFuente<<endl;
    }
    void imprimirRecordPuerto(){
		cout<<puertoDestino<<endl;
	}

    void imprimirRecordFecha(){
		cout<<fecha<<endl;
    }

    int sumaRegistrosDia2(){
        int count = 0;
        if (fecha == "11-8-2020"){
            count+=1;
        }
        return count;
    }
    
	
};
/*AQUÍ SE CREA UNA INSTANCIA DE VECTOR PARA JALAR LOS DATOS 
Y ACOMODARLOS DE MANERA MÁS ESTRUCTURADA EN BLOQUES POR LINEA*/
vector<Record> conexiones;
void leerDatos(string path){
	ifstream fileIn;
	fileIn.open(path);
	string line, partes;
	vector<string> valores;
	while(getline(fileIn, line)){
		istringstream sIn(line);
		while(getline(sIn, partes, ',')){
			valores.push_back(partes);
		}
		if(valores[7].find('\r')!=valores[7].npos){
			valores[7]=valores[7].substr(0, valores[7].size()-1);
		}
		Record r(valores[0], valores[1], valores[2], valores[3], valores[4], valores[5], valores[6], valores[7]);
		conexiones.push_back(r);
		valores.clear();
	}
}
/*EL SIGUIENTE BLOQUE DE CÓDIGO CONTIENE UNA SERIE DE FUNCIONES QUE VAN A SERVIR PARA 
ORDENAR LOS DATOS DE VARIAS MANERAS PARA PODER MANIPULAR LOS DATOS Y HACER BÚSQUEDAS DE
FORMA MÁS CONVENINETE*/
int compararPorNombreFuente(Record a, Record b){
	if(a.nombreFuente<b.nombreFuente){
		return -1;
	}else if (a.nombreFuente==b.nombreFuente){
		return 0;
	}else{
		return 1;
	}
}

int compararPorNombreDestino(Record a, Record b){
	if(a.nombreDestino<b.nombreDestino){
		return -1;
	}else if (a.nombreDestino==b.nombreDestino){
		return 0;
	}else{
		return 1;
	}
}

int compararPorFecha(Record a, Record b){
	if(a.fecha<b.fecha){
		return -1;
	}else if (a.fecha==b.fecha){
		return 0;
	}else{
		return 1;
	}
}


string segundoDia(Record a, Record b){
	if(a.fecha<b.fecha){
		return b.fecha;
	}
}


int compararPorPuertoDestino(Record a, Record b){
	if(a.puertoDestino<b.puertoDestino){
		return -1;
	}else if (a.puertoDestino==b.puertoDestino){
		return 0;
	}else{
		return 1;
	}
}
/*EN ESTE BLOQUE DE CÓDIGO SE GENERAN DOS CLASES QUE SIRVEN PARA ORDENAR LOS DATOS 
DE MANERA LEXICOGRÁFICA O NÚMERICA DEPENDIENDO DEL TIPO DE DATO A ORDENAR*/
template <class T>
class Sort{
	public:
	virtual void sort(vector<T> &data, int comparador(T a, T b))=0;
	void intercambiar(vector<T> &data, int posI, int posJ){
		T temp=data[posI];
		data[posI]=data[posJ];
		data[posJ]=temp;
	}
	
	void imprimir(vector<T> data){
		for(int i=0; i<data.size(); i++){
			cout<<data[i]<<",";
		}
		cout<<endl;
	}
};

template <class T>
class MergeSort: public Sort<T>{
	
	public:
	void sort(vector<T> &data, int comparador(T a, T b)){
		sortAux(data, 0, data.size()-1, comparador);
	}
	private:
	void sortAux(vector<T> &data, int lo, int hi, int comparador(T a, T b)){
		if(lo>=hi){
			return;
		}
		int mid=(lo+hi)/2;
		sortAux(data, lo, mid, comparador);
		sortAux(data, mid+1, hi, comparador);
		merge(data, lo, mid, hi, comparador);
	}
	
	void merge(vector<T> &data, int low, int mid, int hi, int comparador(T a, T b)){
	int sizeA=mid-low+1;
	int sizeB=hi-mid;
	vector<T> copiaA;
	vector<T> copiaB;
	
	for(int i=0; i<sizeA; i++){
		copiaA.push_back(data[low+i]);
	}
	
	for(int i=0; i<sizeB; i++){
		copiaB.push_back(data[mid+i+1]);
	}
	
	int indexA=0;
	int indexB=0;
	int indexData=low;
	while(indexA<sizeA&&indexB<sizeB){
		if(comparador(copiaA[indexA],copiaB[indexB])<0){
			data[indexData]=copiaA[indexA];
			indexA++;
		}else{
			data[indexData]=copiaB[indexB];
			indexB++;
		}
		indexData++;
	}
	
	while(indexA<sizeA){
		data[indexData]=copiaA[indexA];
		indexA++;
		indexData++;
	}
	
	while(indexB<sizeB){
		data[indexData]=copiaB[indexB];
		indexB++;
		indexData++;
	}
}
	
};

/*EL SIGUIENTE BLOQUE DE CÓDIGO CONTIENE UNA SERIE DE FUNCIONES QUE VAN A SERVIR PARA 
COMPARAR LOS DATOS Y HACER BÚSQUEDAS DE FORMA QUE PODAMOS BUSCAR CUALQUIER TIPO DE DATO 
CON LA HABILIDAD DE DETERMINAR ESPECÍFICAMENTE UN DATO DE FORMA MÁS CONVENINETE*/
int compararPorNombreDestino2(Record a, string b){
	if(a.nombreDestino<b){
		return -1;
	}else if (a.nombreDestino==b){
		return 0;
	}else{
		return 1;
	}
}

int compararPorNombreFuente2(Record a, string b){
	if(a.nombreFuente<b){
		return -1;
	}else if (a.nombreFuente==b){
		return 0;
	}else{
		return 1;
	}
}

int compararPorPuertoDestino2(Record a, int b){
	if(a.puertoDestino2<b){
		return -1;
	}else if (a.puertoDestino2==b){
		return 0;
	}else{
		return 1;
	}
}

int compararPorPuertoDestino3(Record a, Record b){
	if(a.puertoDestino2<b.puertoDestino2){
		return -1;
	}else if (a.puertoDestino2==b.puertoDestino2){
		return 0;
	}else{
		return 1;
	}
}

int compararPorFecha(Record a, string b){
	if(a.fecha<b){
		return -1;
	}else if (a.fecha==b){
		return 0;
	}else{
		return 1;
	}
}

/*ESTA FUNCION HACE LA BÚSQUEDA CON UN MÉTODO BINARIO PUES LAS FUNCIONES ANTERIORES NOS SIRVEN PARA ORDENAR
LOS DATOS Y QUE PUEDA FUNCIONAR ESTE TIPO DE BÚSQUEDA*/
template <class T, class M>
int busquedaBinaria2(vector<T> a, M buscado, int comparador(T a, M b)){
	int inicio=0;
	int fin=a.size()-1;
	while(fin>=inicio){
		int medio=(inicio+fin)/2;
		if(comparador(a[medio],buscado)==0){
			return medio;
		}else if(comparador(a[medio], buscado)<0){
			inicio=medio+1;
		}else{
			fin=medio-1;
		}
	}
	return -1;
}
 
//AQUÍ SE RESUELVEN LAS PREGUNTAS ESPECÍFICAS PARA EL RETO
int main(){
	leerDatos("/mnt/c/Users/Bernardo Reyes Díaz/Desktop/equipo2.csv");
	cout<<"Datos leidos"<<endl;
	MergeSort<Record> destinoOrden;
	destinoOrden.sort(conexiones, compararPorNombreDestino);
//PREGUNTA 1
    cout<<"la cantidad de registros es: "<<conexiones.size()<<endl;
	cout<<"Datos ordenados por destino"<<endl;
//PREGUNTA 6
    string gMail= "gmail.com";
    int posGMail=busquedaBinaria2(conexiones, gMail, compararPorNombreDestino2);
    if(posGMail!=-1){
		cout<<"utilizan gmail.com"<<endl;
	}
    else { 
        cout<<"ningun registro va a gmail.com"<<endl;
    }

    string oMail= "outlook.com";
    int posOMail=busquedaBinaria2(conexiones, oMail, compararPorNombreDestino2);
    if(posOMail!=-1){
		cout<<"utilizan outlook.com"<<endl;
	}
    else { 
        cout<<"ningun registro va a outlook.com"<<endl;
    }

    string pMail= "protonmail.com";
    int posPMail=busquedaBinaria2(conexiones, pMail, compararPorNombreDestino2);
    if(posPMail!=-1){
		cout<<"utilizan protonmail.com"<<endl;
	}
    else { 
        cout<<"ningun registro va a protonmail.com"<<endl;
    }

    string freeMail= "freemailserver.com";
    int posFreeMail=busquedaBinaria2(conexiones, freeMail, compararPorNombreDestino2);
    if(posFreeMail!=-1){
		cout<<"utilizan freemailserver.com"<<endl;
	}
    else { 
        cout<<"ningun registro va a freemailserver.com"<<endl;
    }

	string serv= "server.reto.com";
    int posServ=busquedaBinaria2(conexiones, serv, compararPorNombreDestino2);
    if(posServ!=-1){
		cout<<"utilizan server.reto.com"<<endl;
	}
    else { 
        cout<<"ningun registro va a server.reto.com"<<endl;
    }
//PREGUNTA 3
    MergeSort<Record> fuenteOrden;
	fuenteOrden.sort(conexiones, compararPorNombreFuente);
	cout<<"Datos ordenados por fuente"<<endl;
    string j= "jeffrey.reto.com";
    int pos2=busquedaBinaria2(conexiones, j, compararPorNombreFuente2);
    if(pos2!=-1){
		cout<<"encontrado"<<endl;
	}
    else { 
        cout<<"ninguna computadora pertence a Jefrrey."<<endl;
    }
    string b= "betty.reto.com";
    int pos3=busquedaBinaria2(conexiones, b, compararPorNombreFuente2);
    if(pos3!=-1){
		cout<<"encontrado"<<endl;
	}
    else { 
        cout<<"ninguna computadora pertence a Betty."<<endl;
    }

    string k= "katherine.reto.com";
    int pos4=busquedaBinaria2(conexiones, k, compararPorNombreFuente2);
    if(pos4!=-1){
		cout<<"encontrado"<<endl;
	}
    else { 
        cout<<"ninguna computadora pertence a Katherine."<<endl;
    }

    string s= "scott.reto.com";
    int pos5=busquedaBinaria2(conexiones, s, compararPorNombreFuente2);
    if(pos5!=-1){
		cout<<"encontrado"<<endl;
	}
    else { 
        cout<<"ninguna computadora pertence a Scott."<<endl;
    }

    string be= "benjamin.reto.com";
    int pos6=busquedaBinaria2(conexiones, be, compararPorNombreFuente2);
    if(pos6!=-1){
		cout<<"encontrado"<<endl;
	}
    else { 
        cout<<"ninguna computadora pertence a Benjamin."<<endl;
    }

    string sa= "samuel.reto.com";
    int pos7=busquedaBinaria2(conexiones, sa, compararPorNombreFuente2);
    if(pos7!=-1){
		cout<<"encontrado"<<endl;
	}
    else { 
        cout<<"ninguna computadora pertence a Samuel."<<endl;
    }

    string r= "raymond.reto.com";
    int pos8=busquedaBinaria2(conexiones, r, compararPorNombreFuente2);
    if(pos8!=-1){
		cout<<"encontrado"<<endl;
	}
    else { 
        cout<<"ninguna computadora pertence a Raymond."<<endl;
    }
//PREGUNTA 5
    string server= "server.reto.com";
    int pos9=busquedaBinaria2(conexiones, server, compararPorNombreFuente2);
    if(pos9!=-1){
		cout<<"encontrado"<<endl;
	}
    else { 
        cout<<"ninguna computadora se llama server.reto.com."<<endl;
    }
//PREGUNTA 7
    MergeSort<Record> puertoOrden;
	puertoOrden.sort(conexiones, compararPorPuertoDestino3);
	cout<<"Datos ordenados por puerto de destino como ints"<<endl;
    for (int puerto=1; puerto<1000; puerto++){
		int datoPuerto = busquedaBinaria2(conexiones, puerto, compararPorPuertoDestino2);
        if (datoPuerto != -1){
            cout<<puerto<<endl;
        }
    }
//PREGUNTA 2
    MergeSort<Record> fechaOrden;
	fechaOrden.sort(conexiones, compararPorFecha);
	cout<<"Datos ordenados por fecha"<<endl;
    int nCount = 0;
    for (int i=0; i<conexiones.size(); i++){
		conexiones[i].sumaRegistrosDia2();
        if (conexiones[i].sumaRegistrosDia2() == 1){
            nCount += 1;
        }
	}
     cout<<"cantidad de registros el segundo día: "<<nCount<<endl;
    
		//conexiones[i].imprimirRecordFecha();
    
    /*if (r.puertoDestino < 1000){
        for (int i=0; i<conexiones.size(); i++){
		conexiones[i].imprimirRecordPuerto();
    }*/


	return 0;
}