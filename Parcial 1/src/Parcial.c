/*
 ============================================================================
 Name        : Parcial.c
 Author      : gula
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utn.h"
#include "clientes.h"
#include "publicacion.h"
#include "informes.h"

#define CANTIDADCLIENTES 7
#define CANTIDADPUBLICACIONES 7
int informes;

int menu(int*opcion);
int main()
{
	setbuf(stdout, NULL);
    Cliente clientes[CANTIDADCLIENTES];
    Publicacion publicaciones [CANTIDADPUBLICACIONES];
    int opcion;
    int auxid;
    int auxIdCliente;
    char auxNombre [50];
    char auxApellido[50];
    char auxTextoAviso[64];
    int auxNumeroRubro;
    char auxCuit[50];
    int confirmar;
    int i;

    cli_inicializarArray(clientes,CANTIDADCLIENTES);
    publi_inicializarArray(publicaciones,CANTIDADPUBLICACIONES);


    cli_alta(clientes,cli_obtenerID(),CANTIDADCLIENTES,"perez","pedro","152461535");
    cli_alta(clientes,cli_obtenerID(),CANTIDADCLIENTES,"mafia","lucia","22250452");
    cli_alta(clientes,cli_obtenerID(),CANTIDADCLIENTES,"ramiro","azafran","002678226");
    cli_alta(clientes,cli_obtenerID(),CANTIDADCLIENTES,"perro","coriandro","12859218921");
    cli_alta(clientes,cli_obtenerID(),CANTIDADCLIENTES,"rica","cebolla","3421292");

    publi_alta(publicaciones,0,CANTIDADPUBLICACIONES,"Publicacion 0",1);
    publi_alta(publicaciones,1,CANTIDADPUBLICACIONES,"Publicacion 1",2);
    publi_alta(publicaciones,2,CANTIDADPUBLICACIONES,"Publicacion 2",1);
    publi_alta(publicaciones,3,CANTIDADPUBLICACIONES,"Publicacion 3",2);
    publi_alta(publicaciones,4,CANTIDADPUBLICACIONES,"Publicacion 4",2);

    do{
        menu(&opcion);
        switch (opcion){
            case 1:
            		if(!utn_getLetras(auxNombre,50,3,"\nIngrese el nombre: ",
                		"\nError..El nombre debe contener solo letras")&&
                    !utn_getLetras(auxApellido,50,3,"\nIngrese el apellido: ",
                    		"\nError..El apellido debe contener solo letras")&&
                    !utn_getCuit(auxCuit,50,3,"Ingrese el cuit: ",
                    		"Error...Ingrese el cuit debe ingresarse solo con numero Cant 11")){
                        auxid=cli_obtenerID();
                        cli_alta(clientes,auxid,CANTIDADCLIENTES,auxApellido,auxNombre,auxCuit);
                        printf("Alta satisfactoria Nº de Id: %d",auxid);
						getchar();

                    }
                break;
            case 2:
                if(!utn_getEntero(&auxid,3,"\nIngrese el id: ","\nError! Ingrese un id valido ",-1,999)&&
                    !cli_existeId(clientes,CANTIDADCLIENTES,auxid))
                {
                    cli_modificarbyId(clientes,CANTIDADCLIENTES,auxid);
                }else{
                        printf("\nEl id no existe..Vuelva A Intentarlo");
                        getchar();
                    }
                break;
            case 3:
                if(!utn_getEntero(&auxid,3,"\nIngrese el id: ","\nError! Ingrese un id valido ",-1,999)&&
                    !cli_existeId(clientes,CANTIDADCLIENTES,auxid))
                    {
                	cli_listar(clientes,CANTIDADCLIENTES,auxid);
                	!utn_getEntero(&auxIdCliente,3,"\nIngrese Id Cliente:","\n Error! Ingrese un id valido",-1,999)&&
                	!publi_existeIdCliente(publicaciones,CANTIDADPUBLICACIONES,auxIdCliente);
                	if(!utn_getEntero(&confirmar,3,"\nEsta seguro q desea eliminar? 0-si 1-no ",
                	   "Error! Elija una opcion valida",0,1)&& !confirmar)
                	{
                		cli_eliminarbyId(clientes,CANTIDADCLIENTES,auxid,auxIdCliente);
                		printf("Cliente y publicaciones eliminadas con exito\n\n");
                	}
                }else{
                        printf("\nEl id no existe. Vuelva a Intentarlo");
                        getchar();
                    }

                break;
            case 4:
                if(!utn_getEntero(&auxid,3,"\nIngrese el id del cliente: ","\nError...Ingrese un id valido ",-1,999)&&
                    !cli_existeId(clientes,CANTIDADCLIENTES,auxid)&&
                    !utn_getEntero(&auxNumeroRubro,3,"\nIngrese el numero de rubro 1: Arte  2: Publicidad :",
                    		"\nError ingrese un numero valido",0,2)&&
                    !utn_getLetrasYNumeros(auxTextoAviso,64,"\nIngrese el texto del aviso :"))
                    {
                	publi_alta(publicaciones,auxid,CANTIDADPUBLICACIONES,auxTextoAviso,auxNumeroRubro);
                    }else{
                        printf("\nERROR! Vuelva a intentarlo");
                    }
                break;
            case 5:
            	if(!utn_getEntero(&auxid,3,"\nIngrese el id la publicacion a modificar: ","\nError! Ingrese un ID valido ",-1,999)
            			&& !publi_existeId(publicaciones,CANTIDADPUBLICACIONES,auxid))
            	{
            		publi_ImprimiByIdCliente(publicaciones,CANTIDADPUBLICACIONES,clientes,CANTIDADCLIENTES,auxid,&i);
            		if(!utn_getEntero(&confirmar,3,"\nDesea cambiar el estado? 0-si 1-no","\nError! Ingrese una opcion valida",0,1)&&
            			!confirmar){
            				publicaciones[i].estadoPublicacion=0;
            				printf("Publicacion PAUSADA");
            			}
            	}

                break;
            case 6: if(!utn_getEntero(&auxid,3,"\nIngrese el id la publicacion a modificar: ","\nError! Ingrese un ID valido",-1,999)
        			&& !publi_existeId(publicaciones,CANTIDADPUBLICACIONES,auxid))
        	{
        		publi_ImprimiByIdCliente(publicaciones,CANTIDADPUBLICACIONES,clientes,CANTIDADCLIENTES,auxid,&i);
        		if(!utn_getEntero(&confirmar,3,"\nDesea cambiar el estado? 0-si 1-no","\nError! Ingrese una opcion valida",0,1)&&
        			!confirmar){
        				publicaciones[i].estadoPublicacion=0;
        				printf("Publicacion REANUDADA");
        			}
        	}

                break;
            case 7:
            	inf_impClientesYAvisos(clientes,CANTIDADCLIENTES,publicaciones,CANTIDADPUBLICACIONES);
                break;
            case 8:
            	printf("\n1 Cliente mas avisos \n2 Cliente mas avisos pausados\n3 Rubro con mas avisos\n 4-SALIR");
            	    utn_getEntero(&informes,3,"\nIngrese una opcion: ","\nError. Ingrese una opcion de informe",1,3);
            		if(informes==1){
            				inf_clienteMasAvisos(publicaciones,CANTIDADPUBLICACIONES,clientes,CANTIDADCLIENTES);
            		}
            		if(informes==2){
            			inf_clienteMasAvisosPausados(publicaciones,CANTIDADPUBLICACIONES,clientes,CANTIDADCLIENTES);
            		}
            		if(informes==3){
            			inf_rubroMasAvisos(publicaciones,CANTIDADPUBLICACIONES,clientes,CANTIDADCLIENTES);
            		}
            		if (informes==4){
            			break;
            		}break;
            case 9:
            		utn_getEntero(&informes,3,
            				"\nIngrese la opcion de informe: '4' para ver cliente con mas avisos activos,"
            				" '5' para ver cliente con mas avisos pausados","Opcion invalida",4,5);
            		if(informes==4){
            			inf_clienteMasAvisos(publicaciones,CANTIDADPUBLICACIONES,clientes,CANTIDADCLIENTES);
            		}

            		if(informes==5){
            			inf_clienteMasAvisosPausados(publicaciones,CANTIDADPUBLICACIONES,clientes,CANTIDADCLIENTES);
            		}
            }
    }while(opcion!=10);

    return EXIT_SUCCESS;
}
int menu(int*opcion){
    printf("\n1-ALTAS\n2-MODIFICAR\n3-BAJA\n4-PUBLICAR AVISO\n5-PAUSAR AVISO\n6-REANUDAR AVISO \n7-IMPRIMIR CLIENTES\n8-INFORMAR\n9-INFORMES 2"
    		"\n10 Salir");
    utn_getEntero(opcion,3,"\nIngrese una opcion: ","\nError...ingrese una opcion valida...",1,10);
    return 0;

}



