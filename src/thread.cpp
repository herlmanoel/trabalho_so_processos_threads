#include <thread>
#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include <unistd.h>

#include "Matriz.cpp"
#include <math.h> 
using namespace std;

int calculaElemento(Matriz* m1, Matriz* m2, int linha, int coluna) {
    int elemento = 0;
    for (int i = 0; i < m1->colunas; i++) {
        elemento += m1->matriz[linha][i] * m2->matriz[i][coluna];
    }
    return elemento;
}


//  cd "/home/herlmanoel/dev/SO/exercicio01/src/" && g++ thread.cpp -o thread -pthread && "/home/herlmanoel/dev/SO/exercicio01/src/"thread arquivo01.txt arquivo02.txt 3

void * calcularThread(int i, int P, int qtdElementos, string pathParticoes, Matriz * m1, Matriz * m2) {
    int inicio = i;
    int fim = P - 1;
    if (inicio > 0) {
        inicio = i * P;
        fim = ((i+1) * P) - 1;
    }

    string nomeArquivo = pathParticoes + to_string(m1->linhas) + "_" + 
    to_string(m2->colunas) + "_" + to_string(i) + "_arquivo"+ ".txt";
    ofstream out(nomeArquivo);

    steady_clock::time_point begin = steady_clock::now();
    for(int j = inicio; j <= fim; j++) {
        int linha = j / m1->linhas;
        int coluna = j % m2->colunas; 
        int elemento = calculaElemento(m1, m2, linha, coluna);

        out <<  
            to_string(linha) + "_" + to_string(coluna) +
            " " + to_string(elemento)  + "\n";
        int indicePosterior = j + 1;
        if (indicePosterior >= qtdElementos) {
            break;
        }
    } 
    steady_clock::time_point end = steady_clock::now();
    out << "TEMPO " + to_string(duration_cast<microseconds>(end - begin).count()) + "\n";
    out.close();  
    pthread_exit(NULL);  
}



// cd "/home/herlmanoel/dev/SO/exercicio01/src/" && g++ paralelo.cpp -o paralelo && "/home/herlmanoel/dev/SO/exercicio01/src/"paralelo arquivo01.txt arquivo02.txt 10
// cd "/home/herlmanoel/dev/SO/exercicio01/src/" && g++ thread.cpp -o thread -pthread && "/home/herlmanoel/dev/SO/exercicio01/src/"thread arquivo01.txt arquivo02.txt 3
int main(int argc, char *argv[]) {
    double soma = 0;
    string arquivo_matriz_01 = argv[1];
    string arquivo_matriz_02 = argv[2];
    int P = atoi(argv[3]);

    string pathBase = "data/";
    string pathParticoes = pathBase + "particoes/";

    arquivo_matriz_01 = pathBase + "input/" + arquivo_matriz_01;
    arquivo_matriz_02 = pathBase + "input/" + arquivo_matriz_02;


    Matriz* m1 = new Matriz(arquivo_matriz_01);
    Matriz* m2 = new Matriz(arquivo_matriz_02);

    int qtdElementos = m1->linhas * m2->colunas;
    int qtdThreads = qtdElementos / P;
    int resto = qtdElementos % P;

    if(resto > 0) {
        qtdThreads++;
    }
    
    for (int z = 1; z <= 10; z++) {

        thread *threads = new thread[qtdThreads];
        int status;
        void *retorno_thread;

        for(int i = 0; i < qtdThreads; i++) {
            threads[i] = thread(calcularThread, i, P, qtdElementos, pathParticoes, m1, m2);
        }

        for(int i = 0; i < qtdThreads; i++) {
            threads[i].join();
        }

        string nomeArquivoCompleto = pathBase + "matriz_result.txt";
        ofstream out(nomeArquivoCompleto);
        double tempoTotal = 0.0;
        for (size_t i = 0; i < qtdThreads; i++) {
            string nomeArquivo = pathParticoes + to_string(m1->linhas) + "_" + to_string(m2->colunas) + "_" + to_string(i) + "_arquivo"+ ".txt";
            string filename(nomeArquivo);
            string line;
            ifstream input_file(filename);
            int count = 0;
            while (getline(input_file, line)){

                vector<string> vectorLine = m1->split(line, " ");
                if(!vectorLine[0].compare("TEMPO")) {
                    float tempo = stof(vectorLine[1]);
                    tempoTotal += tempo; 
                    continue;
                }
                out << line << endl;
            }
        }
        tempoTotal = tempoTotal / pow(10, 6);
        out << "TEMPO " << tempoTotal << endl;
        cout <<  "TEMPO [" << z << "]: " << tempoTotal << endl;
        soma += tempoTotal;
        out.close(); 

        delete [] threads;
        
        
    }

    delete m1;
    delete m2;

    cout << "MEDIA: " << soma/10 << endl;
    
    

    return 0;
}