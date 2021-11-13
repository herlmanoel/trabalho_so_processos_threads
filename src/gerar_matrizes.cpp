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

int main(int argc, char *argv[]) {

    Matriz* m1 = new Matriz();
    Matriz* m2 = new Matriz();


    m1->gerarMatrizArquivo(6, 6, "data/arquivo01.txt");
    m1->gerarMatrizArquivo(6, 6, "data/arquivo02.txt");

    
    return 0;
}