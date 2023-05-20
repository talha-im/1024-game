#include <iostream>
#include <ctime>
#include <iomanip>
#include <cstdlib>

using namespace std;

int board[4][4];
int best = 0, score = 0;

void newGame();
void printUI();
void startPieces();
void addPiece();
void up();
void down();
void left();
void right();
bool winCon();
bool loseCon();

int main() {
	srand(time(0));
	char cmnd;
	bool playing = true;
	newGame();
	while (playing) {
		system("cls");
		printUI();
		if (winCon()) {
			cout << "You WON\n";
			playing = false;
		}
		else if (loseCon()) {
			cout << "You LOST\n" << "Press 'n' for NEW GAME or ANY key to EXIT: ";
			cin >> cmnd;
			if (cmnd == 'n')
				newGame();
			else
				playing = false;
		}
		else {
			cout << "Enter Command: ";
			cin >> cmnd;
			switch (cmnd) {
			case 'w':
				up();
				break;
			case 's':
				down();
				break;
			case 'a':
				left();
				break;
			case 'd':
				right();
				break;
			case 'n':
				newGame();
				break;
			case 'q':
				playing = false;
				break;
			}
		}
	}
	return 0;
}
void newGame() {
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			board[i][j] = 0;
		}
	}
	score = 0;
	startPieces();
}
void startPieces() {
	bool addFirst = false, addSecond = false;
	int piece1 = 0, piece2 = 0;
	int rowpos = 0, colpos = 0;
	while (!addFirst) {
		rowpos = rand() % 4;
		colpos = rand() % 4;
		if (board[rowpos][colpos] == 0) {
			piece1 = (rand() % 2) + 1;
			board[rowpos][colpos] = piece1;
			addFirst = true;
		}
	}
	while (!addSecond) {
		rowpos = rand() % 4;
		colpos = rand() % 4;
		if (board[rowpos][colpos] == 0) {
			piece2 = (rand() % 2) + 1;
			board[rowpos][colpos] = piece2;
			addSecond = true;
		}
	}
}
void printUI() {
	for (int i = 0;i < 21;i++)
		cout << "-";
	cout << endl;
	for (int i = 0;i < 4;i++) {
		cout << "|";
		for (int j = 0;j < 4;j++) {
			if (board[i][j] == 0) {
				cout << setw(4) << " ";
			}
			else {
				cout << setw(4) << board[i][j];
			}
			cout << "|";
		}
		cout << endl;
		for (int k = 0;k < 21;k++)
			cout << "-";
		cout << endl;
	}
	cout << "Score: " << score << "\t" << "Best: " << best << endl;
	cout << "Instructions: \n";
	cout << "Press 'w' to move UP\n" << "Press 'a' to move LEFT\n" << "Press 's' to move DOWN\n" << "Press 'd' to move RIGHT\n" << "Press 'n' for NEWGAME\n" << "Press 'q' to QUIT\n";
}
bool winCon() {
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			if (board[i][j] == 1024)
				return true;
		}
	}
	return false;
}
bool loseCon() {
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			if (board[i][j] == 0)
				return false;
		}
	}
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			if (i == 0) {
				if (j == 0) {
					if ((board[i][j] == board[i][j + 1]) || (board[i][j] == board[i + 1][j]))
						return false;
				}
				if (j == 1 || j == 2) {
					if ((board[i][j] == board[i][j + 1]) || (board[i][j] == board[i + 1][j]) || (board[i][j] == board[i][j - 1]))
						return false;
				}
				if (j == 3) {
					if ((board[i][j] == board[i][j - 1]) || (board[i][j] == board[i + 1][j]))
						return false;
				}
			}
			if (i == 1 || i == 2) {
				if (j == 0) {
					if ((board[i][j] == board[i - 1][j]) || (board[i][j] == board[i][j + 1]) || (board[i][j] == board[i + 1][j]))
						return false;
				}
				if (j == 1 || j == 2) {
					if ((board[i][j] == board[i - 1][j]) || (board[i][j] == board[i][j - 1]) || (board[i][j] == board[i + 1][j]) || (board[i][j] == board[i][j + 1]))
						return false;
				}
				if (j == 3) {
					if ((board[i][j] == board[i][j - 1]) || (board[i][j] == board[i - 1][j]) || (board[i][j] == board[i + 1][j]))
						return false;
				}
			}
			if (i == 3) {
				if (j == 0) {
					if ((board[i][j] == board[i - 1][j]) || (board[i][j] == board[i][j + 1]))
						return false;
				}
				if (j == 1 || j == 2) {
					if ((board[i][j] == board[i][j - 1]) || (board[i][j] == board[i - 1][j]) || (board[i][j] == board[i][j + 1]))
						return false;
				}
				if (j == 3) {
					if ((board[i][j] == board[i - 1][j]) || (board[i][j] == board[i][j - 1]))
						return false;
				}
			}
		}
	}
	return true;
}
void up() {
	bool flag = false, toAdd = false;
	for (int i = 1;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			if (board[i][j] == board[i - 1][j] || board[i - 1][j] == 0) {
				flag = true;
				for (int k = i;k > 0 && flag;k--) {
					if (board[k][j] != board[k - 1][j] && board[k - 1][j] != 0) {
						flag = false;
					}
					else {
						if (board[k - 1][j] == board[k][j]) {
							score += (board[k - 1][j] + board[k][j]);
							if (best < score)
								best = score;
						}
						board[k - 1][j] += board[k][j];
						if (board[k][j] > 0)
							toAdd = true;
						board[k][j] = 0;
					}
				}
			}
		}
	}
	if (toAdd)
		addPiece();
}
void down() {
	bool flag = false, toAdd = false;
	for (int i = 2;i >= 0;i--) {
		for (int j = 0;j < 4;j++) {
			if (board[i][j] == board[i + 1][j] || board[i + 1][j] == 0) {
				flag = true;
				for (int k = i;k < 3 && flag;k++) {
					if (board[k][j] != board[k + 1][j] && board[k + 1][j] != 0) {
						flag = false;
					}
					else {
						if (board[k + 1][j] == board[k][j]) {
							score += (board[k + 1][j] + board[k][j]);
							if (best < score)
								best = score;
						}
						board[k + 1][j] += board[k][j];
						if (board[k][j] > 0)
							toAdd = true;
						board[k][j] = 0;
					}
				}
			}
		}
	}
	if (toAdd)
		addPiece();
}
void left() {
	bool flag = false, toAdd = false;
	for (int j = 1;j < 4;j++) {
		for (int i = 0;i < 4;i++) {
			if (board[i][j] == board[i][j - 1] || board[i][j - 1] == 0) {
				flag = true;
				for (int k = j;k > 0 && flag;k--) {
					if (board[i][k] != board[i][k - 1] && board[i][k - 1] != 0) {
						flag = false;
					}
					else {
						if (board[i][k - 1] == board[i][k]) {
							score += (board[i][k - 1] + board[i][k]);
							if (best < score)
								best = score;
						}
						board[i][k - 1] += board[i][k];
						if (board[i][k] > 0)
							toAdd = true;
						board[i][k] = 0;
					}
				}
			}
		}
	}
	if (toAdd)
		addPiece();
}
void right() {
	bool flag = false, toAdd = false;
	for (int j = 2;j >= 0;j--) {
		for (int i = 0;i < 4;i++) {
			if (board[i][j] == board[i][j + 1] || board[i][j + 1] == 0) {
				flag = true;
				for (int k = j;k < 3;k++) {
					if (board[i][k] != board[i][k + 1] && board[i][k + 1] != 0) {
						flag = false;
					}
					else {
						if (board[i][k + 1] == board[i][k]) {
							score += (board[i][k + 1] + board[i][k]);
							if (best < score)
								best = score;
						}
						board[i][k + 1] += board[i][k];
						if (board[i][k] > 0)
							toAdd = true;
						board[i][k] = 0;
					}
				}
			}
		}
	}
	if (toAdd)
		addPiece();
}
void addPiece() {
	bool added = false;
	int rowpos = 0, colpos = 0;
	int piece = 0;
	while (!added) {
		rowpos = rand() % 4;
		colpos = rand() % 4;
		if (board[rowpos][colpos] == 0) {
			piece = (rand() % 2) + 1;
			board[rowpos][colpos] = piece;
			added = true;
		}
	}
}