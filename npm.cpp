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

int limiteDeContagio;
int cantidadDeLocales;
vector<int> beneficioDeLocal;
vector<int> contagioPorLocal;

//i el local que estoy tomando en cuenta
//k cardinal hasta el momento.
int fuerzaBruta(int localActual, int k, int contagio, vector<int>& solParcial){ // FUERZA BRUTA
	if (localActual >= cantidadDeLocales) //caso en que soy hoja
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


	solParcial.push_back(localActual);
	int der = fuerzaBruta(localActual+2, k+beneficioDeLocal[localActual], contagio-contagioPorLocal[localActual], solParcial);
	//sumo dos a "localActual" para que no agarre el de al lado si es que agrego un negocio

	solParcial.pop_back();
	int izq = fuerzaBruta(localActual+1, k, contagio, solParcial);

	return max(izq, der);
}

int backtracking(int localActual, int k, int contagio, vector<int>& solParcial){ // BACKTRACKING
	if (localActual >= cantidadDeLocales) //caso en que soy hoja
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

	solParcial.push_back(localActual);
	int der = backtracking(localActual+2, k+beneficioDeLocal[localActual], contagio-contagioPorLocal[localActual], solParcial);
	//sumo dos a i para que no agarre el de al lado ya que agrego al negocio i.

	solParcial.pop_back();
	int izq = backtracking(localActual+1, k, contagio, solParcial);

	return max(izq, der);
}

//defino un diccionario
int infinito = -10e6; //
int programacionDinamica(int localActual, int contagio, vector<vector<int> >& dicc){ //m = M pero como variable local, para no cambiar M
	//TOP DOWN con memoización
	if(contagio < 0) 				return infinito;
	if(contagio == 0) 				return 0;
	if(localActual >= cantidadDeLocales)		return 0;
	if(dicc[localActual][contagio] == -1){
		dicc[localActual][contagio] = max(programacionDinamica(localActual+1, contagio, dicc), programacionDinamica(localActual+2, contagio-contagioPorLocal[localActual], dicc) + beneficioDeLocal[localActual]);
	}
	return dicc[localActual][contagio];
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
    cin >> cantidadDeLocales >> limiteDeContagio;
    beneficioDeLocal.assign(cantidadDeLocales, 0);
    contagioPorLocal.assign(cantidadDeLocales, 0);


    for (int i = 0; i < cantidadDeLocales; ++i) {
    	cin >> beneficioDeLocal[i];
    	cin >> contagioPorLocal[i];
    }

    vector<int> solParcial;
    cout << "Cantidad de locales: " << cantidadDeLocales << endl;
    cout << "Limite de contagio: " << limiteDeContagio << endl;

    // Ejecutamos el algoritmo y obtenemos su tiempo de ejecución.
	int optimum;
	//optimum = INFTY;
	auto start = chrono::steady_clock::now();
	if (algoritmo == "FB")
	{
		optimum = fuerzaBruta(0, 0, limiteDeContagio, solParcial);
	}
	else if (algoritmo == "BT")
	{
		//K = INFTY;
		//poda_optimalidad = poda_factibilidad = true;
		optimum = backtracking(0, 0, limiteDeContagio, solParcial);
	}
	else if (algoritmo == "BT-F")
	{	//Acá va la imprementación con Backtraking con poda por factivilidad
		//poda_optimalidad = false;
		//poda_factibilidad = true;
		//optimum = BT(0, 0, 0);
	}
	else if (algoritmo == "BT-O")
	{	//Acá va la imprementación con Backtraking con poda por óptimalidad
		//poda_optimalidad = true;
		//poda_factibilidad = false;
		//optimum = BT(0, 0, 0);
	}
	else if (algoritmo == "PD")
	{
		// Obtenemos la solucion optima.
		vector< vector<int> > dicc(cantidadDeLocales+1, vector<int>(limiteDeContagio+1, -1));
		optimum = programacionDinamica(0, limiteDeContagio, dicc);
	}
	auto end = chrono::steady_clock::now();
	double total_time = chrono::duration<double, milli>(end - start).count();

	// Imprimimos el tiempo de ejecución por stderr.
	clog << "Tiempo en ejecución: " << total_time << endl;

    // Imprimimos el resultado por stdout.
    cout << (optimum == infinito ? -1 : optimum) << endl;
   
    return 0;
}
