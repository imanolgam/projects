#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <unordered_map>

using namespace std;
class Record{
	public:
	string fecha;
	string hora;
	string ipFuente;
	int puertoFuente;
	string nombreFuente;
	string ipDestino;
	int puertoDestino;
	string nombreDestino;
	
	Record(string f, string h, string iF, string pF, string nF, string iD, string pD, string nD){
		fecha=f;
		hora=h;
		ipFuente=iF;
		if(pF=="-"){
			puertoFuente=0;
		}else{
			
			try{
				puertoFuente=stoi(pF);
			}catch (const std::invalid_argument& ia){
				puertoFuente=0;
				cout<<"error"<<pD<<endl;
			}
		}
		nombreFuente=nF;
		ipDestino=iD;
		if(pD=="-"){
			puertoDestino=0;
		}else{
			try{
				puertoDestino=stoi(pD);
			}catch (const std::invalid_argument& ia){
				puertoDestino=0;
				cout<<"error"<<pD<<endl;
			}
		}
		nombreDestino=nD;
	}
	
	void imprimirRecord(){
		cout<<nombreFuente<<endl;
	}
};

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

class infoConexion{
	public:
	int puertoRemoto;
	string ipRemota;
	string nombreRemoto;
	
	infoConexion(int pR, string ipR, string nR){
		puertoRemoto=pR;
		ipRemota=ipR;
		nombreRemoto=nR;
	}
};


class ConexionesComputadora{
	public:
	string ip;
	string nombre;
	list<infoConexion> entrantes;
	list<infoConexion> salientes;
	
	ConexionesComputadora(){
	
	}
	
	ConexionesComputadora(string ip, string nombre){
		this->ip=ip;
		this->nombre=nombre;
	}
	
	void nuevaEntrante(int puerto, string ip, string nombre){
		infoConexion a(puerto, ip, nombre);
		entrantes.push_front(a);
	}
	
	void nuevaSaliente(int puerto, string ip, string nombre){
		infoConexion a(puerto, ip, nombre);
		salientes.push_back(a);
	}
};


int main(){
	leerDatos("/mnt/c/Users/Bernardo Reyes Díaz/Desktop/nuevo2.csv");
    string ipInput;
    cout << "Ingresar IP personal: ";
    cin >> ipInput;
    string ipTodos = "192.168.221.";
    string ipConcatenado = ipTodos + ipInput;
    cout << "El IP personal completo es: " << ipConcatenado << endl;

    ConexionesComputadora Computadora;
	for(Record r: conexiones){
		if(r.ipFuente==ipConcatenado){
            Computadora.nuevaSaliente(r.puertoDestino, r.ipDestino, r.nombreDestino);
			}
        else if (r.ipDestino==ipConcatenado){
            Computadora.nuevaEntrante(r.puertoFuente, r.ipFuente, r.nombreFuente);
		}
	}

auto v = Computadora.entrantes.front();

cout << "Última conexión entrante es: ";
cout << "IP: " << v.ipRemota << ", ";
cout << "nombre: " << v.nombreRemoto << ", ";
cout << "puerto: " << v.puertoRemoto << endl;

    
    


cout << "Cantidad de conexiones entrantes: " << Computadora.entrantes.size() << endl;
cout << "Cantidad de conexiones salientes: " << Computadora.salientes.size() << endl;



}