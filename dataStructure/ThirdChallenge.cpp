#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <map>

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

//PREGUNTA 1
    unordered_set<string> noReto;
    string retoCom = "reto.com";
    for(Record r: conexiones){
        size_t foundDestino = r.nombreDestino.find(retoCom);
        if(foundDestino == string::npos){
            if(r.nombreDestino != "-"){
            noReto.insert(r.nombreDestino);
            }
        }
        size_t foundFuente = r.nombreFuente.find(retoCom);
        if(foundFuente == string::npos){
            if(r.nombreFuente != "-"){
            noReto.insert(r.nombreFuente);
            }
        }
    }
    cout << "PREGUNTA 1: análisis visual del conjunto " << endl;
    cout << "CONJUNTO\n";
    for (auto i = noReto.begin(); i != noReto.end(); ++i) { 
        cout << *i << '\n'; 
    }
    cout << "___________" << endl;
    
	unordered_map<string, ConexionesComputadora> cc;
    int count = 0;
	for(Record r: conexiones){
		if(r.ipFuente!="-"){
			if(cc.find(r.ipFuente)==cc.end()){
				ConexionesComputadora a(r.ipFuente, r.nombreFuente);
				cc[r.ipFuente]=a;
			}
			cc[r.ipFuente].nuevaSaliente(r.puertoDestino, r.ipDestino, r.nombreDestino);
            
		}
        if(r.ipDestino!="-"){
			if(cc.find(r.ipDestino)==cc.end()){
				ConexionesComputadora b(r.ipDestino, r.nombreDestino);
				cc[r.ipDestino]=b;
			}
			cc[r.ipDestino].nuevaEntrante(r.puertoFuente, r.ipFuente, r.nombreFuente);
		}
    }

//PREGUNTA 2

cout << "PREGUNTA 2: DETERMINAR LAS IPs DE LAS DIRECCIONES ANÓMALAS" << endl;
for(auto ipAnomala: cc){
    if(ipAnomala.second.nombre == "u862h1cxhmv93xxpd5r3.net"){
        cout <<" La IP de: "<< ipAnomala.second.nombre << " es: " << ipAnomala.first << endl;  
    } 
    if(ipAnomala.second.nombre == "nyh5274rfoxkdl5biuiw.com"){
        cout <<" La IP de: "<< ipAnomala.second.nombre << " es: " << ipAnomala.first << endl;  
    } 

}
    cout << "___________" << endl;


//PREGUNTA 3
    string ipDominio = "192.168.221.";

    for(int i = 1; i <= 254; i++){
        string ipConcatenado = ipDominio + to_string(i);
        if(cc[ipConcatenado].entrantes.size() >= 1){
            count++;
        }
    }
    cout << "PREGUNTA 3:" << endl;
    cout << "La cantidad de IPs del dominio reto.com que tienen al menos una conexión entrante es: " << count << endl;
    cout << "___________" << endl;

//PREGUNTA 4
    unordered_set<string> ipUnicas;

    for(auto conexion: cc["192.168.221.1"].entrantes){
        ipUnicas.insert(conexion.ipRemota);
    }

    for(auto conexion: cc["192.168.221.94"].entrantes){
        ipUnicas.insert(conexion.ipRemota);
    }

    for(auto conexion: cc["192.168.221.66"].entrantes){
        ipUnicas.insert(conexion.ipRemota);
    }

    for(auto conexion: cc["192.168.221.18"].entrantes){
        ipUnicas.insert(conexion.ipRemota);
    }

cout << "PREGUNTA 4: MOSTRAR LAS IPs ÚNICAS DE LAS CONEXIONES ENTRANTES EN ALGUNAS COMPUTADORAS" << endl;
    cout << "IPs Únicas\n";
    for (auto i = ipUnicas.begin(); i != ipUnicas.end(); ++i) { 
        cout << *i << '\n'; 
    }
cout << "___________" << endl;

//PREGUNTA 6
int count2 = 0;
int count3 = 0;
for(auto conexion: cc["192.168.221.147"].entrantes){
        if(conexion.nombreRemoto == "u862h1cxhmv93xxpd5r3.net"){
            count2++;
        }
        else if (conexion.nombreRemoto == "nyh5274rfoxkdl5biuiw.com"){
            count3++;
        }

}

for(auto conexion: cc["192.168.221.147"].salientes){
        if(conexion.nombreRemoto == "u862h1cxhmv93xxpd5r3.net"){
            count2++;
        }
        else if (conexion.nombreRemoto == "nyh5274rfoxkdl5biuiw.com"){
            count3++;
        }

}

cout << "PREGUNTA 6: DETERMINAR SI LAS IPs ÚNICAS HAN ESTABLECIDO CONEXIÓN CON LAS IPs ANÓMALAS" << endl;
if(count2 > 0){
    cout << "La dirección anómala 'u862h1cxhmv93xxpd5r3.net' sí ha establecido conexión con la IP única '192.168.221.147'" << endl;
}
else {
    cout << "La dirección ánomala 'u862h1cxhmv93xxpd5r3.net' no ha establecido conexión con la IP única '192.168.221.147'" << endl;
}

if(count3 > 0){
    cout << "La dirección anómala 'nyh5274rfoxkdl5biuiw.com' sí ha establecido conexión con la IP única '192.168.221.147'" << endl;
}
else {
    cout << "La dirección ánomala 'nyh5274rfoxkdl5biuiw.com' no ha establecido conexión con la IP única '192.168.221.147'" << endl;
}

cout << "___________" << endl;

/*cout << count2 << endl;
cout << count3 << endl;*/
}