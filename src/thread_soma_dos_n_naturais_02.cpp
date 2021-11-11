#include <iostream>
#include <unistd.h> // sleep

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

const int N_THREADS = 5;
pthread_t thread[N_THREADS]; // num da thread
int status; 
void * thread_return;
// g++ thread_soma_dos_n_naturais.cpp -o teste -lpthread && ./teste

int soma = 0;

void * hello_word(void * tid) {
    if((int) (size_t) tid > 0 ) {
        pthread_join(thread[(int) (size_t) tid - 1], &thread_return); // espero a thread anterior
        // garantidno sequencialidade
         cout << ". A Thread #" << (int) (size_t) tid -1 << " terimnou. \n" << 
            "Esta é a Thread #" << (int) (size_t) tid << " \n";
    } else {
        cout << "Essa é a primeira Thread #" << (int) (size_t) tid << " \n";
    }
   
    soma = soma + 1;
    cout << "O valor da sua soma é " << soma << "\n";
    sleep(1);
    pthread_exit(NULL);
}

// neste código temos duas threads a que executa o main e a que executa o hello_word
int main(int argc, char const *argv[]) {
    
    int i = 0;
    for (i = 0; i < N_THREADS; i++) {
        cout << "Processo principal criado thread #" << i << "\n";
        status = pthread_create(&thread[i], NULL, hello_word, (void *) (size_t) i);

        if(status != 0 ) {
            cout << "Erro na criação da thread. \n Código de erro: " << status << "\n";
            return 1;
        }
    }
    
    cout << "Esperando a thread " << i - 1 << " finalizar \n";
    pthread_join(thread[i - 1], &thread_return);
    cout << "Processo pai vai finalizar \n";
    cout << "Thread " << i - 1 << " finalizada!\n";
    
    return 0;
}
