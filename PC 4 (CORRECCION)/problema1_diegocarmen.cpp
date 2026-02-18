#include <iostream>
using namespace std;

void suma_polinomios(int *p1, int *p2, int *p3,int n){
    cout<<"\nSuma de los tres polinomios: ";
    for(int i(0);i<n;i++){
        int suma=*(p1+i)+*(p2+i)+*(p3+i);
        if(i==n-1){
            cout<<suma;
            break;
        }
        cout<<suma<<"x^"<<n-1-i<<" + ";
    }
    cout<<endl;
}
void producto_polinomios(int *p1, int *p2, int *p3, int g_p1, int g_p2, int g_p3){
    
    int tam_p1_p2=g_p1+g_p2+1;
    int *p1_p2=new int[tam_p1_p2]{0};

    for(int i(0);i<=g_p1;i++){
        for(int j(0); j<=g_p2;j++){
            p1_p2[i+j]+= p1[i]*p2[j];
        }
    }

    int tam_pR_p3=g_p1+g_p2+g_p3+1;
    int *pR_p3=new int[tam_pR_p3]{0};

    for(int i(0);i<=tam_p1_p2-1;i++){
        for(int j(0); j<=g_p3;j++){
            pR_p3[i+j]+=p1_p2[i]*p3[j];
        }
    }

    cout << "\nProducto de los tres polinomios: ";
    for (int i(0);i<tam_pR_p3;i++) {
        if(pR_p3[i]!=0){
            cout<<pR_p3[i];
            if (i != tam_pR_p3-1) {
                cout<<"x^"<<tam_pR_p3-1-i<<" + ";
            }
        }
    }
    cout<<endl;

    delete [] p1_p2;
    delete [] pR_p3;
}

int main() {
    int n1=3, n2=3, n3=3;
    int *pol1=new int[n1]{1,0,3};//grado igual a 2
    int *pol2=new int[n2]{0,-4,5};//grado igual a 1
    int *pol3=new int[n3]{3,0,1};//grado igual a 2

    suma_polinomios(pol1,pol2,pol3,3);
    producto_polinomios(pol1,pol2+1,pol3,2,1,2);

    delete [] pol1;
    delete [] pol2;
    delete [] pol3;
    return 0;
}