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
//n cantidad de locales
//M limite de contagio
//b y c, beneficio y contagio

int n, M;
vector<int> b, c;

int limiteDeContagio;
int cantidadDeLocales;
vector<int> contagioPorLocal;
vector<int> beneficioDeLocal;

//i el local que estoy tomando en cuenta
//k cardinal hasta el momento.
int FB(int i, int k, int contagio, vector<int>& solParcial){ // FUERZA BRUTA
	if (i >= cantidadDeLocales) //caso en que soy hoja
	{
		if (contagio>=0)
		{

			/*for (int i = 0; i < solParcial.size(); ++i)
			{
				cout << solParcial[i] << ", ";
			}
			cout << " no "<< endl;*/
			return k;
		}
		//creo que no hace falta verificar si es que estoy viendo
		//negocios de por medio.
		return 0;
	}

	//cout << i << " ";

	solParcial.push_back(i);
	int der = FB(i+2, k+beneficioDeLocal[i], contagio-contagioPorLocal[i], solParcial);
	//sumo dos a i para que no agarre el de al lado si es que agrego un negocio

	solParcial.pop_back();
	int izq = FB(i+1, k, contagio, solParcial);

	return max(izq, der);
}

int maximo;

int BT(int i, int k, int contagio, vector<int>& solParcial){ // BACKTRACKING
	if (i >= cantidadDeLocales) //caso en que soy hoja
	{
		if (contagio>=0)
		{
			return k;
		}
		//creo que no hace falta verificar si es que estoy viendo
		//negocios de por medio.
		return -1; //sino devuelvo algo que no cuente como sol
	}

	/*aca van las podas. */

	//podas por factibilidad
	if (contagio<0){
		return -1;
	}

	//podas por optimalidad

	solParcial.push_back(i);
	int der = BT(i+2, k+beneficioDeLocal[i], contagio-contagioPorLocal[i], solParcial);
	//sumo dos a i para que no agarre el de al lado ya que agrego al negocio i.

	solParcial.pop_back();
	int izq = BT(i+1, k, contagio, solParcial);

	return max(izq, der);
}

//defino un diccionario
int infinito = -10e6;
vector< vector<int> > dicc;
int pd(int i, int m){ //m = M pero como variable local, para no cambiar M
	//TOP DOWN
	//cout << i << "t" << m <<endl; //CANTIDAD DE LOCALES??
	if(m < 0)				return infinito;
	if(m == 0) 				return 0;
	if(i >= n) 				return 0;
	if(i >= n and m == 0) 	return 0;
	if(dicc[i][m] == -1){
		dicc[i][m] = max(pd(i+1, m), pd(i+2, m-c[i]) + b[i]);
	}
	return dicc[i][m];
}


int main(int argc, char** argv){
	/*
	n=5;
	M=40;
	b={50, 25, 10, 20, 15};
	c={10, 10, 20, 30, 20};
	
	std::vector<int> v;

	int res = FB(0, 0, 40, v);
	cout << "FUERZA BRUTA: " << res << endl;
	*/

	/*for (int i = 0; i < v.size(); ++i)
	{
		cout << v[i] << ", ";
	}*/

	//vector<vector<int>> N;
	//dicc = vector<vector<int>>(n+1, vector<int>(M+1, -1));  // vector de N+1 x M+1
	/*for (int i = 0; i < n+1; ++i)
			for (int j = 0; j < M+1; ++j)
				pd(i, j);*/

	//cout<< "llegue: ";

	//int res3 = pd(0, 40);
	/*
	cout << res3<< endl;

	std::vector<int> w;
	cout << "BACKTRACKING: " << BT(0 , 1, 40, v) << endl;
	*/
	vector<int> solParcial;

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
    cin >> cantidadDeLocales >> limiteDeContagio;
    beneficioDeLocal.assign(cantidadDeLocales, 0);
    contagioPorLocal.assign(cantidadDeLocales, 0);

    for (int i = 0; i < cantidadDeLocales; ++i) {
    	cin >> beneficioDeLocal[i];
    	cin >> contagioPorLocal[i];
    }

    cout << "Cantidad de locals: " << cantidadDeLocales << endl;
    cout << "Limite de contagio: " << limiteDeContagio << endl;

    for (int i = 0; i < cantidadDeLocales; ++i){
    	cout << i << ") " << "Beneficio de " << beneficioDeLocal[i] << " y contagio " << contagioPorLocal[i] << endl; 
    }

    // Ejecutamos el algoritmo y obtenemos su tiempo de ejecución.
	int optimum;
	//optimum = INFTY;
	auto start = chrono::steady_clock::now();
	if (algoritmo == "FB")
	{
		optimum = FB(0, 0, limiteDeContagio, solParcial);
	}
	else if (algoritmo == "BT")
	{
		//K = INFTY;
		//poda_optimalidad = poda_factibilidad = true;
		optimum = BT(0, 0, limiteDeContagio, solParcial);
	}
	else if (algoritmo == "BT-F")
	{	//Acá va la imprementación con Backtraking con poda por factivilidad
		//K = INFTY;
		//poda_optimalidad = false;
		//poda_factibilidad = true;
		//optimum = BT(0, 0, 0);
	}
	else if (algoritmo == "BT-O")
	{	//Acá va la imprementación con Backtraking con poda por óptimalidad
		//K = INFTY;
		//poda_optimalidad = true;
		//poda_factibilidad = false;
		//optimum = BT(0, 0, 0);
	}
	else if (algoritmo == "PD")
	{
		//// Precomputamos la solucion para los estados.
		//M = vector<vector<int>>(n+1, vector<int>(W+1, UNDEFINED));
		//for (int i = 0; i < n+1; ++i)
		//	for (int j = 0; j < W+1; ++j)
		//		PD(i, j);
		optimum = pd(0, limiteDeContagio);

		//// Obtenemos la solucion optima.
		//optimum = PD(0, 0);
	}
	auto end = chrono::steady_clock::now();
	double total_time = chrono::duration<double, milli>(end - start).count();

	// Imprimimos el tiempo de ejecución por stderr.
	clog << total_time << endl;

    // Imprimimos el resultado por stdout.
    cout << (optimum == infinito ? -1 : optimum) << endl;
   
    return 0;
}
