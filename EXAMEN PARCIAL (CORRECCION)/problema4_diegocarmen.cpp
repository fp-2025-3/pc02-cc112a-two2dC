#include <iostream> 
using namespace std;

void imprimir(int *codigos, float *promedios, int n){
    for(int i(0);i<n;i++){
        cout<<"\nCodigo: "<<*(codigos+i)<<" Promedio: "<<*(promedios+i);
    }
    cout<<endl;
}

void agregar_estudiante(int *&codigos, float *&promedios, int &n, int &n_MAX){
    
    //AGREGA UN ESTUDIANTE, Y SI ESTA LLENO DUPLICA LA CAPACIDAD
    if(n==n_MAX){
        int *codigos_aux=new int[n]; float *promedios_aux=new float[n];
        int new_n_MAX=n_MAX*2;

        for(int i=0;i<n;i++){
            *(promedios_aux+i)=*(promedios+i);
            *(codigos_aux+i)=*(codigos+i);
        }
        
        delete [] codigos;
        delete [] promedios;
        codigos=new int[new_n_MAX];
        promedios=new float[new_n_MAX];

        for(int i=0;i<n;i++){
            *(promedios+i)=*(promedios_aux+i);
            *(codigos+i)=*(codigos_aux+i);
        }
        n_MAX=new_n_MAX;
        
        delete[] codigos_aux;
        delete[] promedios_aux;
    }

    cout<<"Escriba los datos del estudiante: \n";
    cout<<"\nCodigo: ";cin>>*(codigos+n);
    cout<<"Promedio: ";cin>>*(promedios+n);
    n++;
}
void filtrar_estudiantes(int *&codigos, float *&promedios, int &n, int &n_MAX){
    int *codigos_aux=new int[n]; float *promedios_aux=new float[n];
    int j=0; 

    for(int i=0;i<n;i++){
        if( *(promedios+i) >= 10){
            *(promedios_aux+j)=*(promedios+i);
            *(codigos_aux+j)=*(codigos+i);
            j++;
        }
    }
    
    n_MAX=j;
    n=n_MAX;
    delete [] codigos;
    delete [] promedios;
    codigos=new int[n_MAX];
    promedios=new float[n_MAX];

    for(int i=0;i<n;i++){
        *(promedios+i)= *(promedios_aux+i);
        *(codigos+i)= *(codigos_aux+i);
    }
    delete [] codigos_aux;
    delete [] promedios_aux;
}

int main() {
    int n=5, n_MAX=5; //COMO EN EL EJEMPLO
    int *codigos=new int[n_MAX]{ 101 , 102 , 103 , 104 , 105 }; 
    float *promedios=new float[n_MAX]{ 14.5 , 8.0 , 16.2 , 9.5 , 12.3 };
    char opc;
    
    cout<<"Estudiantes registrados: ";
    imprimir(codigos, promedios, n);
    
    do{
        cout<<"\nDesea agregar un estudiante: (s->SI  o  n->NO): ";cin>>opc;  
    }while(opc!='s' && opc!='n'); //SE USA ESTE BUCLE PARA SABER SI EL USUARIO INGRESO "s" O "n"
    if(opc=='s'){
        agregar_estudiante(codigos, promedios, n, n_MAX);
    }
    
    cout<<"\nFiltrando estudiantes desaprobados...\n";
    filtrar_estudiantes(codigos, promedios, n, n_MAX);
    cout<<"\nEstudiantes aprobados: ";
    imprimir(codigos, promedios, n);

    delete [] codigos;
    delete [] promedios;
    return 0;
}