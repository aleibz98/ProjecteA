#include <iostream>
#include <queue>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <utility>

using namespace std;

typedef Grafo bool[][];

list< list > matrixToList(Grafo g){
    list< list<int> > result;
    for(int i = 0; i < g.size(); i++){
        for(int j = 0; j < g.size(); j++){
           //No recordo com era tot el tema de les referencies i els iteradors a les llistes xddd
        }
    }
    return result;
}

int contarCompConexas(Grafo g){
    int componentes = 0;
    int nodosVisitados = 0;
    bool checks[g.size()] = {false};
    queue<int> q;
    q.push(0);
    while(nodosVisitados < g.size()){
        componentes++;
        while(not q.empty()){
            int actual = q.front();
            q.pop();
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

Grafo percolacion_nodos(list< list<int> > g, float q){


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


//Aqui utilitzem 'grafo' pero ens referim a una graella
bool graellaValida(Grafo g){
    stack< pair<int,int> > s;
    bool[g.size()][g.size()] checks = {false};

    for(int i = 0; i < g.size(); i++){
        s.push(make_pair(i,g.size()-1));
    }
    while(not s.empty() and not result){
        pair<int,int> actual = s.top();
        s.pop();
        checks[actual.first][actual.second] = true;

        if(actual.second == 0){
            return true;
        }

        //Els fiquem en aquest ordre perque ens interessa anar cap adalt i es una pila
        //Caldria tenir en compte no anar a posicions < 0 o > g.size()
        if(g[actual.first][actual.second + 1] and not checks[actual.first + 1][actual.second + 1]){
            s.push(make_pair(actual.first,actual.second + 1));
        }
        if(g[actual.first + 1][actual.second] and not checks[actual.first + 1][actual.second]){
            s.push(make_pair(actual.first + 1,actual.second));
        }
        if(g[actual.first - 1][actual.second] and not checks[actual.first - 1][actual.second]){
            s.push(make_pair(actual.first - 1,actual.second));
        }
        if(g[actual.first][actual.second - 1] and not checks[actual.first][actual.second -1]){
            s.push(make_pair(actual.first,actual.second - 1));
        }
    }
    return false;
}


int main() {

    srand (time(NULL));

}
