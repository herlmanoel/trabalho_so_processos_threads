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
        int elemento = 0;
        for (int i = 0; i < m1->colunas; i++) {
            elemento += m1->matriz[linha][i] * m2->matriz[i][coluna];
        }
        return elemento;
    }


int main(int argc, char *argv[]) {
    string arquivo_matriz_01 = argv[1];
    string arquivo_matriz_02 = argv[2];
    int P = atoi(argv[3]);

    // int P = 4;
    // string arquivo_matriz_01 = "arquivo01.txt";
    // string arquivo_matriz_02 = "arquivo02.txt";

    Matriz* m1 = new Matriz(arquivo_matriz_01);
    Matriz* m2 = new Matriz(arquivo_matriz_02);

    Matriz* res = new Matriz(m1->linhas, m2->colunas);
    vector<vector<int>>* matrizResultado = &(res->matriz);

    int qtdElementos = m1->linhas * m2->colunas;
    int qtdProcessos = qtdElementos  / P;
    int resto = qtdElementos % P;

    if(resto > 0) {
        qtdProcessos++;
    }

    pid_t processo_filho[qtdProcessos];

    m1->gerarMatrizArquivo(6, 6, "arquivo01.txt");
    m1->gerarMatrizArquivo(6, 6, "arquivo02.txt");

    // res->printMatriz();


    // m1->printMatriz();
    // cout << endl << endl;
    // m2->printMatriz();
    // cout << endl << endl;

    // res->printMatriz();
    

    // cout << "Pai #" << getpid() << endl;

    for(int i = 0; i < qtdProcessos; i++) {
        processo_filho[i] = fork();

        if(processo_filho[i] == (pid_t) 0) {
            int inicio = i;
            int fim = P - 1;
            
            if (inicio > 0) {
                inicio = i * P;
                fim = ((i+1) * P) - 1;
            }

            // cout << "inicio: " << inicio << endl;
            // cout << "fim: " << fim << endl;
        
            string nomeArquivo = to_string(qtdProcessos) + "_" + to_string(qtdProcessos) + "_" + to_string(i) + "_arquivo"+ ".txt";
            ofstream out(nomeArquivo);
            // cout << inicio << " " << fim << endl;
            for(int j = inicio; j <= fim; j++) {
                int l = j / 6;
                int c = j % 6; 
                
                int n = calculaElemento(m1, m2, l, c);
                out << l << "_" << c << " "<< n << endl;
                int indicePosterior = j + 1;
                if (indicePosterior >= qtdElementos) {
                    break;
                }
            }  
            // cout << endl;
            
            // cout << i << " " << " # " << getpid() << endl;
            out.close(); 
            exit(0);
        } else {
            wait(NULL);
        }
    }  

    string nomeArquivoCompleto = "arquivoCompleto.txt";
    ofstream out(nomeArquivoCompleto);
    for (size_t i = 0; i < qtdProcessos; i++) {
        string nomeArquivo = to_string(qtdProcessos) + "_" + to_string(qtdProcessos) + "_" + to_string(i) + "_arquivo"+ ".txt";
        string filename(nomeArquivo);
        string line;
        ifstream input_file(filename);

        int count = 0;
        while (getline(input_file, line)){
            out << line << endl; 
        }
    }
    out.close(); 
    
        

    // res->printMatriz((*matrizResultado));
    return 0;
}