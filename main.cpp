#include <iostream>
#include <queue>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <utility>
#include <vector>
#include <cmath>

using namespace std;

typedef vector< vector<bool> > Grafo;

struct Datos_generador{
    int tamano;     //Tamany del graf
    float q;        //coeficient q
    float comps;    //nombre de components connexes que s'han generat
    float p_connex; //probabilitat de ser connex amb els parametres indicats

    void print() {
        cout << tamano << ' ' << q << ' ' << comps << ' ' << p_connex << endl;
    }
};

struct Datos_perc_aristas{
    int tamano;
    float q;
    float prob_connex;

    void print() {
        cout << tamano << ' ' << q << ' ' << prob_connex << endl;
    }
};

/*list< list > matrixToList(Grafo g){
    list< list<int> > result;
    for(int i = 0; i < g.size(); i++){
        for(int j = 0; j < g.size(); j++){
           //No recordo com era tot el tema de les referencies i els iteradors a les llistes xddd
        }
    }
    return result;
}
*/

int contarCompConexas(Grafo g){
    int componentes = 0;
    int nodosVisitados = 0;
    bool checks[g.size()] = {false};
    queue<int> q;
    q.push(0);

    //BFS
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
    vector< vector<bool> > result(size, vector<bool>(size,false));
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            if(rand()%100 <= probabilidad*100){
                result[i][j] = true;
                result[j][i] = true;
            }
        }
    }
    return result;
}

Grafo random_geometric_graph(int size, float r){
      vector< pair<float,float> > puntos(size);
      vector< vector<bool> > result(size, vector<bool>(size,false));

      //generar punts aleatoris
      for(int i = 0; i < size; ++i){
          float x = rand()%10000 / 10000;
          float y = rand()%10000 / 10000;
          puntos.append(make_pair(x,y));
      }

      for(int i = 0; i < size; i++){
          for(int j = 0; j < size; j++){
              float x1, x2, y1, y2;
              x1 = puntos[i].first;
              x2 = puntos[j].first;
              y1 = puntos[i].second;
              y2 = puntos[j].second;

              float d = cmath.sqrt(cmath.pow(x1-x2,2)+cmath.pow(y1-y2,2));
              if(d <= r){
                  result[i][j] = true;
                  result[j][i] = true;
              }
          }
      }
      return result;
}


Grafo percolacion_nodos(list< list<int> > g, float q){
    //Aqui es suposa que el graf estaria representat amb la llista d'adjacencies

}


Grafo percolacion_aristas(Grafo g, float q){
    Grafo copia = g;        //aixo fa una copia real o nomes copia la referencia a memoria??
    for(int i = 0; i < g.size(); ++i){
        for(int j = 0; j < g.size(); ++j){
            if(g[i][j] and rand()%100 < q*100){
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
    vector< vector<bool> > checks(g.size(), vector<bool>(g.size(),false));

    for(int i = 0; i < g.size(); i++){
        s.push(make_pair(i,g.size()-1));    //Primer fiquem tota la fila d'abaix a la pila
    }

    //DFS
    while(not s.empty()){
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

    //TESTERS
    //Components connexes
    vector<int> sizes = {10, 20, 40, 60, 80, 100};
    Datos_generador res_connexio[600]; //struct per guardar la info
    for(int k = 0; k < sizes.size(); k++) {
        float coef = 0.0;
        for (int i = 0; i < 100; ++i) {
            int comps = 0;
            int connex = 0;
            for (int j = 0; j < 50; ++j) {
                Grafo g = generador_basico(sizes[k],coef);
                int aux = contarCompConexas(g);
                comps += aux;
                if (aux == 1) connex++;
            }
            res_connexio[k*100 + i].comps = comps/50.0;
            res_connexio[k*100 + i].q = coef;
            res_connexio[k*100 + i].tamano = sizes[k];
            float prob_connex = connex / 50.0;
            res_connexio[k*100 + i].p_connex = prob_connex;
            coef += 0.005;
        }
    }

    for(auto a:res_connexio){
        a.print();
    }

    //Percolacio arestes
    //Suposarem que els grafs tenen que ser connexos
    /*
    Datos_perc_aristas results[300];          //first tindra el valor del coeficient q i second tindra el valor de f(q)
    for(int k = 0; k < sizes.size(); ++k) {
        float val = 0.0;
        for (int i = 0; i < 100; ++i) {            //Farem 20 iteracions buscant aproximar els punts de transició, per als quals f(q) passa de 0 -> 1
            int suma = 0;
            for (int j = 0; j < 10; j++) {        //Per a cada iteració, farem 10 proves per obtenir el promig
                Grafo g = generador_basico(sizes[k], ------);      //Aquesta probabilitat tindria que generar un graf connex
                int b = contarCompConexas(g);
                if(b > 1) j--;
                else {
                    Grafo f = percolacion_aristas(g, val);
                    int a = contarCompConexas(f);
                    if(a == 1) suma += 1;
                }
            }
            results[k*20 + i].tamano = sizes[k];
            results[k*20 + i].prob_connex = suma/10.0;
            results[k*20 + i].q = val;

            val += 0.01;
        }
    }
    */





}
