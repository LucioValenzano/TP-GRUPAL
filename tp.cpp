#include <iostream>
#include <conio.h>
#include <string.h>

using namespace std;

// Registro de asegurados
struct Asegurados
{
    int nroPoliza;
    char dni[10];
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
    char dniAsegurado[10];
    char dniOtroConductos[10];
    int nroPoliza;
    char calle[35];
    int alturaCalle;
};

void leerDatosAlumno(Asegurados &a)
{
    char opcion;
    cout << "Ingrese el numero de poliza: ";
    cin >> a.nroPoliza;
    cout << "Ingrese dni: " ;
    cin >> a.dni;
    cout << "Ingrese nombre: ";
    cin >> a.nombre;
    cout << "Ingrese apellido: ";
    cin >> a.apellido;
    cout << "Ingrese si tiene cuota al dia (S/N): ";
    cin >> opcion;
    if (opcion == 'S' || opcion == 's')
    {
        a.cuotaDia = true;
    }
    else
    {
        a.cuotaDia = false;
    }
    cout << "Ingrese la patente del auto: ";
    cin >> a.patenteAuto;
    cout << "Ingrese si esta activo o no (S/N): ";
    cin >> opcion;
    if (opcion == 'S' || opcion == 's')
    {
        a.activa = true;
    }
    else
    {
        a.activa = false;
    }
    cout << "Ingrese la cantidad de incidentes: ";
    cin >> a.cantIncidentes;
    return;
}

void mostrarPoliza(Asegurados a){
    cout << "Numero de poliza: "<< a.nroPoliza << endl;
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
    cout << "1 - Cargar una nueva poliza." <<endl;
    cout << "2 - Desactivar una poliza existente." <<endl;
    cout << "3 - Buscar una poliza por Nro. de Poliza o por DNI (Un cliente puede tener mas de una poliza)." <<endl;
    cout << "4 - Listar todas las polizas activas ordenadas por saldo descendente." <<endl;
    cout << "5 - Procesar un lote de incidentes." <<endl;
    cout << "6 - Mostrar todas las polizas que no tengan la cuota al dia. La salida debe ser en un reporte escrito en formato html." <<endl;
    cout << "7 - Mostrar el mismo reporte que el punto 7 en formato CSV." <<endl;
    cout << "8 - Finalizar jornada (sobreescribir 'Asegurados.BAK')." <<endl;
    cout << "ESC - SALIR" << endl;
    do
    {
        opcion = getch();
    } while (!(opcion >= '1' && opcion <= '8') && opcion != 27);
    return opcion;
    
}

void cargarPoliza(){
    FILE* f;
    Asegurados a;
    if (f = fopen("Asegurados.BAK","ab"))
    {
        leerDatosAlumno(a);
        fwrite(&a,sizeof(Asegurados),1,f);
        fclose(f);
    }
    return;
}

void mostrarPolizas(){
    FILE *f;
    Asegurados a;
    int i = 0;
    if (f= fopen("Asegurados.BAK", "rb"))
    {
        while (fread(&a, sizeof(Asegurados), 1, f)){
            i++;
            cout << endl << "Poliza " << i << endl;
            mostrarPoliza(a);
        }
       fclose(f);
    }
    return;
}

void buscarPoliza(int polizaBuscada, Asegurados &a){
    FILE *f;
    if (f = fopen("Asegurados.BAK", "rb"))
    {
        while (fread(&a, sizeof(Asegurados), 1, f))
        {
            if (a.nroPoliza == polizaBuscada)
            {
                cout << "Poliza encontrada" <<endl;
                mostrarPoliza(a);
            }
        }
        fclose(f);
    }
    return;
}

void desactivarPoliza(int polizaBuscada, Asegurados &a){
    FILE *f;
    if (f = fopen("Asegurados.BAK", "ab"))
    {
        while (fread(&a,sizeof(Asegurados),1,f))
        {
            if (a.nroPoliza == polizaBuscada)
            {
                cout << "Poliza encontrada" << endl;
                a.activa = false;
            }
        }
        fclose(f);
    }
    return;
}

int main(){
    system("cls");
    FILE* f;
    Asegurados a;
    char opcion;
    int polizaBuscada;
    do
    {
        opcion = menu();
        switch (opcion)
        {
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
                cout << "Ingrese la poliza que quiera buscar: ";
                cin >> polizaBuscada;
                buscarPoliza(polizaBuscada,a);
                cout << endl << "Presione un boton para continuar";
                getch();
                system("cls");
            break;
        case '4':
                mostrarPolizas();// no lo muestra en orden descendente por saldo, solo lo muestra
                cout << endl << "Presione un boton para continuar";
                getch();
                system("cls");
            break;
        case '5':
                cout << endl << "Presione un boton para continuar";
                getch();
                system("cls");
            break;
        case '6':
                cout << endl << "Presione un boton para continuar";
                getch();
                system("cls");
            break;
        case '7':
                 cout << endl << "Presione un boton para continuar";
                getch();
                system("cls");
            break;
        case '8':
                cout << endl << "Presione un boton para continuar";
                getch();
                system("cls");
            break;
        }
    } while (opcion != 27);
    



return 0;
}


/*
Al comenzar la jornada se “levantan” todas las pólizas desde el archivo “Asegurados.BAK”.
Cada vez que el usuario requiera se procesará un “lote de incidentes”. Se desconoce cuántos
incidentes puede haber en cada lote, pero puede ser tan grande que haga difícil su manejo en
un vector.
El procesamiento de un lote de incidentes implica la actualización de la cantidad de incidentes
de aquellas pólizas que sean afectadas. Además, cada vez que se procesa un lote, deben
“transladarse” los registros procesados a un archivo llamado “procesados.BAK”, el cual
contiene todos los incidentes de todos los lotes procesados en el día.
Al finalizar el día se reescribe el archivo “Asegurados.BAK”. con las pólizas activas únicamente
y sus cantidades de incidentes actualizadas.
Ud. y su equipo deben confeccionar un programa que permita:
1. “Levantar” las cuentas del archivo “Asegurados.BAK”.
2. Cargar una nueva póliza.
3. Desactivar una póliza existente.
4. Buscar una póliza por Nro. de Póliza o por DNI (Un cliente puede tener más de una
póliza).
5. Listar todas las pólizas activas ordenadas por saldo descendente.
6. Procesar un lote de incidentes.
7. Mostrar todas las pólizas que no tengan la cuota al día.. La salida debe ser en un
reporte escrito en formato html.
8. Mostrar el mismo reporte que el punto 7 en formato CSV.
9. Finalizar jornada (sobreescribir “Asegurados.BAK”.).
10. Se recomienda realizar un procedimiento de prueba para crear un incidente o más
incidentes en un archivo (para luego poder procesarlo).
*/

