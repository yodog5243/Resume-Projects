#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_COLUMNS 7
#define MAX_ROWS 6

//struct function that creates the node
struct Node {
	int row;
	char column;
	char ifOn;
	struct Node *nextMove;
	struct Node *next;
	struct Node *north;
	struct Node *south;
	struct Node *east;
	struct Node *west;
};

//this function uses the fact that all nodes are connected horizontally and vertically to find a given node based on inputed 
//column and row
struct Node* findNode(int findRow, char findColumn, struct Node *head) {
        while((head->row) < findRow) { head = (head)->north; }
	while((head->row) > findRow) { head = (head)->south; }
	while((head->column) < findColumn) { head = (head)->east; }
	while((head->column) > findColumn) { head = (head)->west; }
        return head;
}

//this function makes the board by just creating 42 nodes and assigns them a row and column
struct Node* makeBoard() {
	struct Node *head = (struct Node *) malloc(sizeof(struct Node));
	struct Node *holder = head;
	char column = 'a';
	for(int i = 0; i < MAX_COLUMNS; i++) {
		for(int j = 1; j < MAX_ROWS+1; j++) {
        		(head)->row = j;
        		(head)->column = column;
        		(head)->ifOn = '.';
			(head)->next = (struct Node *) malloc(sizeof(struct Node));
			head = (head)->next;
		}
		column++;
	}
	return holder;
}	

//this function connects everything vertically
void connectVertical(struct Node *head) {
	struct Node *prev;
	for(int i = 0; i < MAX_COLUMNS; i++) {
               for(int j = 0; j < MAX_ROWS; j++) {
			(head)->north = (head)->next; 
			prev = head;
			//if((head)->row == 6) { (head)->north = NULL; }
			head = (head)->next;
			if((head)->row != 1) { (head)->south = prev; }
		}
	(head)->north = NULL;
	}
}

//this function connects all the board nodes horizontally
void connectHorizontal(struct Node *head) {
	struct Node *prev;
	struct Node *original = head;
	for(int i = 0; i < MAX_COLUMNS; i++) {
		prev = head;
               	for(int j = 0; j < MAX_ROWS; j++) {
			if((head)->next != NULL) { head = (head)->next; }
			//printf("%c%d\n", (head)->column, (head)->row);
               	}
		(prev)->east = head;
		(head)->west = (prev);
        }
}

//function to check if the board is full, uses the nextmove order on played moves and takes in the first move
bool isFull(struct Node *original) {
	int counter = 0;
	while((original)->nextMove != NULL) {
		original = (original)->nextMove;
		counter++;
	}
	if(counter == 41) {
		return true;
	} else {
		return false;
	}
}

//function to take input, also checks if the input is correct
char getInput(char move, int player) {
        printf("\nPlayer %d input your move: ", player);
        scanf(" %c", &move);
	switch(move) {
		case('a'):
			break;
		case('b'):
                        break;
		case('c'):
                        break;
		case('d'):
                        break;
		case('e'):
                        break;
		case('f'):
                        break;
		case('g'):
                        break;
		default:
			getInput(move, player);
	}
        return move;
}

//this function doesnt create the node but instead turns it on by changing the ifOn attribute of the node
//to whoever made the move. starts at the bottom of a column and works its way up till theres an empty spot
//also checks to see if column is full and returns played node
struct Node* listAdd(char column, char player, struct Node *head) {
	int play = 0;
	if(player == 'X') { play = 1; }
	if(player == 'O') { play = 2; }
	head = findNode(1, column, head);
	while((head)->ifOn != '.') {
		if((head)->row != 6) {
			head = (head)->north;
		} else { 
			printf("make another move, this column is full\n");
			return listAdd(getInput(column, play), player, head);
			break;
		}
	}
	if((head)->ifOn == '.') {
		(head)->ifOn = player;
	}
	return head;
}

//this function prints the board out for the user to see
void printBoard(struct Node *head) {
	head = findNode(6, 'a', head);
	for(char column = 'a'; column < 'h'; column++) {
		printf("    %c", column);
	}
	printf("\n\n");
	char column = 'a';
	for(int i = 6; i > 0; i--) {
		printf("%d    %c    %c    %c    %c    %c    %c    %c\n\n", i, (findNode(i, column, head))->ifOn, (findNode(i, column + 1, head))->ifOn, (findNode(i, column + 2, head))->ifOn, (findNode(i, column + 3, head))->ifOn, (findNode(i, column + 4, head))->ifOn, (findNode(i, column + 5,
head))->ifOn, (findNode(i, column + 6, head))->ifOn);
		
	}   
}

//function checks to see if anyone has won horizontally, takes in a move and checks left and right.
//it takes in the most recent move played
bool checkHorizontal(struct Node *move, char player) {
	int counter = 1;
	struct Node *original = move;
	bool stillGo = true;
	while(stillGo == true) {
		if((move)->column == 'a') { break; }
		if((move)->west->ifOn == player) {
			counter++;
			if((move)->column != 'a') {
				move = (move)->west;
			} else {
				stillGo = false;
			}
		} else { stillGo = false; }
	}
	//printf("\n\n\n%d\n\n\n", counter);
	stillGo = true;
	move = original;
	while(stillGo == true) {
                if((move)->east->ifOn == player) {
                        counter++;
                        if((move)->column != 'g') {
                                move = (move)->east;
                        } else {
                                stillGo = false;
                        }
                } else { stillGo = false; }
        }
	//printf("\n\n\n%d\n\n\n", counter);
	if(counter >= 4) { return true; 
	} else { return false; }
}

//same as check horizontal but vertical
bool checkVertical(struct Node *move, char player) {
        int counter = 1;
        struct Node *original = move;
        bool stillGo = true;
        while(stillGo == true) {
                if((move)->row == 1) { break; }
                if((move)->south->ifOn == player) {
                        counter++;
                        if((move)->row != 1) {
                                move = (move)->south;
                        } else {
                                stillGo = false;
                        }
                } else { stillGo = false; }
        }
        //printf("\n\n\n%d\n\n\n", counter);
        stillGo = true;
        move = original;
        while(stillGo == true) {
                if((move)->north->ifOn == player) {
                        counter++;
                        if((move)->row != 6) {
                                move = (move)->north;
                        } else {
                                stillGo = false;
                        }
                } else { stillGo = false; }
        }
        //printf("\n\n\n%d\n\n\n", counter);
        if(counter >= 4) { return true;
        } else { return false; }
}

//same as check horizontal but diagnol, up right and down left
bool checkDiagnolR(struct Node *move, char player) {
        int counter = 1;
        struct Node *original = move;
        bool stillGo = true;
        while(stillGo == true) {
                if((move)->row == 1 || (move)->column == 'a') { break; }
                if((findNode((move)->row - 1, (move)->column - 1, move))->ifOn == player) {
                        counter++;
                        if((move)->row != 1 || (move)->column != 'a') {
                                move = findNode((move)->row - 1, (move)->column - 1, move);
                        } else {
                                stillGo = false;
                        }
                } else { stillGo = false; }
        }
        //printf("\n\n\n%d\n\n\n", counter);
        stillGo = true;
        move = original;
        while(stillGo == true) {
                if((move)->row == 6 || (move)->column == 'g') { break; }
                if((findNode((move)->row + 1, (move)->column + 1, move))->ifOn == player) {
                        counter++;
                        if((move)->row != 6 || (move)->column != 'g') {
                                move = findNode((move)->row + 1, (move)->column + 1, move);
                        } else {
                                stillGo = false;
                        }
                } else { stillGo = false; }
        }
        //printf("\n\n\n%d\n\n\n", counter);
        if(counter >= 4) { return true;
        } else { return false; }
}

//this one is down right and up left
bool checkDiagnolL(struct Node *move, char player) {
        int counter = 1;
        struct Node *original = move;
        bool stillGo = true;
        while(stillGo == true) {
                if((move)->row == 6 || (move)->column == 'a') { break; }
                if((findNode((move)->row + 1, (move)->column - 1, move))->ifOn == player) {
                        counter++;
                        if((move)->row != 6 || (move)->column != 'a') {
                                move = findNode((move)->row + 1, (move)->column - 1, move);
                        } else {
                                stillGo = false;
                        }
                } else { stillGo = false; }
        }
        //printf("\n\n\n%d\n\n\n", counter);
        stillGo = true;
        move = original;
        while(stillGo == true) {
                if((move)->row == 1 || (move)->column == 'g') { break; }
                if((findNode((move)->row - 1, (move)->column + 1, move))->ifOn == player) {
                        counter++;
                        if((move)->row != 1 || (move)->column != 'g') {
                                move = findNode((move)->row - 1, (move)->column + 1, move);
                        } else {
                                stillGo = false;
                        }
                } else { stillGo = false; }
        }
        //printf("\n\n\n%d\n\n\n", counter);
        if(counter >= 4) { return true;
        } else { return false; }
}

//combines all the directional checks to return a boolean isWon
bool checkWon(struct Node *move, char player) {
	bool isWon = false;
	if(checkHorizontal(move, player)) { isWon = true; }
	if(checkVertical(move, player)) { isWon = true; }	
	if(checkDiagnolR(move, player)) { isWon = true; }
	if(checkDiagnolL(move, player)) { isWon = true; }
	return isWon;
}

//this connects all the moves to make the final move printout
struct Node* makeFinal(struct Node *prev, struct Node *new) {
	if(prev == NULL) {
		(new)->nextMove = NULL;
		return new;
	} else {
		(prev)->nextMove = new;
		(new)->nextMove = NULL;
		return new;
	}
}

//this just cycles through the nextmove to printout all the moves taken during the game
void printFinal(struct Node *original) {
	while((original)->nextMove != NULL) {
		printf(" %c%d ->", (original)->column, (original)->row);
		original = (original)->nextMove;
	}
}

//this function contains the heart of the program. it calls the majority of the functions above to play the game. I have tried to keep this function
//as small as possible but moving most code into their own functions
int main() {
	char moveOne;
	char moveTwo;
	struct Node *newBoard = makeBoard();
	struct Node *add = NULL;
	struct Node *prev = NULL;
	struct Node *original = NULL;
	connectVertical(newBoard);
	for(int i = 0; i < MAX_ROWS; i++) {
		connectHorizontal(newBoard);
		newBoard = (newBoard)->north;
	}
	while(isFull(newBoard) == false) {
		//printf("\nPlayer one input your move: ");
		//scanf(" %c", &moveOne);
		moveOne = getInput(moveOne, 1);
		if(prev == NULL) {
			add = listAdd(moveOne, 'X', newBoard);
			original = add;
		} else { add = listAdd(moveOne, 'X', newBoard); }
		prev = makeFinal(prev, add);
		printBoard(newBoard);
		if(isFull(original)) {
			printf("\nGame Over! The board is full so it is a draw!\n");
			break;
		}
		if(checkWon(add,'X')) {
			printf("\nGame Over! Player One has won!\n");		
			break;
		}
		//printf("\nPlayer two input your move: ");
		//scanf(" %c", &moveTwo);
		moveTwo = getInput(moveTwo, 2);
		printf("\n");
		add = listAdd(moveTwo, 'O', newBoard);
		prev = makeFinal(prev, add);
		printBoard(newBoard);
		if(isFull(original)) {
                        printf("\nGame Over! The board is full so it is a draw!\n");
                        break;
                }
		//printFinal(original);
		if(checkWon(add, 'O')) {
			printf("\nGame Over! Player Two has won!\n");
			break;
		}
	}
	printf("\nHere are your moves in order\n");
	printFinal(original);
	return 0;	
} 
