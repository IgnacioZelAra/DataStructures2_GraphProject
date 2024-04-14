#include "Graph.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include <fstream>
#include <sstream>

using namespace std;



void loadData(Graph& grafo, string& filename) {
    ifstream inputFile(filename);
    string origen, destino, distance;
    string line;

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            stringstream ss(line);
            getline(ss, origen, ',');
            getline(ss, destino, ',');
            getline(ss, distance, ',');

            if (grafo.getCantonIndex(origen) == -1) grafo.agregarCanton(origen);
            if (grafo.getCantonIndex(destino) == -1) grafo.agregarCanton(destino);

            int distancia = stoi(distance);
            grafo.agregarArista(origen, destino, distancia);

        }
        inputFile.close();
    }
}


Graph loadProvincia(string& provincia) {
    Graph grafo;
    string filename = provincia + ".txt";
    loadData(grafo, filename);
    return grafo;
   
}


void displayMenu() {
    cout << "1. Seleccionar una Provincia.\n";
    cout << "2. Encontrar el camino mas corto entre dos cantones.\n";
    cout << "3. Encontrar los vecinos de un canton.\n";
    cout << "4. Minima cantidad de cable entre todos los cantones.\n";
    cout << "0. Salir.\n";
}

string selectRegion() {
    vector<string> regions = { "Cartago", "Alajuela", "SanJose", "Guanacaste", "Heredia", "Limon", "Puntarenas" };
    cout << "Seleccione una Provincia:\n";
    for (int i = 0; i < regions.size(); i++) {
        cout << i + 1 << ". " << regions[i] << '\n';
    }
    int choice;
    cin >> choice;
    return regions[choice - 1];
}

void findShortestPath(Graph grafo) {
    string origen, destino;
    cout << "Ingrese el canton de Origen: ";
    getline(cin >> ws, origen);
    cout << "Ingrese el canton de Destino: ";
    getline(cin >> ws, destino);
    int indexOrigen = grafo.getCantonIndex(origen);
    int indexDestino = grafo.getCantonIndex(destino);
    cout << "El camino mas corto es : " << grafo.caminoCorto(indexOrigen, indexDestino) << '\n';
}


void displayNeighboringCantons(Graph grafo) {
    string canton;
    cout << "Ingrese el nombre del canton: ";
    getline(cin >> ws, canton);
    int index = grafo.getCantonIndex(canton);
    
    if (index != -1) {
        cout << "Cantones vecinos de " << canton << ":\n";
        grafo.getCantonName(grafo.getCantonNeighbors(index));
    } else {
        cout << "El canton no existe en esta provincia.\n";
    }
}




void cableMinimunLenght(Graph grafo) {
    grafo.mostrarRutaArbol(grafo, 0);
}


int main() {
    vector<string> provincias = { "Cartago", "Alajuela", "SanJose", "Guanacaste", "Heredia", "Limon", "Puntarenas" };
    
    map<string, Graph> graphs;

    for (string& provincia : provincias) {
        graphs[provincia] = loadProvincia(provincia);
    }

    int choice;
    string currentRegion;
    do {
        displayMenu();
        cout << "Ingrese su seleccion: ";
        cin >> choice;
        switch (choice) {
        case 1:
            currentRegion = selectRegion();
            cout << "Provincia Seleccionada: " << currentRegion << '\n';
            break;
        case 2:
            if (!currentRegion.empty()) {
                findShortestPath(graphs[currentRegion]);
            } else {
                cout << "Debe seleccionar una Provincia primero.\n";
            }
            break;

        case 3:
            if (!currentRegion.empty()) {
                displayNeighboringCantons(graphs[currentRegion]);
            } else {
                cout << "Debe seleccionar una Provincia primero.\n";
            }
            break;
        case 4: 
            if (!currentRegion.empty()) {
                cableMinimunLenght(graphs[currentRegion]);
            }
            else {
                cout << "Debe seleccionar una Provincia primero .\n";
            }
            break;
        }
    } while (choice != 0);
    return 0;
}
