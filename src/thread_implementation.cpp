#include <cekeikon.h>

void inicializa(Mat_<float>& A, Mat_<float>& B, int n, int seed) { 
    A.create(n,n);
    B.create(n,n);
    srand(seed);
    for (int l=0; l<n; l++)
        for (int c=0; c<n; c++)
            A(l,c)=rand()%n;
    for (int l=0; l<n; l++)
        for (int c=0; c<n; c++)
            B(l,c)=rand()%n;
}
void multMatConvencional(const Mat_<float>& A, const Mat_<float>& B, Mat_<float>& D) { 
    D.create(A.rows,B.cols);
 for (int l=0; l<A.rows; l++)
 for (int c=0; c<B.cols; c++) {
 float d=0.0;
 for (int i=0; i<A.cols; i++)
 d=d+A(l,i)*B(i,c);
 D(l,c)=d;
 }
}
