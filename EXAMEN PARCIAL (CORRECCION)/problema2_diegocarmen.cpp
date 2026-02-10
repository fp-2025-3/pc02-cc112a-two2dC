#include <iostream> 
#include <cstring>
using namespace std;
const int N=30, n=20;//N->LOS CORREDORES MAXIMOS QUE PUEDEN PARTICIPAR   n->CANTIDAD MAXIMA DE CARACTERES

void ranking(char (*a)[n], int b[N], int tam){
    for(int i(0);i<tam-1;i++){
        for(int j(0);j<tam-1;j++){
            if( *(b+j+1) < *(b+j) ){
                char temp_nombre[n];
                
                swap( *(b+j),*(b+j+1) );
                strcpy(temp_nombre, *(a+j));
                strcpy(*(a+j), *(a+j+1));
                strcpy(*(a+j+1), temp_nombre);
            }
        }
    }

    for(int i(0);i<tam;i++){
        cout<<i+1<<". "<<*(a+i)<<" - "<<*(b+i)<<" segundos\n";
    }
}

void buscar(char (*a)[n], int b[N], char *c, int tam){
    for(int i(0);i<tam;i++){
        if(strcmp(c,*(a+i)) == 0){
            cout<<"Corredor encontrado";
            cout<<"\nPosicion: "<<i+1;
            cout<<"\nTiempo: "<<*(b+i)<<" segundos\n";
            return ;
        }
    }
    cout<<"Corredor no encontrado\n";
}

void buscar_rango(char (*a)[n], int b[N], int min, int max, int tam){
    cout<<"Corredores en el rango ["<<min<<", "<<max<<"]\n";
    for(int i(0);i<tam;i++){
        if( *(b+i)>=min && *(b+i)<=max ){
            cout<<*(a+i)<<" - "<<*(b+i)<<" segundos\n";
        }
    }
}

int main(){
    char nombre[N][n], c[N]; int tiempo[N], corredores, min, max;

    cout<<"Ingrese el numero de corredores: "; cin>>corredores;
    cout<<endl; cin.ignore();
    for(int i(0);i<corredores;i++){
        cout<<"Nombre del corredor "<<i+1<<": ";
        cin.getline(*(nombre+i), n);
        cout<<"Tiempo (en segundos): ";cin>>tiempo[i];
        cin.ignore();
    }
    cout<<"\n\nRANKING FINAL: \n";
    ranking(nombre, tiempo, corredores);

    cout<<"\nIngrese nombre a buscar: ";cin.getline(c,n);
    buscar(nombre,tiempo, c, corredores);

    cout<<"\nIngrese tiempo minimo y maximo: ";cin>>min>>max;
    buscar_rango(nombre,tiempo, min, max, corredores);

    return 0;
}