#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

constexpr const char X = 'X';
constexpr const char O = 'O';
constexpr const char EMPTY = ' ';
constexpr const char DRAW = 'D';
constexpr const char NO_ONE = 'N';
constexpr const int NUM_SQUARES = 9;
const std::vector<std::vector <int>> POSSIBLE_WINNING_COMBINATIONS {{0, 1, 2},
                                                                  {3, 4, 5},
                                                                  {6, 7, 8},
                                                                  {0, 3, 6},
                                                                  {1, 4, 7},
                                                                  {2, 5, 8},
                                                                  {0, 4, 8},
                                                                  {2, 4, 6}};
const std::vector<int> BEST_MOVES{0, 4, 6, 2, 8, 7 , 5, 1, 3};                                                                  
std::vector<char> board(NUM_SQUARES, EMPTY);

void instruction();
char askYesNo(const std::string &message);
char getHumanPiece();
char getComputerPiece(const char humanPiece);
char changePiece(const char piece);
char findWinner();
bool isDraw();
void displayBoard();
int getHumanMove();
int getComputerMove(const char computerPiece);
int getNumber(const std::string &message);
void congratulateWinner(const char winner, const char humanPiece, const char computerPiece);
bool isLegal(const int position);

int main() {
    instruction();
    char humanPiece = getHumanPiece();
    char computerPiece = getComputerPiece(humanPiece);
    char move = X;
    int position{};
    while(findWinner() == NO_ONE) {
        if(move == humanPiece) {
            position = getHumanMove();
            board[position] = humanPiece;
        }
        else {
            position = getComputerMove(computerPiece);
            board[position] = computerPiece;
        }

        move = changePiece(move);
        displayBoard();
    }

    congratulateWinner(findWinner(), humanPiece, computerPiece);
}

void instruction() {
    std::cout << std::setw(50) << "Welcome to TIC TAC TOE" << std::endl
              << "In this game you will compete against the computer, make your move by entering a number 0 - 8" << std::endl
              << "The entered number connected to the cell number in the illustration below:" << std::endl
              << "  0  |  1  |  2  " << std::endl
              << "-----------------" << std::endl
              << "  3  |  4  |  5  " << std::endl
              << "-----------------" << std::endl
              << "  6  |  7  |  8  " << std::endl;
}

char askYesNo(const std::string &message) {
    char result{};
    std::cout << message;
    std::cin >> result;

    return result;
}

char getHumanPiece() {
    char answer;
    do {
        answer = askYesNo("Do you want to go first? (y/n)\n");
        if(answer != 'y' && answer != 'n') {
            std::cout << "Incorrect choice. Try again." << std::endl;
        }
    } while (answer != 'y' && answer != 'n');
    
    return answer == 'y'? X: O;
}

char getComputerPiece(const char humanPiece) {
    return changePiece(humanPiece);
}

char changePiece(const char piece) {
    return piece == X? O: X;
}

char findWinner() {
    for(auto &winningCombination: POSSIBLE_WINNING_COMBINATIONS) {
        if(board[winningCombination[0]] == board[winningCombination[1]]
        && board[winningCombination[0]] == board[winningCombination[2]]
        && board[winningCombination[0]] != EMPTY) {
            return board[winningCombination[0]];
        }
    }

    if(isDraw()) {
        return DRAW;
    }

    return NO_ONE;
}

bool isDraw() {
    return std::count(board.begin(), board.end(), EMPTY) > 0? false : true;
}

void displayBoard() {
    std::cout << "\n  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << "  " << std::endl
              << "-----------------" << std::endl
              << "  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << "  " << std::endl
              << "-----------------" << std::endl
              << "  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << "  " << std::endl;
}

int getHumanMove() {
    int position{};
    do {
        position = getNumber("Enter your move: ");
        
        if(isLegal(position)) {
            return position;
        } 
        else {
            std::cout << "This move is illegal, try again" << std::endl;
        }
    } while(!isLegal(position));
}

int getNumber(const std::string &message) {
    int number{};
    std::cout << message;
    std::cin >> number;
    return number;
}

int getComputerMove(const char computerPiece) {
    bool found = false;
    int position{};
    while(!found && position < NUM_SQUARES) {
        if(isLegal(position)) {
            board[position] = computerPiece;
            found = findWinner() == computerPiece;
            board[position] = EMPTY;
        }
        if(!found) {
            position++;
        }
    }

    if(!found) {
        position = 0;
        while(!found && position < NUM_SQUARES) {
            if(isLegal(position)) {
                board[position] = changePiece(computerPiece);
                found = findWinner() == changePiece(computerPiece);
                board[position] = EMPTY;
            }
            if(!found) {
                position++;
            }   
        }
    }

    if(!found) {
        position = 0;
        size_t i{};
        while(i < NUM_SQUARES && !found) {
            position = BEST_MOVES[i];
            if(isLegal(position)) {
                found = true;
            }

            i++;
        }
    }

    return position;
}
void congratulateWinner(const char winner, const char humanPiece, const char computerPiece) {
    std::cout << std::endl << "===============================================================" << std::endl;
    if(winner == humanPiece) {
        std::cout << "Congratulations, you beat the computer." << std::endl;
    }
    else if(winner == computerPiece) {
        std::cout << "The computer turned out to be smarter than you, loser." << std::endl;
    }
    else if(winner == DRAW) {
        std::cout << "The winner could not be found." << std::endl;
    }

}

bool isLegal(const int position) {
    return board[position] == EMPTY? true : false;
}