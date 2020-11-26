#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED
typedef struct{
    char nombre[50];
    char apellido[50];
    char cuit[50];
    int idCliente;
    int isEmpty;
}Cliente;



Cliente* clientes_new();
void clientes_delete();
Cliente* clientes_newConParametros(int idCliente, char *nombre, char *apellido, char *cuit);

int clientes_setNombre(Cliente* this,char* nombre);
int clientes_getNombre(Cliente* this,char* nombre);

int clientes_setApellido(Cliente* this,char* apellido);
int clientes_getApellido(Cliente* this,char* apellido);

int clientes_setIdCliente(Cliente* this,char* idCliente);
int clientes_getIdCliente(Cliente* this,int* idCliente);

int clientes_setIsEmpty(Cliente* this,char* isEmpty);
int clientes_getIsEmpty(Cliente* this,int* isEmpty);

int clientes_setCuit(Cliente *this, char* clientCuit);
int clientes_getCuit(Cliente *this, char* clientCuit);

void clientes_mostrar(void* pCliente);

#endif // CLIENTES_H_INCLUDED
