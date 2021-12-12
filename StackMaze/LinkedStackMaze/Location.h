// https://eboong.tistory.com/33 및 교재 p.127의 3.10 Location2D 참고
#include <cstdio>
class Location {
	int row;	 
	int col;	 
public:
	Location(int r = 0, int c = 0) : row(r), col(c) {}
	bool isNeighbor(Location& p) { 
		return ((row == p.row && (col == p.col - 1 || col == p.col + 1)) // row값이 같고 col값이 인접한지
			|| (col == p.col && (row == p.row - 1 || row == p.row + 1))); // col값이 같고 row값이 인접한지
	}
	bool operator==(Location& p) { return row == p.row && col == p.col; } 	// 위치 p가 자신과 같은 위치인지를 검사하는 함수 

	void display() 
	{ 
		printf("row : %d, col : %d\n", row+1, col+1); 
	}

	int getRow() 
	{ 
		return row; 
	}
	void setRow(int r)
	{
		row = r;
	}
	int getCol() 
	{ 
		return col; 
	}
	void setCol(int c) 
	{ 
		col = c; 
	}

	
};
