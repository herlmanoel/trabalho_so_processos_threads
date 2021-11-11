#include <iostream>
#include <unistd.h> // sleep

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int N_THREADS = 5;

// g++ thread_soma_dos_n_naturais.cpp -o teste -lpthread && ./teste


void * hello_word(void * tid) {
    cout << "Hollo Word. Esta é a thread " << (int) (size_t) tid << "\n";

    sleep(((int) (size_t) tid + 1) + 2);
    pthread_exit(NULL);
}

// neste código temos duas threads a que executa o main e a que executa o hello_word
int main(int argc, char const *argv[]) {
    pthread_t thread[N_THREADS]; // num da thread
    int status; 
    void * thread_return;
    
    for (int i = 0; i < N_THREADS; i++) {
        cout << "Processo principal criado #" << i;
        status = pthread_create(&thread[i], NULL, hello_word, (void *) (size_t) i);

        if(status != 0 ) {
            cout << "Erro na criação da thread. \n Código de erro: " << status << "\n";
            return 1;
        }
    }
    
    cout << "Processo principal criando a Thread \n";
       
    for (int i = 0; i < N_THREADS; i++) {
        cout << "Esperando Thread #" << i << " finalizar \n";
        pthread_join(thread[i], &thread_return);
        cout << "Thread #" << i << " finalizada! \n";
    }

    cout << "Processo pai vai finalizar \n";
    
    return 0;
}
