#include "LinkedQueue.h"
#include <cstdlib>

class queueMaze {
    int row, col;
    int** map;
    LinkedQueue locQueue;
    Location entry, exitLoc;

public:
    queueMaze()
    {
        set(0, 0);
    }

    void set(int row, int col)
    {
        map = new int* [row];
        for (int i = 0; i < row; i++)
            map[i] = new int[col];
    }

    bool mazeSize(const char* file) // 미로의 max 사이즈 구하기
    {
        char d;
        int c = 0, r = 0;
        FILE* Maze;
        fopen_s(&Maze, file, "rb");
        if (Maze == NULL)
        {

            return false;
        }
        else if (Maze != NULL)
        {
            while ((d = fgetc(Maze)) != '\n' && d != '\r') // 개행이 아니고 빈공간이 아닐때에 c값 증가
            {
                if (d != ' ') c++;
            }
            while ((d = fgetc(Maze)) != EOF) // file의 끝이 아니고 읽어온 d가 개행일때 r값 증가
            {
                if (d == '\n') r++;
            }
            fclose(Maze);
        }
        row = r; // row 값을 r로 초기화 - 행
        col = c; // col 값을 c로 초기화 - 열
        set(row, col);
    }

    void setMaze(const char* file) // 입구, 출구 위치 set
    {
        mazeSize(file);
        char d;
        FILE* Maze;
        fopen_s(&Maze, file, "rb");
        if (Maze != NULL)
        {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    while (d = getc(Maze)) {
                        if ((d == '0' || d == '1')) { // 0이나 1로 표시 되어 있는 글자는 무시
                            ungetc(d, Maze);
                            fscanf_s(Maze, "%d", &map[i][j]);
                            break;
                        }
                        else if (d == 'e') { // 'e' 표시 되어 있는 위치를 스택에 푸시
                            map[i][j] = d;
                            Node* entry = new Node(i, j);
                            locQueue.enqueue(entry);
                            break;
                        }
                        else if (d == 'x') { // 'x' 표시 되어 있는 위치 exitLoc에 저장(출구)
                            map[i][j] = d;
                            exitLoc.setRow(i);
                            exitLoc.setCol(j);
                            break;
                        }
                    }
                }
            }
        }
    }

    void bluePrint()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (map[i][j] == 0) //txt 안에서 0(길)이면
                {
                    printf("  ");
                }
                else if (map[i][j] == 1) //txt 안에서 1(벽)이면
                {
                    printf("■");
                }
                else if (map[i][j] == 2) //길 or 벽 이 아니면 이동경로로 표시되어짐
                {
                    printf("□");
                }
                else if (map[i][j] == 'e') // 입구
                {
                    printf("↘");
                }
                else if (map[i][j] == 'x') // 출구
                {
                    printf("↘");
                }
            }
            printf("\n");
        }
        printf("\n");
    }


    bool isValidLoc(int r, int c) //만약 r, c가 0보다 작거나 최대 row col값(미로 최댓값)을 벗어나면 false 반환
    {
        if (r < 0 || c < 0 || r >= row || c >= col)
            return false;
        else
            return (map[r][c] == 0 || map[r][c] == 'x'); // 0(통로) 혹은 x(출구) 일경우 true 반환
    }

    void searchWidth() // 너비우선 
    {
        bluePrint(); //초기 map 상태 보여주기 위함

        while (locQueue.isEmpty() == false) {
            Location* here = locQueue.dequeue()->getLocation(); //현재 위치는 setMaze에서 push 했던 entry위치

            int r = here->getRow();
            int c = here->getCol();
            here->display();

            if (exitLoc.getRow() == r && exitLoc.getCol() == c) // setMaze에서 저장해둔 위치값(출구)이 일치한다면
            {
                printf("미로찾기 성공!\n");
                exit(1);
            }
            else {
                map[r][c] = 2; // 현재 위치가 출구가 아니라면?
                bluePrint();
                if (isValidLoc(r - 1, c)) { locQueue.enqueue(new Node(r - 1, c)); }
                if (isValidLoc(r + 1, c)) { locQueue.enqueue(new Node(r + 1, c)); }
                if (isValidLoc(r, c - 1)) { locQueue.enqueue(new Node(r, c - 1)); }
                if (isValidLoc(r, c + 1)) { locQueue.enqueue(new Node(r, c + 1)); }

            }
        }
    }

    void searchHeight() // 깊이우선
    {
        bluePrint(); //초기 map 상태 보여주기 위함

        while (locQueue.isEmpty() == false) {
            Location* here = locQueue.dequeue()->getLocation(); //현재 위치는 setMaze에서 push 했던 entry위치

            int r = here->getRow();
            int c = here->getCol();
            here->display();

            if (exitLoc.getRow() == r && exitLoc.getCol() == c) // setMaze에서 저장해둔 위치값(출구)이 일치한다면
            {
                printf("미로찾기 성공!\n");
                exit(1);
            }
            else {
                map[r][c] = 2; // 현재 위치가 출구가 아니라면?
                bluePrint();
                if (isValidLoc(r, c - 1)) { locQueue.enqueue(new Node(r, c - 1)); }
                if (isValidLoc(r, c + 1)) { locQueue.enqueue(new Node(r, c + 1)); }
                if (isValidLoc(r - 1, c)) { locQueue.enqueue(new Node(r - 1, c)); }
                if (isValidLoc(r + 1, c)) { locQueue.enqueue(new Node(r + 1, c)); }

            }
        }
    }
};

int main() {
    queueMaze maze1;
    maze1.setMaze("maze2.txt");
    //maze1.searchHeight();
    maze1.searchWidth();
}