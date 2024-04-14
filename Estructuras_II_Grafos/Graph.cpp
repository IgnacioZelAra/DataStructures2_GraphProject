#include "Graph.h"
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <iostream>
using namespace std;

Graph::Graph() {}

void Graph::agregarCanton( string& nombre) {
    cantones[nombre] = nombres.size();
    nombres.push_back(nombre);
    listaAdyacencia.push_back({});
}

void Graph::agregarArista( string& origen,  string& destino, int distancia) {
    int indiceOrigen = cantones[origen];
    int indiceDestino = cantones[destino];
    listaAdyacencia[indiceOrigen].push_back({ indiceDestino, distancia });
    listaAdyacencia[indiceDestino].push_back({ indiceOrigen, distancia }); // Para un Graph no dirigido
}

int Graph::obtenerDistancia( string& origen,  string& destino)  {
    int indiceOrigen = cantones.at(origen);
    for ( auto& vecino : listaAdyacencia[indiceOrigen]) {
        if (vecino.indice == cantones.at(destino)) {
            return vecino.distancia;
        }
    }
    return -1; // Distancia no encontrada
}

void Graph::mostrarGrafo()  {
    for (size_t i = 0; i < listaAdyacencia.size(); ++i) {
        cout << nombres[i] << ": ";
        for ( auto& vecino : listaAdyacencia[i]) {
            cout << nombres[vecino.indice] << " (" << vecino.distancia << "), ";
        }
        cout << '\n';
    }
}


int Graph::getCantonIndex(string& nombre)  {
    auto it = cantones.find(nombre);
    if (it != cantones.end()) {
        return it->second;
    }
    return -1;
}

void Graph::getCantonName(vector<int> cantons)
{
    for (int cantonsIndex : cantons) {
        cout << this->nombres[cantonsIndex] << '\n';
    }
}

int Graph::caminoCorto(int origen, int destino)
{
    vector< int > distCantones;
    for (int i = 0; i < this->listaAdyacencia.size(); i++){
        distCantones.push_back(1010209023298);
    }

    distCantones[origen] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> cantonSig;
    
    cantonSig.push(pair<int, int>(0, origen));

    while (!cantonSig.empty()){
        int aux = cantonSig.top().second;
        int dist = cantonSig.top().first;
        cantonSig.pop();

        if (aux != destino && dist <= distCantones[aux]){
            for (int i = 0; i < this->listaAdyacencia[aux].size(); i++){
                int vecino = this->listaAdyacencia[aux][i].indice;
                int peso = this->listaAdyacencia[aux][i].distancia;
                if (distCantones[vecino] > distCantones[aux] + peso){
                    distCantones[vecino] = distCantones[aux] + peso;
                    cantonSig.push(pair<int, int>(distCantones[vecino], vecino));
                }
            }
        }
    }
    
    return distCantones[destino];

    

}


vector<int> Graph::getCantonNeighbors(int cantonIndex) {
    vector<int> neighbors;
    vector<bool> visited(listaAdyacencia.size(), false);

    if (cantonIndex >= 0 && cantonIndex < listaAdyacencia.size()) {
        for (const Vecino& vecino : listaAdyacencia[cantonIndex]) {
            if (!visited[vecino.indice]) {
                neighbors.push_back(vecino.indice);
                visited[vecino.indice] = true;
            }
        }
    }
    
    return neighbors;
}

void Graph::mostrarRutaArbol(const Graph& grafo, int origen) {
    std::vector<bool> visitados(grafo.listaAdyacencia.size(), false);
    std::queue<int> cola;

    visitados[origen] = true;
    cola.push(origen);

    while (!cola.empty()) {
        int actual = cola.front();
        cola.pop();

        std::cout << grafo.nombres[actual] << " -> ";

        for (const Graph::Vecino& vecino : grafo.listaAdyacencia[actual]) {
            if (!visitados[vecino.indice]) {
                visitados[vecino.indice] = true;
                cola.push(vecino.indice);
            }
        }
    }
    std::cout << "FIN" << std::endl;
}
