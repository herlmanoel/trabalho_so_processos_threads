#include <iostream>

using namespace std;

int main() {

  int P = 1;

  int qtdProcessos = (6 * 6) / P;
  int resto = (6 * 6) % P;

  if(resto > 0) {
    qtdProcessos++;
  }
  cout << qtdProcessos << endl;

  for(int i = 0; i < qtdProcessos; i++){
    int inicio = i;
    int fim = P - 1;
    if(inicio > 0) {
      inicio = i * P;
      fim = ((i+1) * P) - 1;
    }
    
    cout << inicio << " " << fim << endl;
    for(int j = inicio; j <= fim; j++) {      

      int l = j / 6;
      int c = j % 6; 
      // cout << l << "_" << c << " " << j << endl;

      if (j > 36) {
        break;
      }
    }
    cout << endl;
  }
} 


// ====================
// #include <iostream>

// using namespace std;

// int main() {

//   int P = 10;

//   int qtdProcessos = (6 * 6) / P;
//   int resto = (6 * 6) % P;

//   if(resto > 0) {
//     qtdProcessos++;
//   }
//   cout << resto << endl;

//   for(int i = 0; i < qtdProcessos; i++){
//     int inicio = i;
//     int fim = P - 1;
//     if(inicio > 0) {
//       inicio = i * P;
//       fim = ((i+1) * P) - 1;
//     }
    
//     // cout << inicio << " " << fim << endl;
//     for(int j = inicio; j <= fim; j++) {      

//       int l = j / 6;
//       int c = j % 6; 
//       cout << l << "_" << c << " " << j << endl;

//       if (j > 36) {
//         break;
//       }
//     }
//     // cout << endl;
//   }
// } 