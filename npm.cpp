#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <set>
#include <map>

using namespace std;
//n cantidad de locales
//M limite de contagio
//b y c, beneficio y contagio

int n, M;
vector<int> b, c;

//i el local que estoy tomando en cuenta
//k cardinal hasta el momento. 
int FB(int i, int k, int contagio, vector<int>& solParcial){
	if (i >= n) //caso en que soy hoja
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
	int der = FB(i+2, k+b[i], contagio-c[i], solParcial);
	//sumo dos a i para que no agarre el de al lado si es que agrego un negocio

	solParcial.pop_back();
	int izq = FB(i+1, k, contagio, solParcial);

	return max(izq, der);
}

int maximo; 

int BT(int i, int k, int contagio, vector<int>& solParcial){
	if (i >= n) //caso en que soy hoja
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
	int der = BT(i+2, k+b[i], contagio-c[i], solParcial);
	//sumo dos a i para que no agarre el de al lado ya que agrego al negocio i. 

	solParcial.pop_back();
	int izq = BT(i+1, k, contagio, solParcial);

	return max(izq, der);
}

//defino un diccionario
int infinito = -10e6;
vector< vector<int> > dicc;
int pd(int i, int m){ //m = M pero como variable local, para no cambiar M 

	//cout << i << "t" << m <<endl;
	if(m<0) return infinito;
	if(m==0) return 0;
	if(i>=n) return 0;
	if(i>=n and m==0) return 0;
	if(dicc[i][m] == -1){
		dicc[i][m] = max(pd(i+1, m), pd(i+2, m-c[i]) + b[i]); 
	}
	return dicc[i][m];
}


int main()
{
	n=5; 
	M=40;
	b={50, 25, 10, 20, 15};
	c={10, 10, 20, 30, 20};

	std::vector<int> v;

	int res = FB(0, 0, 40, v);
	cout << "la respuesta es " << res << endl;

	/*for (int i = 0; i < v.size(); ++i)
	{
		cout << v[i] << ", ";
	}*/

	//vector<vector<int>> N;
	dicc = vector<vector<int>>(n+1, vector<int>(M+1, -1));
	/*for (int i = 0; i < n+1; ++i)
			for (int j = 0; j < M+1; ++j)
				pd(i, j);*/

	cout<< "llegue";

	int res3 = pd(0, 40);

	cout << res3<< endl; 

	return 0;
}