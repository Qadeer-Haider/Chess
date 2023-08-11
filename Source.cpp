#include <iostream>
#include <conio.h>
#include <math.h>
#include <Windows.h>
#include <fstream>
using namespace std;

#define Box char(0xDB)  

enum Color
{
	Black = 0,
	White = 1,
};

void ChangeColor(int color)
{
	HANDLE HConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(HConsole, color);
}

void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}

void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void Initailiztion(char B[8][8], int& Turn)
{
	Turn = 0;
	for (int ri = 1; ri < 7; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
		{
			if (ri == 1)
			{
				B[ri][ci] = 'P';
			}
			else if (ri == 6)
			{
				B[ri][ci] = 'p';
			}
			else
			{
				B[ri][ci] = '-';
			}
		}

	}

	//for black player
	B[0][0] = 'R';
	B[0][1] = 'N';
	B[0][2] = 'B';
	B[0][3] = 'Q';
	B[0][4] = 'K';
	B[0][5] = 'B';
	B[0][6] = 'N';
	B[0][7] = 'R';

	//for white palyer
	B[7][0] = 'r';
	B[7][1] = 'n';
	B[7][2] = 'b';
	B[7][3] = 'q';
	B[7][4] = 'k';
	B[7][5] = 'b';
	B[7][6] = 'n';
	B[7][7] = 'r';

}

void Load_Game(char B[8][8], int& Turn)
{
	ifstream Rdr("Load.txt");
	for (int ri = 0; ri < 8; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
		{
			Rdr >> B[ri][ci];
		}
	}
	Rdr >> Turn;
}

void Save_Game(char B[8][8],int Turn)
{
	ofstream Rdr("Save.txt");
	char save_choice='\0';
	
	cout << "\nDo you want to save game... \n";
	cout << "Press Y for Yes and N for No...\n";

	do
	{
		cin >> save_choice;
		if (save_choice != 'Y' && save_choice != 'y' && save_choice != 'N' && save_choice != 'n')
		{
			cout << "Try Again...\n";
		}
	} while (save_choice != 'Y' && save_choice != 'y' && save_choice != 'N' && save_choice != 'n');
	if (save_choice=='y' || save_choice=='Y')
	{
		for (int ri = 0; ri < 8; ri++)
		{
			for (int ci = 0; ci < 8; ci++)
			{
				Rdr << B[ri][ci] << "\t";
			}
			Rdr << endl;
		}
		Rdr << Turn;
	}
	
}

void ChessDisplay()
{
	ChangeColor(9);
	cout << "=======================================================================\n\n";
	cout << "           ________   _    _    _______    ________   ________      \n";
	cout << "          /   _____| | |  | |  |   ____|  /  _____/  /  _____/      \n";
	cout << "         |   |       | |__| |  |  |___   |  (_____  |  (______        \n";
	cout << "         |   |       |  __  |  |   ___|   \\_____  \\  \\______  \\  \n";
	cout << "         |   |_____  | |  | |  |  |____    _____)  |   _____) |    \n";
	cout << "          \\________| |_|  |_|  |_______|  /_______/  /_______/     \n\n\n";
	cout << "=======================================================================\n\n";
}

void Game_Start_Message(char P_Name[2][50], char B[8][8], int& Turn)
{
	ChangeColor(9);
	cout << "\n\n";
	cout << "Enter Player's Name who want black pieces : ";
	cin >> P_Name[0];
	cout << endl;
	cout << "Enter Player's Name who want White pieces : ";
	cin >> P_Name[1];
	cout << endl;

	cout << "Please read the below instruction before starting the game...\n";
	cout << "Instructions :-\n";
	cout << "1-The Possible moves are shown in ";
	ChangeColor(2);
	cout << "green\n";
	ChangeColor(9);
	cout << "2-The Possible kills  are shown in ";
	ChangeColor(4);
	cout << "red\n";
	ChangeColor(9);
	cout << "A message will be displayed when your king is in check\n";
	cout << "The Upper pieces are labeled as black pieces and lower one as white pieces\n";


	char Select = '0';
	cout << "\nDo you want to start a previous game...\n";
	cout << "Press Y for Yes and N for N...\n";

	do
	{
		cin >> Select;
		if (Select != 'Y' && Select != 'y' && Select != 'N' && Select != 'n')
		{
			cout << "Try Again...\n";
		}
	} while (Select != 'Y' && Select != 'y' && Select != 'N' && Select != 'n');


	if (Select == 'Y' || Select == 'y')
	{
		Load_Game(B, Turn);
		cout << "\n\Your Game has been Loaded...\n";
		cout << "Enter any key to start...\n";
		_getch();
	}
	else
	{
		cout << "\n\nYour New Game is Ready...\n";
		cout << "Enter any key to start...\n";
		_getch();
	}

}

void DisplayBoard(char b[8][8])
{
	char s = -37;
	system("cls");
	cout << "\n\t\t\t\t\t\t\t\t";
	ChangeColor(8);
	cout << "(Black Pieces)";
	ChangeColor(1);

	cout << "\n\n\t";

	for (int i = 0; i < 129; i++)
	{
		cout << s;
	}
	cout << endl;

	for (int ri = 0; ri < 8; ri++)
	{
		for (int i = 0; i < 9; i++)
		{

			cout << "\t" << s << "\t";
		}

		cout << endl;

		cout << "\t" << s << "\t";
		for (int ci = 0; ci < 8; ci++)
		{

			switch (b[ri][ci])
			{
			case'R':
			case'N':
			case'B':
			case'Q':
			case'K':
			case'P':
				ChangeColor(8);
				break;
			case'r':
			case'n':
			case'b':
			case'q':
			case'k':
			case'p':
				ChangeColor(7);
				break;
			case'*':
				ChangeColor(2);
				break;
			case'+':
				ChangeColor(4);
				break;
			}


			if (b[ri][ci] == '-')
			{
				cout << " ";
			}
			else if (b[ri][ci] == '*' || b[ri][ci] == '+')
			{
				cout << Box;
			}
			else
			{
				cout << b[ri][ci];
			}
			ChangeColor(1);
			cout << "\t" << s << "\t";
		}
		cout << endl;
		for (int i = 0; i < 9; i++)
		{

			cout << "\t" << s << "\t";
		}
		cout << endl << "\t";
		for (int i = 0; i < 129; i++)
		{
			cout << s;
		}
		cout << endl;
	}

	cout << "\n\t\t\t\t\t\t\t\t";
	ChangeColor(7);
	cout << "(White Pieces)\n";
	ChangeColor(1);

}

void Player_Message(char P_Name[], int Turn)
{
	cout << "\n";
	cout << P_Name << " Turn's";
	if (Turn == 0)
	{
		ChangeColor(8);
		cout << "(Black Pieces)";
	}
	else
	{
		ChangeColor(7);
		cout << "(White Pieces)";
	}

	ChangeColor(9);
	cout << endl;
}

void Turn_Change(int& Turn)
{
	Turn = (Turn + 1) % 2;
}

void Source_Point(int& s_ri, int& s_ci)
{
	int rpos = 0, cpos = 0;
	getRowColbyLeftClick(rpos, cpos);
	s_ri = (rpos - 3) / 4;
	s_ci = (cpos - 8) / 16;

}

bool Is_Black_Piece(char sym)
{
	if ('A' <= sym && 'Z' >= sym)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Is_White_Piece(char sym)
{
	if ('a' <= sym && 'z' >= sym)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Is_Valid_Starting_point(char sym, int Turn, int sri, int sci)
{
	if (sri < 0 || sri >7)
	{
		return false;
	}
	if (sci < 0 || sci >7)
	{
		return false;
	}

	if (Turn == Black)
	{
		return (Is_Black_Piece(sym));
	}
	else if (Turn == White)
	{
		return(Is_White_Piece(sym));
	}
}

void Destination_Point(int& d_ri, int& d_ci)
{
	int rpos = 0, cpos = 0;
	getRowColbyLeftClick(rpos, cpos);
	d_ri = (rpos - 3) / 4;
	d_ci = (cpos - 8) / 16;

}

bool Is_Valid_Destination(char sym, int turn, int dri, int dci)
{
	if (dri < 0 || dri >7)
	{
		return false;
	}
	if (dci < 0 || dci >7)
	{
		return false;
	}
	if (turn == Black)
	{
		if (sym == '-' || Is_Black_Piece(sym) == false || Is_White_Piece(sym) == true)
		{
			return true;
		}
	}
	else if (turn == White)
	{
		if (sym == '-' || Is_White_Piece(sym) == false || Is_Black_Piece(sym) == true)
		{
			return true;
		}
	}
	return false;
}

void Making_Move_On_Board(char B[8][8], int sri, int sci, int dri, int dci)
{
	B[dri][dci] = B[sri][sci];
	B[sri][sci] = '-';
}

bool Is_North_South_Axis_Movement(int sri, int sci, int dri, int dci)
{
	return (sci == dci && sri != dri);
}

bool Is_East_West_Axis_Movement(int sri, int sci, int dri, int dci)
{
	return (sri == dri && sci != dci);
}

bool Is_Slope_Axis_Movement(int sri, int sci, int dri, int dci)
{
	int Delta_R = dri - sri;
	int Delta_C = dci - sci;
	return (Delta_R == Delta_C || Delta_R == -Delta_C);
}

bool Is_North_South_Path_Clear(char B[8][8], int sri, int sci, int dri, int dci)
{
	if (sri < dri)
	{
		for (int r = sri + 1; r < dri; r++)
		{
			if (B[r][sci] != '-')
			{
				return false;
			}

		}
		return true;
	}
	else if (sri > dri)
	{
		for (int r = sri - 1; r > dri; r--)
		{
			if (B[r][sci] != '-')
			{
				return false;
			}

		}
		return true;
	}
}

bool Is_East_West_Path_Clear(char B[8][8], int sri, int sci, int dri, int dci)
{
	if (sci < dci)
	{
		for (int c = sci + 1; c < dci; c++)
		{
			if (B[sri][c] != '-')
			{
				return false;
			}

		}
		return true;
	}
	else if (sci > dci)
	{
		for (int c = sci - 1; c > dci; c--)
		{
			if (B[sri][c] != '-')
			{
				return false;
			}

		}
		return true;
	}
}

bool Is_Sloppy_Path_Clear(char B[8][8], int sri, int sci, int dri, int dci)
{
	int Delta_R = dri - sri;
	int Delta_C = dci - sci;

	if (Delta_R < 0 && Delta_C < 0)
	{
		for (int i = 1; i < abs(Delta_R); i++)
		{
			if (B[sri - i][sci - i] != '-')
			{
				return false;
			}
		}
		return true;
	}
	else if (Delta_R < 0 && Delta_C > 0)
	{
		for (int i = 1; i < abs(Delta_R); i++)
		{
			if (B[sri - i][sci + i] != '-')
			{
				return false;
			}
		}
		return true;

	}
	else if (Delta_R > 0 && Delta_C > 0)
	{
		for (int i = 1; i < Delta_R; i++)
		{
			if (B[sri + i][sci + i] != '-')
			{
				return false;
			}
		}
		return true;
	}
	else if (Delta_R > 0 && Delta_C < 0)
	{
		for (int i = 1; i < Delta_R; i++)
		{
			if (B[sri + i][sci - i] != '-')
			{
				return false;
			}
		}
		return true;
	}
}

bool Is_Rook_Legal_Move(char B[8][8], int sri, int sci, int dri, int dci)
{
	if ((Is_North_South_Axis_Movement(sri, sci, dri, dci) == true && Is_North_South_Path_Clear(B, sri, sci, dri, dci) == true) ||
		(Is_East_West_Axis_Movement(sri, sci, dri, dci) == true && Is_East_West_Path_Clear(B, sri, sci, dri, dci) == true))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Is_Bishop_Legal_Move(char B[8][8], int sri, int sci, int dri, int dci)
{
	if (Is_Slope_Axis_Movement(sri, sci, dri, dci) == true && Is_Sloppy_Path_Clear(B, sri, sci, dri, dci) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Is_Queen_Legal_Move(char B[8][8], int sri, int sci, int dri, int dci)
{
	if (Is_Bishop_Legal_Move(B, sri, sci, dri, dci) == true || Is_Rook_Legal_Move(B, sri, sci, dri, dci) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Is_King_Legal_Move(char B[8][8], int sri, int sci, int dri, int dci)
{
	int Delta_R = abs(dri - sri);
	int Delta_C = abs(dci - sci);
	return (Is_Queen_Legal_Move(B, sri, sci, dri, dci)
		&& ((Delta_R == 1 && Delta_C == 1) || (Delta_R == 1 && Delta_C == 0) || (Delta_R == 0 && Delta_C == 1)));

}

bool Is_Knight_Legal_Move(char B[8][8], int sri, int sci, int dri, int dci)
{
	int Delta_R = abs(dri - sri);
	int Delta_C = abs(dci - sci);
	return ((Delta_R == 1 && Delta_C == 2) || (Delta_R == 2 && Delta_C == 1));
}

bool Is_Kill_Happen(char B[8][8], int dri, int dci)
{
	if (B[dri][dci] != '-')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Is_Downward_Path_Clear_And_Movement_For_Black_Pawn(char B[8][8], int sri, int sci, int dri, int dci)
{
	if (sri < dri && sci == dci)
	{
		for (int r = sri + 1; r < dri; r++)
		{
			if (B[r][sci] != '-')
			{
				return false;
			}
		}
	}
	else if (sri > dri)
	{
		return false;
	}
	return true;
}

bool Is_Sloppy_Path_Movement_For_Black_Pawn(char B[8][8], int sri, int sci, int dri, int dci)
{
	if (sri < dri)
	{
		if (Is_Kill_Happen(B, dri, dci) == true)
		{
			return true;
		}
	}
	return false;
}

bool Is_Pawn_Legal_Move_For_Black(char B[8][8], int sri, int sci, int dri, int dci)
{
	int Delta_R = abs(dri - sri);
	int Delta_C = abs(dci - sci);

	if (sri == 1)
	{
		if (((Delta_R == 2 && Delta_C == 0) || (Delta_R == 1 && Delta_C == 0)) && Is_Kill_Happen(B, dri, dci) == false
			&& Is_Downward_Path_Clear_And_Movement_For_Black_Pawn(B, sri, sci, dri, dci) == true)
		{
			return true;
		}
		if ((Delta_R == 1 && Delta_C == 1) && Is_Sloppy_Path_Movement_For_Black_Pawn(B, sri, sci, dri, dci) == true)
		{
			return true;
		}
	}
	else
	{
		if ((Delta_R == 1 && Delta_C == 0) && Is_Kill_Happen(B, dri, dci) == false
			&& Is_Downward_Path_Clear_And_Movement_For_Black_Pawn(B, sri, sci, dri, dci) == true)
		{
			return true;
		}
		if ((Delta_R == 1 && Delta_C == 1) && Is_Sloppy_Path_Movement_For_Black_Pawn(B, sri, sci, dri, dci) == true)
		{
			return true;
		}
	}

	return false;
}

bool Is_Upward_Path_Clear_And_Movement_For_White_Pawn(char B[8][8], int sri, int sci, int dri, int dci)
{
	if (sri > dri && sci == dci)
	{
		for (int r = sri - 1; r > dri; r--)
		{
			if (B[r][sci] != '-')
			{
				return false;
			}

		}
	}
	else if (sri < dri)
	{
		return false;
	}
	return true;
}

bool Is_Sloppy_Path_Movement_For_White_Pawn(char B[8][8], int sri, int sci, int dri, int dci)
{
	if (sri > dri)
	{
		if (Is_Kill_Happen(B, dri, dci) == true)
		{
			return true;
		}
	}
	return false;
}

bool Is_Pawn_Legal_Move_For_White(char B[8][8], int sri, int sci, int dri, int dci)
{
	int Delta_R = abs(dri - sri);
	int Delta_C = abs(dci - sci);

	if (sri == 6)
	{
		if (B[sri][sci] == 'p')
		{
			if (((Delta_R == 2 && Delta_C == 0) || (Delta_R == 1 && Delta_C == 0)) && Is_Kill_Happen(B, dri, dci) == false
				&& Is_Upward_Path_Clear_And_Movement_For_White_Pawn(B, sri, sci, dri, dci) == true)
			{
				return true;
			}
			if ((Delta_R == 1 && Delta_C == 1) && Is_Sloppy_Path_Movement_For_White_Pawn(B, sri, sci, dri, dci) == true)
			{
				return true;
			}
		}
	}
	else
	{
		if ((Delta_R == 1 && Delta_C == 0) && Is_Kill_Happen(B, dri, dci) == false
			&& Is_Upward_Path_Clear_And_Movement_For_White_Pawn(B, sri, sci, dri, dci) == true)
		{
			return true;
		}
		if ((Delta_R == 1 && Delta_C == 1) && Is_Sloppy_Path_Movement_For_White_Pawn(B, sri, sci, dri, dci) == true)
		{
			return true;
		}
	}

	return false;
}

bool Is_Legal_Move_Of_The_Piece(char B[8][8], int sri, int sci, int dri, int dci)
{
	switch (B[sri][sci])
	{
	case 'R':
	case 'r':
		return (Is_Rook_Legal_Move(B, sri, sci, dri, dci));
		break;
	case 'B':
	case 'b':
		return (Is_Bishop_Legal_Move(B, sri, sci, dri, dci));
		break;
	case 'Q':
	case 'q':
		return (Is_Queen_Legal_Move(B, sri, sci, dri, dci));
		break;
	case 'K':
	case 'k':
		return (Is_King_Legal_Move(B, sri, sci, dri, dci));
		break;
	case 'N':
	case 'n':
		return (Is_Knight_Legal_Move(B, sri, sci, dri, dci));
		break;
	case 'P':
		return (Is_Pawn_Legal_Move_For_Black(B, sri, sci, dri, dci));
		break;
	case 'p':
		return (Is_Pawn_Legal_Move_For_White(B, sri, sci, dri, dci));
		break;
	}
	return true;
}

void Pawn_Promotion(char B[8][8], int Turn)
{
	char promote = NULL;
	if (Turn == Black)
	{
		for (int c = 0; c < 8; c++)
		{
			if (B[7][c] == 'P')
			{
				cout << "You want your Pawn to be promoted to which piece...\n";
				cout << "Press 'Q' for Queen...\n";
				cout << "Press 'R' for Rook...\n";
				cout << "Press 'N' for Knight...\n";
				cout << "Press 'B' for Bishop...\n";
				cin >> promote;
				switch (promote)
				{
				case 'Q':
				case 'q':
					B[7][c] = 'Q';
					break;
				case 'B':
				case 'b':
					B[7][c] = 'B';
					break;
				case 'N':
				case 'n':
					B[7][c] = 'N';
					break;
				case 'R':
				case 'r':
					B[7][c] = 'R';
					break;
				}
			}
		}

	}
	else if (Turn == White)
	{
		for (int c = 0; c < 8; c++)
		{
			if (B[0][c] == 'p')
			{
				cout << "You want your Pawn to be promoted to which piece...\n";
				cout << "Press 'Q' for Queen...\n";
				cout << "Press 'R' for Rook...\n";
				cout << "Press 'N' for Knight...\n";
				cout << "Press 'B' for Bishop...\n";
				cin >> promote;
				switch (promote)
				{
				case 'Q':
				case 'q':
					B[0][c] = 'q';
					break;
				case 'B':
				case 'b':
					B[0][c] = 'b';
					break;
				case 'N':
				case 'n':
					B[0][c] = 'n';
					break;
				case 'R':
				case 'r':
					B[0][c] = 'r';
					break;
				}
			}
		}

	}
}

void Find_King(char B[8][8], int Turn, int& Kri, int& Kci)
{
	if (Turn == Black)
	{
		for (int r = 0; r < 8; r++)
		{
			for (int c = 0; c < 8; c++)
			{
				if (B[r][c] == 'K')
				{
					Kri = r;
					Kci = c;
				}
			}
		}
	}
	else if (Turn == White)
	{
		for (int r = 0; r < 8; r++)
		{
			for (int c = 0; c < 8; c++)
			{
				if (B[r][c] == 'k')
				{
					Kri = r;
					Kci = c;
				}
			}
		}
	}

}

bool Check(char B[8][8], int Turn)
{
	int kri, kci;
	Find_King(B, Turn, kri, kci);
	if (Turn == White)
	{
		for (int r = 0; r < 8; r++)
		{
			for (int c = 0; c < 8; c++)
			{
				if (B[r][c] >= 'A' && B[r][c] <= 'Z')
				{
					if (Is_Legal_Move_Of_The_Piece(B, r, c, kri, kci) == true)
					{
						return true;
					}
				}
			}
		}
	}
	else if (Turn == Black)
	{
		for (int r = 0; r < 8; r++)
		{
			for (int c = 0; c < 8; c++)
			{
				if (B[r][c] >= 'a' && B[r][c] <= 'z')
				{
					if (Is_Legal_Move_Of_The_Piece(B, r, c, kri, kci) == true)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Checkbased(char B[8][8], int Turn, int sri, int sci, int dri, int dci)
{
	char TempBoard[8][8];
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			TempBoard[r][c] = B[r][c];
		}
	}

	if (Is_Legal_Move_Of_The_Piece(B, sri, sci, dri, dci) == true)
	{
		Making_Move_On_Board(TempBoard, sri, sci, dri, dci);
		if (Check(TempBoard, Turn) == false)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}

bool Legal(char B[8][8], int sri, int sci, int dri, int dci, int Turn)
{
	if (Checkbased(B, Turn, sri, sci, dri, dci) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Check_Mate(char B[8][8], int Turn, int& whowin)
{
	bool flag = true;
	if (Turn == Black)
	{
		for (int sri = 0; sri < 8; sri++)
		{
			for (int sci = 0; sci < 8; sci++)
			{
				if (B[sri][sci] >= 'A' && B[sri][sci] <= 'Z')
				{
					for (int dri = 0; dri < 8; dri++)
					{
						for (int dci = 0; dci < 8; dci++)
						{
							if (Legal(B, sri, sci, dri, dci, Turn) == true && Is_Valid_Destination(B[dri][dci], Turn, dri, dci == true))
							{
								flag = false;
							}
							else
							{
								whowin = 1;
							}

						}
					}

				}
			}

		}
	}
	else if (Turn == White)
	{
		for (int sri = 0; sri < 8; sri++)
		{
			for (int sci = 0; sci < 8; sci++)
			{
				if (B[sri][sci] >= 'a' && B[sri][sci] <= 'z')
				{
					for (int dri = 0; dri < 8; dri++)
					{
						for (int dci = 0; dci < 8; dci++)
						{
							if (Legal(B, sri, sci, dri, dci, Turn) == true && Is_Valid_Destination(B[dri][dci], Turn, dri, dci == true))
							{
								flag = false;
							}
							else
							{
								whowin = 0;
							}
						}
					}

				}
			}

		}
	}

	return flag;
}

void Undo(char Board[8][8], char DummmyBoard[8][8], int& Turn)
{
	char choice = '\0';
	cout << "Do want to undo your last move...\n";
	cout << "Press Y for Yes and N for N...\n";

	do
	{
		cin >> choice;
		if (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
		{
			cout << "Try Again...\n";
		}
	} 
	while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');


	if (choice == 'Y' || choice == 'y')
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				Board[i][j] = DummmyBoard[i][j];

			}
		}
		Turn++;
	}
}

void Highlight_Possible_Moves(char B[8][8], int sri, int sci, int Turn)
{
	char DBoard[8][8];
	for (int ri = 0; ri < 8; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
		{
			DBoard[ri][ci] = B[ri][ci];
		}
	}
	for (int ri = 0; ri < 8; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
		{
			if (Legal(B, sri, sci, ri, ci, Turn) == true && Is_Valid_Destination(B[ri][ci], Turn, ri, ci) == true)
			{
				if (Is_Kill_Happen(B, ri, ci) == true)
				{
					DBoard[ri][ci] = '+';
				}
				else
				{
					DBoard[ri][ci] = '*';
				}
			}
		}

	}
	DisplayBoard(DBoard);
}

void Game_Over()
{
	cout << "=======================================================================\n\n";
	cout << "\t   __________       ____       ___      ___    _______                    \n";
	cout << "\t  /  ________|     / __ \\     |   \\    /   |  /   ____|                 \n";
	cout << "\t |  |   ____      / /__\\ \\    | |\\ \\  / /| | |  |___                  \n";
	cout << "\t |  |  |___ \\    / ______ \\   | | \\ \\/ / | | |   ___|                \n";
	cout << "\t |  |_____|  |  / /      \\ \\  | |  \\__/  | | |  |_____                 \n";
	cout << "\t  \\_________/  /_/        \\_\\ |_|        |_|  \\_______|               \n";
	cout << "\t   _________      _        _      _______     _______                     \n";
	cout << "\t  / _______ \\    \\ \\      / /    /  _____|   |  ___  |                 \n";
	cout << "\t | |       | |    \\ \\    / /    |  |___      | |___) |                  \n";
	cout << "\t | |       | |     \\ \\  / /     |   ___|     | ____  |                  \n";
	cout << "\t | |_______| |      \\ \\/ /      |  |_____    | |   \\ \\                \n";
	cout << "\t  \\_________/        \\__/        \\_______|   |_|    \\_\\          \n\n\n";
	cout << "=======================================================================\n\n";

}

int main()
{
	char Board[8][8];
	char DummyBoard[8][8];
	int Turn = 0;
	char Player_Name[2][50];
	int Starting_Row_index = 0, Starting_Columns_index = 0;
	int Destination_Row_index = 0, Destination_Columns_index = 0;
	char symbol;

	int whowin;

	Initailiztion(Board, Turn);

	ChessDisplay();

	Game_Start_Message(Player_Name, Board, Turn);

	do
	{
		DisplayBoard(Board);
		
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				DummyBoard[i][j] = Board[i][j];
			}
		}

		Player_Message(Player_Name[Turn], Turn);
		cout << endl;

		if (Check(Board, Turn) == true)
		{
			ChangeColor(4);
			cout << "Your King is in Danger";
			ChangeColor(1);
		}

		ChangeColor(9);
		cout << "\nClick Source Point \n";
		do
		{
			Source_Point(Starting_Row_index, Starting_Columns_index);
			symbol = Board[Starting_Row_index][Starting_Columns_index];
			if (!Is_Valid_Starting_point(symbol, Turn, Starting_Row_index, Starting_Columns_index))
			{
				cout << "\nInvalid Move ...\n";
				cout << "Try Agin...\n";
			}
		} while (!Is_Valid_Starting_point(symbol, Turn, Starting_Row_index, Starting_Columns_index));

		Highlight_Possible_Moves(Board, Starting_Row_index, Starting_Columns_index, Turn);

		cout << "\nClick Destination Point \n";
		do
		{
			Destination_Point(Destination_Row_index, Destination_Columns_index);
			symbol = Board[Destination_Row_index][Destination_Columns_index];
			if (!Is_Valid_Destination(symbol, Turn, Destination_Row_index, Destination_Columns_index))
			{
				cout << "\nInvalid Move ...\n";
				cout << "Try Agin...\n";
				Sleep(1000);
			}
		} while (!Is_Valid_Destination(symbol, Turn, Destination_Row_index, Destination_Columns_index));

		if (Legal(Board, Starting_Row_index, Starting_Columns_index, Destination_Row_index, Destination_Columns_index, Turn) == true)
		{
			
			Making_Move_On_Board(Board, Starting_Row_index, Starting_Columns_index, Destination_Row_index, Destination_Columns_index);	
			
			Pawn_Promotion(Board, Turn);

			DisplayBoard(Board);

			Save_Game(Board,Turn);

			Undo(Board, DummyBoard, Turn);

			Turn_Change(Turn);
		}
		else
		{
			cout << "Illegal move of the piece...\n";
			cout << "Try Again...\n";
			DisplayBoard(Board);
		}

	} while (!Check_Mate(Board, Turn, whowin));
	system("cls");
	Game_Over();

	cout << "__________________________________________________________\n";
	cout << "                                                  \n";
	cout << "\t\t\t" << Player_Name[whowin] << " Wins...\n";
	cout << "__________________________________________________________\n";

	return 0;
}

