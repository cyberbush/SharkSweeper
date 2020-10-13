/* David Bush, CS120-02, 3/31/20, Assignment 10, Complete */
#include <iostream>
#include <cstdlib>
using namespace std;

// Global Variables
int sharks = 0, sizecomp = 10, sizeplay = 10, height = 10, width = 10, guessx, guessy ;
int coordx[100], coordy[100];
char map_comp[10][10], map_player[10][10]; 

// Prototypes
void array_start();
void array_player_start();
void array_sharks();
void array_complete();
void array_coord_test(int, int);
void coord_test0(int, int);
void ask_coords(); 
bool proceed();
void print_comp();
void print_play();


void array_start()
{
	for(int i=0; i<sizecomp; i++)
	{
		for(int k=0; k<sizecomp; k++)
		{
			map_comp[i][k] = '0';
		}
	}

}

void array_player_start()
{
	for(int i=0; i<sizeplay; i++)
	{
		for(int k=0; k<sizeplay; k++)
		{
			map_player[i][k] = '+';
		}
	}
	
}

// This function generates random coordinates and then adds these coordinates as mines 
void array_sharks()
{
	int x, y;
	//Sets random x and y coords
	for(int i=0; i<sharks; i++)
	{
		coordx[i] = random() % 10;
	}
	for(int k=0; k<sharks; k++)
	{
		coordy[k] = random() % 10;
	}
	for(int p=0; p<sharks; p++)
	{
		x = coordx[p];
		y = coordy[p];

		if (map_comp[y][x]=='*' && x!=9)
		{
			do{
				x +=1;
			}while(map_comp[y][x]=='*'); 
		}
		else if (map_comp[y][x]=='*' && x!=0)
		{
			do{
				x -=1;
			}while(map_comp[y][x]=='*');
		}

		map_comp[y][x] = '*' ;
	}	

	//print coords
//	for(int z=0; z<sharks; z++)
//	{
//		cout << "(" << coordx[z] << "," << coordy[z] << ")" << " ";
//	}
//	cout << endl;
}

// This function is used to check if a coordinate has a mine and adds +1 for each surrounding mine
void array_complete()
{
	int x, y, a, b, c, d, e, f, g, h, r, s, j, l, m, n;
	for(int i=0; i<sizecomp; i++)
	{
		for(int k=0; k<sizecomp; k++)
		{
			// Top 3 coords adjacent
			if(map_comp[i][k] == '*' && !(i==0))
			{	
				//top left
				if(!(k==0))
				{
					a = i-1;
					b = k-1;
					if (map_comp[a][b] != '*')
						map_comp[a][b] += 1;
				}
				//top top
				c = i-1;
				d = k;
				if (map_comp[c][d] != '*')
					map_comp[c][d] += 1;
				//top right
				if(!(k==9))
				{	
					y = i-1;
					x = k+1;
					if (map_comp[y][x] != '*')
						map_comp[y][x] += 1;
				}
			}
			// Middle coords adjacent
			// mid right
			if(map_comp[i][k] == '*' && !(k==9))
			{
				j = i;
				l = k+1;
				if (map_comp[j][l] != '*')
					map_comp[j][l] += 1;
			}
			// mid left
			if(map_comp[i][k] == '*' && !(k==0))
			{
				m = i;
				n = k-1;
				if (map_comp[m][n] != '*')
					map_comp[m][n] += 1;
			}
			// Bottom 3 coords adjacent
			if(map_comp[i][k] == '*' && !(i==9))
			{	
				// bot right
				if(!(k==9))
				{
					e = i+1; 
					f = k+1;
					if (map_comp[e][f] != '*')
						map_comp[e][f] += 1;
				}
				// bot bot
					g = i+1;
					h = k;
					if (map_comp[g][h] != '*')
						map_comp[g][h] += 1;
				// bot left
				if(!(k==0))
				{	
					r = i+1;
					s = k-1;
					if (map_comp[r][s] != '*')
						map_comp[r][s] += 1;
				}
			}	
		}
	}
}

// This function tests if the player entered a coordinate that has a mine and then reveals the coord if not
void array_coord_test(int x, int y)
{
	int test;
	if(map_comp[y][x]=='*')
		test = 0;
	else if(map_comp[y][x]=='0')
		test = 2;
	else
		test = 1;

	switch(test)
	{
		case 0:
			cout << "Game Over!\n";
			print_comp();
			exit(0);
			break;
		case 1:
			map_player[y][x] = map_comp[y][x];
			print_play();
			break;
		case 2:
			coord_test0(x, y);
			print_play();
			break;
		default:
			cout << "Error\n";
	}
}

// This function that reveals surrounding squares if '0' is revealed
void coord_test0(int x, int y)
{
	if(x==width || y==height || x<0 || y<0 || map_player[y][x] == map_comp[y][x])
		return;

	map_player[y][x] = map_comp[y][x];
	if(map_player[y][x] =='0')
	{
		coord_test0((x+1),y);
		coord_test0((x+1),(y+1));
		coord_test0((x+1),(y-1));
		coord_test0(x,(y-1));
		coord_test0(x,(y+1));
		coord_test0((x-1),(y-1));
		coord_test0((x-1),(y+1));
		coord_test0((x-1),y);
	}
}


void ask_coords()
{
	do
	{	cout << "Enter x coordinate: \n";
		cin >> guessx ; 
	}while(guessx<0 || guessx>9);
	do
	{	cout << "Enter y coordinate: \n";
		cin >> guessy;
	}while(guessy<0 || guessy>9);
}

// Makes sure there are still squares to be revealed
bool proceed() 
{
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			if(map_comp[i][j] != '*' && map_player[i][j] != map_comp[i][j])
				return true;
		}
	}
	return false;
}
void print_comp()
{
	for(int i=0; i<sizecomp; i++)
	{
		for(int k=0; k<sizecomp; k++)
		{
			cout << map_comp[i][k];
			cout << " ";
		}
		cout << endl;
	}
}

void print_play()
{
	for(int i=0; i<sizeplay; i++)
	{
		for(int k=0; k<sizeplay; k++)
		{
			cout << map_player[i][k];
			cout << " ";
		}
		cout << endl;
	}
}

int main()
{
	cout << "Hello! Thanks for playing my shark finder game. To play enter a x and y coordinate to test a square.";
	cout << " If you uncover a shark you lose! Uncovered squares have a number representing how many sharks are ";
	cout << "around it (zero's reveal all squares around them). Good luck!\n\n";
	array_start();
	cout << "Enter number of sharks in game: ";
	cin >> sharks ;
	cout << "\n";
	array_sharks();
	array_complete();
	// cout << "Key : \n";
	// print_comp();	
	cout << "\nPlayer's screen: \n";
	array_player_start();
	print_play();
	do
	{
		ask_coords();
		array_coord_test(guessx, guessy);

	}while(proceed()==true);

	cout << "You won! Good job!\n";
	print_comp();
	exit(0);
}
