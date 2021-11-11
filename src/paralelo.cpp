#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include <sys/wait.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#include "Matriz.cpp"

using namespace std;

int calculaElemento(Matriz* m1, Matriz* m2, int linha, int coluna) {
        int soma = 0;
        for (int i = 0; i < m1->colunas; i++) {
            soma += m1->matriz[linha][i] * m2->matriz[i][coluna];
            cout << m1->matriz[linha][i] << " * " << m2->matriz[i][coluna] << " + ";
        }
        cout << "= " << soma;
        cout <<  endl << endl;
        

        // cout << linha << "_" << coluna << ": " << soma << endl;
        return soma;
    }


// cd "/home/herlmanoel/dev/SO/exercicio01/" && 
// g++ sequencial02.cpp Matriz.cpp -o sequencial02 &&
//  "/home/herlmanoel/dev/SO/exercicio01/"sequencial02
int main(int argc, char *argv[]) {
    // int dim_n1 = atoi(argv[1]);
    // int dim_m1 = atoi(argv[2]);
    // int dim_n2 = atoi(argv[3]);
    // int dim_m2 = atoi(argv[4]);

    int P = 2;

    Matriz* m1 = new Matriz("arquivo01.txt");
    Matriz* m2 = new Matriz("arquivo02.txt");

    Matriz* res = new Matriz(m1->linhas, m2->colunas);
    vector<vector<int>>* matrizResultado = &(res->matriz);

    int qtdProcessos = (m1->linhas * m2->colunas) / P;

    pid_t processo_filho[qtdProcessos];


    // m1->printMatriz();
    // m2->printMatriz();
    // res->multiplicar(m1, m2, res);
    // m1->gerarMatrizArquivo(2, 2, "arquivo01.txt");
    // m1->gerarMatrizArquivo(2, 2, "arquivo02.txt");

    // res->printMatriz();


    m1->printMatriz();
    cout << endl << endl;
    m2->printMatriz();
    cout << endl << endl;

    res->printMatriz();
    

    // cout << "Pai #" << getpid() << endl;

    for(int i = 0; i < qtdProcessos; i++){
        processo_filho[i] = fork();
        if(processo_filho[i] == (pid_t) 0) {
            string nomeArquivo = to_string(qtdProcessos) + "_" + to_string(qtdProcessos) + "_" + to_string(i) + "_arquivo"+ ".txt";
            ofstream out(nomeArquivo);
            for(int j = 0; j < P; j++) {
                int n = calculaElemento(m1, m2, i, j);
            }  
            // cout << i << " " << " # " << getpid() << endl;
            out.close(); 
            exit(0);
        } else {
            wait(NULL);
        }
        res->printMatriz((*matrizResultado));

    }  

    res->printMatriz((*matrizResultado));
    return 0;
}