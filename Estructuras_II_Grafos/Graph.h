#include <vector>
#include <string>
#include <map>
using namespace std;

class Graph {
public:
    Graph();
    void agregarCanton(string& nombre);
    void agregarArista(string& origen, string& destino, int distancia);
    int obtenerDistancia(string& origen, string& destino);
    void mostrarGrafo();
    int getCantonIndex(std::string& nombre);
    void getCantonName(vector <int>);

    //Primer Caso de Uso:
    int caminoCorto(int origen, int destino);
    void mostrarRutaArbol(const Graph& grafo, int origen);
    void floydWarshall();

    vector<int> getCantonNeighbors(int cantonIndex);
private:
    struct Vecino {
        int indice;
        int distancia;
    };

    map<string, int> cantones;
    vector<string> nombres;
    vector<vector<Vecino>> listaAdyacencia;
};