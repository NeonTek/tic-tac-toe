#include <iostream>
#include <string>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

std::string positions[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

int turn = 0;
bool player2 = false;
bool ai = false;
bool vsPlayer = false;
int no = 0;

void menu();
void game();
void switchPlayer() {
    player2 = !player2;
    turn++;
    no++;
}
void resetBoard() {
    for (int i = 0; i < 9; i++)
        positions[i] = std::to_string(i + 1);
}
void drawBoard() {
    system("CLS");
    for (int i = 0; i < 9; i++) {
        if (i == 1 || i == 4 || i == 7) {
            std::cout << " | " << positions[i] << " | ";
        } else {
            std::cout << " " << positions[i];
        }
        if ((i + 1) % 3 == 0 && i > 0)
            std::cout << "\n---|---|---\n";
    }
}
void resetGame() {
    resetBoard();
    turn = 0;
}

bool checkWin() {
    // Check rows
    if ((positions[0] == positions[1] && positions[1] == positions[2]) || // Row 1
        (positions[3] == positions[4] && positions[4] == positions[5]) || // Row 2
        (positions[6] == positions[7] && positions[7] == positions[8])) { // Row 3
        return true;
    }

    // Check columns
    if ((positions[0] == positions[3] && positions[3] == positions[6]) || // Column 1
        (positions[1] == positions[4] && positions[4] == positions[7]) || // Column 2
        (positions[2] == positions[5] && positions[5] == positions[8])) { // Column 3
        return true;
    }

    // Check diagonals
    if ((positions[0] == positions[4] && positions[4] == positions[8]) || // Diagonal 1
        (positions[2] == positions[4] && positions[4] == positions[6])) { // Diagonal 2
        return true;
    }

    return false;
}
void gameDrawn() {
    drawBoard();
    std::cout << "\nGame drawn! No one wins.\n";
    std::cout << "1. Try Again!\n";
    std::cout << "2. Menu\n";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        resetGame(); 
        game();
    } 
    if (choice == 2) {
        resetGame();
        menu();
    }
}
void callWin() {
    if (vsPlayer == true) {
        std::cout << "Player " << (player2? "2" : "1") << " wins!\n";
    } else {
        std::cout << (no % 2 == 0? "AI wins\n" : "You win!\n");
    }
    std::cout << "1. Try Again!\n";
    std::cout << "2. Menu\n";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        resetGame(); 
        game();
    } 
    if (choice == 2) {
        resetGame();
        menu();
    }
}

void aiMove() {
    // Check for winning move
    for (int i = 0; i < 3; ++i) {
        // Check rows
        if (positions[i*3] == "O" && positions[i*3 + 1] == "O" && positions[i*3 + 2] != "X") {
            if (positions[i*3 + 2] != "O") {
                positions[i*3 + 2] = "O";
                return;
            }
        }
        if (positions[i*3] == "O" && positions[i*3 + 2] == "O" && positions[i*3 + 1] != "X") {
            if (positions[i*3 + 1] != "O") {
                positions[i*3 + 1] = "O";
                return;
            }
        }
        if (positions[i*3 + 1] == "O" && positions[i*3 + 2] == "O" && positions[i*3] != "X") {
            if (positions[i*3] != "O") {
                positions[i*3] = "O";
                return;
            }
        }
        
        // Check columns
        if (positions[i] == "O" && positions[i + 3] == "O" && positions[i + 6] != "X") {
            if (positions[i + 6] != "O") {
                positions[i + 6] = "O";
                return;
            }
        }
        if (positions[i] == "O" && positions[i + 6] == "O" && positions[i + 3] != "X") {
            if (positions[i + 3] != "O") {
                positions[i + 3] = "O";
                return;
            }
        }
        if (positions[i + 3] == "O" && positions[i + 6] == "O" && positions[i] != "X") {
            if (positions[i] != "O") {
                positions[i] = "O";
                return;
            }
        }
    }

    // Check diagonals
    if (positions[0] == "O" && positions[4] == "O" && positions[8] != "X") {
        if (positions[8] != "O") {
            positions[8] = "O";
            return;
        }
    }
    if (positions[0] == "O" && positions[8] == "O" && positions[4] != "X") {
        if (positions[4] != "O") {
            positions[4] = "O";
            return;
        }
    }
    if (positions[4] == "O" && positions[8] == "O" && positions[0] != "X") {
        if (positions[0] != "O") {
            positions[0] = "O";
            return;
        }
    }
    if (positions[2] == "O" && positions[4] == "O" && positions[6] != "X") {
        if (positions[6] != "O") {
            positions[6] = "O";
            return;
        }
    }
    if (positions[2] == "O" && positions[6] == "O" && positions[4] != "X") {
        if (positions[4] != "O") {
            positions[4] = "O";
            return;
        }
    }
    if (positions[4] == "O" && positions[6] == "O" && positions[2] != "X") {
        if (positions[2] != "O") {
            positions[2] = "O";
            return;
        }
    }

    // Block player
    for (int i = 0; i < 3; ++i) {
        // Check rows
        if (positions[i*3] == "X" && positions[i*3 + 1] == "X" && positions[i*3 + 2] != "O") {
            if (positions[i*3 + 2] != "X") {
                positions[i*3 + 2] = "O";
                return;
            }
        }
        if (positions[i*3] == "X" && positions[i*3 + 2] == "X" && positions[i*3 + 1] != "O") {
            if (positions[i*3 + 1] != "X") {
                positions[i*3 + 1] = "O";
                return;
            }
        }
        if (positions[i*3 + 1] == "X" && positions[i*3 + 2] == "X" && positions[i*3] != "O") {
            if (positions[i*3] != "X") {
                positions[i*3] = "O";
                return;
            }
        }
        
        // Check columns
        if (positions[i] == "X" && positions[i + 3] == "X" && positions[i + 6] != "O") {
            if (positions[i + 6] != "X") {
                positions[i + 6] = "O";
                return;
            }
        }
        if (positions[i] == "X" && positions[i + 6] == "X" && positions[i + 3] != "O") {
            if (positions[i + 3] != "X") {
                positions[i + 3] = "O";
                return;
            }
        }
        if (positions[i + 3] == "X" && positions[i + 6] == "X" && positions[i] != "O") {
            if (positions[i] != "X") {
                positions[i] = "O";
                return;
            }
        }
    }

    // Check diagonals
    if (positions[0] == "X" && positions[4] == "X" && positions[8] != "O") {
        if (positions[8] != "X") {
            positions[8] = "O";
            return;
        }
    }
    if (positions[0] == "X" && positions[8] == "X" && positions[4] != "O") {
        if (positions[4] != "X") {
            positions[4] = "O";
            return;
        }
    }
    if (positions[4] == "X" && positions[8] == "X" && positions[0] != "O") {
        if (positions[0] != "X") {
            positions[0] = "O";
            return;
        }
    }
    if (positions[2] == "X" && positions[4] == "X" && positions[6] != "O") {
        if (positions[6] != "X") {
            positions[6] = "O";
            return;
        }
    }
    if (positions[2] == "X" && positions[6] == "X" && positions[4] != "O") {
        if (positions[4] != "X") {
            positions[4] = "O";
            return;
        }
    }
    if (positions[4] == "X" && positions[6] == "X" && positions[2] != "O") {
        if (positions[2] != "X") {
            positions[2] = "O";
            return;
        }
    }

    // If no win/block is possible, make a random move
    int choice;
    while (true) {
        choice = rand() % 9;
        if (positions[choice] != "X" && positions[choice] != "O") {
            positions[choice] = "O";
            break;
        }
    }
}




void playerMove() {
    std::string letter = "X";
    int choice;
    std::cout << "Player " << (player2  && ai == false? "2" : "1") << "'s turn: ";
    std::cin >> choice;
    if (turn == 9 && checkWin() == false) {
        gameDrawn();
        return;
    }
    if (checkWin() == true) {
        callWin();
        return;
    }
    if (choice >= 1 && choice <= 9 && positions[choice - 1] != "X" && positions[choice - 1] != "O") {
        if (player2 == true && vsPlayer == true) {
            letter = "O";
        } 
        positions[choice - 1] = letter;
        
    } else {
        std::cout << "Invalid move. Try again.\n";
        playerMove();
    }
    switchPlayer();
}

void playGame() {
    playerMove();
    if (ai == true) {
        aiMove();
    }
    system("CLS");
    drawBoard();
}


void game() {
    resetGame(); // Ensure the game starts with a fresh board
    while (true) {
        system("CLS"); // Clear the screen
        drawBoard();

        if (checkWin()) {
            callWin();
            break;
        }

        if (turn >= 9) {
            gameDrawn();
            break;
        }

        if (player2 && ai) {
            aiMove(); // AI makes a move
            switchPlayer();
        } else {
            playerMove(); // Player makes a move
            if (!vsPlayer && turn < 9) {
                aiMove(); // AI makes a move
                switchPlayer();
            }
        }

        if (checkWin()) {
            drawBoard();
            callWin();
            break;
        }

        if (turn >= 9) {
            gameDrawn();
            break;
        }
        no++;
    }
}


void menu() {
    system("CLS");
    std::cout << "Welcome to Tic Tac Toe!\n";
    std::cout << "1. Player vs Player\n";
    std::cout << "2. Player vs AI\n";
    std::cout << "3. Exit\n";
    int choice;
    std::cin >> choice;
    switch (choice) {
        case 1:
            vsPlayer = true;
            player2 = false;
            ai = false;
            game();
            break;
        case 2:
            vsPlayer = false;
            player2 = false;
            ai = true;
            game();
            break;
        case 3:
            return;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            menu();
    }
    system("CLS");
}

int main() {
    srand(time(0)); // Seed the random number generator
    menu();
    return 0;
}
