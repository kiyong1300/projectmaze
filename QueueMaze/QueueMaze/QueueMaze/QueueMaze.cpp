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

    bool mazeSize(const char* file) // �̷��� max ������ ���ϱ�
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
            while ((d = fgetc(Maze)) != '\n' && d != '\r') // ������ �ƴϰ� ������� �ƴҶ��� c�� ����
            {
                if (d != ' ') c++;
            }
            while ((d = fgetc(Maze)) != EOF) // file�� ���� �ƴϰ� �о�� d�� �����϶� r�� ����
            {
                if (d == '\n') r++;
            }
            fclose(Maze);
        }
        row = r; // row ���� r�� �ʱ�ȭ - ��
        col = c; // col ���� c�� �ʱ�ȭ - ��
        set(row, col);
    }

    void setMaze(const char* file) // �Ա�, �ⱸ ��ġ set
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
                        if ((d == '0' || d == '1')) { // 0�̳� 1�� ǥ�� �Ǿ� �ִ� ���ڴ� ����
                            ungetc(d, Maze);
                            fscanf_s(Maze, "%d", &map[i][j]);
                            break;
                        }
                        else if (d == 'e') { // 'e' ǥ�� �Ǿ� �ִ� ��ġ�� queue�� Ǫ��
                            map[i][j] = d;
                            Node* entry = new Node(i, j);
                            locQueue.enqueue(entry);
                            break;
                        }
                        else if (d == 'x') { // 'x' ǥ�� �Ǿ� �ִ� ��ġ exitLoc�� ����(�ⱸ)
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
                if (map[i][j] == 0) //txt �ȿ��� 0(��)�̸�
                {
                    printf("  ");
                }
                else if (map[i][j] == 1) //txt �ȿ��� 1(��)�̸�
                {
                    printf("��");
                }
                else if (map[i][j] == 2) //�� or �� �� �ƴϸ� �̵���η� ǥ�õǾ���
                {
                    printf("��");
                }
                else if (map[i][j] == 'e') // �Ա�
                {
                    printf("��");
                }
                else if (map[i][j] == 'x') // �ⱸ
                {
                    printf("��");
                }
            }
            printf("\n");
        }
        printf("\n");
    }


    bool isValidLoc(int r, int c) //���� r, c�� 0���� �۰ų� �ִ� row col��(�̷� �ִ�)�� ����� false ��ȯ
    {
        if (r < 0 || c < 0 || r >= row || c >= col)
            return false;
        else
            return (map[r][c] == 0 || map[r][c] == 'x'); // 0(���) Ȥ�� x(�ⱸ) �ϰ�� true ��ȯ
    }

    void searchWidth() // �ʺ�켱 
    {
        bluePrint(); //�ʱ� map ���� �����ֱ� ����

        while (locQueue.isEmpty() == false) {
            Location* here = locQueue.dequeue()->getLocation(); //���� ��ġ�� setMaze���� enqueue �ߴ� entry��ġ

            int r = here->getRow();
            int c = here->getCol();
            here->display();

            if (exitLoc.getRow() == r && exitLoc.getCol() == c) // setMaze���� �����ص� ��ġ��(�ⱸ)�� ��ġ�Ѵٸ�
            {
                printf("�̷�ã�� ����!\n");
                exit(1);
            }
            else {
                map[r][c] = 2; // ���� ��ġ�� �ⱸ�� �ƴ϶��?
                bluePrint();
                if (isValidLoc(r - 1, c)) { locQueue.enqueue(new Node(r - 1, c)); }
                if (isValidLoc(r + 1, c)) { locQueue.enqueue(new Node(r + 1, c)); }
                if (isValidLoc(r, c - 1)) { locQueue.enqueue(new Node(r, c - 1)); }
                if (isValidLoc(r, c + 1)) { locQueue.enqueue(new Node(r, c + 1)); }

            }
        }
    }

    void searchHeight() // ���̿켱
    {
        bluePrint(); //�ʱ� map ���� �����ֱ� ����

        while (locQueue.isEmpty() == false) {
            Location* here = locQueue.dequeue()->getLocation(); //���� ��ġ�� setMaze���� enqueue �ߴ� entry��ġ

            int r = here->getRow();
            int c = here->getCol();
            here->display();

            if (exitLoc.getRow() == r && exitLoc.getCol() == c) // setMaze���� �����ص� ��ġ��(�ⱸ)�� ��ġ�Ѵٸ�
            {
                printf("�̷�ã�� ����!\n");
                exit(1);
            }
            else {
                map[r][c] = 2; // ���� ��ġ�� �ⱸ�� �ƴ϶��?
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
    maze1.setMaze("maze.txt");
    maze1.searchWidth();
}