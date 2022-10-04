Readme
Jackson Durant


        I created this project by first creating 42 nodes in makeBoard. All these nodes were just connected with a next attribute that will not be used anywhere else but just to connect initially. I then connected all the nodes in functions connectHorizontal and connectVertical. These functions used math to connect all the nodes as if they were actually a board. Once the board was made I created printBoard to print the board. takeInput to take the input and check to make sure the input was a correct column. The function isFull checks to see if the board is full by going through the move order list. I created two different functions to keep track of moves, one tracks and the other prints the moves out. CheckWon calls checkVertical, checkHorizontal, and two Diagnol check functions to see if anyone has won. All of this culminates in the main function which runs on a while loop that never ends technically, but there are multiple checks in the loop that would break it out, if someone won or if the board is filled.


I used pointers by creating directional pointers. North, south, east, and west. I mapped out these pointers for each node on the board. This made it easy to traverse the board and get to any node that I wanted with my findNode function. This made it extremely easy to turn a node on whenever a move was played.


Thanks for playing my game!