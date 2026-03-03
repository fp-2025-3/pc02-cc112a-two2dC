#include <iostream>
#include <fstream>
using namespace std;

const int MAX=150;

struct Venta{
    int idVenta;
    int idVendedor;
    int idProducto;
    int cantidad;
    double precioUnitario;
};

int buscarID(int ids[], int n, int id) {
    for(int i(0);i<n;i++){
        if(ids[i]==id) return i;
    }    
    return -1;
}

void total(fstream &d, Venta &e, int &t_r, double &t_m, int ID_vendedor[], double recaudacion[], int &num_vendedores, int ID_producto[], int unidades[], int &num_productos){
    while (d.read((char *)&e, sizeof(Venta))) {
        double monto = e.cantidad * e.precioUnitario;
        t_r++;
        t_m += monto;

        int iv = buscarID(ID_vendedor, num_vendedores, e.idVendedor);
        if(iv == -1){
            ID_vendedor[num_vendedores] = e.idVendedor;
            recaudacion[num_vendedores] = monto;
            num_vendedores++;
        }else{
            recaudacion[iv] += monto;
        }

        int ip = buscarID(ID_producto, num_productos, e.idProducto);
        if (ip == -1) {
            ID_producto[num_productos] = e.idProducto;
            unidades[num_productos]    = e.cantidad;
            num_productos++;
        }else{
            unidades[ip] += e.cantidad;
        }
    }
}

int mejorVendedor(int idsVendedor[], double recaudacion[], int numVendedores) {
    int id=0;
    for (int i(1); i < numVendedores; i++){
        if(recaudacion[i]>recaudacion[id]) id=i;
    }
    return id;
}

int mejorProducto(int idsProducto[], int unidades[], int numProductos) {
    int id=0;
    for (int i(1);i<numProductos; i++){
        if(unidades[i]>unidades[id]) id=i;
    }
    return id;
}

void sospechosas(Venta &e,fstream &d, ofstream &r){
    d.clear();  
    d.seekg(0);
    while(d.read((char *)&e, sizeof(Venta))){
        if(e.cantidad>100){
            r<<"\nID Venta: "<<e.idVenta<<" | Vendedor: "<<e.idVendedor<<" | Producto: "<<e.idProducto<<" | Cantidad: "<<e.cantidad;
        }
    }
}

void REPORTE_GENERAL(const char *a, Venta &e){
    fstream datos(a,ios::binary | ios::in);
    ofstream reporte("reporte.txt");
    int total_registros(0),ids_vendedor[MAX], ids_producto[MAX], unidades[MAX], numVendedores(0), numProductos(0) ;
    double total_monto(0), recaudacion[MAX];
    
    if(!datos.is_open()){
        cout<<"\nNO SE PUDO ABRIR EL ARCHIVO.\n";
        return ;
    }
    
    total(datos, e, total_registros, total_monto,ids_vendedor, recaudacion, numVendedores, ids_producto, unidades, numProductos);

    int idx_vendedor = mejorVendedor(ids_vendedor, recaudacion, numVendedores);
    int idx_producto = mejorProducto(ids_producto, unidades, numProductos);

    reporte<<"\n--- REPORTE  GENERAL DE VENTAS ---\n";
    reporte<<"\nTotal de registros: "<<total_registros<<endl;
    reporte<<"\nMONTO TOTAL VENDIDO: "<<endl<<"S/. "<<total_monto<<endl;
    reporte<<"\n---------------------"<<endl;
    reporte<<"VENDEDOR CON MAYOR RECAUDACIÓN: "<<endl;
    reporte<<"ID Vendedor: "<<ids_vendedor[idx_vendedor] <<endl;
    reporte<<"Total vendido: "<<"S/. "<<recaudacion[idx_vendedor] <<endl;
    reporte<<"\n---------------------"<<endl;
    reporte<<"PRODUCTO MÁS VENDIDO: "<<endl;
    reporte<<"ID Producto: "<<ids_producto[idx_producto]<<endl;
    reporte<<"Total unidades: "<<unidades[idx_producto]<<endl;
    reporte<<"\n---------------------"<<endl;
    reporte<<"VENTAS SOSPECHOSAS(cantidad> 100): "<<endl;
    sospechosas(e, datos, reporte);
    
    reporte<<endl;
    datos.close();
}

int main(){
    const char *nombre="ventas.dat";
    Venta p;
    REPORTE_GENERAL(nombre, p);
    return 0;
}