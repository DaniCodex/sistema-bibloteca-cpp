#include <iostream>
#include <string>
#include <vector>
#include <windows.h> 
#include <cstdlib>
#include <ctime>
#include <limits>

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
    {"3", "Cien años de soledad", "Gabriel García Márquez", 2},
    {"4", "El principito", "Antoine de Saint-Exupéry", 1},
    {"5", "Orgullo y prejuicio", "Jane Austen", 2}
};

struct Prestamo {
    string codigo;
    string titulo;
    string autor;
    int cantidadDisponible;
};

vector<Prestamo> prestamos;


void sistemaInicio();
void loginUsuario();
void registroUsuario();
void loginAdministrador();
void verificacionUsuario();
void verificacionAdmin(string id, string contrasena);
void verLibrosAlmacenados();
void agregarLibros(string titulo, string autor);
void eliminarLibro();
void menuAdmin();
void dbRegister(int idUsuario, string contrasena, string correo);
void registrarUsuario(int id, string correo, string contrasena, string nombres);
void limpiarTerminal();
void menuUsuario();
void verLibrosDisponibles(const vector<Libro>& libros); 
void prestarLibro(vector<Libro>& libros); 
void devolverLibro();
void verMisPrestamos(); 
void buscarLibros();  
void informacionBiblioteca() ;
void preguntasFrecuentes();
void contactarSoporte();
int generarNumeroAleatorio();


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

void sistemaInicio() {
    int opcion;
    cout << "====================================================" << endl;
    cout << "                SISTEMA DE BIBLIOTECA               " << endl;
    cout << "====================================================" << endl;
    cout << "  [1] Usuario (Consultar prestamos, buscar libros)" << endl;
    cout << "  [2] Administrador (Gestionar inventario, usuarios)" << endl;
    cout << "  [3] Salir del sistema" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "Ingrese su opcion: "; cin >> opcion;
    
    while (cin.fail() || opcion < 1 || opcion > 3) {
        cin.clear(); 
        cin.ignore(1000, '\n'); 
        cout << "Opcion no valida. Intente nuevamente: ";
        cin >> opcion;
    }

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
            cout << "Inicio de sesión exitoso." << endl;
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
    cout << "Contraseña: "; cin >> contrasena;

    cout << "-------------------------------------------" << endl;
    cout << " Usuario " << nombre  << " registrado correctamente" << endl;
    cout << "-------------------------------------------" << endl;

    Sleep(5); 
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
        cout << "Error: capacidad máxima de usuarios alcanzada.\n";
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

    while (cin.fail() || menu < 1 || menu > 6) {
        cin.clear(); 
        cin.ignore(1000, '\n');
        cout << "Opcion no valida. Por favor, intente de nuevo: "; cin >> menu;
    }

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
            cout << "Opción no válida. Por favor, intenta de nuevo." << endl;
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
        cout << "[4] Ver mis préstamos" << endl;
        cout << "[5] Actualizar perfil" << endl;
        cout << "[6] Cerrar sesión" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "Opción: "; cin >> opcion;
        cout << "-------------------------------------------" << endl;

        switch(opcion) {
            case 1:
                verLibrosDisponibles(libros); 
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
                cout << "Cerrando sesión..." << endl;
                sistemaInicio(); // Regresar al menú de inicio
                break;
            default:
                cout << "Opción no válida. Por favor, intenta de nuevo." << endl;
        }
    } while (opcion != 6);
}
void verLibrosDisponibles(const vector<Libro>& libros) {
    limpiarTerminal();
    
    // Número de libros
    int totalLibros = 5;

    // Mostrar la información de los libros
    for (int i = 0; i < libros.size(); i++) {
        cout << "Código: " << libros[i].codigo << endl;
        cout << "Título: " << libros[i].titulo << endl;
        cout << "Autor: " << libros[i].autor << endl;
        cout << "Cantidad disponible: " << libros[i].cantidadDisponible << endl;
        cout << "-------------------------" << endl;
    }


    cout << "Presione cualquier tecla para continuar... \n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Esperar entrada de usuario
    cin.get(); // Pausar para que el usuario vea los resultados
}

void informacionBiblioteca() {
    cout << "Información de la biblioteca: \n";
    cout << "Horario: Lunes a Viernes de 8am a 6pm\n";
    cout << "Ubicación: Calle Ejemplo 123\n";
    cout << "Servicios: Préstamo de libros, salas de estudio, eventos.\n";
    cout << "Presione cualquier tecla para continuar... \n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    verificacionUsuario();
}
void preguntasFrecuentes() {
    cout << "Preguntas Frecuentes:\n";
    cout << "1. ¿Cómo me registro?\n";
    cout << "2. ¿Cuántos libros puedo prestar?\n";
    cout << "3. ¿Qué hago si olvido mi contraseña?\n";
    cout << "Presione cualquier tecla para continuar... \n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    verificacionUsuario();
}
void contactarSoporte() {
    cout << "Para contactar soporte, envía un correo a soporte@biblioteca.com\n";
    cout << "Presione cualquier tecla para continuar... \n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    verificacionUsuario();
}
void prestarLibro(vector<Libro>& libros) {

    string solicitarCodigo;
    string volverPrestarse;

    int totalLibros = 5;
    
    for (int i = 0; i < libros.size(); i++) {
        cout << "Código: " << libros[i].codigo << endl;
        cout << "Título: " << libros[i].titulo << endl;
        cout << "Autor: " << libros[i].autor << endl;
        cout << "Cantidad disponible: " << libros[i].cantidadDisponible << endl;
        cout << "-------------------------" << endl;
    }

    do {
        cout << "Ingrese el codigo del libro a prestar: "; cin >> solicitarCodigo;

        bool libroEncontrado = false;

        for (int i = 0; i < libros.size(); i++) {
            if (solicitarCodigo == libros[i].codigo) {
                libroEncontrado = true;
                if (libros[i].cantidadDisponible > 0) {
                    libros[i].cantidadDisponible--; 
                    cout << "Buscando Libro... \n";
                    Sleep(generarNumeroAleatorio() * 1000); 
                    cout << "Libro prestado exitosamente.\n";
                    prestamos.push_back({libros[i].codigo, libros[i].titulo, libros[i].autor, libros[i].cantidadDisponible});
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

void devolverLibro(){}


void verMisPrestamos(){
    limpiarTerminal();

    cout << "----------- Tus préstamos -----------" << endl;

    // Usando un bucle for normal para recorrer el vector
    for (int i = 0; i < prestamos.size(); i++) {
        cout << "Código: " << prestamos[i].codigo;
        cout << ", Título: " << prestamos[i].titulo << endl;
    }

    cout << "-------------------------------------" << endl;
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
            verLibrosAlmacenados(); 
            break;
        case 2:
            
            break;
        case 3:
            
            break;
        case 4:
            cout << "Saliendo del menú administrador." << endl;
            break;
        default:
            cout << "Opción no válida." << endl;
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
void verLibrosAlmacenados() {
    limpiarTerminal();
    
    // Ejemplo de libros almacenados (puedes reemplazar esto por datos de una base de datos o archivos)
    vector<int> codigos = {1, 2, 3, 4, 5}; 
    vector<string> titulos = {"El Alquimista", "1984", "Cien años de soledad", "El principito", "Orgullo y prejuicio"};
    vector<string> autores = {"Paulo Coelho", "George Orwell", "Gabriel García Márquez", "Antoine de Saint-Exupéry", "Jane Austen"};
    vector<string> estados = {"disponible", "prestado", "disponible", "disponible", "prestado"}; // Estado de cada libro

    cout << "----------- Libros Almacenados -----------" << endl;
    cout << "-------------------------------------------" << endl;

    // Mostrar todos los libros almacenados
    for (size_t i = 0; i < codigos.size(); i++) {
        cout << "Código: " << codigos[i] 
             << ", Título: " << titulos[i] 
             << ", Autor: " << autores[i] 
             << ", Estado: " << estados[i] << endl;
    }

    cout << "-------------------------------------------" << endl;
    cout << "Presione cualquier tecla para continuar... \n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Esperar entrada de usuario
    cin.get(); // Pausar para que el usuario vea los resultados
}
void agregarLibros(string titulo, string autor) {
    
}
void eliminarLibro() {
    
}


























