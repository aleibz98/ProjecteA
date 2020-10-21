#include <iostream>
#include <queue>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <utility>
#include <vector>
#include <math.h>

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

struct Datos_perc_nodos{
    int tamano;
    float q;
    float prob_connex;

    void print() {
        cout << tamano << ' ' << q << ' ' << prob_connex << endl;
    }
};

struct Datos_matriz{
    int tamano;
    float q;
    float p_valida;

    void print(){
        cout << tamano << ' ' << q << ' ' << p_valida << endl;
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
          puntos[i] = make_pair(x,y);
      }

      for(int i = 0; i < size; i++){
          for(int j = 0; j < size; j++){
              float x1, x2, y1, y2;
              x1 = puntos[i].first;
              x2 = puntos[j].first;
              y1 = puntos[i].second;
              y2 = puntos[j].second;

              float d = sqrt(pow(x1-x2,2)+pow(y1-y2,2));
              if(d <= r){
                  result[i][j] = true;
                  result[j][i] = true;
              }
          }
      }
      return result;
}

// Aquesta funcio no sera optima, ja que la realitzem amb una matrium mentre que de manera optima es realitzaria amb una llista de punters
Grafo percolacion_nodos(Grafo g, float q){
    Grafo copia = g;
    bool nodos[g.size()] = {false};
    for (int i = 0; i < g.size(); i ++){
        float a = rand()%100;
        if(a > q*100){  //Els nodes que NO borram
            nodos[i] = true;
        }
    }
    for(int i = 0; i < copia.size(); ++i){
        for(int j = 0; j < copia.size(); ++j){
            if((not nodos[i]) or (not nodos[j])) {
                copia[i][j] = false;
            }
        }
    }
    return copia;
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
        //Caldria tenir en compte no anar a posicions < 0 o > g.size() - 1
        if(actual.second + 1 < g.size() and g[actual.first][actual.second + 1] and not checks[actual.first][actual.second + 1]){
            s.push(make_pair(actual.first,actual.second + 1));
        }
        if(actual.first + 1 < g.size() and g[actual.first + 1][actual.second] and not checks[actual.first + 1][actual.second]){
            s.push(make_pair(actual.first + 1,actual.second));
        }
        if(actual.first - 1 >= 0 and g[actual.first - 1][actual.second] and not checks[actual.first - 1][actual.second]){
            s.push(make_pair(actual.first - 1,actual.second));
        }
        if(actual.second - 1 >= 0 and g[actual.first][actual.second - 1] and not checks[actual.first][actual.second -1]){
            s.push(make_pair(actual.first,actual.second - 1));
        }
    }
    return false;
}


int main() {
    srand (time(NULL));
    vector<int> sizes = {10, 20, 40, 60, 80, 100};

    //TESTERS
    //Components connexes
    int iters_coef_gen = 100;
    int repeticions_gen = 50;
    Datos_generador res_connexio[iters_coef_gen * sizes.size()]; //struct per guardar la info
    for(int k = 0; k < sizes.size(); k++) {
        float coef = 0.0;
        for (int i = 0; i < iters_coef_gen; ++i) {
            int comps = 0;
            int connex = 0;
            for (int j = 0; j < repeticions_gen; ++j) {
                //Grafo g = generador_basico(sizes[k],coef);
                Grafo g = random_geometric_graph(sizes[k],coef);
                int aux = contarCompConexas(g);
                comps += aux;
                if (aux == 1) connex++;
            }
            res_connexio[k*iters_coef_gen + i].comps = comps/float(repeticions_gen);
            res_connexio[k*iters_coef_gen + i].q = coef;
            res_connexio[k*iters_coef_gen + i].tamano = sizes[k];
            float prob_connex = connex / float(repeticions_gen);
            res_connexio[k*iters_coef_gen + i].p_connex = prob_connex;
            coef += 0.005;
        }
    }

    for(auto a:res_connexio){
        a.print();
    }

    //Percolacio arestes
    //Suposarem que els grafs tenen que ser connexos
    int iters_coef_arestes = 100;
    int repeticions_arestes = 10;

    Datos_perc_aristas results[iters_coef_arestes * sizes.size()];          //first tindra el valor del coeficient q i second tindra el valor de f(q)
    for(int k = 0; k < sizes.size(); ++k) {
        float val = 0.0;
        for (int i = 0; i < iters_coef_arestes; ++i) {            //Farem 20 iteracions buscant aproximar els punts de transició, per als quals f(q) passa de 0 -> 1
            int suma = 0;
            for (int j = 0; j < repeticions_arestes; j++) {        //Per a cada iteració, farem 10 proves per obtenir el promig
                //Grafo g = generador_basico(sizes[k], ------);      //Aquesta probabilitat tindria que generar un graf connex
                Grafo g = random_geometric_graph(sizes[k],------);
                int b = contarCompConexas(g);
                if(b > 1) j--;
                else {
                    Grafo f = percolacion_aristas(g, val);
                    int a = contarCompConexas(f);
                    if(a == 1) suma += 1;
                }
            }
            results[k*20 + i].tamano = sizes[k];
            results[k*20 + i].prob_connex = suma/float(repeticions_arestes);
            results[k*20 + i].q = val;

            val += 1 / iters_coef_arestes;
        }
    }

    for(auto a:results){
        a.print();
    }


    //Percolacio nodes
    int iters_coef_nodes = 100;
    int repeticions_nodes = 10;
    Datos_perc_nodos results_nodes[iters_coef_nodes * sizes.size()];          //first tindra el valor del coeficient q i second tindra el valor de f(q)

    for(int k = 0; k < sizes.size(); ++k) {
        float val = 0.0;
        for (int i = 0; i < iters_coef_nodes; ++i) {            //Farem 20 iteracions buscant aproximar els punts de transició, per als quals f(q) passa de 0 -> 1
            int suma = 0;
            for (int j = 0; j < repeticions_nodes; j++) {        //Per a cada iteració, farem 10 proves per obtenir el promig
                //Grafo g = generador_basico(sizes[k], ------);      //Aquesta probabilitat tindria que generar un graf connex
                Grafo g = random_geometric_graph(sizes[k],------);
                int b = contarCompConexas(g);
                if(b > 1) j--;
                else {
                    Grafo f = percolacion_nodos(g, val);
                    int a = contarCompConexas(f);
                    if(a == 1) suma += 1;
                }
            }
            results_nodes[k*iters_coef_nodes + i].tamano = sizes[k];
            results_nodes[k*iters_coef_nodes + i].prob_connex = suma/float(repeticions_nodes);
            results_nodes[k*iters_coef_nodes + i].q = val;

            val += 1 / iters_coef_nodes;
        }
    }

    for(auto a:results_nodes){
        a.print();
    }


    //Graella
    int num_iteracions_coeficient;
    int repeticions_graella;
    Datos_matriz resultados_matriz[num_iteracions_coeficient*sizes.size()];

    //Suposarem que la graella original te que ser valida abans d'aplicar-hi la percolacio
    int it = 0;
    for (auto size: sizes) {
        float coef = 0.0;
        for (int i = 0; i < num_iteracions_coeficient; ++i) {
            int contador = 0;
            for (int j = 0; j < repeticions_graella; ++j) {
                Grafo g = random_geometric_graph(size, coef); //fixar el coeficient o iterar amb diferents coeficients
                if (graellaValida(g)) {
                    Grafo g2 = percolacion_nodos(g, q); //fixar q o iterar amb diferents
                    if (graellaValida(g2)) {
                        contador++;
                    }
                }
            }
            resultados_matriz[it].tamano = size;
            resultados_matriz[it].q = coef;
            resultados_matriz[it].p_valida = contador / float(repeticions_graella);
            it++;

            coef += 1/num_iteracions_coeficient;
        }
    }

    for(auto a:resultados_matriz){
        a.print();
    }
}
