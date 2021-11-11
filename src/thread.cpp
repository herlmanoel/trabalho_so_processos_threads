#include <iostream>


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// add para executar -lpthread
// -lpthread

void * hello_word(void * tid) {
    cout << "Hollo Word. Esta é a thread " << (int) (size_t) tid << "\n";
    pthread_exit(NULL);
}

// neste código temos duas threads a que executa o main e a que executa o hello_word
int main(int argc, char const *argv[]) {
    pthread_t thread; // num da thread
    int status; 
    void * thread_return;
    
    cout << "Processo principal criando a Thread \n";
    status = pthread_create(&thread, NULL, hello_word, 0);
    // &thread -> ao final da execução ela tem o num da thread
    // hello_word -> fun que determina o que a thread vai fazer 
    // 0 -> é uma maneira para eu conseguir identificar quais threads to criando: void * tid

    if(status != 0 ) {
        cout << "Erro na criação da thread. \n Código de erro: " << status << "\n";
        return 1;
    }

    cout << "Esperando thread finalizar \n";

    // pthread_join -> diz qual a thread to esperando terminar
    pthread_join(thread, &thread_return);
    //  &thread_return armazena o return da função

    cout << "Thread finalizada \n";

    cout << "Processo pai vai finalizar \n";
    
    return 0;
}
