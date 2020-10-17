#include <iostream>
#include <queue>
#include <list>
#include <stdlib.h>
#include <time.h>

using namespace std;

typedef Grafo bool[][];

int contarCompConexas(Grafo g){
    int componentes = 0;
    int nodosVisitados = 0;
    bool checks[g.size()] = {false};
    queue q;
    q.push(0);
    while(nodosVisitados < g.size()){
        componentes++;
        while(not q.empty()){
            int actual = q.pop();
            nodosVisitados++;
            checks[actual] = true;

            for(int i = 0; i < g.size(); i++){
                if(g[actual][i] and not checks[i]){
                    q.push(i);
                }
            }
        }
        for(int i = 0; i < g.size() and q.empty(); ++i){
            if(not checks[i]) q.push(i);
        }
    }
    return componentes;
}

Grafo generador_basico(int size, float probabilidad){
    bool[size][size] result = {false};
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            if(rand() >= q){
                result[i][j] = true;
                result[j][i] = true;
            }
        }
    }
    return result;
}

Grafo percolacion_nodos(Grafo g, float q){


}

Grafo percolacion_aristas(Grafo g, float q){
    Grafo copia = g;        //aixo fa una copia real o nomes copia la referencia a memoria??
    for(int i = 0; i < g.size(); ++i){
        for(int j = 0; j < g.size(); ++j){
            if(g[i][j] and rand() < q){
                copia[i][j] = false;
                copia[j][i] = false;
            }
        }
    }
    return copia;
}

int main() {

    srand (time(NULL));

}
