#include <iostream>
#include <fstream>
using namespace std;

struct Empleado{
    int id;
    char nombre[30];
    double salario;
};

void acceder(const char *a, Empleado &e){
    fstream datos(a,ios::binary | ios::in | ios::out);
    if(!datos.is_open()){
        cout<<"\nNO SE PUDO ABRIR EL ARCHIVO.\n";
        return ;
    }

    int ID;
    double nuevo_salario;
    cout<<"Ingrese ID de empleado: ";cin>>ID;

    cout<<"\n--- DATOS DEL EMPLEADO ---";
    datos.seekg((ID-1)*sizeof(Empleado));
    datos.read((char *)&e, sizeof(Empleado));
    cout<<"\nID: "<<e.id;
    cout<<"\nNombre: "<<e.nombre;
    cout<<"\nSalario: "<<e.salario;
    
    do{
        cout<<"\nIngrese nuevo salario: ";cin>>nuevo_salario;
    }while(nuevo_salario<=0);
    e.salario=nuevo_salario;
    datos.seekp((ID-1)*sizeof(Empleado));
    datos.write((char *)&e, sizeof(Empleado));
    cout<<"\nSalario actualizado correctamente."<<endl;

    datos.close();
}

int main(){
    const char *nombre="empleados.dat";
    Empleado p;
    acceder(nombre, p);
    return 0;
}