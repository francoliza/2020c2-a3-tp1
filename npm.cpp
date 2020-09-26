#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <climits>
#include <set>
#include <map>

using namespace std;

int M; 						//limite de contagio 
int n; 						//cantidad de locales 
vector<int> b;				//beneficio para cada local
vector<int> c;				//contagio que produce cada local
int inf = 10e6;

//i el local que estoy tomando en cuenta
//k cardinal de beneficio hasta el momento.
//m contagio maximo
//sol vector de solucion parcial
int fuerzaBruta(int i, int k, int m, vector<int> sol){ // FUERZA BRUTA
	if (i==n) //caso en que soy hoja
	{
		if (m>=0)
		{
			//si son locales contiguos no es una solucion valida.
			if(sol.size()>=2){
				for (int j=0; j<sol.size()-1; ++j)
				{
					if (sol[j]+1 == sol[j+1])
					{
						return -inf;
					}
				}				
			}	

			return k;
		}
		return -inf;
	}

	//recursion agregando el local i
	sol.push_back(i);
	int der = fuerzaBruta(i+1, k+b[i], m-c[i], sol);
	//recursion agregando el 
	sol.pop_back();
	int izq = fuerzaBruta(i+1, k, m, sol);

	return max(izq, der);
}

int maximo = 0;
bool poda_optimalidad = true;
bool poda_factibilidad = true;
int backtracking(int i, int k, int m){ // BACKTRACKING
	if (i>=n) //caso en que soy hoja y vi todos los locales
	{
		if (m>=0)
		{
			//aca como sumo de a dos ya estoy construyendo una solucion valida
			if (k>maximo)
			{
				maximo = k; 
				return maximo;
			}
			return k;
		}
		return -inf;
	}

	//poda por factibilidad
	if (poda_factibilidad and m<0){
		return -inf;
	}
	//podas por optimalidad
	//miro los elementos que me quedan por agregar si no superan el maximo salgo
	if (poda_optimalidad)
	{
		int p = k; 
		for (int j=i; j<n; ++j)
		{
			p=p+b[j];
		}
		if (p<maximo){
			return -inf;
		}
	}

	//hago la recursion y tomo el maximo beneficio obtenido.
	//en cada paso construyo una solucion valida ya que si agrego el elemento i 
	//me aseguro no agregar el i+1.(especie de poda)
	return max(backtracking(i+1, k, m), backtracking(i+2, k+b[i], m-c[i]));
}

//defino un diccionario
//vector<vector<int> > dicc;
int programacionDinamica(int i, int m, vector<vector<int> >&dicc){
	//TOP DOWN con memoización
	if(m < 0) 	return -inf;
	if(m == 0) 	return 0;
	if(i >= n)	return 0;
	if(dicc[i][m] == -1){
		dicc[i][m] = max(programacionDinamica(i+1, m, dicc), programacionDinamica(i+2, m-c[i], dicc)+b[i]);
	}
	return dicc[i][m];
}


int main(int argc, char** argv){
	// Leemos el parametro que indica el algoritmo a ejecutar.
	map<string, string> algoritmos_implementados = {
		{"FB", "Fuerza Bruta"}, {"BT", "Backtracking con podas"}, {"BT-F", "Backtracking con poda por factibilidad"}, 
		{"BT-O", "Backtracking con poda por optimalidad"}, {"PD", "Programacion dinámica"}
	};

	// Verificar que el algoritmo pedido exista.
	if (argc < 2 || algoritmos_implementados.find(argv[1]) == algoritmos_implementados.end())
	{
		cerr << "Algoritmo no encontrado: " << argv[1] << endl;
		cerr << "Los algoritmos existentes son: " << endl;
		for (auto& alg_desc: algoritmos_implementados) cerr << "\t- " << alg_desc.first << ": " << alg_desc.second << endl;
		return 0;
	}
	string algoritmo = argv[1];

    // Leemos el input.
    cin >> n >> M;
    b.assign(n, 0);
    c.assign(n, 0);


    for (int i=0; i<n; ++i) {
    	cin >> b[i];
    	cin >> c[i];
    }

    vector<int> sol;
    cout << "Cantidad de locales: " << n << endl;
    cout << "Limite de contagio: " << M << endl;

    // Ejecutamos el algoritmo y obtenemos su tiempo de ejecución.
	int optimum;
	//optimum = INFTY;
	auto start = chrono::steady_clock::now();
	if (algoritmo == "FB")
	{
		optimum = fuerzaBruta(0, 0, M, sol);
	}
	else if (algoritmo == "BT")
	{
		//K = INFTY;
		//poda_optimalidad = poda_factibilidad = true;
		optimum = backtracking(0, 0, M);
	}
	else if (algoritmo == "BT-F")
	{	//Acá va la imprementación con Backtraking con poda por factivilidad
		poda_optimalidad = false;
		poda_factibilidad = true;
		optimum = backtracking(0, 0, M);
	}
	else if (algoritmo == "BT-O")
	{	//Acá va la imprementación con Backtraking con poda por óptimalidad
		poda_optimalidad = true;
		poda_factibilidad = false;
		optimum = backtracking(0, 0, M);
	}
	else if (algoritmo == "PD")
	{
		// Obtenemos la solucion optima.
		vector< vector<int> > d(n+1, vector<int>(M+1, -1));
		//no se si hay que buscar el max por toda la matriz;

		optimum = programacionDinamica(0, M, d);
	}
	auto end = chrono::steady_clock::now();
	double total_time = chrono::duration<double, milli>(end - start).count();

	// Imprimimos el tiempo de ejecución por stderr.
	clog << "Tiempo en ejecución: " << total_time << endl;

    // Imprimimos el resultado por stdout.
    cout << (optimum == inf ? -1 : optimum) << endl;
   
    return 0;
}
