#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Seleccion{
    string nombre;
    int PG;
    int PE;
    int PP;
    int GF;
    int GC;
    int DG;
    int puntaje_total;
    float rendimiento;
};

void registrar(Seleccion *&p, const int n){
    for(int i(0);i<n;i++){
        int suma1(0), suma2(0);
        int num1=rand()%100;
        int num2=rand()%(100-num1);

        p[i].PG=num1;
        p[i].PE=num2;
        p[i].PP=100-num1-num2;

        //PARTIDOS GANADOS     n1->GOLES A FAVOR          n2->GOles en CONTRA
        num1=1+rand()%5; //Genera de 1 a 5
        num2=rand()%(num1); //Genera de 0 a num1-1

        suma1+=p[i].PG * num1;
        suma2+=p[i].PG * num2;
        //PARTIDOS EMPATADOS
        num1=rand()%6;
        suma1+=p[i].PE * num1;
        suma2+=p[i].PE * num1;
        //PARTIDOS PERDIDOS
        num2=1+rand()%5; //Genera de 1 a 5
        num1=rand()%num2; //Genera de 0 a num2-1
        suma1+=p[i].PP * num1;
        suma2+=p[i].PP * num2;

        p[i].GF=suma1;
        p[i].GC=suma2;

        p[i].DG=suma1-suma2;
        p[i].puntaje_total= p[i].PE + p[i].PG*3;
        p[i].rendimiento=100 * (p[i].puntaje_total / (300.0));
    }
}
void imprimir(Seleccion *p, const int n){
    cout<<"Seleccion\tPG\tPE\tPP\tGF\tGC\tDG\tPts\tRend(%)\n";
    for(int i(0);i<n;i++){
        cout<<p[i].nombre<<"\t\t"<<p[i].PG<<"\t"<<p[i].PE<<"\t"<<p[i].PP<<"\t"<<p[i].GF<<"\t"<<p[i].GC<<"\t"<<p[i].DG<<"\t"<<p[i].puntaje_total<<"\t"<<p[i].rendimiento;
        cout<<endl;
    }
}
void ordenar(Seleccion *&p, const int n){
    for(int i(0);i<n-1;i++){
        for(int j(0);j<n-1;j++){
            if(p[j+1].puntaje_total>p[j].puntaje_total){
                swap(p[j+1],p[j]);
            }
            if(p[j+1].puntaje_total==p[j].puntaje_total){
                if(p[j+1].DG>p[j].DG){
                    swap(p[j+1],p[j]);
                }else if(p[j+1].GF>p[j].GF){
                    swap(p[j+1],p[j]);
                }
            }
        }
    }
    imprimir(p,n);
    cout<<"\nCampeon: "<<p[0].nombre<<"| Puntaje: "<<p[0].puntaje_total<<"| DG: "<<p[0].DG<<"| Rendimiento: "<<p[0].rendimiento<<"%";
    cout<<endl;
}

int main() {
    srand(time(NULL));
    const int n_paises=5;
    Seleccion *paises=new Seleccion[n_paises];
    paises[0].nombre="Peru";paises[1].nombre="Chile";paises[2].nombre="Bolivia";paises[3].nombre="USA";paises[4].nombre="Brasil";

    registrar(paises, n_paises);
    ordenar(paises,n_paises);

    delete []paises;
    return 0;
}