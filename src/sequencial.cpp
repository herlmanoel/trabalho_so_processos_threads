#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
using namespace std::chrono;

vector<vector<int>> n1;

// g++ arquivo01.cpp -Wall -o prog && prog
int main(int argc, char *argv[]) {
    // int dim_n1 = atoi(argv[1]);
    // int dim_m1 = atoi(argv[2]);
    // int dim_n2 = atoi(argv[3]);
    // int dim_m2 = atoi(argv[4]);

    int dim_n1 = 4;
    int dim_m1 = 4;
    int dim_n2 = 4;
    int dim_m2 = 4;

    vector<vector<int>> n1;

    for (int i = 0; i < dim_n1; i++) {
        n1.push_back(vector<int>());
        for (int j = 0; j < dim_m1; j++) {
            n1[i].push_back(rand() % 10 + 1);
        }
    }   
        

    vector<vector<int>> n2;
    for (int i = 0; i < dim_n2; i++) {
        n2.push_back(vector<int>());
        for (int j = 0; j < dim_m2; j++) {
            n2[i].push_back(rand() % 10 +1);
        }
    }

    
    vector<vector<int>> res;
    steady_clock::time_point begin = steady_clock::now();
    for (int i = 0; i < dim_m1; i++) {
        res.push_back(vector<int>());
        for (int j = 0; j < dim_m2; j++) {
            res[i].push_back(0);
            for (int k = 0; k < dim_m1; k++) {
                res[i][j] += n1[i][k] * n2[k][j];
            }
        }
    }
    steady_clock::time_point end = steady_clock::now();
    cout << "\n \n" << "Tempo: " << duration_cast<milliseconds>(end - begin).count() << " [ms]" << endl;


	ofstream out("arquivo02.txt");
    out << dim_m1  << " " <<  dim_m2 <<  "\n"; 
    for (int i = 0; i < dim_m1; i++) {
        for (int j = 0; j < dim_m2; j++) {
            out << "C_" << i  << "_" << j << " " <<  res[i][j] <<  "\n"; 
            // out << res[i][j] <<  " ";   
        }
        // out <<  "\n"; 
    }
	out.close();
    
    return 0;
}