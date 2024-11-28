#include <iostream>
#include <string>
#include <vector>
#include <windows.h> 
#include <cstdlib>
#include <ctime>
#include <limits>
#include "termcolor.hpp"

using namespace std;

const int maxUsuarios = 100;
int ids[maxUsuarios]; 
string correos[maxUsuarios];
string contrasenas[maxUsuarios];
string nombres[maxUsuarios];
int numUsuarios = 0; 

struct Libro {
    string codigo;
    string titulo;
    string autor;
    int cantidadDisponible;
};

vector<Libro> libros = {
    {"1", "El Alquimista", "Paulo Coelho", 3},
    {"2", "1984", "George Orwell", 5},
    {"3", "Cien años de soledad", "Gabriel Garcia Márquez", 2},
    {"4", "El principito", "Antoine de Saint-Exupéry", 1},
    {"5", "Orgullo y prejuicio", "Jane Austen", 2}
};

struct Prestamo {
    string codigo;
    string titulo;
    string autor;
    int cantidadPrestada;
};

vector<Prestamo> prestamos;


void sistemaInicio();
void loginUsuario();
void registroUsuario();
void loginAdministrador();
void verificacionUsuario();
void verificacionAdmin(string id, string contrasena);
void agregarLibros();
void eliminarLibro();
void menuAdmin();
void dbRegister(int idUsuario, string contrasena, string correo);
void registrarUsuario(int id, string correo, string contrasena, string nombres);
void limpiarTerminal();
void menuUsuario();
void verLibrosDisponibles(); 
void prestarLibro(vector<Libro>& libros); 
void devolverLibro();
void verMisPrestamos(); 
void buscarLibros();  
void informacionBiblioteca() ;
void preguntasFrecuentes();
void contactarSoporte();
int generarNumeroAleatorio();
void mostrarMisPrestamos ();
void leerOpcionValida(int& opcion, int min, int max);


//FUNCION PRINCIPAL
int main() {
    sistemaInicio();  
}

//CODIGO GENERAL
int generarNumeroAleatorio() {
    srand(time(0));
    int tiempoAleatorio = rand() % 5 + 1;

    return tiempoAleatorio;
}

void leerOpcionValida(int& opcion, int min, int max) {
    while (cin.fail() || opcion < min || opcion > max) {
        cin.clear(); 
        cin.ignore(1000, '\n'); 
        cout << "Opcion no valida. Intente nuevamente: "; cin >> opcion;
    }
}

void sistemaInicio() {
    int opcion;
    cout <<  "====================================================" << endl;
    cout << termcolor::red << "                SISTEMA DE BIBLIOTECA               " << termcolor::reset << endl;
    cout << "====================================================" << endl;
    cout << "  [1] Usuario (Consultar prestamos, buscar libros)" << endl;
    cout << "  [2] Administrador (Gestionar inventario, usuarios)" << endl;
    cout << "  [3] Salir del sistema" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "Ingrese su opcion: "; cin >> opcion;
    
    leerOpcionValida(opcion, 1,3);

    cout << "----------------------------------------------------" << endl;

    switch (opcion) {
        case 1: 
            cout << "Accediendo al modulo de Usuario..." << endl;
            Sleep(generarNumeroAleatorio() * 1000);
            verificacionUsuario();
            break;

        case 2: 
            cout << "Accediendo al modulo de Administrador..." << endl;
            Sleep(generarNumeroAleatorio() * 1000);
            loginAdministrador();
            break;

        case 3: 
            cout << "Cerrando Sesion..." << endl;
            Sleep(generarNumeroAleatorio() * 1000);
            break;

        default: 
            cout << "Vuelva a elegir una opcion valida." << endl;
            sistemaInicio(); 
            break;
    }
    cout << "====================================================" << endl;
}

void limpiarTerminal () {
    #ifdef _WIN32
        system("CLS"); // Para Windows
    #else
        system("clear"); // Para Linux y Mac
    #endif
}

void pausar() {
    cout << "Presione cualquier tecla para continuar...\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar la entrada previa
    cin.get(); // Esperar que el usuario presione Enter
}

//CODIGO PARA PROGRAMAR LA FUNCIONALIDAD EL USUARIO
void loginUsuario() {
    limpiarTerminal();
    int id;
    string contrasena;
    char opcion;

    cout << "============================================" << endl;
    cout << "               INICIAR SESION                " << endl;
    cout << "============================================" << endl;;
    cout << "ID del usuario:  "; cin >> id; 
    cout << "Contrasena: "; cin >> contrasena;
    cout << "--------------------------------------------" << endl;

    for (int i = 0; i < numUsuarios; i++) {
        if (ids[i] == id && contrasenas[i] == contrasena) {
            cout << "Inicio de sesion exitoso." << endl;
            Sleep(2);
            menuUsuario();
            return; 
        }
    }
    
    cout << "ID o contrasena incorrectos.Desea registrarse (s/n): "; cin >> opcion;
;
    if (opcion == 's' || opcion == 'S') {
        registroUsuario();
    } else {
        verificacionUsuario(); 
    }
}
void registroUsuario() {

    limpiarTerminal();
    int numero; 
    string contrasena;
    string correo;
    string nombre;

    cout << "                Registro de Usuario" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Tipo de usuario: Usuario" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "ID del usuario:  "; cin >> numero; 
    cout << "Nombre del Usuario:  "; cin >> nombre; 
    cout << "Correo Electronico: "; cin >> correo;
    cout << "Contrasena: "; cin >> contrasena;

    cout << "-------------------------------------------" << endl;
    cout << termcolor::green << " Usuario " << nombre  << " registrado correctamente" << termcolor::reset << endl;
    cout << "-------------------------------------------" << endl;

    Sleep(5000); 
    registrarUsuario(numero, correo, contrasena, nombre); 
    verificacionUsuario();
}
void registrarUsuario(int id, string correo, string contrasena, string nombre) { 
    if (numUsuarios < maxUsuarios) {
        ids[numUsuarios] = id; 
        correos[numUsuarios] = correo;
        contrasenas[numUsuarios] = contrasena;
        nombres[numUsuarios] = nombre;
        numUsuarios++;
        cout << "Usuario registrado exitosamente.\n";
    } else {
        cout << termcolor::green << "Error: capacidad maxima de usuarios alcanzada.\n" << termcolor::reset;
    }
}
void verificacionUsuario() {
    limpiarTerminal();
    int menu;
    cout << "========================================" << endl;
    cout << "          MENU DE USUARIO               " << endl;
    cout << "========================================" << endl;
    cout << " [1] Iniciar sesion                     " << endl;
    cout << " [2] Registrarse                        " << endl;
    cout << " [3] Informacion de la biblioteca       " << endl;
    cout << " [4] Preguntas frecuentes               " << endl;
    cout << " [5] Contactar soporte                  " << endl;
    cout << " [6] Salir                              " << endl;
    cout << "========================================" << endl;
    cout << "Seleccione una opcion: "; cin >> menu;
    cout << "========================================" << endl;

    leerOpcionValida(menu, 1,6);

    switch(menu) {
        case 1:
            loginUsuario();
            break;
        case 2:
            registroUsuario();
            break;
        case 3:
            informacionBiblioteca(); 
            break;
        case 4:
            preguntasFrecuentes(); 
            break;
        case 5:
            contactarSoporte(); 
            break;
        case 6:
            sistemaInicio();
            break;
        default:
            cout << "Opcion no válida. Por favor, intenta de nuevo." << endl;
            verificacionUsuario();
    }
}
void menuUsuario() {
    limpiarTerminal();

    int opcion;

    do {
        cout << "----------- Bienvenido, " << endl;
        cout << "-------------------------------------------" << endl;
        cout << "[1] Ver libros disponibles" << endl;
        cout << "[2] Prestar libro" << endl;
        cout << "[3] Devolver libro" << endl;
        cout << "[4] Ver mis prestamos" << endl;
        cout << "[5] Actualizar perfil" << endl;
        cout << "[6] Cerrar sesión" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "Opcion: "; cin >> opcion;
        cout << "-------------------------------------------" << endl;

        switch(opcion) {
            case 1:
                verLibrosDisponibles(); 
                break;
            case 2:
                prestarLibro(libros); 
                break;
            case 3:
                devolverLibro(); 
                break;
            case 4:
                verMisPrestamos(); 
                break;
            case 5:
                buscarLibros(); 
                break;
            case 6:
                cout << "Cerrando sesion..." << endl;
                sistemaInicio(); 
                break;
            default:
                cout << "Opcion no valida. Por favor, intenta de nuevo." << endl;
        }
    } while (opcion != 6);
}
void verLibrosDisponibles() {
    limpiarTerminal();

    // Mostrar la información de los libros
    for (int i = 0; i < libros.size(); i++) {
        cout << "Codigo: " << libros[i].codigo << endl;
        cout << "Titulo: " << libros[i].titulo << endl;
        cout << "Autor: " << libros[i].autor << endl;
        cout << "Cantidad disponible: " << libros[i].cantidadDisponible << endl;
        cout << "-------------------------" << endl;
    }


    pausar();
}

void informacionBiblioteca() {
    cout << "Informacion de la biblioteca: \n";
    cout << "Horario: Lunes a Viernes de 8am a 6pm\n";
    cout << "Ubicacion: Calle Ejemplo 123\n";
    cout << "Servicios: Prestamo de libros, salas de estudio, eventos.\n";
    cout << "Presione cualquier tecla para continuar... \n";
    pausar();
}


void preguntasFrecuentes() {
    cout << "Preguntas Frecuentes:\n";
    cout << "1. Como me registro?\n";
    cout << "2. Cuantos libros puedo prestar?\n";
    cout << "3. Que hago si olvido mi contrasena?\n";
    cout << "Presione cualquier tecla para continuar... \n";
    pausar();
}

void contactarSoporte() {
    cout << "Para contactar soporte, envia un correo a soporte@biblioteca.com\n";
    cout << "Presione cualquier tecla para continuar... \n";
    pausar();
}


void prestarLibro(vector<Libro>& libros) {

    string solicitarCodigo;
    string volverPrestarse;

    int totalLibros = 5;
    
    for (int i = 0; i < libros.size(); i++) {
        cout << "Codigo: " << libros[i].codigo << endl;
        cout << "Título: " << libros[i].titulo << endl;
        cout << "Autor: " << libros[i].autor << endl;
        cout << "Cantidad disponible: " << libros[i].cantidadDisponible << endl;
        cout << "-------------------------" << endl;
    }

    do {
        cout << "Ingrese el codigo del libro a prestar: "; cin >> solicitarCodigo;

        bool libroEncontrado = false;
        int cantidadPrestada = 0;

        for (int i = 0; i < libros.size(); i++) {
            if (solicitarCodigo == libros[i].codigo) {
                libroEncontrado = true;
                if (libros[i].cantidadDisponible > 0) {
                    libros[i].cantidadDisponible--; 
                    cantidadPrestada++;
                    cout << "Buscando Libro... \n";
                    Sleep(generarNumeroAleatorio() * 1000); 
                    cout << "Libro prestado exitosamente.\n";

                    bool prestamoExistente = false;

                    for (int j = 0; j < prestamos.size(); j++) {
                        if (prestamos[j].codigo == libros[i].codigo) {
                            prestamos[j].cantidadPrestada++;  // Incrementar la cantidad prestada
                            prestamoExistente = true;
                            break;
                        }
                    }

                    // Si no existe un préstamo previo, agregarlo
                    if (!prestamoExistente) {
                        prestamos.push_back({
                            libros[i].codigo,
                            libros[i].titulo,
                            libros[i].autor,
                            1 // Empezamos con 1 libro prestado
                        });
                    }

                } else {
                    cout << "Buscando Libro...";
                     Sleep(generarNumeroAleatorio() * 1000);
                    cout << "No hay copias disponibles de este libro.\n";
                }
                break;
            }
        }

        if (!libroEncontrado) {
            cout << "El libro no esta disponible o no existe. \n";
        }

        cout << "Desea adquir otro libro? (s/n) "; cin >> volverPrestarse;

    } while (volverPrestarse == "s" || volverPrestarse == "S");
    
    limpiarTerminal();
}

void devolverLibro() {
    limpiarTerminal();
    string solicitarCodigo;

    cout << "=============================================" << endl;
    cout << "          DEVOLVER PRESTAMOS     " << endl;
    cout << "=============================================" << endl;

    mostrarMisPrestamos();

    cout << "Ingrese el codigo del libro a devolver: "; cin >> solicitarCodigo;

    bool libroDevuelto = false;

    for (int i = 0; i < prestamos.size(); i++) {
        if (solicitarCodigo == prestamos[i].codigo) {
            // Buscar el libro en el vector libros para actualizar la cantidad disponible
            for (int j = 0; j < libros.size(); j++) {
                if (libros[j].codigo == prestamos[i].codigo) {
                    // Incrementar la cantidad disponible
                    libros[j].cantidadDisponible++;
                    break; // Salir del bucle una vez encontrado el libro
                }
            }

            // Eliminar el préstamo de la lista
            prestamos.erase(prestamos.begin() + i);

            cout << "El libro ha sido devuelto exitosamente.\n";
            libroDevuelto = true;
            break;  // Salir del bucle ya que solo se puede devolver un libro a la vez
        }
    }

    if (!libroDevuelto) {
        cout << "No se encontró un prestamo con ese codigo.\n";
    }

    pausar();  // Si deseas pausar después de la devolución, puedes mantener este código.
}


void mostrarMisPrestamos () {
     if (prestamos.size() < 1) {
        cout << "Su historial de prestamos esta vacio." << endl;
        pausar();
        return; 
    }

    for (int i = 0; i < prestamos.size(); i++) {
        cout << "---------------------------------------------" << endl;
        cout << "Codigo   : " << prestamos[i].codigo << endl;
        cout << "Titulo   : " << prestamos[i].titulo << endl;
        cout << "Autor    : " << prestamos[i].autor << endl;
        cout << "Cantidad : " << prestamos[i].cantidadPrestada << endl;
    }
    cout << "---------------------------------------------" << endl;
}

void verMisPrestamos(){
    limpiarTerminal();
    cout << "=============================================" << endl;
    cout << "          LISTADO DETALLADO DE PRESTAMOS     " << endl;
    cout << "=============================================" << endl;

    mostrarMisPrestamos();
    pausar();
}


void buscarLibros(){} 

//CODIGO PARA PROGRAMAR LA FUNCIONALIDAD DEL ADMINISTRADOR

void menuAdmin() {
    int opc;
    cout << "-------------------------------------------" << endl;
    cout << "Menu Administrador" << endl;
    cout << "[1] Ver libros almacenados" << endl;
    cout << "[2] Agregar libro" << endl;
    cout << "[3] Eliminar libro" << endl;
    cout << "[4] Salir" << endl;
    cout << "Opción: "; cin >> opc;

    switch(opc) {
        case 1:
            verLibrosDisponibles(); 
            break;
        case 2:
            agregarLibros();
            break;
        case 3:
            
            break;
        case 4:
            cout << "Saliendo del menu administrador." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
            menuAdmin(); 
    }
}
void loginAdministrador() {
    string contrasena;
    string id;
    cout << "                INICIAR SESION" << endl;
    cout << "Tipo de usuario: Administrador" << endl;
    cout << "ID: "; cin >> id;
    cout << "Contraseña: "; cin >> contrasena;
    verificacionAdmin(id, contrasena);
}

void verificacionAdmin(string id, string contrasena) {
     limpiarTerminal();
    string identificacion = "admin001";
    string contra = "ucsur001";
    if (identificacion == id && contra == contrasena) {
        menuAdmin();
    } else {
        cout << "ID o contraseña inválida, vuelva a intentarlo" << endl;
        loginAdministrador();
    }
}

void agregarLibros() {
    int cod;
    string title;
    string author;
    int amount;
    cout << "----------- Sistema de agrecacion de libros ---------------- " << endl;
    cout << "Titulo: "; cin >> title;
    cout << "Autor: "; cin >> author;
    cout << "Cantidad: ";cin >>amount;
    cod = libros.size() + 1;
    cout << "-------------------------------------------" << endl;
    libros.push_back({to_string(cod),title,author,amount});
    cout << "Libro agregado con exito" << endl;
    menuAdmin();    
}

void eliminarLibro() {
    
}



























