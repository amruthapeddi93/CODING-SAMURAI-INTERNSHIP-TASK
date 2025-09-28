#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const char HUMAN = 'X';
const char COMPUTER = 'O';
const char EMPTY = ' ';

struct Move {
    int row, col;
};

// Print the board
void printBoard(const vector<vector<char>>& board) {
    cout << "\n";
    cout << "  0   1   2\n";
    for (int r = 0; r < 3; ++r) {
        cout << r << " ";
        for (int c = 0; c < 3; ++c) {
            cout << board[r][c];
            if (c < 2) cout << " | ";
        }
        cout << "\n";
        if (r < 2) cout << "  ---------\n";
    }
    cout << "\n";
}

// Check if any moves left
bool isMovesLeft(const vector<vector<char>>& board) {
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            if (board[r][c] == EMPTY) return true;
    return false;
}

// Evaluate board: +10 if COMPUTER wins, -10 if HUMAN wins, 0 otherwise
int evaluate(const vector<vector<char>>& b, char computerSymbol, char humanSymbol) {
    // Rows
    for (int row = 0; row < 3; ++row) {
        if (b[row][0] == b[row][1] && b[row][1] == b[row][2]) {
            if (b[row][0] == computerSymbol) return +10;
            else if (b[row][0] == humanSymbol) return -10;
        }
    }
    // Columns
    for (int col = 0; col < 3; ++col) {
        if (b[0][col] == b[1][col] && b[1][col] == b[2][col]) {
            if (b[0][col] == computerSymbol) return +10;
            else if (b[0][col] == humanSymbol) return -10;
        }
    }
    // Diagonals
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
        if (b[0][0] == computerSymbol) return +10;
        else if (b[0][0] == humanSymbol) return -10;
    }
    if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
        if (b[0][2] == computerSymbol) return +10;
        else if (b[0][2] == humanSymbol) return -10;
    }
    return 0;
}

// Minimax algorithm (returns score). depth is current depth, isMax true when maximizing for computer.
int minimax(vector<vector<char>>& board, int depth, bool isMax, char computerSymbol, char humanSymbol) {
    int score = evaluate(board, computerSymbol, humanSymbol);

    // If terminal states
    if (score == 10) return score - depth; // prefer faster wins
    if (score == -10) return score + depth; // prefer slower losses
    if (!isMovesLeft(board)) return 0;

    if (isMax) {
        int best = numeric_limits<int>::min();
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                if (board[r][c] == EMPTY) {
                    board[r][c] = computerSymbol;
                    best = max(best, minimax(board, depth + 1, !isMax, computerSymbol, humanSymbol));
                    board[r][c] = EMPTY;
                }
            }
        }
        return best;
    }
    else {
        int best = numeric_limits<int>::max();
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                if (board[r][c] == EMPTY) {
                    board[r][c] = humanSymbol;
                    best = min(best, minimax(board, depth + 1, !isMax, computerSymbol, humanSymbol));
                    board[r][c] = EMPTY;
                }
            }
        }
        return best;
    }
}

// Find best move for computer
Move findBestMove(vector<vector<char>>& board, char computerSymbol, char humanSymbol) {
    int bestVal = numeric_limits<int>::min();
    Move bestMove = { -1, -1 };

    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (board[r][c] == EMPTY) {
                board[r][c] = computerSymbol;
                int moveVal = minimax(board, 0, false, computerSymbol, humanSymbol);
                board[r][c] = EMPTY;
                if (moveVal > bestVal) {
                    bestMove.row = r;
                    bestMove.col = c;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

// Check for winner or draw; returns 'X' or 'O' if someone won, 'D' for draw, 'N' for none yet
char checkGameState(const vector<vector<char>>& b) {
    // Rows and cols
    for (int i = 0; i < 3; ++i) {
        if (b[i][0] != EMPTY && b[i][0] == b[i][1] && b[i][1] == b[i][2]) return b[i][0];
        if (b[0][i] != EMPTY && b[0][i] == b[1][i] && b[1][i] == b[2][i]) return b[0][i];
    }
    // Diagonals
    if (b[0][0] != EMPTY && b[0][0] == b[1][1] && b[1][1] == b[2][2]) return b[0][0];
    if (b[0][2] != EMPTY && b[0][2] == b[1][1] && b[1][1] == b[2][0]) return b[0][2];
    // Draw or None
    if (!isMovesLeft(b)) return 'D';
    return 'N';
}

int main() {
    cout << "Tic-Tac-Toe (You vs Computer)\n";
    cout << "You can choose X or O. X always goes first.\n";

    char humanSym;
    while (true) {
        cout << "Pick your symbol (X/O): ";
        cin >> humanSym;
        if (humanSym == 'X' || humanSym == 'x') { humanSym = 'X'; break; }
        if (humanSym == 'O' || humanSym == 'o') { humanSym = 'O'; break; }
        cout << "Invalid choice. Please enter X or O.\n";
    }
    char computerSym = (humanSym == 'X') ? 'O' : 'X';

    // Who goes first?
    bool humanTurn = (humanSym == 'X'); // X goes first
    cout << (humanTurn ? "You go first.\n" : "Computer goes first.\n");

    vector<vector<char>> board(3, vector<char>(3, EMPTY));
    printBoard(board);

    while (true) {
        if (humanTurn) {
            int r, c;
            while (true) {
                cout << "Enter your move (row and column): ";
                if (!(cin >> r >> c)) {
                    cout << "Invalid input. Please enter two numbers (0-2).\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                if (r < 0 || r > 2 || c < 0 || c > 2) {
                    cout << "Out of range. Use 0, 1, or 2.\n";
                    continue;
                }
                if (board[r][c] != EMPTY) {
                    cout << "Cell already occupied. Choose another.\n";
                    continue;
                }
                board[r][c] = humanSym;
                break;
            }
            printBoard(board);
        }
        else {
            cout << "Computer is thinking...\n";
            Move best = findBestMove(board, computerSym, humanSym);
            if (best.row != -1) {
                board[best.row][best.col] = computerSym;
                cout << "Computer played: (" << best.row << ", " << best.col << ")\n";
                printBoard(board);
            }
            else {
                // Shouldn't happen; fallback to first empty
                for (int i = 0; i < 3; i++) {
                    bool placed = false;
                    for (int j = 0; j < 3; j++) {
                        if (board[i][j] == EMPTY) {
                            board[i][j] = computerSym; placed = true; break;
                        }
                    }
                    if (placed) break;
                }
                printBoard(board);
            }
        }

        char state = checkGameState(board);
        if (state == humanSym) {
            cout << "Congratulations — you win!\n";
            break;
        }
        else if (state == computerSym) {
            cout << "Computer wins. Better luck next time!\n";
            break;
        }
        else if (state == 'D') {
            cout << "It's a draw.\n";
            break;
        }

        humanTurn = !humanTurn;
    }

    cout << "Game over.\n";
    return 0;
}
