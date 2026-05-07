#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// Convert chess notation (e.g., "e2" → "e4") into board indices
// Time Complexity: O(1)
// Space Complexity: O(1)
pair<pair<int,int>, pair<int,int>> convert(string p1, string p2) {
    int row1 = 8 - (p1[1] - '0');
    int col1 = p1[0] - 'a';

    int row2 = 8 - (p2[1] - '0');
    int col2 = p2[0] - 'a';

    return {{row1, col1}, {row2, col2}};
}

// Initialize the chessboard with pieces in their starting positions
// Time Complexity: O(8) ≈ O(1)
// Space Complexity: O(1) (modifies board in place)
void initializeboard(vector<vector<char>>& board) {
    for (int j = 0; j < 8; j++) {
        board[1][j] = 'p';
        board[6][j] = 'P';
    }
    board[0][0] = board[0][7] = 'r'; board[7][0] = board[7][7] = 'R';
    board[0][1] = board[0][6] = 'n'; board[7][1] = board[7][6] = 'N';
    board[0][2] = board[0][5] = 'b'; board[7][2] = board[7][5] = 'B';
    board[0][3] = 'q'; board[7][3] = 'Q';
    board[0][4] = 'k'; board[7][4] = 'K';
}

// Validate pawn moves (forward, double step, diagonal capture)
// Time Complexity: O(1)
// Space Complexity: O(1)
bool ispawnvalid(vector<vector<char>>& board, int sr, int sc, int dr, int dc) {
    char piece = board[sr][sc];
    if (piece == 'P') { // White pawn
        if (sc == dc && dr == sr-1 && board[dr][dc] == '.') return true;
        if (sr == 6 && sc == dc && dr == sr-2 && board[sr-1][sc] == '.') return true;
        if (abs(dc-sc) == 1 && dr == sr-1 && islower(board[dr][dc])) return true;
    }
    if (piece == 'p') { // Black pawn
        if (sc == dc && dr == sr+1 && board[dr][dc] == '.') return true;
        if (sr == 1 && sc == dc && dr == sr+2 && board[sr+1][sc] == '.') return true;
        if (abs(dc-sc) == 1 && dr == sr+1 && isupper(board[dr][dc])) return true;
    }
    return false;
}

// Print the board to console
// Time Complexity: O(64) ≈ O(1)
// Space Complexity: O(1)
void print(vector<vector<char>> board) {
    for (int i = 0; i < 8; i++) {   
        for (int j = 0; j < 8; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Validate rook moves (straight lines, no blocking pieces)
// Time Complexity: O(n) where n ≤ 8 (board size)
// Space Complexity: O(1)
bool isrookvalid(vector<vector<char>>& board, int sr, int sc, int dr, int dc){
    if(sr == dr){ // Same row
        int step = (dc > sc) ? 1 : -1;
        for(int j = sc+step; j != dc; j+=step){
            if(board[sr][j] != '.') return false;
        }
        return true;
    }
    if(sc == dc){ // Same column
        int step = (dr > sr) ? 1 : -1;
        for(int i = sr+step; i != dr; i+=step){
            if(board[i][sc] != '.') return false;
        }
        return true;
    }
    return false;
}

// Validate bishop moves (diagonals, no blocking pieces)
// Time Complexity: O(n) where n ≤ 8
// Space Complexity: O(1)
bool isbishopvalid(vector<vector<char>>& board, int sr, int sc, int dr, int dc){
    if(abs(dr-sr) != abs(dc-sc)) return false; // Must be diagonal
    int rstep = (dr > sr) ? 1 : -1;
    int cstep = (dc > sc) ? 1 : -1;
    int r = sr + rstep, c = sc + cstep;
    while(r != dr && c != dc){
        if(board[r][c] != '.') return false;
        r += rstep; c += cstep;
    }
    return true;
}

// Validate knight moves (L-shape)
// Time Complexity: O(1)
// Space Complexity: O(1)
bool isknightvalid(vector<vector<char>>& board, int sr, int sc, int dr, int dc){
    int r = abs(dr-sr);
    int c = abs(dc-sc);
    return (r==2 && c==1) || (r==1 && c==2);
}

// Validate king moves (one square in any direction)
// Time Complexity: O(1)
// Space Complexity: O(1)
bool iskingvalid(vector<vector<char>>& board, int sr, int sc, int dr, int dc){
    char piece = board[sr][sc];
    if(piece == 'k' || piece == 'K'){
        int r = abs(dr-sr);
        int c = abs(dc-sc);
        return (r <= 1 && c <= 1);
    }
    return false;
}

// Validate queen moves (rook OR bishop logic)
// Time Complexity: O(n) where n ≤ 8
// Space Complexity: O(1)
bool isqueenvalid(vector<vector<char>>& board, int sr, int sc, int dr, int dc){
    return isrookvalid(board,sr,sc,dr,dc) || isbishopvalid(board,sr,sc,dr,dc);
}

// Main game loop
// Time Complexity: O(∞) until user exits (each iteration O(64) for printing + O(8) for validation)
// Space Complexity: O(64) for board
int main() {
    vector<vector<char>> board(8, vector<char>(8, '.'));  
    initializeboard(board);

    while (true) {
        print(board);

        string p1, p2;
        cout << "Enter source (e.g. e2) or 'exit': ";
        cin >> p1;
        if (p1 == "exit") break;

        cout << "Enter destination (e.g. e4): ";
        cin >> p2;
        if (p2 == "quit") break;

        auto coords = convert(p1, p2);
        int sr = coords.first.first;
        int sc = coords.first.second;
        int dr = coords.second.first;
        int dc = coords.second.second;
        if ((isupper(board[sr][sc]) && isupper(board[dr][dc])) ||(islower(board[sr][sc]) && islower(board[dr][dc]))) {
            cout << "same pieces cannot be captured\n";
            continue; // skip move
        }

        if (board[sr][sc] == '.') {
            cout << "NO PIECE FOUND\n";
            continue;
        }

        // Check each piece type
        if (ispawnvalid(board, sr, sc, dr, dc) ||
            isrookvalid(board, sr, sc, dr, dc) ||
            isbishopvalid(board, sr, sc, dr, dc) ||
            isknightvalid(board, sr, sc, dr, dc) ||
            iskingvalid(board, sr, sc, dr, dc) ||
            isqueenvalid(board, sr, sc, dr, dc)) {
            
            // Perform move
            board[dr][dc] = board[sr][sc];
            board[sr][sc] = '.';
        }
        else {
            cout << "Invalid move!\n";
        }
    }
    return 0;
}
