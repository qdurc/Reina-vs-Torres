/*
Realizar un programa C++ que genere los movimientos posibles (según las reglas del ajedrez) de
una Reina amenazada por dos Torres enemigas. El programa debe desplegar el tablero con las
jugadas posibles de la Reina, colocando una V donde la reina pueda moverse sin ser eliminada y
una X donde pueda moverse, pero ser eliminada por una o las dos torres enemigas.
RESTRICCIONES:

A. El programa debe solicitar al usuario las posiciones de las dos torres enemigas y la de la
reina. ✅
B. Las posiciones de las torres no deben solaparse, es decir, no deben estar en la misma
posición. Las Torres deben estar en casillas distintas. ✅
C. La posición de la reina no debe coincidir con las de las torres. ✅
D. Debe desplegar el cuadro del ajedrez indicando a la reina con una R, las torres como T y
las jugadas según se establece en el enunciado. ✅
*/

#include <iostream>
using namespace std;

//Varibales globlales
const int BOARD_SIZE = 8;
const char EMPTY = '-';
const char QUEEN = 'R';
const char TOWER = 'T';
const char TOWER_MOVE = 'X';

//Estructuras de datos
struct Position {
    //Posicion de las fichas
    int row; //Filas
    int col; // Columnas
};

struct Game {
    //Estructura del juego 8 x 8
    char board[BOARD_SIZE][BOARD_SIZE];
    Position queen; //Ficha de la reina
    Position towers[2]; //2 Fichas de torres
};

//Prototipo de funciones 
void initializeBoard(Game&);
void printBoard(const Game&);
void placePiece(Game&, const Position&, char);
bool canQueenMove(const Game&, const Position&);
bool verifyPos(const Game&, const Position&);
void generateQueenMoves(Game&);
bool isValidRange(int&, int&);

//Función que inicializa la tabla de Ajedrez
void initializeBoard(Game& game) {
    //For loop de la tabla vacía de arriba a abajo "-"
    for (int i = 0; i < BOARD_SIZE; i++) {
        //For loop de la tabla vacía de izquierda a derecha "-"
        for (int j = 0; j < BOARD_SIZE; j++) {
            game.board[i][j] = EMPTY;
        }
    }
}

//Función imprime muestra los bordes de la tabla (filas, columnas)
void printBoard(const Game& game) {
    //For loop que imprime de izquierda a derecha las columnas 1-8
    cout << "  ";
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i + 1 << " ";
    }
    cout << endl;

    //For loop que imprime de arriba hacia abajo las filas 1-8
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i + 1 << " ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << game.board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

//Funcion que posiciona las fichas en el tablero 
void placePiece(Game& game, const Position& pos, char piece) {
    game.board[pos.row][pos.col] = piece;
}

//Valida si una Reina puede moverse a una posición específica
bool canQueenMove(const Game& game, const Position& newPos) {
    //Verifica si la reina se mueve en su posición actual, se mueve horizontalmente en la fila
    if (game.queen.row == newPos.row || 
    //Verifica si la reina se mueve en su posición actual, se mueve verticalmente en la columna
        game.queen.col == newPos.col || 
    /* Verifica si la diferencia de las filas son iguales que la diferencia de las columnas,
    esto indica que la reina se mueve diagonalmente */
        abs(game.queen.row - newPos.row) == abs(game.queen.col - newPos.col)){
        return true;
    }
    return false;
}

//Valida si la posición no está ocupada por la reina o una torre
bool verifyPos(const Game& game, const Position& pos) {
    //Esta parte verifica que la posición no sea la misma que la posición de la Reina
    return (pos.row != game.queen.row || pos.col != game.queen.col) &&
    //Esta parte verifica que la posición no sea la misma que la posición de la Torre 1 
           (pos.row != game.towers[0].row || pos.col != game.towers[0].col) &&
    //Esta parte verifica que la posición pos no sea la misma que la posición de la Torre 2
           (pos.row != game.towers[1].row || pos.col != game.towers[1].col);
}
/* Si la posición es diferente al de la reina y las torres devuelve true
De lo contrario, devuelve false */

//Función que genera los movimientos de la reina
void generateQueenMoves(Game& game) {
    //Se genera el tablero
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            //Representa una nueva posición en el tablero
            Position newPos = {i, j};
            /* Verifica que la reina se pueda mover 
            y no haya niguna ficha en dicha posición*/
            if (canQueenMove(game, newPos) && verifyPos(game, newPos)) {
                //Se coloca V en la posición que se mueve la reina
                game.board[i][j] = 'V';
                
                /*Verifica si el movimiento de la reina se encuentra en la misma fila 
                o columna que una de las dos torres en el tablero */
                if (newPos.row == game.towers[0].row || 
                    newPos.row == game.towers[1].row ||
                    newPos.col == game.towers[0].col || 
                    newPos.col == game.towers[1].col) {
                    //Se coloca X en la posición que se mueve la reina pero se encuentran las torres
                    game.board[i][j] = TOWER_MOVE;
                }
            }
        }
    }
}

// Función para verificar si una fila y columna están dentro del rango válido (1-8)
bool isValidRange(int& row, int& col) {
    //Si el rango se encuentra entre 1 y 8, es válido
    if ((row >= 1 && row <= 8) && (col >= 1 && col <= 8)){
        return true;
    }
    //De lo contrario, no es válido
    else{
        return false;
    }
}

int readInt() {
    int value;
    while (!(cin >> value)) {
        cout << "Ingrese un valor válido: ";
        cin.clear();
        cin.ignore(123, '\n');
    }
    return value;
}

void menu(){
    Game game; //Se crea el juego
    initializeBoard(game); //Se inicia el tablero
    int option;
    bool gameInitialized = false;

    while (true) {
        cout<< "Menu:\n"
            << "1. Posicionar torres y reina\n"
            << "2. Generar movimientos\n"
            << "3. Mostrar tablero\n"
            << "4. Reiniciar juego\n"
            << "5. Salir\n"
            << "Seleccione una opción: ";
        int option = readInt();
        cout << endl;

        switch (option) {
            case 1:
                if (gameInitialized) {
                    cout << "Las torres y la reina ya han sido posicionadas.\n" << endl;
                } else {
                    // Posición de la Reina
                    cout << "Posicione la Reina (fila columna): ";
                    cin >> game.queen.row >> game.queen.col;
                    /* Se valida que las entradas del usuario de la Reina 
                       no salgan del tamaño del tablero MIN 1; MAX = 8
                    */
                    if (!isValidRange(game.queen.row, game.queen.col)) {
                        cout << "La Reina está fuera de rango\n" << endl;
                        break;
                    }
                    /* Se ajustan las coordenadas de la reina a un índice basado en 0 
                    en lugar de un índice basado en 1. */
                    game.queen.row--; 
                    game.queen.col--; 

                    // Posición de la Torre 1
                    cout << "Posicione la Torre 1 (fila columna): ";
                    cin >> game.towers[0].row >> game.towers[0].col;
                    /* Se valida que las entradas del usuario de la torre 1 
                       no salgan del tamaño del tablero MIN 1; MAX = 8
                    */
                    if (!isValidRange(game.towers[0].row, game.towers[0].col)) {
                        cout << "La torre 1 está fuera de rango\n" << endl;
                        break;
                    }
                    /* Se ajustan las coordenadas de la torre 1 a un índice basado en 0 
                    en lugar de un índice basado en 1. */
                    game.towers[0].row--; 
                    game.towers[0].col--; 

                    // Posición de la Torre 2
                    cout << "Posicione la Torre 2 (fila columna): ";
                    cin >> game.towers[1].row >> game.towers[1].col;
                    /* Se valida que las entradas del usuario de la torre 2 
                       no salgan del tamaño del tablero MIN 1; MAX = 8
                    */
                    if (!isValidRange(game.towers[1].row, game.towers[1].col)) {
                        cout << "La torre 2 está fuera de rango\n" << endl;
                        break;
                    }
                    /* Se ajustan las coordenadas de la torre 2 a un índice basado en 0 
                    en lugar de un índice basado en 1. */
                    game.towers[1].row--; 
                    game.towers[1].col--; 

                    // Verificar si las torres se encuentran en la misma posición
                    if (game.towers[0].row == game.towers[1].row && game.towers[0].col == game.towers[1].col) {
                        cout << "Las torres no pueden solaparse.\n" << endl;
                        gameInitialized = false;
                    } 
                    // Verificar si la reina se encuentran en la misma posición de la torre 1 
                    else if (game.queen.row == game.towers[0].row && game.queen.col == game.towers[0].col) {
                        cout << "La Torre 1 no puede solaparse con la Reina.\n" << endl;
                        gameInitialized = false;
                    }
                    // Verificar si la reina se encuentran en la misma posición de la torre 2
                    else if (game.queen.row == game.towers[1].row && game.queen.col == game.towers[1].col) {
                        cout << "La Torre 2 no puede solaparse con la Reina.\n" << endl;
                        gameInitialized = false;
                    }
                    /* Si no se encuentran en la misma posición, 
                    entonces se colocan las fichas */
                    else {
                        placePiece(game, game.queen, QUEEN);
                        placePiece(game, game.towers[0], TOWER);
                        placePiece(game, game.towers[1], TOWER);
                        cout << "Fichas posicionadas correctamente\n" << endl;
                        gameInitialized = true;
                    }
                }
                break;
            case 2:
                //Si no se ha iniciado el juego
                if (!gameInitialized) {
                    cout << "Debe posicionar todas las fichas\n" << endl;
                } 
                //De lo contrario, se generan los movimientos de la reina
                else {
                    generateQueenMoves(game);
                    printBoard(game);
                }
                break;
            case 3:
                //Se muestra el tablero 
                printBoard(game);
                break;
            case 4:
                //Si no se ha iniciado el juego
                if (!gameInitialized) {
                    cout << "Juego no iniciado\n" <<endl;
                } 
                //De lo contrario, se reinicia el juego 
                else {
                    initializeBoard(game); 
                    gameInitialized = false;
                    cout << "Juego reiniciado\n" <<endl;
                }
                break;
            case 5:
                cout << "Saliendo del juego...\n";
            default:
                cout << "Opción inválida, intente de nuevo.\n";
                break;
        }
        cout << endl;
    }
}

int main() { 
    cout << "---- Reinas vs Torres ----\n" << endl;
    menu();
    return 0;
}
