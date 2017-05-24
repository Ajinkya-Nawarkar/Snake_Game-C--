//*******************************************************************************************************************************************************************//
//***************************************************************************************************************************//
//																															*//
// File name : Snake_Game.cpp																								*//
//																															*//
// Author: Ajinkya Nawarkar    		                	 date created: 05 / 23 / 2017										*//
//														 last updated : 05 / 23 / 2017										*//
//																															*//
// Program Description : This program defines the methods for the Snake game. 												*//
//																															*//
//***************************************************************************************************************************//
//*********************************************************************************************************************************************************************//

//Snake game Program

//Include the libraries
#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

//Define the required variables
bool gameOver = false, print = false;
const int width = 20;
const int height = 20;
int x = 0, y = 0, foodX = 0, foodY = 0, score = 0;
int tailX[100], tailY[100];
int nTail=0;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

//Define the Setup method which setups the inital frame and variables at the start of a new game
void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	foodX = rand() % width;
	foodY = rand() % height;
	score = 0;
	nTail = 0;
	tailX[100] = {};
	tailY[100] = {};
}

//Define the Draw method which prints the layout asynchronously after every move
void Draw()
{
	system("cls");	//Clears the screen

	//Create the frame layout for the game
	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			
			if (i == y && j == x)	//print the head
				cout << "O";
			else if (i == foodY && j == foodX)	//Print the food at random location on the map layout
				cout << "F";
			else			
			{
				print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)	//Print the tail
					{
						cout << "o";	
						print = true;
					}			
				}
				if (!print)
					cout << " ";
			}
				
			if (j == width-1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width+2; i++)
		cout << "#";

	cout << endl;

	cout << "Score: " << score << endl;	//Print current score



}

//Define the Input method to accept the keyboard hits and set direction for the snake
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w': 
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'q':
			gameOver = true;
			break;
		}
	}
}

void Logic()
{
	//Swap the positions of each segment of snake and store it in a container
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X = 0, prev2Y = 0;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
		
	//Locomote the snake's hed and the following body
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
		
	//Account for locomotion out the map layout
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;
	
	//Check if the snake's head hits the tail
	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}

	//Account for the food eaten by the snake's head
	if (x == foodX && y == foodY)
	{
		score += 10;
		foodX = rand() % width;
		foodY = rand() % height;
		nTail++;
	}
}

int main()
{	
	//Start the game
	char ch = 'y';
	while (ch == 'y')
	{
		Setup();
		while (!gameOver)
		{
			Draw();
			Input();
			Logic();
			Sleep(20);
		}
		cout << "Do you want to play a new game? (Y or press a key to exit)" << endl;
		cin >> ch;
	}
	return 0;
}