#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void generar_archivo(const char *a){
    ifstream leer(a);
    ofstream reporte("reporteAlumnos.txt");
    int codigo, total_estudiantes(0), i , j, k;  
    //el promedio menor es 21 para que se actualice cuando se evalue con el primero
    //el promedio mayor es 0 para que se actualice cuando se evalue con el primero
    float promedio, promedio_mayor(0), promedio_menor(21), promedio_general(0);
    string nombre, condicion, nombre_menor, nombre_mayor;

    if(!leer.is_open()){
        cout<<"\nNO SE PUDO ABRIR EL ARCHIVO.\n";
        return ;
    }else{
        while(leer>>codigo>>nombre>>i>>j>>k){
            total_estudiantes++;
            promedio=(i+j+k)/3.0;
            promedio_general+=promedio;

            if(promedio_menor>promedio){
                promedio_menor=promedio;
                nombre_menor=nombre;
            }
            if(promedio_mayor<promedio){
                promedio_mayor=promedio;
                nombre_mayor=nombre;
            }

            reporte<<codigo<<" "<<nombre<<" "<<promedio<<" ";
            if(i<5 || j<5 || k<5){
                reporte<<"DESAPROBADO POR REGLA ACADÉMICA";
            }else if(promedio>=10){
                reporte<<"APROBADO";
            }else{
                reporte<<"DESAPROBADO";
            }
            reporte<<endl;
        }
        promedio_general/=total_estudiantes;
        reporte<<"\n\nTotal de estudiantes: "<<total_estudiantes<<"\n";
        reporte<<"Promedio general: "<<promedio_general<<"\n";
        reporte<<"Estudiante con mayor promedio: "<<nombre_mayor<<" "<<promedio_mayor<<"\n";
        reporte<<"Estudiante con menor promedio:"<<nombre_menor<<" "<<promedio_menor<<"\n";
    }
}

int main(){
    const char *nombre="notas.txt";
    generar_archivo(nombre);
    return 0;
}