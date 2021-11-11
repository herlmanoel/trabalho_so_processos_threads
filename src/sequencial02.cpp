#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "Matriz.cpp"

using namespace std;
using namespace std::chrono;


// cd "/home/herlmanoel/dev/SO/exercicio01/" && 
// g++ sequencial02.cpp Matriz.cpp -o sequencial02 &&
//  "/home/herlmanoel/dev/SO/exercicio01/"sequencial02
int main(int argc, char *argv[]) {
    // int dim_n1 = atoi(argv[1]);
    // int dim_m1 = atoi(argv[2]);
    // int dim_n2 = atoi(argv[3]);
    // int dim_m2 = atoi(argv[4]);

    int dim_n1 = 4;
    int dim_m1 = 4;
    int dim_n2 = 4;
    int dim_m2 = 4;

    Matriz* m1 = new Matriz("arquivo01.txt");

    m1->printMatriz();

    m1->gerarMatrizArquivo(10, 10, "arquivo03.txt");

    return 0;
}