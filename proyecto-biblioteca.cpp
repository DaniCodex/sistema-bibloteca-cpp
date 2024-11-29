#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <windows.h> 
#include <cstdlib>
#include <ctime>
#include "termcolor.hpp"
#include <regex> 

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
    {"3", "Cien anos de soledad", "Gabriel Garcia Marquez", 2},
    {"4", "El Principito", "Antoine de Saint-Exupery", 1},
    {"5", "Orgullo y prejuicio", "Jane Austen", 2},
    {"6", "Don Quijote de la Mancha", "Miguel de Cervantes", 4},
    {"7", "Matar a un ruisenor", "Harper Lee", 6},
    {"8", "Cumbres Borrascosas", "Emily Bronte", 3},
    {"9", "Cronica de una muerte anunciada", "Gabriel Garcia Marquez", 5},
    {"10", "La sombra del viento", "Carlos Ruiz Zafon", 7},
    {"11", "El retrato de Dorian Gray", "Oscar Wilde", 4},
    {"12", "Fahrenheit 451", "Ray Bradbury", 6},
    {"13", "El gran Gatsby", "F. Scott Fitzgerald", 5},
    {"14", "La casa de los espiritus", "Isabel Allende", 3},
    {"15", "La tregua", "Mario Benedetti", 2}
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
void menuUsuario(string nombreUsuario);
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
void mostrarLibrosDisponibles();


//FUNCION PRINCIPAL
int main() {
    sistemaInicio();  
}

//CODIGO GENERAL
int generarNumeroAleatorio() {
    srand(time(0));
    int tiempoAleatorio = rand() % 3 + 1;

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
    cin.ignore(1000, '\n'); // Ignorar la entrada previa
    cin.get(); // Esperar que el usuario presione Enter
}

//CODIGO PARA PROGRAMAR LA FUNCIONALIDAD EL USUARIO
void loginUsuario() {
    limpiarTerminal();
    int id;
    string contrasena;
    char opcion;
    string nombreUsuario = "";

    cout << "============================================" << endl;
    cout << "               INICIAR SESION                " << endl;
    cout << "============================================" << endl;;
    cout << "ID del usuario:  "; cin >> id; 
    cout << "Contrasena: "; cin >> contrasena;
    cout << "--------------------------------------------" << endl;

    for (int i = 0; i < numUsuarios; i++) {
        if (ids[i] == id && contrasenas[i] == contrasena) {
            nombreUsuario = nombres[i];
            cout << termcolor::green << "Inicio de sesion exitoso." << termcolor::reset << endl;
            Sleep(generarNumeroAleatorio() * 1000);
            menuUsuario(nombreUsuario);
            return; 
        }
    }
    
    cout << termcolor::red << "ID o contrasena incorrectos. Desea registrarse (s/n): " << termcolor::reset; cin >> opcion;
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
    string contrasena, correo, nombre;

    cout << "============================================" << endl;
    cout << "               REGISTRARSE                  " << endl;
    cout << "============================================" << endl;;
    cout << "Tipo de usuario: Usuario" << endl;
    cout << "-------------------------------------------" << endl;

    do {
        cout << "ID del usuario:  "; cin >> numero;
        if (cin.fail() || numero <= 0) {
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            cout << termcolor::red << "Por favor, ingrese un ID valido (numero positivo).\n" << termcolor::reset;
        }
    } while (numero <= 0);

    do {
        cout << "Nombre del Usuario:  "; cin.ignore(); 
        getline(cin, nombre);
        if (!regex_match(nombre, regex("^[a-zA-Z ]+$"))) {
            cout << termcolor::red << "Por favor, ingrese un nombre valido (solo letras y espacios).\n" << termcolor::reset;
        }
    } while (!regex_match(nombre, regex("^[a-zA-Z ]+$")));

    do {
        cout << "Correo Electronico: ";  cin >> correo;
        if (!regex_match(correo, regex(R"((\w+)(\.{0,1})(\w*)@(\w+)\.(\w+))"))) {
            cout << termcolor::red <<  "Por favor, ingrese un correo electronico valido.\n" << termcolor::reset;
        }
    } while (!regex_match(correo, regex(R"((\w+)(\.{0,1})(\w*)@(\w+)\.(\w+))")));

    do {
        cout << "Contrasena (minimo 4 caracteres): ";  cin >> contrasena;
        if (contrasena.length() < 4) {
            cout << termcolor::red << "La contrasena debe tener al menos 4 caracteres.\n" << termcolor::reset;
        }
    } while (contrasena.length() < 4);



    cout << "-------------------------------------------" << endl;
    cout << termcolor::green << " Usuario " 
         << termcolor::yellow << nombre 
         << termcolor::green << " registrado correctamente" 
         << termcolor::reset << endl;
    cout << "-------------------------------------------" << endl;

    Sleep(generarNumeroAleatorio() * 1000); 
    registrarUsuario(numero, correo, contrasena, nombre);
    loginUsuario(); 
    verificacionUsuario();
}
void registrarUsuario(int id, string correo, string contrasena, string nombre) { 
    if (numUsuarios < maxUsuarios) {
        ids[numUsuarios] = id; 
        correos[numUsuarios] = correo;
        contrasenas[numUsuarios] = contrasena;
        nombres[numUsuarios] = nombre;
        numUsuarios++;
    } else {
        cout << termcolor::red << "Error: capacidad maxima de usuarios alcanzada.\n" << termcolor::reset;
    }
}
void verificacionUsuario() {
    limpiarTerminal();
    int menu;
    cout << "======================================" << endl;
    cout << "          MENU DE USUARIO               " << endl;
    cout << "======================================" << endl;
    cout << " [1] Iniciar sesion                     " << endl;
    cout << " [2] Registrarse                        " << endl;
    cout << " [3] Informacion de la biblioteca       " << endl;
    cout << " [4] Preguntas frecuentes               " << endl;
    cout << " [5] Contactar soporte                  " << endl;
    cout << " [6] Salir                              " << endl;
    cout << "======================================" << endl;
    cout << "Seleccione una opcion: "; cin >> menu;
    cout << "======================================" << endl;

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
void menuUsuario(string nombreUsuario) {
    limpiarTerminal();

    for (int i = 0; i < nombreUsuario.length(); i++) {
        nombreUsuario[i] = toupper(nombreUsuario[i]); 
    }

    int opcion;
   

    do {
        cout << "=========================================" << endl;
        cout << "        BIENVENIDO " << termcolor::yellow << nombreUsuario << termcolor::reset << "!" << endl;
        cout << "=========================================" << endl;
        cout << "[1] Ver libros disponibles" << endl;
        cout << "[2] Prestar libro" << endl;
        cout << "[3] Devolver libro" << endl;
        cout << "[4] Ver mis prestamos" << endl;
        cout << "[5] Buscar libro" << endl;
        cout << "[6] Cerrar sesion" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Opcion: "; cin >> opcion;
        cout << "-----------------------------------------" << endl;

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
void mostrarLibrosDisponibles() {
    cout << "=============================================" << endl;
    cout << "          LIBROS DISPONIBLES     " << endl;
    cout << "=============================================" << endl;
    for (int i = 0; i < libros.size(); i++) {
        cout << "Codigo: " << libros[i].codigo << endl;
        cout << "Titulo: " << libros[i].titulo << endl;
        cout << "Autor: " << libros[i].autor << endl;
        cout << "Cantidad disponible: " << libros[i].cantidadDisponible << endl;
        cout << "-----------------------------------------" << endl;
    }
}
void verLibrosDisponibles() {
    limpiarTerminal();
    mostrarLibrosDisponibles();
    pausar();
    limpiarTerminal();
}
void informacionBiblioteca() {
    limpiarTerminal();
    cout << "Informacion de la biblioteca: \n";
    cout << "Horario: Lunes a Viernes de 8am a 6pm\n";
    cout << "Ubicacion: Calle Ejemplo 123\n";
    cout << "Servicios: Prestamo de libros, salas de estudio, eventos.\n\n";
    pausar();
    verificacionUsuario();
}
void preguntasFrecuentes() {
    limpiarTerminal();
    cout << "Preguntas Frecuentes:\n";
    cout << "1. Como me registro?\n";
    cout << "2. Cuantos libros puedo prestar?\n";
    cout << "3. Que hago si olvido mi contrasena?\n\n";
    pausar();
    verificacionUsuario();
}
void contactarSoporte() {
    limpiarTerminal();
    cout << termcolor::blue << "Para contactar soporte, envia un correo a soporte@biblioteca.com\n\n" << termcolor::reset;
    pausar();
    verificacionUsuario();
}
void prestarLibro(vector<Libro>& libros) {
    limpiarTerminal();
    string solicitarCodigo;
    string volverPrestarse;

    mostrarLibrosDisponibles();

    do {
        cout << "Ingrese el codigo del libro a prestar: "; cin >> solicitarCodigo;

        bool libroEncontrado = false;
        bool yaPrestado = false;

        for (int i = 0; i < prestamos.size(); i++) {
            if (prestamos[i].codigo == solicitarCodigo) {
                yaPrestado = true;
                break;
            }
        }

        if (yaPrestado) {
            cout << termcolor::yellow << "Ya tienes un prestamo activo de este libro. No puedes prestar mas copias." << termcolor::reset << endl;
        } else {
            for (int i = 0; i < libros.size(); i++) {
                if (solicitarCodigo == libros[i].codigo) {
                    libroEncontrado = true;

                    if (libros[i].cantidadDisponible > 0) {
                        libros[i].cantidadDisponible--; 
                        cout << termcolor::blue << "Buscando Libro..." << termcolor::reset << endl;
                        Sleep(generarNumeroAleatorio() * 1000);
                        cout << termcolor::green << "Libro prestado exitosamente." << termcolor::reset << endl;

                        prestamos.push_back({
                            libros[i].codigo,
                            libros[i].titulo,
                            libros[i].autor,
                            1 
                        });

                    } else {
                        cout << termcolor::blue << "Buscando Libro..." << termcolor::reset << endl;
                        Sleep(generarNumeroAleatorio() * 1000);
                        cout << termcolor::red << "No hay copias disponibles de este libro.\n" << termcolor::reset;
                    }
                    break;
                }
            }

            if (!libroEncontrado) {
                cout << termcolor::red << "El libro no esta disponible o no existe." << termcolor::reset << endl;
            }
        }

        cout << "Desea adquirir otro libro? (s/n): "; cin >> volverPrestarse;

    } while (volverPrestarse == "s" || volverPrestarse == "S");

    limpiarTerminal();
}
void devolverLibro() {
    limpiarTerminal();
    string solicitarCodigo;
    char respuesta;

    do {

        if (prestamos.empty()) {
            cout << termcolor::red << "No hay libros para devolver.\n" << termcolor::reset;
            pausar();
            break;
        }

        limpiarTerminal();
        cout << "=============================================" << endl;
        cout << "          DEVOLVER PRESTAMOS                 " << endl;
        cout << "=============================================" << endl;

        mostrarMisPrestamos();

        cout << "Ingrese el codigo del libro a devolver: "; cin >> solicitarCodigo;

        bool libroDevuelto = false;

        for (int i = 0; i < prestamos.size(); i++) {
            if (solicitarCodigo == prestamos[i].codigo) {
                for (int j = 0; j < libros.size(); j++) {
                    if (libros[j].codigo == solicitarCodigo) {
                        libros[j].cantidadDisponible++;  
                        break;
                    }
                }
                prestamos.erase(prestamos.begin() + i);
                libroDevuelto = true;
                cout << termcolor::green << "Libro devuelto exitosamente.\n" << termcolor::reset;
                break;
            }
        }

        if (!libroDevuelto) {
            cout << termcolor::red << "No se encontro un prestamo con ese codigo.\n" << termcolor::reset;
        }

        if (!prestamos.empty()) {
            cout << "Desea devolver otro libro? (s/n): "; cin >> respuesta;
        } else {
            cout << termcolor::yellow << "No quedan libros para devolver.\n" << termcolor::reset;
            pausar();
            break;
        }

    } while (respuesta == 's' || respuesta == 'S');
    limpiarTerminal();
}
void mostrarMisPrestamos () {
     if (prestamos.size() < 1) {
        cout << "Su historial de prestamos esta vacio." << endl;
        pausar();
        return; 
    }

    for (int i = 0; i < prestamos.size(); i++) {
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
    limpiarTerminal();
}
void buscarLibros() {
    limpiarTerminal();
    string criterioBusqueda;
    string terminoBusqueda;
    bool libroEncontrado = false;

    cout << "=============================================" << endl;
    cout << "               BUSCAR LIBROS                 " << endl;
    cout << "=============================================" << endl;
    cout << "[1] Buscar por titulo" << endl;
    cout << "[2] Buscar por autor" << endl;
    cout << "[3] Buscar por codigo" << endl;
    cout << "Seleccione el criterio de busqueda: ";
    
    int opcion; cin >> opcion;

    leerOpcionValida(opcion, 1, 3);  

    cin.ignore();  

    switch (opcion) {
        case 1:
            cout << "Ingrese el titulo del libro: ";
            getline(cin, terminoBusqueda);
            break;
        case 2:
            cout << "Ingrese el autor del libro: ";
            getline(cin, terminoBusqueda);
            break;
        case 3:
            cout << "Ingrese el codigo del libro: "; 
            cin >> terminoBusqueda;
            break;
        default:
            cout << termcolor::red << "Opcion no valida." << termcolor::reset << endl;
            return;
    }

    for (int i = 0; i < terminoBusqueda.length(); i++) {
        terminoBusqueda[i] = toupper(terminoBusqueda[i]);  
    }

    cout << "Buscando libros...\n";
    Sleep(generarNumeroAleatorio() * 1000); 

    limpiarTerminal();

    cout << "=============================================" << endl;
    cout << "              RESULTADOS DE BUSQUEDA         " << endl;
    cout << "=============================================" << endl;

    for (const auto& libro : libros) {
        bool coincidencia = false;

        string tituloUpper = libro.titulo;
        string autorUpper = libro.autor;
        string codigoUpper = libro.codigo;

        for (int i = 0; i < tituloUpper.length(); i++) {
            tituloUpper[i] = toupper(tituloUpper[i]);
        }
        for (int i = 0; i < autorUpper.length(); i++) {
            autorUpper[i] = toupper(autorUpper[i]);
        }
        for (int i = 0; i < codigoUpper.length(); i++) {
            codigoUpper[i] = toupper(codigoUpper[i]);
        }

        if (opcion == 1 && tituloUpper.find(terminoBusqueda) != string::npos) {
            coincidencia = true;
        } else if (opcion == 2 && autorUpper.find(terminoBusqueda) != string::npos) {
            coincidencia = true;
        } else if (opcion == 3 && codigoUpper == terminoBusqueda) {
            coincidencia = true;
        }

        if (coincidencia) {
            cout << termcolor::green << "Codigo: " << libro.codigo << termcolor::reset << endl;
            cout << "Titulo: " << libro.titulo << endl;
            cout << "Autor: " << libro.autor << endl;
            cout << "Cantidad disponible: " << libro.cantidadDisponible << endl;
            cout << "---------------------------------------------" << endl;
            libroEncontrado = true;
        }
    }

    if (!libroEncontrado) {
        cout << termcolor::red << "No se encontraron libros con el criterio proporcionado." << termcolor::reset << endl;
    }
    pausar();  
}



//CODIGO PARA PROGRAMAR LA FUNCIONALIDAD DEL ADMINISTRADOR

void menuAdmin() {
    int opc;
    cout << "=============================================" << endl;
    cout << "              MENU ADMINISTRADOR             " << endl;
    cout << "=============================================" << endl;
    cout << "[1] Ver libros almacenados" << endl;
    cout << "[2] Agregar libro" << endl;
    cout << "[3] Salir" << endl;
    cout << "Opcion: "; cin >> opc;
    
    leerOpcionValida(opc, 1,3);

    cout << "---------------------------------------------" << endl;

    switch(opc) {
        case 1:
            verLibrosDisponibles(); 
            break;
        case 2:
            agregarLibros();
            break;
        case 3:
            cout << "Saliendo del menu administrador." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
            menuAdmin(); 
    }
}
void loginAdministrador() {
    limpiarTerminal();
    string contrasena;
    string id;

    cout << "============================================" << endl;
    cout << "               INICIAR SESION                  " << endl;
    cout << "============================================" << endl;;
    cout << "Tipo de usuario: Administrador" << endl;
    cout << "-------------------------------------------" << endl;;
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
        cout << "-------------------------------------------" << endl;
        cout << "ID o contrasena invalida, vuelva a intentarlo" << endl;
        loginAdministrador();
    }
}
void agregarLibros() {
    limpiarTerminal();
    int cod;
    string title;
    string author;
    int amount;
    cout << "============================================" << endl;
    cout << "               AGREGAR LIBROS                  " << endl;
    cout << "============================================" << endl;
    cout << "Titulo: "; cin >> title;
    cout << "Autor: "; cin >> author;
    cout << "Cantidad: ";cin >>amount;
    cod = libros.size() + 1;
    cout << "-------------------------------------------" << endl;
    libros.push_back({to_string(cod),title,author,amount});
    cout << termcolor::red << "Libro agregado con exito" << termcolor::reset << endl;
    menuAdmin();    
}




























