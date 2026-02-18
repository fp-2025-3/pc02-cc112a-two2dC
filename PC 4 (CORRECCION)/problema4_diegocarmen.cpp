#include <iostream>
#include <cstring>
using namespace std;

struct Item{
    char *descripcion; 
    int cantidad;
    double precioUnitario;
};
struct Pedido{
    int numeroPedido;
    char *nombreCliente;
    Item *items;
    int cantidadItems;
};

Item crearItem(const char *descripcion, int cantidad, double precio){
    Item it;
    it.descripcion = new char[strlen(descripcion) + 1]; strcpy(it.descripcion, descripcion);
    it.cantidad = cantidad;
    it.precioUnitario = precio;
    return it;

}
void *crearPedido(int numero, const char *cliente, int cantidaditems){ //CANTIDADITEMS=3;
    Pedido *nuevo=new Pedido();
    nuevo->nombreCliente=new char[strlen(cliente)+1];
    nuevo->items=new Item[cantidaditems];
    nuevo->cantidadItems=cantidaditems;
    nuevo->numeroPedido=numero;

    strcpy(nuevo->nombreCliente,cliente);
    nuevo->items[0]=crearItem("Latop",1,100);
    nuevo->items[1]=crearItem("Mouse",2,200);
    nuevo->items[2]=crearItem("Teclado",3,300);

    return nuevo;
}
double calcularTotal(const Pedido *p){
    double suma=0;
    for(int i(0);i<p->cantidadItems;i++){
        suma+=p->items[i].cantidad * p->items[i].precioUnitario;
    }
    return suma;
}
void *itemMasCaro(Pedido *p){
    int ind, mayor=0;
    for(int i(0);i<p->cantidadItems;i++){
        if(p->items[i].precioUnitario>mayor){
            mayor=p->items[i].precioUnitario;
            ind=i;
        }
    }
    cout<<"\nItem mas caro: "<<p->items[ind].descripcion<<" | Precio: "<<mayor<<endl;
    return &p->items[ind];
}
void liberarPedido(Pedido *p){
    for(int i = 0; i < p->cantidadItems; i++){
        delete[] p->items[i].descripcion;
    }

    delete[] p->items;
    delete[] p->nombreCliente;
    delete p;
}

int main() {
    Pedido *p= (Pedido*)crearPedido(101, "Carlos Perez", 3);
   
    cout<<"\nPedido N: "<<p->numeroPedido;
    cout<<"\nCliente: "<<p->nombreCliente;
    
    cout<<"\n\nItems:";
    for(int i(0);i<p->cantidadItems;i++){
        cout<<"\n -"<<p->items[i].descripcion<<" | Cant: "<<p->items[i].cantidad<<" | Precio: "<<p->items[i].precioUnitario;
    }
    cout<<endl<<endl;

    cout<<"Total: "<<calcularTotal(p);
    itemMasCaro(p);
    liberarPedido(p);
    return 0;
}