/*��Ŀ��  N�ʺ�����*/
/*2053380 ���*/

#include <iostream>

using namespace std;
#define DEBUG 0

//�����Ϣ��
class Log//���ڵ��������Ϣ����,����Ҫʵ����
{
private:
	Log() = delete;
	Log(const Log&) = delete;
	Log(Log&&) = delete;

public:
	static void Error(const char* message) {
		std::cout << "[ERROR]" << message << std::endl;
	}

	static void Warn(const char* message) {
		std::cout << "[WARNING]" << message << std::endl;
	}

	static void Info(const char* message) {
		std::cout << "[INFO]" << message << std::endl;
	}
};

//����������

class ChessBoard
{
public:
	ChessBoard(int queen);
	ChessBoard() { ; }
	~ChessBoard() { ; }

	void OutPut();
	void PlaceQueen(int row);

	//how many solution have been found
	const int GetSlnNum()const;

	//If (row,col) can place a queen
	bool Check(int row, int col);

	//If (row,col) is in the correct range
	bool ifInside(int row, int col);
private:
	int m_queen;//the number of the queen
	int m_sln;//the solution of this problem

	bool* m_pChessboard;
};
//��������������



int main()
{
	cout << "����N x N �����̣�����N���ʺ�Ҫ�����лʺ���ͬһ�С��к�ͬһб���ϣ�\n\n";
	cout << "������ʺ����:";
	int queen_number = 0;
	cin >> queen_number;

	while (cin.fail() || queen_number <= 0) {
		cout << "����������������룺\n";
		cin.clear();
		cin.ignore(65535, '\n');
		cin >> queen_number;
	}

	cout << '\n';

	ChessBoard chess = ChessBoard(queen_number);

	cout << "�ʺ�ڷ�\n\n";
	chess.PlaceQueen(0);//begin with the first line

	cout << "�˻ʺ����⹲��" << chess.GetSlnNum() << "�ֽ⣡" << endl;

	std::cout << "���س������˳�\n";
	std::cin.get();
	std::cin.get();

	return 0;
}


//������ʵ��

#if DEBUG
#include "Log.h" // ע�⣬�����ύ�ļ�ʱ��ԭ�д������һ��cpp�ڣ���˸ô���Ч
#endif // DEBUG

#define Placed   true
#define UnPlaced false

ChessBoard::ChessBoard(int queen)
{
	m_queen = queen;
	m_pChessboard = new bool[queen * queen];
#if DEBUG
	if (!m_pChessboard) {
		Log::Error("nullptr in chessboard's construction");
		return;
	}
#endif
	bool* p = m_pChessboard;
	for (int i = 0; i < queen * queen; i++) {
		*p = UnPlaced;
		p++;
	}
}

void ChessBoard::OutPut()
{
	m_sln++;
	cout << "��" << m_sln << "�ֽⷨ��\n\n";
	bool* p = m_pChessboard;
	for (int i = 0; i < m_queen * m_queen; i++) {
		if (*p == Placed) {
			cout << "x ";
		}
		else {
			cout << *p << ' ';
		}
		if ((i + 1) % m_queen == 0) {
			cout << '\n';
		}
		p++;
	}
	cout << "\n\n";
}

void ChessBoard::PlaceQueen(int row)
{
	bool* p = m_pChessboard;//p is the head of the chessboard
	int   offset = 0;
	for (int column = 0; column < m_queen; column++)//look every col
	{
		offset = (row * m_queen) + column;
		*(p + offset) = Placed;
		//== array[row][column] = Placed;
		//just try if this place can place a queen

		if (Check(row, column))
		{
			if (row + 1 == m_queen)//this row is the last row and you can place a queen successfully, so it's a kind of solution
			{
				OutPut();
			}
			else//in the middle line, this place is fine, and you need to keep trying the next line
			{
				PlaceQueen(row + 1);
			}
		}
		*(p + offset) = UnPlaced;
		// == array[row][column] = false;
		//if you finish a method, to get another method, you need to remove the queen that's been placed
	}
}

const int ChessBoard::GetSlnNum() const
{
	return m_sln;
}

bool ChessBoard::Check(int row, int col)
{
	bool* p = m_pChessboard;
	if (row == 0) {
		return true;//the first row, you can even place anywhere
	}

	//check the previous col
	for (int i = 0; i < row; i++) {
		if (*(p + (i * m_queen) + col) == Placed) {
			return false;
		}
	}

	int x = row, y = col;
	//check the diagonal(�Խ���), four direction
	//1. left_above
	x--;
	y--;
	while (1)
	{
		if (!ifInside(x, y)) {
			break;//break the border, if you got this step, this direction is placeable
		}

		if (*(p + (x * m_queen) + y) == UnPlaced) {
			x--;
			y--;
		}
		else {//you have placed a queen here
			return false;
		}
	}

	x = row, y = col;//return the origin point
	//2. right_above
	x++;
	y--;
	while (1)
	{
		if (!ifInside(x, y)) {
			break;//break the border
		}

		if (*(p + (x * m_queen) + y) == UnPlaced) {
			x++;
			y--;
		}
		else {//you have placed a queen here
			return false;
		}
	}

	x = row, y = col;//return the origin point
	//3. right_down
	x++;
	y++;
	while (1)
	{
		if (!ifInside(x, y)) {
			break;//break the border
		}

		if (*(p + (x * m_queen) + y) == UnPlaced) {
			x++;
			y++;
		}
		else {//you have placed a queen here
			return false;
		}
	}

	x = row, y = col;//return the origin point
	//4. left_down
	x--;
	y++;
	while (1)
	{
		if (!ifInside(x, y)) {
			break;//break the border
		}

		if (*(p + (x * m_queen) + y) == UnPlaced) {
			x--;
			y++;
		}
		else {//you have placed a queen here
			return false;
		}
	}

	return true;
}

bool ChessBoard::ifInside(int row, int col)
{
	if (row >= 0 && col >= 0) {
		if (row < m_queen && col < m_queen) {
			return true;
		}
	}
	return false;
}


//������ʵ�ֽ���