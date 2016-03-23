#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int n_calculations = 0;//Global variable to calculate number of sub-problems calculated in each method.

/***Calculates C(n,k) by divide and conquer method. Inefficient.**/
long cnk_dc(int n, int k){
	if ( k == 0 || k == n) return 1;
	else{
		n_calculations++;
	   	return cnk_dc(n-1, k) + cnk_dc(n-1, k-1);	
	}
}

/**Calculates C(n,k) by dynamic programming method.**/
long cnk_dp(const int n, const int k){
	int** c = new int*[n+1];
	for (int i = 0; i <= n; i++){
		c[i] = new int[k+1];
	}
	
	//Initialization of array.
	for(int i = 0; i <= n; i++){
		for ( int j = 0; j <= k; j++ ) {
			if ( j == 0 || j == i){
				c[i][j] = 1;
			}
			else{
				c[i][j] = -1;
			}
		}
	}
	
	//Dynamic Programming Algorithm.
	for (int i = 1; i <= n; i++){
		for ( int j = 1; j <= k; j++){
			if (j > i-1 || i == j) continue;
			n_calculations++;
			c[i][j] = c[i-1][j] + c[i-1][j - 1];
		}	
	}

	return c[n][k];
}

long** memory; //Memory Table for memorization technique.

/**Memory allocation of memory table**/
void initialize(int n, int k){
	memory = new long*[n+1];
	for (int i = 0; i <= n; i++){
		memory[i] = new long[k+1];
	}
	for (int i = 0; i <= n; i++){
		for (int j = 0; j <= k; j++){
			memory[i][j] = -1;
		}
	}

}

/**Memory de-allocation of memory table**/
void freearray(int n, int k) {
	for (int i = 0; i <=n; i++ ){
		delete [] memory[i];
	}
}

/**Calculates C(n, k) by  memorization technique**/
long cnk_mm(int n, int k){
	if ( k == 0 || k == n) return 1;
	else if (memory[n][k] > -1 ) return memory[n][k];
	else{
		n_calculations++;
	   	long temp = cnk_mm(n-1, k) + cnk_mm(n-1, k-1);
		memory[n][k] = temp;
		return temp;
	}
}

int main(int argc, char* argv[]){
	ofstream out1("running-time.csv"); //Output file initialized for running time
	ofstream out2("n-subproblems.csv"); //Output file initialized for counting number of subproblems.

	out1 << "N,Divide&Conquer,Dynamic Programming,Memorization" << endl; //Headers in runnign-time file
	out2 << "N,Divide&Conquer,Dynamic Programming,Memorization" << endl;//Headers in number of subproblems counting file
	int start = 0, end = 0; //Start and End values for range of n.
	stringstream(argv[1]) >> start;
	stringstream(argv[2]) >> end;
	int iterations = 20; //Number of iterations set for each C(n, k) calculation, and average is taken.
	int k = 0;
	stringstream(argv[3]) >> k;
	for (int i = start; i <= end; i += 5){
		long t_dc=0, t_dp=0, t_mm=0; //Running time initializers for each method.
		long n_dc=0, n_dp=0, n_mm=0; // Initializers for Number of subproblems solved for each method.
		
		for(int j = 0; j < iterations; j++){
			int  n = i;
			/*Divide and Conquer block starts*/
			n_calculations = 0;
			std::clock_t begin = std::clock();
			long cnk = cnk_dc(n, k);
			int t = ((std::clock() - begin)/(double)(CLOCKS_PER_SEC/1000000));
			t_dc += t;
			n_dc += n_calculations;
			/*Divide and Conquer block ends*/
			
			/*Dynamic Programming block starts*/
			n_calculations = 0;
			begin = std::clock();
			cnk = cnk_dp(n, k);
			t = ((std::clock() - begin)/(double)(CLOCKS_PER_SEC/1000000));
			t_dp += t;
			n_dp += n_calculations;
			/*Dynamic Programming block ends*/

			/*Memorization block starts*/
			initialize(n,k); //Initialize the memory table.

			n_calculations = 0;
			begin = std::clock();
			cnk = cnk_mm(n, k);
			t = ((std::clock() - begin)/(double)(CLOCKS_PER_SEC/1000000));
			t_mm += t;
			n_mm += n_calculations;

			freearray(n, k);//Free up memory table in each itertion.
			/*Memorization block ends*/
		}
		
		/*Write Times and number of subproblems solved to corresponding files*/
		out1 << i << "," << t_dc/(double)iterations << ",";
		out1 << t_dp/(double)iterations << ",";;
		out1 <<  t_mm/(double)iterations <<endl;
		
		out2 << i << "," << n_dc/(double)iterations << ",";
		out2 << n_dp/(double)iterations << ",";;
		out2 <<  n_mm/(double)iterations <<endl;
	}
	
	//Close file pointers.
	out1.close();
	out2.close();

	return 0; //Return main program successfully.
}
