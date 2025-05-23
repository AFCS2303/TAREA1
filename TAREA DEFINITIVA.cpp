#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

const int MAX_N = 50; // Tamaño máximo del laberinto

struct Pos { 
    int x, y; 
};

// Función para reiniciar todas las variables de estado
void ReiniciarEstado(bool visitado[MAX_N][MAX_N], int& recursivas, bool& encontrado, int& LongitudCaminoEncontrado, int& LongitudCaminoActual, Pos CaminoEncontrado[MAX_N * MAX_N]) { 
    for (int i = 0; i < MAX_N; ++i) {
        for (int j = 0; j < MAX_N; ++j) {
            visitado[i][j] = false;
        }
    }
    recursivas = 0; 
    encontrado = false; 
    LongitudCaminoEncontrado = 0; 
    LongitudCaminoActual = 0; 
    for (int i = 0; i < MAX_N * MAX_N; ++i) {
        CaminoEncontrado[i] = {0, 0};
    }
}

bool EsValido(int x, int y, int Laberinto[MAX_N][MAX_N], bool visitado[MAX_N][MAX_N], int N) {
    return (x >= 0 && x < N && y >= 0 && y < N) && (Laberinto[x][y] == 0 || Laberinto[x][y] == 2) && !visitado[x][y]; 
}

void BackTrackingFilaXColumna(int x, int y, int Laberinto[MAX_N][MAX_N], bool visitado[MAX_N][MAX_N], int N, int& recursivas, bool& encontrado, int& LongitudCaminoActual, int& LongitudCaminoEncontrado, Pos CaminoEncontrado[MAX_N * MAX_N]) { 
    recursivas++; 
    if (encontrado) return; 
    if (Laberinto[x][y] == 2) { 
        encontrado = true; 
        CaminoEncontrado[LongitudCaminoActual++] = {x, y}; 
        LongitudCaminoEncontrado = LongitudCaminoActual; 
        return; 
    } 
    visitado[x][y] = true; 
    CaminoEncontrado[LongitudCaminoActual++] = {x, y}; 
    int DireccionesX[] = {1, -1, 0, 0}; // Primero se mueve horizontalmente (derecha/izquierda)
    int DireccionesY[] = {0, 0, 1, -1}; // Luego explora verticalmente (arriba/abajo)


    for (int i = 0; i < 4; ++i) { 
        int nx = x + DireccionesX[i]; 
        int ny = y + DireccionesY[i]; 
        if (EsValido(nx, ny, Laberinto, visitado, N)) { 
            BackTrackingFilaXColumna(nx, ny, Laberinto, visitado, N, recursivas, encontrado, LongitudCaminoActual, LongitudCaminoEncontrado, CaminoEncontrado); 
            if (encontrado) return; 
        } 
    } 
    visitado[x][y] = false; 
    LongitudCaminoActual--; 
}

void BackTrackingColumnaXFila(int x, int y, int Laberinto[MAX_N][MAX_N], bool visitado[MAX_N][MAX_N], int N, int& recursivas, bool& encontrado, int& LongitudCaminoActual, int& LongitudCaminoEncontrado, Pos CaminoEncontrado[MAX_N * MAX_N]) 
{
    recursivas++;
    if (encontrado) return;
    if (Laberinto[x][y] == 2) {
        encontrado = true;
        CaminoEncontrado[LongitudCaminoActual++] = {x, y};
        LongitudCaminoEncontrado = LongitudCaminoActual;
        return;
    }
    visitado[x][y] = true;
    CaminoEncontrado[LongitudCaminoActual++] = {x, y};
    
    int DireccionesX[] = {0, 0, 1, -1}; // Mantiene la posición horizontal al inicio, luego explora izquierda/derecha
    int DireccionesY[] = {1, -1, 0, 0}; // Prioriza el movimiento vertical primero (arriba/abajo)

    for (int i = 0; i < 4; ++i) {
        int nx = x + DireccionesX[i];
        int ny = y + DireccionesY[i];
        if (EsValido(nx, ny, Laberinto, visitado, N)) {
            BackTrackingColumnaXFila(nx, ny, Laberinto, visitado, N, recursivas, encontrado, LongitudCaminoActual, LongitudCaminoEncontrado, CaminoEncontrado);
            if (encontrado) return;
        }
    }
    visitado[x][y] = false;
    LongitudCaminoActual--;
}

void imprimirCamino(Pos CaminoEncontrado[MAX_N * MAX_N], int LongitudCaminoEncontrado) {
    cout << "Camino encontrado:" << endl;
    for (int i = 0; i < LongitudCaminoEncontrado; ++i) {
        cout << "(" << CaminoEncontrado[i].x << "," << CaminoEncontrado[i].y << ")";
        if (i != LongitudCaminoEncontrado - 1) cout << " -> ";
    }
    cout << endl;
}

int main() {
    // Variables de estado
    bool visitado[MAX_N][MAX_N] = {false};
    int recursivas = 0;
    bool encontrado = false;
    int LongitudCaminoEncontrado = 0;
    int LongitudCaminoActual = 0;
    Pos CaminoEncontrado[MAX_N * MAX_N];
    
    // Laberinto
   int N = 0;
    cout << "Ingrese el Size del laberinto (N x N): ";
   cin >> N;
    int Laberinto[MAX_N][MAX_N] = {
    {0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0},
    {0,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1},
    {0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1},
    {0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
    {0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2}  // Salida en (49,49)
    };  
    


 /*  int Laberinto[MAX_N][MAX_N] = {
    {0, 1, 0, 0, 0, 1, 0, 0, 0, 1},  // Fila 0 (Inicio en (0,0))
    {0, 1, 0, 1, 1, 1, 0, 1, 0, 1},  // Fila 1
    {0, 0, 0, 1, 0, 1, 0, 1, 0, 0},  // Fila 2
    {0, 1, 0, 1, 0, 0, 0, 1, 1, 0},  // Fila 3
    {1, 1, 0, 1, 0, 1, 1, 1, 0, 0},  // Fila 4
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 1},  // Fila 5 (¡Punto de bifurcación!)
    {0, 1, 1, 1, 0, 1, 0, 1, 0, 1},  // Fila 6
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 1},  // Fila 7
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},  // Fila 8
    {0, 0, 0, 0, 0, 1, 0, 0, 2, 1}   // Fila 9 (Salida en (9,8))
    };  */
  


     /* int Laberinto[MAX_N][MAX_N] = {
    {0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0}, // Fila 0 (Inicio)
    {0,1,0,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1,1,0},
    {0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,0,1,0},
    {0,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,0,1,0},
    {0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0},
    {0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,0,1,0,1,0},
    {0,1,0,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,1,0},
    {0,1,1,1,1,1,0,1,0,1,1,1,1,0,1,0,1,0,1,0},
    {0,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,1,0,1,0},
    {1,1,1,1,0,1,0,1,1,1,1,0,1,0,1,0,1,0,1,0},
    {0,0,0,1,0,1,0,0,0,0,1,0,1,0,1,0,1,0,1,0},
    {0,1,0,1,0,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0},
    {0,1,0,1,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0},
    {0,1,0,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
    {0,1,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
    {0,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
    {0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
    {1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
    {0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},
    {1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}   // Fila 19 (Salida en (19,19))
    };  */
 

    // Primera ejecución: FilaXColumna
    for (int iter = 1; iter <= 100; iter++) {
        cout << "Iteracion " << iter << endl;

        auto start1 = high_resolution_clock::now();
        BackTrackingFilaXColumna(0, 0, Laberinto, visitado, N, recursivas, encontrado, LongitudCaminoActual, LongitudCaminoEncontrado, CaminoEncontrado);
        auto end1 = high_resolution_clock::now();
        duration<double, milli> duracion1 = end1 - start1;
        if (encontrado) {
            cout << "FilaxColumna: Tiempo de ejecucion: (" << duracion1.count() << "), recursivas: (" << recursivas << "), celdas usadas: (" << LongitudCaminoEncontrado << ")" << endl;
        } else {
            cout << "FilaxColumna: No se encontro camino." << endl;
        }

        ReiniciarEstado(visitado, recursivas, encontrado, LongitudCaminoEncontrado, LongitudCaminoActual, CaminoEncontrado);

        auto start2 = high_resolution_clock::now();
        BackTrackingColumnaXFila(0, 0, Laberinto, visitado, N, recursivas, encontrado, LongitudCaminoActual, LongitudCaminoEncontrado, CaminoEncontrado);
        auto end2 = high_resolution_clock::now();
        duration<double, milli> duracion2 = end2 - start2;
        if (encontrado) {
            cout << "ColumnaXFila: Tiempo de ejecucion: (" << duracion2.count() << "), recursivas: (" << recursivas << "), celdas usadas: (" << LongitudCaminoEncontrado << ")" << endl;
        } else {
            cout << "ColumnaXFila: No se encontro camino." << endl;
        }

        cout << endl;

        ReiniciarEstado(visitado, recursivas, encontrado, LongitudCaminoEncontrado, LongitudCaminoActual, CaminoEncontrado);
    }

    return 0;
}
