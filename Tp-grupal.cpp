#include <iostream>
#include <conio.h>
#include <string.h>

using namespace std;

// Registro de asegurados
struct Asegurados
{
    int nroPoliza;
    char dni[12];
    char nombre[25];
    char apellido[25];
    bool cuotaDia;
    char patenteAuto[8];
    bool activa;
    int cantIncidentes;
};

struct NodoAsegurados
{
    Asegurados info;
    NodoAsegurados *sgte;
};

struct Incidentes
{
    int codigoIncidente;
    char fechaHora[15];
    char dniAsegurado[12];
    char dniOtroConductor[12];
    int nroPoliza;
    char calle[35];
    int alturaCalle;
};

struct NodoIncidentes
{
    Incidentes info;
    NodoIncidentes *sgte;
};

void insertarOrdenado(NodoAsegurados *&lista, Asegurados ainsertar)
{
    NodoAsegurados *paux = lista;
    NodoAsegurados *anterior =NULL;
    while (paux && paux->info.cantIncidentes > ainsertar.cantIncidentes)
    {
        anterior = paux;
        paux = paux->sgte;
    }
    if ( paux!= lista)
    {
        anterior->sgte = new NodoAsegurados();
        anterior->sgte->info = ainsertar;
        anterior->sgte->sgte = paux;

    }
    else
    {
        lista= new NodoAsegurados();
        lista->sgte = paux;
        lista->info = ainsertar;
    }
    return;
}


void datosPrueba(NodoAsegurados *&listaAsegurados){
    FILE *f;
    Asegurados a[3];

    a[0].nroPoliza = 1;
    strcpy(a[0].dni, "44.134.512");
    strcpy(a[0].nombre,"Ramiro");
    strcpy(a[0].apellido, "Fernandez");
    a[0].cuotaDia = false;
    strcpy(a[0].patenteAuto,"AS584FR");
    a[0].activa = true;
    a[0].cantIncidentes = 3;
    /****/
    a[1].nroPoliza = 2;
    strcpy(a[1].dni, "44.134.512");
    strcpy(a[1].nombre,"Ramiro");
    strcpy(a[1].apellido, "Fernandez");
    a[1].cuotaDia = true;
    strcpy(a[1].patenteAuto,"AS584FR");
    a[1].activa = true;
    a[1].cantIncidentes = 5;
    /****/
    a[2].nroPoliza = 3;
    strcpy(a[2].dni, "24.112.512");
    strcpy(a[2].nombre,"Juana");
    strcpy(a[2].apellido, "Ramirez");
    a[2].cuotaDia = false;
    strcpy(a[2].patenteAuto,"MJ593PY");
    a[2].activa = false;
    a[2].cantIncidentes = 1;
    /****/

    if(f = fopen("Asegurados.BAK","wb"))
    {
        fwrite(&a, sizeof(Asegurados),3,f);
        fclose(f);
        cout << endl << "Datos de prueba cargados" << endl;
    }

    if(f = fopen("Asegurados.BAK","rb"))
    {
        int i=0;
        while (fread(&a[i],sizeof(Asegurados),1,f))
        {
            insertarOrdenado (listaAsegurados,a[i]);
            i++;
        }
        fclose(f);
    }


return;
}

void leerDatosAsegurados(NodoAsegurados *&lista ,Asegurados &a)
{
    char opcion;
    cout << endl << "Ingrese el numero de poliza: ";
    cin >> a.nroPoliza;
    cout << "Ingrese dni (XX.XXX.XXX): " ;
    cin >> a.dni;
    cout << "Ingrese nombre: ";
    cin >> a.nombre;
    cout << "Ingrese apellido: ";
    cin >> a.apellido;
    cout << "Ingrese si tiene cuota al dia (S/N): ";
    do
    {
        opcion = getch();
    } while (opcion != 'S' && opcion != 's' && opcion != 'N' && opcion != 'n');
    if (opcion == 'S' || opcion == 's')
    {
        a.cuotaDia = true;
    }
    else if (opcion == 'N' || opcion == 'n')
    {
        a.cuotaDia = false;
    }

    cout << endl << "Ingrese la patente del auto (AA999AA): ";
    cin >> a.patenteAuto;
    cout << "Ingrese si esta activo o no (S/N): ";
    do
    {
        opcion = getch();
    } while (opcion != 'S' && opcion != 's' && opcion != 'N' && opcion != 'n');
    if (opcion == 'S' || opcion == 's')
    {
        a.activa = true;
    }
    else if (opcion == 'N' || opcion == 'n')
    {
        a.activa = false;
    }
    cout <<endl << "Ingrese la cantidad de incidentes: ";
    cin >> a.cantIncidentes;

    insertarOrdenado(lista,a);
    return;
}

void leerDatosIncidentes (Incidentes &i){
    cout << "Ingrese el codigo de incidente: ";
    cin >> i.codigoIncidente;
    cout << "Ingrese la fecha y hora (AAAAMMDD:MM): " ;
    cin >> i.fechaHora;
    cout << "Ingrese DNI del asegurado (XX.XXX.XXX): ";
    cin >> i.dniAsegurado;
    cout << "Ingrese DNI del otro conductor (XX.XXX.XXX): ";
    cin >> i.dniOtroConductor;
    cout << "Ingrese el numero de poliza: ";
    cin >> i.nroPoliza;
    cout << "Ingrese el nombre de la calle: ";
    cin >> i.calle;
    cout << "Ingrese la altura de la calle: ";
    cin >> i.alturaCalle;
}

void mostrarDatosAsegurado(NodoAsegurados *lista){
    cout << endl << "Nro Poliza: " << lista->info.nroPoliza << endl;
    cout << "DNI: " << lista->info.dni << endl;
    cout << "Nombre: " << lista->info.nombre << endl;
    cout << "Apellido: " << lista->info.apellido << endl;
    cout << "Cuota al dia: " << lista->info.cuotaDia << endl;
    cout << "Patente: " << lista->info.patenteAuto << endl;
    cout << "Activa: " << lista->info.activa << endl;
    cout << "Cant. de incidentes: " << lista->info.cantIncidentes << endl;
}


void mostrarListaAsegurados (NodoAsegurados *lista)
{
    while (lista != NULL)
    {
        if (lista->info.activa == true)
        {
            mostrarDatosAsegurado(lista);
        }
        
        lista = lista->sgte;
    }

    return;
}

// menu, lo muestra y me hace el getch
char menu(){
    char opcion;
    cout << "0 - Levantar los datos de prueba." <<endl;
    cout << "1 - Cargar una nueva poliza." <<endl;
    cout << "2 - Desactivar una poliza existente." <<endl;
    cout << "3 - Buscar una poliza por Nro. de Poliza o por DNI (Un cliente puede tener mas de una poliza)." <<endl;
    cout << "4 - Listar todas las polizas activas ordenadas por cantidad de incidentes en orden descendente." <<endl;
    cout << "5 - Procesar un lote de incidentes." <<endl;
    cout << "6 - Mostrar todas las polizas que no tengan la cuota al dia. La salida debe ser en un reporte escrito en formato html." <<endl;
    cout << "7 - Mostrar el mismo reporte que el punto 6 en formato CSV." <<endl;
    cout << "8 - Finalizar jornada (sobreescribir 'Asegurados.BAK')." <<endl;
    cout << "ESC - SALIR" << endl;
    do
    {
        opcion = getch();
    } while (!(opcion >= '0' && opcion <= '8') && opcion != 27);
    return opcion;

}


void buscarPoliza(int polizaBuscada, NodoAsegurados *lista){

    bool encontrado = false;
    {
        while ( lista != NULL)
        {
            if (lista->info.nroPoliza == polizaBuscada)
            {
                encontrado = true;
                cout << endl << "Poliza encontrada" << endl;
                mostrarDatosAsegurado(lista);
            }
            lista = lista->sgte;
        }
        if (encontrado == false)
        {
            cout << endl << "No se encontro la poliza" << endl;
        }
        
    }
    return;
}

void buscarDNI(char dniBuscado[], NodoAsegurados *lista){
    bool encontrado = false;
    {
        while ( lista != NULL)
        {
            if (strcmp (lista->info.dni, dniBuscado) == 0)
            {
                encontrado = true;
                cout << endl << "**** DNI encontrado ****" << endl;
                mostrarDatosAsegurado(lista);
            }
            lista = lista->sgte;
        }
        if (encontrado == false)
        {
            cout << endl << "No se encontro el DNI" << endl;
        }
        
    }
    return;
}

void desactivarPoliza(int polizaBuscada, Asegurados &a, NodoAsegurados *&lista){
    NodoAsegurados *aux = lista;
    bool encontrado = false;
    {
        while (aux != NULL)
        {
            if (aux->info.nroPoliza == polizaBuscada)
            {
                encontrado = true;
                cout << endl << "Poliza encontrada" << endl;
                aux->info.activa = false;
                cout << endl << "Se desactivo la poliza" << endl;
                break;
            }
            aux = aux->sgte;
        }
        if (encontrado == false)
        {
            cout << endl << "No se encontro la poliza" << endl;
        }
    }
return;
}

void mostrarLista (NodoIncidentes *lista)
{
    while (lista != NULL)
    {
        cout << endl  << "Codigo de incidente: " <<lista->info.codigoIncidente << endl;
        cout << "Fecha y Hora: " << lista->info.fechaHora << endl;
        cout << "DNI del asegurado: " << lista->info.dniAsegurado << endl;
        cout << "DNI del otro conductor: " << lista->info.dniOtroConductor << endl;
        cout << "Numero de poliza: " << lista->info.nroPoliza << endl;
        cout << "Calle: " << lista->info.calle <<endl;
        cout << "Altura: " << lista->info.alturaCalle << endl;
        lista = lista->sgte;
    }
    return;
}
void InsertarSiguiente (NodoIncidentes  *&n, Incidentes x)
{
    NodoIncidentes *nuevo= new NodoIncidentes();
    nuevo->info = x;
    if (n)
    {
        nuevo->sgte = n->sgte;
        n->sgte = nuevo;
    }
    else
    {
        nuevo->sgte= n;
        n= nuevo;
    }
    return;
}

void loteIncidentes(NodoIncidentes *&listaIncidentes, NodoAsegurados *&listaAsegurados){
    Incidentes i;
    FILE* f;
    leerDatosIncidentes(i);
    InsertarSiguiente(listaIncidentes,i);
    mostrarLista(listaIncidentes);
    NodoAsegurados *aux = listaAsegurados;
    while (aux != NULL)
    {
        if (aux->info.nroPoliza == i.nroPoliza)
        {
            aux->info.cantIncidentes +=1;
        }
        aux = aux->sgte;
    }
    if (f = fopen("procesados.BAK","ab"))
    {
        fwrite(&i,sizeof(Incidentes),1,f);
    }

    return;
}



void reporteHTML(NodoAsegurados *lista){
    FILE *f;
    f = fopen("salidahtml.html", "wt");
    fprintf(f,"<html><body>\n");
    fprintf(f,"<h1>Reporte de asegurados con polizas que no estan al dia</h1>\n");
    fprintf(f,"<table border=1>\n");
    fprintf(f,"<th>Numero de poliza</th><th>DNI</th><th>Nombre</th><th>Apellido</th><th>Patente del auto</th><th>Activa</th><th>Cantidad de incidentes</th>\n");
    while (lista != NULL)
    {
        if(lista->info.cuotaDia != true)
        {
            fprintf(f,"<tr>\n");
            fprintf(f,"<td>%d</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%d</td><td>%d</td>\n",lista->info.nroPoliza,lista->info.dni,lista->info.nombre,lista->info.apellido,lista->info.patenteAuto,lista->info.activa,lista->info.cantIncidentes);
            fprintf(f,"</tr>\n");
        }
        lista = lista->sgte;
    }
    fprintf(f, "</table>");
    fprintf(f, "</body>");
    fprintf(f, "</html>");
    fclose(f);
    cout << endl << "Reporte en HTML hecho" << endl;
    return;
}

void reporteCSV(NodoAsegurados *lista){
    FILE *f;
    FILE *f2;
    f = fopen("salidaexcel.csv", "wt");
    f2 = fopen("Asegurados.BAK","rb+");
    fprintf(f,"Numero de poliza;DNI;Nombre;Apellido;Patente del auto; Activa; Cantida de incidentes\n");
    while (lista != NULL)
    {
        if (lista->info.cuotaDia!= true)
        {
            fprintf(f,"%d;%s;%s;%s;%s;%d;%d\n",lista->info.nroPoliza,lista->info.dni,lista->info.nombre,lista->info.apellido,lista->info.patenteAuto,lista->info.activa,lista->info.cantIncidentes);
        }
        lista = lista->sgte;
    }
    fclose(f);
    cout << endl << "Reporte en CSV hecho" << endl;
    return;

}

// para ver lo que sobrescribe la funcion sobreescribir

// void mostrarPoliza(Asegurados &a){
//     cout << "DNI: " << a.dni << endl ;
//     cout << "Nombre: " << a.nombre << endl;
//     cout << "Apellido: " << a.apellido << endl;
//     cout << "Cuota al dia: " << a.cuotaDia << endl;
//     cout << "Patente del auto: " << a.patenteAuto << endl;
//     cout << "Activo o no: " << a.activa << endl;
//     cout << "Cantidad de incidentes: " << a.cantIncidentes << endl;
//     return;
// }

// void mostrarPolizas(){
//     FILE *f;
//     Asegurados a;
//     if (f= fopen("Asegurados.BAK", "rb"))
//     {
//         while (fread(&a, sizeof(Asegurados), 1, f)){
//                 cout << endl << "**** Numero de poliza: " << a.nroPoliza << " ****" << endl;
//                 mostrarPoliza(a);
//         }
//        fclose(f);
//     }
//     return;
// }

void sobreescribir(NodoAsegurados *lista){
    FILE *f;
    if (f = fopen("Asegurados.BAK","wb")){
        while (lista !=NULL)
        {
            if (lista->info.activa == true )
            {
                fwrite(&lista->info, sizeof(Asegurados),1,f);
            }
            lista = lista->sgte;
        }
        cout << "Archivo sobreescrito" << endl;
        fclose(f);
    }
    // mostrarPolizas();
    return;
}

int main(){
    system("cls");
    Asegurados a;
    NodoAsegurados *listaAsegurados = NULL;
    NodoIncidentes *listaIncidentes = NULL;
    Incidentes* lista = NULL;
    char opcion, opcion2, dniBuscado[12];
    int polizaBuscada;
    do
    {
        opcion = menu();
        switch (opcion)
        {
        case '0':
                datosPrueba(listaAsegurados);
                cout << endl << "Presione un boton para continuar";
                getch();
                system("cls");
            break;
        case '1':
                leerDatosAsegurados(listaAsegurados,a);
                cout << endl << "Presione un boton para continuar";
                getch();
                system("cls");
            break;
        case '2':
                cout << "Ingrese la poliza que quiera desactivar: ";
                cin >> polizaBuscada;
                desactivarPoliza(polizaBuscada,a,listaAsegurados);// no anda bien
                cout << endl << "Presione un boton para continuar";
                getch();
                system("cls");
            break;
        case '3':
                cout << "Ingrese como quiere buscar al asegurado" << endl;
                cout << "1 - Poliza" << endl;
                cout << "2 - DNI" << endl;
                do
                {
                    opcion2 = getch();
                } while (opcion2 != '1' && opcion2 != '2');
                if (opcion2 == '1')
                {
                    cout << "Ingrese la poliza que quiera buscar: ";
                    cin >> polizaBuscada;
                    buscarPoliza(polizaBuscada,listaAsegurados);
                }
                if (opcion2 == '2')
                {
                    cout << "Ingres el DNI que quiere buscar : ";
                    cin >> dniBuscado;
                    buscarDNI(dniBuscado,listaAsegurados);
                }
                cout << endl << "Presione un boton para continuar";
                getch();
                system("cls");
            break;
        case '4':
                mostrarListaAsegurados(listaAsegurados);
                cout << endl << "Presione un boton para continuar";
                getch();
                system("cls");
            break;
        case '5':
                loteIncidentes(listaIncidentes,listaAsegurados);
                cout << endl << "Presione un boton para continuar";
                getch();
                system("cls");
            break;
        case '6':
                reporteHTML(listaAsegurados);
                cout << endl << "Presione un boton para continuar";
                getch();
                system("cls");
            break;
        case '7':
                reporteCSV(listaAsegurados);
                cout << endl << "Presione un boton para continuar";
                getch();
                system("cls");
            break;
        case '8':
                sobreescribir(listaAsegurados);
                cout << endl << "Presione un boton para continuar";
                getch();
                system("cls");
            break;
        }
    } while (opcion != 27);

return 0;
}
