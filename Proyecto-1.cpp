#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <random>
#include <bits/stdc++.h>
#include <sstream> //para pasar int a string
#include <string> 
#include <typeinfo>

using namespace std;

//template al cual se puede agregar cualquier tipo data
template<typename T>
//clase grafo
class Grafo {
    //declaracion de mapa anidado l con T y lista de pares
	map<T, list<pair<T, float>>> l;

public:
	void AgregarArista(T x, T y, float peso) {
		l[x].push_back({y, peso});
	}
	void imprimir() {
		for (auto p : l) {
			T node = p.first;
			cout << node << " -> ";

			for (auto nbr : l[node]) {
				cout << "(" << nbr.first << "," << nbr.second << ") ";
			} cout << endl;
		}
	}

	void djikstra(T fuente) {

		cout<<"Fuente: Especie"<<fuente<<endl;

		map<T, float> dist;

		// inicicializando dist
		for (auto p : l) {
			T node = p.first;
			dist[node] = INT_MAX;
		}
		dist[fuente] = 0;

        // set 's' creado para obtener el elemento de menor distancia al comienzo
		// 	distancia,nodo
		set<pair<float, T>> s;
		s.insert({dist[fuente], fuente});

		while (!s.empty()) {
            
            //define par de 'float' y 'T'
			pair<float, T> p = *s.begin();
			s.erase(s.begin());
			T currNode = p.second;
			float DistanciaAcualNodo = p.first;

			// visitado todos los nodos nbr
			for (auto nbr : l[currNode]) {
				T nbrNodo = nbr.first;
				float DistanciaEntreMedio = nbr.second;
				float nbrNodoDistancia = dist[nbrNodo];

				// potencial nueva distancia = DistanciaAcualNodo + DistanciaEntreMedio
				if (DistanciaAcualNodo + DistanciaEntreMedio < nbrNodoDistancia) {
                    // actualiza distancia en set y map
                    // si nodo no esta presente en set 's' entonces se agrega
					auto pr = s.find({dist[nbrNodo], nbrNodo});
					if (pr != s.end()) {
						s.erase(pr);
					}
					dist[nbrNodo] = DistanciaAcualNodo + DistanciaEntreMedio;
					s.insert({dist[nbrNodo], nbrNodo});
				}
			}
		}
		for (auto x : dist) {
			if(x.second != 0 && x.second != INT_MAX){
				cout << x.first << " esta a distancia " << x.second << " desde fuente" << endl;
			}
		}
	}
};

class Especie{
 private:
    int nivel_trofico;
    int num_especie;
    string id;

 public:
    Especie(int i, int sub_i);
    string get_id();
};

Especie::Especie(int i, int sub_i){ 
    this->nivel_trofico=i;  
    this->num_especie=sub_i;
};

string Especie::get_id(){
    
	ostringstream str1;
	ostringstream str2;
	str1 << nivel_trofico;
	str2 << num_especie;
	string id = "("+str1.str()+","+str2.str()+")";
    return id;
};

using namespace std;
#include <vector> // para obtener definicion de clase vector
using std::vector; 

int main()
{
	int decision_usuario;
    int i,sub_i,aux,aux2,energia_inicial,V,num_depredadores,id_depredador;
    float eficiencia_energia_transferida;
    bool continuar;
	//valores predefinidos
    int num_niveles_troficos=5;
    //ultimo nivel trofico refiere a organismos descomponedores
    int especies_x_nivel[num_niveles_troficos]={4,8,9,4,1};
    srand(time(NULL));
    vector<vector<Especie>> nvl_trofico;
    nvl_trofico.reserve(num_niveles_troficos);

	cout<<"------------------------------"<<endl;
	cout<<"PROGRAMA SIMULADOR RED TROFICA"<<endl;
	cout<<"------------------------------"<<endl;
	cout << endl;
	cout << endl;
	cout<<"MARCAR OPCION"<<endl;
	cout<<"<1> para mostrar informacion del programa."<<endl;
	cout<<"<2> para pasar directamente a simulacion automatica de red trofica."<<endl;
	cout<<">";
	cin>>decision_usuario;
	cout<<endl;


	if(decision_usuario==1){
		cout<<"INFORMACION"<<endl;
		cout<<endl;
		cout<<"Programa crea grafo en representacion de red trofica, tal que conexiones (aristas) \
refieren a la eficiencia,"<<endl;
		cout<<"energia util transferible respecto a la energia total de presa, en cadena trofica integrada \
por especie presa y especie depredadora (vertices)."<<endl;
		cout<<endl;
		cout<<"EJEMPLO DE VISUALIZACION DE VERTICE: \
(nivel trofico, identifiacion dentro de nivel trofico)"<<endl;
		cout<<endl;
		cout<<"En algoritmo de djikstra, que evalua ruta mas corta, se obtendra la suma de "<<endl;
		cout<<"energia util transferible (distancia)desde un vertice fuente dado a otro vertice destino"<<endl;
		cout<<"Una ruta de distancia menor refiere a ruta trofica de menor eficiencia, y viceversa."<<endl;
	}

	cout<<endl;
	string r;
	cout<<"¿Deseas continuar a la ejecucion de simulador de red trofica?s/n"<<endl;
	cout<<">";
	cin>>r;
	cout<<endl;

	if(r=="n"){
		return 0;
	}

    V=0;
    for(i=0; i<num_niveles_troficos;i++){
        V=V+especies_x_nivel[i];
    }
	//creacion grafo
	Grafo<string> g;

    energia_inicial=1000;
    for(i = 0; i< num_niveles_troficos; i++){
        vector<Especie>especie;
        for(sub_i = 0; sub_i < especies_x_nivel[i]; sub_i++) {
            especie.push_back(Especie(i,sub_i));
        }
        nvl_trofico.push_back(especie);
    }

    for(i = 0; i< num_niveles_troficos-1; i++){
        for(sub_i = 0; sub_i < especies_x_nivel[i]; sub_i++) {
            //determina depredadores por niveles troficos (superiores)
            for(aux=i+1; aux <num_niveles_troficos; aux++){
                if(aux==i+1){
                    //numero de depredadores en determinado nivel dado pseudoaleatoriamente
                    num_depredadores=(rand() % (especies_x_nivel[aux])+1);
                }
                else if(aux==i+2){
                    num_depredadores=rand() % (especies_x_nivel[aux]);
                }
                else{
                    num_depredadores=(rand() % (especies_x_nivel[aux]))/3;
                }
                // se seleccionan especies depredadoras en nivel determinado
                if(num_depredadores!=0){
                    // vector que verifica si especie depredadora no se ha repetido
                    vector<int> registro;
                    for(aux2=0; aux2<num_depredadores; aux2++){
                        continuar=false;
                        while (continuar==false){
                            id_depredador = rand() % (especies_x_nivel[aux]);
                            if (find(registro.begin(), registro.end(), id_depredador) != registro.end()){
                                continue;
                            }else{
                                registro.push_back(id_depredador);
                                continuar=true;
                            }
                        }
                        if (aux==(num_niveles_troficos-1)){
                            //organismo muere por causa natural y es descompuesto en totalidad
                            eficiencia_energia_transferida = 1;
                        }else{
                            // valor pseudoaleatorio de energia transferida presa a depredador
                            eficiencia_energia_transferida = ((rand() % (10)) + 5);
                            eficiencia_energia_transferida = eficiencia_energia_transferida/100;
                        }
                        // crea conexion de vertices tipo especie
                        g.AgregarArista(nvl_trofico[i][sub_i].get_id()\
                        ,nvl_trofico[aux][id_depredador].get_id(),\
                        eficiencia_energia_transferida);
                    }
                }
            }
        }
    }
    
	cout<<"--------------"<<endl;
	cout<<"LISTA ENLAZADA"<<endl;
	cout<<"--------------"<<endl;
    g.imprimir();
	cout<<"--------------"<<endl;
    cout << endl;

	cout<<"--------------"<<endl;
	cout<<"ALGORITMO DJIKSTRA"<<endl;
	cout<<"--------------"<<endl;
	g.djikstra(nvl_trofico[0][0].get_id());
	cout<<"--------------"<<endl;
	cout << endl;
}
