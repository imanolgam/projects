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

    map<int, list <string> > top(int n, string fecha){
        map<int, string> topCinco;
        for(auto i:conexionesPorDia(fecha)){
            topCinco.insert(make_pair(i.second,i.first)); 
        }

        map<int, list <string> > todos;
        list <string> dominiosConDuplicados;
        for (auto i: topCinco){
            dominiosConDuplicados.clear();
            for (auto j:conexionesPorDia(fecha)){
                if (i.first==j.second){
                    dominiosConDuplicados.push_back(j.first);
                }
            }
            todos.insert(make_pair(i.first,dominiosConDuplicados));
        }

        map<int, list <string> > todosTop;
        for (auto i = todos.rbegin(); i != todos.rend(); i++){
            if(n >=1){
            todosTop.insert(make_pair(i->first,i->second));               
            }
            n--;
        }
        
        return todosTop;
    }
        
int main(){
	leerDatos("/mnt/c/Users/Bernardo Reyes Díaz/Desktop/nuevo2.csv");

    string mes = "-8-2020";

    for(int i = 10; i < 22; i++){
        string fechaCompleta = to_string(i) + mes;
        cout << "fecha:" << fechaCompleta << endl;
        for(auto i: top(5 , fechaCompleta)){
            cout << "apariciones: " << i.first << " || direcciones: ";
            for (auto a: i.second){
                cout<< a <<", ";
            }
            cout<<endl;
        }

    }
}