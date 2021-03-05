/*Imanol García 
  Bernardo Reyes*/

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

unordered_map<string, int> conexionesPorDia(string fecha){
    unordered_map<string, int> conexionesDia;
    for(auto i : conexiones){
        if(i.nombreDestino != "-" && i.nombreDestino.find("reto.com") == string::npos){
            if(i.fecha==fecha){
                if(conexionesDia.find(i.nombreDestino)==conexionesDia.end()){
                    //conexionesDia.insert({i.nombreDestino, 1}); otro método de insertado
                    conexionesDia[i.nombreDestino]=1;
                }
                else{
                    conexionesDia[i.nombreDestino]++;
                }
            }   
        }    
    }

    return conexionesDia;
}

template <class T>
class Nodo{
	public:
	T value;
	bool visited;
	unordered_map<Nodo<T> *, int> siguientes;
	
	Nodo(T val){
		value=val;
		visited=false;
	}
	
	void agregarArcoDirigidoConPeso(Nodo<T> *sig, int peso){
		if(siguientes.find(sig)==siguientes.end()){
			siguientes[sig]=peso;
		}
	}
	
	void agregarArcoDirigido(Nodo<T> *sig){
		agregarArcoDirigidoConPeso(sig, 1);
	}
	
	void imprimirNodo(){
			cout<<value<<"---->";
			for(auto nodoSiguiente:siguientes){
				cout<<nodoSiguiente.first->value<<","<<nodoSiguiente.second<<";";
			}
			cout<<endl;
	}
	
	/*bool conexion(Nodo<T> *nodo){
	}
	
	void modificarPeso(Nodo<T> *nodo, nuevoPeso){
	}*/
};


template <class T>
class Graph{
	public:
	unordered_map<T, Nodo<T> *> nodos;
	
	void agregarNodo(T value){
		if(nodos.find(value)==nodos.end()){
			Nodo<T> *nuevo=new Nodo<T>(value);
			nodos[value]=nuevo;
		}
	}
	
	void agregarArcoDirigidoConPeso(T nodo1, T nodo2, int peso){
		if(nodos.find(nodo1)!=nodos.end() && nodos.find(nodo2)!=nodos.end()){
			nodos[nodo1]->agregarArcoDirigidoConPeso(nodos[nodo2], peso);
		}			
	}
	
	void agregarArcoDirigido(T nodo1, T nodo2){
		agregarArcoDirigidoConPeso(nodo1, nodo2, 1);
	}
	
	void agregarArcoConPeso(T nodo1, T nodo2, int peso){
		agregarArcoDirigidoConPeso(nodo1, nodo2, peso);
		agregarArcoDirigidoConPeso(nodo2, nodo1, peso);
	}
	
	void agregarArco(T nodo1, T nodo2){
		agregarArcoConPeso(nodo1, nodo2, 1);
	}
	
	void imprimirGrafo(){
		for(auto parValorNodo: nodos){
			parValorNodo.second->imprimirNodo();
		}
	}
	
	unordered_map<string, int> ordenarPorDia(){
		unordered_map<string, int> a;
		//llenar el mapa
		return a;
	}
	
	/*void modificar(T nodo1, T nodo2, int nuevoPeso){
		//Encontrar que existan
		//buscar si existe el arco nodo1-nodo2 y modificarlo
	}*/
	
	bool BFS(T v1, T v2){
		list <Nodo<T>*> cola;
		cola.push_back(nodos[v1]);
		while(true){
			if(cola.empty() == true){
				return false;
			}
			else{			
				Nodo<T>* sacado = cola.front();
				cola.pop_front();
				sacado->visited=true;
				if(sacado == nodos[v2]){
					return true;
				}
				else{
					for(auto i: sacado->siguientes){
						if(i.first->visited == false){
							cola.push_back(i.first);
						}
					}
				}
			}
		}				
	}
void desvisitar(T visitado){
	Nodo<T>* nodo = nodos[visitado];
	for(auto i:nodo->siguientes){
		i.first->visited =false;
	}
}

	bool DFS(T v1, T v2){
		list <Nodo<T>*> pila;
		pila.push_front(nodos[v1]);
		while(true){
			if(pila.empty() == true){
				cout << "pila vacía" << endl;
				return false;
			}
			else{		
				Nodo<T>* sacado = pila.back();
				pila.pop_back();
				sacado->visited=true;
				if(sacado == nodos[v2]){
					return true;
				}
				else{
					for(auto i: sacado->siguientes){
						if(i.first->visited == false){
							pila.push_front(i.first);
						}
					}
				}
			}
		}				
	}
};

unordered_map<string, int> conexionesPorDia(string fecha, string ip){
    unordered_map<string, int> conexionesDia;
    for(auto i : conexiones){
        if(i.ipDestino == ip){
            if(i.fecha==fecha){
                if(conexionesDia.find(i.ipDestino)==conexionesDia.end()){
                    //conexionesDia.insert({i.nombreDestino, 1}); otro método de insertado
                    conexionesDia[i.ipFuente]=1;
                }
                else{
                    conexionesDia[i.ipFuente]++;
                }
            }   
        }    
    }

    return conexionesDia;
}
        
int main(){
	leerDatos("/mnt/c/Users/Bernardo Reyes Díaz/Desktop/nuevo2.csv");
    Graph<string> grafoRedInterna;
    Graph<string> grafoSitiosWeb;
    string ipDominio = "192.168.221.";

    for(auto i :conexiones){
        for(int j = 1; j <= 254; j++){
            string ipConcatenado = ipDominio + to_string(j);
            if(i.ipFuente == ipConcatenado){
                grafoRedInterna.agregarNodo(i.ipFuente);
                grafoRedInterna.agregarArcoDirigido(i.ipFuente,i.ipDestino); 
            }        
        } 
    }

    //grafoRedInterna.imprimirGrafo();
    cout << "___________" << endl;
    for(auto i : grafoRedInterna.nodos){
        cout << i.first << " cantidad de computadoras conectadas de la red interna: " << i.second->siguientes.size() << endl;
    }

    for(auto i : grafoRedInterna.nodos){
        if (grafoRedInterna.BFS(i.first, "192.168.221.147" ) == 1){
            cout << i.first << " sí se conecta a la IP " << endl;
        }
        else{
            cout << i.first << " no se conecta a la IP A: " << endl;
        }
         grafoRedInterna.desvisitar("192.168.221.147");
    }

    for(auto i :conexiones){
        if(i.ipDestino.find("192.168.221.") == string::npos){
            grafoSitiosWeb.agregarNodo(i.ipDestino);
            grafoSitiosWeb.agregarNodo(i.ipFuente);
            grafoSitiosWeb.agregarArcoDirigido(i.ipDestino,i.ipFuente); 
        }
    }  

    //grafoSitiosWeb.imprimirGrafo();  

    for(auto i : grafoSitiosWeb.nodos){
        if(i.first == "148.229.15.44"){
            cout << "se han conectado " << i.second->siguientes.size() << " cantidad de computadoras a B" << endl;
        }
    }   
int contBleach = 0;
string mes = "-8-2020";
    for(auto i : grafoSitiosWeb.nodos){
        if(i.first == "52.95.251.73"){
            for(int j = 10; j < 22; j++){
                string fechaCompleta = to_string(j) + mes;
                cout << "fecha:" << fechaCompleta << endl;
                for(auto i :conexionesPorDia(fechaCompleta, i.first)){
                    contBleach++;
                }
            cout << contBleach << endl;
            contBleach = 0;
            }
        }
    }       
         
}


