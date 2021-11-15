#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include "Matriz.cpp"

using namespace std;
using namespace std::chrono;

vector<vector<int>> n1;

// cd "/home/herlmanoel/dev/SO/exercicio01/src/" && g++ sequencial.cpp -o sequencial && "/home/herlmanoel/dev/SO/exercicio01/src/"sequencial arquivo01.txt arquivo02.txt
int main(int argc, char *argv[]) {
    double soma = 0;
    for (int z = 1; z <= 10; z++) {
        string arquivo_matriz_01 = argv[1];
        string arquivo_matriz_02 = argv[2];

        string pathBase = "data/";

        arquivo_matriz_01 = pathBase + "input/" + arquivo_matriz_01;
        arquivo_matriz_02 = pathBase + "input/" + arquivo_matriz_02;

        // int P = 4;
        // string arquivo_matriz_01 = "arquivo01.txt";
        // string arquivo_matriz_02 = "arquivo02.txt";

        Matriz* m1 = new Matriz(arquivo_matriz_01);
        Matriz* m2 = new Matriz(arquivo_matriz_02);
        
        vector<vector<int>> res;
        steady_clock::time_point begin = steady_clock::now();
        for (int i = 0; i < m1->linhas; i++) {
            res.push_back(vector<int>());
            for (int j = 0; j < m2->colunas; j++) {
                res[i].push_back(0);
                for (int k = 0; k < m1->linhas; k++) {
                    res[i][j] += m1->matriz[i][k] * m2->matriz[k][j];
                }
            }
        }
        steady_clock::time_point end = steady_clock::now();
        string tempoMili = to_string(duration_cast<milliseconds>(end - begin).count());
        string tempo = "Tempo " + tempoMili + "\n";
        string nomeArquivoCompleto = pathBase + "matriz_result.txt";
        ofstream out(nomeArquivoCompleto);
        out << m1->linhas  << " " <<  m2->colunas <<  "\n"; 
        for (int i = 0; i < m1->linhas; i++) {
            for (int j = 0; j < m2->colunas; j++) {
                out << "C_" << i  << "_" << j << " " <<  res[i][j] <<  "\n"; 
            }
        }
        out << tempo;
        float tempoFloat = stof(tempoMili);
        cout <<  "TEMPO [" << z << "]: " << tempoFloat << endl;
        soma += tempoFloat;
        out.close();
    }
    cout << "MEDIA: " << soma/10 << endl;
    
    return 0;
}