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

// Registro de incidentes
struct Incidentes
{
    int codigoIncidente;
    char fechaHora[15];
    char dniAsegurado[12];
    char dniOtroConductor[12];
    int nroPoliza;
    char calle[35];
    int alturaCalle;
    Incidentes *sgte;
};

void datosPrueba(){
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

return;
}

void leerDatosAsegurados(Asegurados &a)
{
    char opcion;
    cout << "Ingrese el numero de poliza: ";
    cin >> a.nroPoliza;
    cout << "Ingrese dni (XX.XXXX.XXXX): " ;
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
    return;
}

void leerDatosIncidentes (Incidentes *&i){
    cout << "Ingrese el codigo de incidente: ";
    cin >> i->codigoIncidente;
    cout << "Ingrese la fecha y hora (AAAAMMDD:MM): " ;
    cin >> i->fechaHora;
    cout << "Ingrese DNI del asegurado (XX.XXXX.XXXX): ";
    cin >> i->dniAsegurado;
    cout << "Ingrese DNI del otro conductor (XX.XXXX.XXXX): ";
    cin >> i->dniOtroConductor;
    cout << "Ingrese el numero de poliza: ";
    cin >> i->nroPoliza;
    cout << "Ingrese el nombre de la calle: ";
    cin >> i->calle;
    cout << "Ingrese la altura de la calle: ";
    cin >> i->alturaCalle;
}

void mostrarPoliza(Asegurados &a){
    cout << "DNI: " << a.dni << endl ;
    cout << "Nombre: " << a.nombre << endl;
    cout << "Apellido: " << a.apellido << endl;
    cout << "Cuota al dia: " << a.cuotaDia << endl;
    cout << "Patente del auto: " << a.patenteAuto << endl;
    cout << "Activo o no: " << a.activa << endl;
    cout << "Cantidad de incidentes: " << a.cantIncidentes << endl;
    return;
}

// menu, lo muestra y me hace el getch
char menu(){
    char opcion;
    cout << "0 - Levanatar los datos de prueba." <<endl;
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

void cargarPoliza(){
    FILE* f;
    Asegurados a;
    if (f = fopen("Asegurados.BAK","ab"))
    {
        leerDatosAsegurados(a);
        fwrite(&a,sizeof(Asegurados),1,f);
        fclose(f);
    }
    return;
}

void mostrarPolizas(){
    FILE *f;
    Asegurados a;
    if (f= fopen("Asegurados.BAK", "rb"))
    {
        while (fread(&a, sizeof(Asegurados), 1, f)){
            if (a.activa == true)
            {             
                cout << endl << "**** Numero de poliza: " << a.nroPoliza << " ****" << endl;
                mostrarPoliza(a);
            }
        }
       fclose(f);
    }
    return;
}

bool buscarPoliza(int polizaBuscada, Asegurados &a){
    FILE *f;
    bool encontrado = false;
    if (f = fopen("Asegurados.BAK", "rb"))
    {
        while ( !encontrado && fread(&a, sizeof(Asegurados), 1, f))
        {
            if (a.nroPoliza == polizaBuscada)
            {
                encontrado = true;
            }
        }
        fclose(f);
    }
    return encontrado;
}

void buscarDNI(char dniBuscado[], Asegurados &a){
    FILE *f;
    bool encontrado = false;
    if (f = fopen("Asegurados.BAK", "rb"))
    {
        while (fread(&a, sizeof(Asegurados), 1, f))
        {
            if (strcmp(a.dni, dniBuscado) == 0)
            {
                cout << endl << "**** DNI ENCONTRADO ****" <<endl;
                encontrado = true;
                mostrarPoliza(a);
            }
        }
        if (encontrado == false)
        {
            cout  << "No se encontro el DNI" << endl;
        }
        fclose(f);
    }
    return;
}

void desactivarPoliza(int polizaBuscada, Asegurados &a){
    FILE *f;
    bool encontrado = false;
    if (f = fopen("Asegurados.BAK","rb+"))
    {
        while (fread(&a,sizeof(Asegurados),1,f))
        {
            if (a.nroPoliza == polizaBuscada)
            {
                encontrado = true;
                cout << "Poliza encontrada" << endl;
                a.activa = false;
                int pos = ftell(f) - sizeof(Asegurados);
                fseek(f,pos,SEEK_SET);
                fwrite(&a,sizeof(Asegurados),1,f);
                cout  << "Se descativo la poliza: "<< polizaBuscada << endl;
                break;
            }
        }
        if (encontrado == false)
        {
            cout << "No se encontro la poliza" << endl;
        }
    }
    fclose(f);
return;
}

void mostrarLista (Incidentes *lista)
{
    int i=1;
    while (lista != NULL)
    {
        cout<< "Asegurado "<<i<<" : "<<endl;
        cout<<"Altura: "<<lista->alturaCalle<<endl;
        cout<<"Calle: "<<lista->calle<<endl;
        cout<<"Codigo de incidente: "<<lista->codigoIncidente<<endl;
        cout<<"DNI del asegurado: "<<lista->dniAsegurado<<endl;
        cout<<"DNI del otro conductor: "<<lista->dniOtroConductor<<endl;
        cout<<"Fecha y Hora: "<<lista->fechaHora<<endl;
        cout<<"Numero de poliza: "<<lista->nroPoliza<<endl<<endl;
        lista = lista->sgte;
        i++;
    }
    return;
}

void loteIncidentes(Incidentes *&lista){
    FILE* f1;
    FILE* f2;
    Asegurados a;
    Incidentes *i = new Incidentes();
    if ((f1 = fopen("procesados.BAK","ab+")) && (f2 = fopen("Asegurados.BAK","rb+")))
    {
        leerDatosIncidentes(i);
        fwrite(&i,sizeof(Incidentes),1,f1);


        i->sgte = lista;

        while (fread(&a,sizeof(Asegurados),1,f2))
        {
            if (a.nroPoliza == i->nroPoliza)
            {
                a.cantIncidentes +=1;
                int pos = ftell(f2) - sizeof(Asegurados);
                fseek(f2,pos,SEEK_SET);
                fwrite(&a,sizeof(Asegurados),1,f2);
                cout << endl << "Se ingreso un nuevo lote de incidentes" << endl;
                break;
            }
        }
        lista=i;
        fclose(f1);
        fclose(f2);
        mostrarLista (lista);
    }
    return;
}

void ordenar(Asegurados v[], int tamlogico)
{
    Asegurados aux;
    int j = 0;
    for (int i = 0; i <  tamlogico - 1; i++)
    {
       for(j =0; j < tamlogico - 1 - i; j++)
       {
           if (v[j+1].cantIncidentes > v[j].cantIncidentes)
           {
               aux = v[j];
               v[j] = v[j+1];
               v[j+1] = aux;
           }
       }
    }
    return;
}

void reporteHTML(Asegurados a){
    FILE *f;
    FILE *f2;
    f = fopen("salidahtml.html", "wt");
    f2 = fopen("Asegurados.BAK","rb+");
    fprintf(f,"<html><body>\n");
    fprintf(f,"<h1>Reporte de asegurados con polizas que no estan al dia</h1>\n");
    fprintf(f,"<table border=1>\n");
    fprintf(f,"<th>Numero de poliza</th><th>DNI</th><th>Nombre</th><th>Apellido</th><th>Patente del auto</th><th>Activa</th><th>Cantidad de incidentes</th>\n");
    while (fread(&a,sizeof(Asegurados),1,f2))
    {
        if(a.cuotaDia != true)
        {
            fprintf(f,"<tr>\n");
            fprintf(f,"<td>%d</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%d</td><td>%d</td>\n",a.nroPoliza,a.dni,a.nombre,a.apellido,a.patenteAuto,a.activa,a.cantIncidentes);
            fprintf(f,"</tr>\n");
        }
    }
    fprintf(f, "</table>");
    fprintf(f, "</body>");
    fprintf(f, "</html>");
    fclose(f);
    cout << endl << "Reporte en HTML hecho" << endl;
    return;
}

void reporteCSV(Asegurados a){
    FILE *f;
    FILE *f2;
    f = fopen("salidaexcel.csv", "wt");
    f2 = fopen("Asegurados.BAK","rb+");
    fprintf(f,"Numero de poliza;DNI;Nombre;Apellido;Patente del auto; Activa; Cantida de incidentes\n");
    while (fread(&a,sizeof(Asegurados),1,f2))
    {
        if (a.cuotaDia != true)
        {
            fprintf(f,"%d;%s;%s;%s;%s;%d;%d\n",a.nroPoliza,a.dni,a.nombre,a.apellido,a.patenteAuto,a.activa,a.cantIncidentes);
        }
    }
    fclose(f);
    cout << endl << "Reporte en CSV hecho" << endl;
    return;

}

void sobreescribir(Asegurados a){
    FILE *f;
    FILE *aux;
    if ((f = fopen("Asegurados.BAK","rb")) && (aux = fopen("Auxiliar","wb")))
    {
        while (fread(&a,sizeof(Asegurados),1,f))
        {
            if (a.activa == true)
            {
                fwrite(&a,sizeof(Asegurados),1,aux);
            }
        }
        fclose(f);
        fclose(aux);
        if ((f = fopen("Asegurados.BAK","wb")) && (fopen("Auxiliar","rb")))
        {
            while (fread(&a,sizeof(Asegurados),1,aux))
            {
                fwrite(&a,sizeof(Asegurados),1,f);
            }
           fclose(f);
           fclose(aux);
            cout << endl << "Archivo sobreescrito" << endl;
        }
    }
    return;
}

int main(){
    system("cls");
    FILE* f;
    Asegurados a;
    Incidentes* lista = NULL;
    char opcion, opcion2, dniBuscado[12];
    int polizaBuscada;
    do
    {
        opcion = menu();
        switch (opcion)
        {
        case '0':
                datosPrueba();
                cout << endl << "Presione un boton para continuar";
                getch();
                system("cls");
            break;
        case '1':
                cargarPoliza();
                cout << endl << "Presione un boton para continuar";
                getch();
                system("cls");
            break;
        case '2':
                cout << "Ingrese la poliza que quiera desactivar: ";
                cin >> polizaBuscada;
                desactivarPoliza(polizaBuscada,a);// no anda bien
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
                    if (buscarPoliza(polizaBuscada,a) == true)
                    {
                        cout << endl << "**** Poliza encontrada ****" << endl << endl;
                        mostrarPoliza(a);
                    }
                    else
                    {
                        cout << "No se encontro la poliza" << endl;
                    }
                }
                if (opcion2 == '2')
                {
                    cout << "Ingres el DNI que quiere buscar : ";
                    cin >> dniBuscado;
                    buscarDNI(dniBuscado,a);
                }
                cout << endl << "Presione un boton para continuar";
                getch();
                system("cls");
            break;
        case '4':
                Asegurados valus[2048];
                int cant;
                if (f = fopen("Asegurados.BAK", "rb"))
                {
                    fseek(f, 0, SEEK_END);
                    cant = ftell(f)/ sizeof(Asegurados);
                    fseek(f, 0, SEEK_SET);
                    fread(valus, sizeof(Asegurados),cant, f);
                    ordenar(valus, cant);
                    fclose(f);
                }
                if (f = fopen("Asegurados.BAK", "wb"))
                {
                    fwrite(valus,sizeof(Asegurados), cant, f);
                    fclose(f);
                }
                mostrarPolizas();
                cout << endl << "Presione un boton para continuar";
                getch();
                system("cls");
            break;
        case '5':
                loteIncidentes(lista);
                cout << endl << "Presione un boton para continuar";
                getch();
                system("cls");
            break;
        case '6':
                reporteHTML(a);
                cout << endl << "Presione un boton para continuar";
                getch();
                system("cls");
            break;
        case '7':
                reporteCSV(a);
                cout << endl << "Presione un boton para continuar";
                getch();
                system("cls");
            break;
        case '8':
                sobreescribir(a);
                mostrarPolizas();
                cout << endl << "Presione un boton para continuar";
                getch();
                system("cls");
            break;
        }
    } while (opcion != 27);

return 0;
}
