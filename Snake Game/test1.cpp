#include < iostream >

#include < conio.h >

using namespace std;

bool gameover;

const int width = 20;

const int height = 17;

int x, y, fruitX, fruitY, score;

int tailX[100], tailY[100]; //snake coordinates

int nTail;

enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN }; // Controls

eDirecton dir;

//�̱���
class Singleton {
private:
	Singleton() :total(0) { cout << "private ������, Instance Falg:" << instanceFlag << endl; };	// �����ڰ� private member �Լ�

	static bool instanceFlag;
	static Singleton* instance;
	int total;
public:

	static Singleton* getInstance()
	{
		if (!instance) 
		{
			cout << "������ ���� �� �ν��Ͻ� �Ҵ�" << endl;
			instanceFlag = true;
			instance = new Singleton();
		}
		return instance;
	}
	~Singleton()
	{
		cout << "public �Ҹ���" << endl;
	}

	void cummulate(int value) 		  // �Է� �ķ����� value�� total�� ���ϱ� 
	{
		if (score != total)
		{
			total += value;		  // ������ ���� �Է¹��� ���� ���մϴ�.!
		}
	}
	int getTotal()
	{
		return total;		  // total���� �����մϴ�.
	}

	void deallocate();

};
bool Singleton::instanceFlag = false;
Singleton* Singleton::instance = NULL;

void Singleton::deallocate()
{
	if (!instanceFlag) { return; }
	delete instance;
	instanceFlag = false;
	cout << "delete instnace, instance flag: " << instanceFlag << endl;
}

//����
struct TailLenght
{
	int lenght = 0;
};

struct UserName
{
	string user;
};

//struct ��� ����
class TailCharacter
{
public:
	TailLenght* TailL;
	UserName* UserN;

	int tail()
	{
		return TailL->lenght;
	}

	string name()
	{
		return UserN->user;
	}
};

//��ҵ鸸 ����
class TailBuilder
{
public:
	virtual TailLenght* CreateTail() = 0;
	virtual UserName* CreateUserName() = 0;
};

class TailDirector
{
	TailBuilder* tBuilder;
public:
	void SetBuilder(TailBuilder* mBuilder)
	{
		tBuilder = mBuilder;
	}

	TailCharacter* CreateCharacter()
	{
		TailCharacter* character = new TailCharacter();

		character->TailL = tBuilder->CreateTail();
		character->UserN = tBuilder->CreateUserName();

		return character;
	}
};

class FirstUser : public TailBuilder
{
public:
	TailLenght* CreateTail()
	{
		TailLenght* tailset = new TailLenght();
		tailset->lenght = nTail;
		return tailset;
	}
	UserName* CreateUserName()
	{
		UserName* nameset = new UserName();
		nameset->user = "���� �̸� YuYoungLee";
		return nameset;
	}
};

//������ Ÿ��
struct ContactName
{
	string copyname = "--------GOSU--------";
};


void Setup() {
	gameover = false;

	dir = STOP;

	x = width / 2;

	y = height / 2;

	fruitX = rand() % width;

	fruitY = rand() % height; score = 0;
}

void Draw() {
	system("cls");

	//�̱��� ����
	Singleton* ptr1;
	ptr1 = Singleton::getInstance();

	//���� ����
	TailCharacter* character;
	TailDirector director;

	FirstUser user;
	director.SetBuilder(&user);
	character = director.CreateCharacter();
	ptr1->cummulate(10);

	//������Ÿ�� ����
	ContactName copy1;
	ContactName copy2 = copy1;
	if (score >= 50)
	{
		cout << copy2.copyname << endl;
	}
	for (int i = 0; i < width + 2; i++)
	{
		cout << "-";						//��� ��
	}
	cout << endl;
	for (int i = 0; i < height; i++) {

		for (int j = 0; j < width; j++) {

			if (j == 0)

				cout << "|";				//���� ��

			if (i == y && j == x)

				cout << "*";				//�� ����

			else if (i == fruitY && j == fruitX)

				cout << "$";				//������

			else {

				bool print = false;

				for (int k = 0; k < nTail; k++) {

					if (tailX[k] == j && tailY[k] == i) {

						cout << "*"; print = true;

					}

				}

				if (!print) cout << " ";

			}

			if (j == width - 1)

				cout << "|";					//���� ��

		}

		cout << endl;

	}

	for (int i = 0; i < width + 2; i++)		//���� ���̸�ŭ
	{
		cout << "-";						//�ϴܺ�
	}
	cout << endl;

	cout << "����:" << score << endl;
	cout << "�̱���- " << ptr1->getTotal() << endl;
	cout << "����- " << character->tail() << endl;
	cout << "����- " << character->name() << endl;
}

void Input()
{
	if (_kbhit()) {

		switch (_getch()) {

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

		case 'x':
			gameover = true;

			break;

		}

	}

}

void algorithm()
{

	int prevX = tailX[0];

	int prevY = tailY[0];

	int prev2X, prev2Y;

	tailX[0] = x;

	tailY[0] = y;

	for (int i = 1; i < nTail; i++) {

		prev2X = tailX[i];

		prev2Y = tailY[i];

		tailX[i] = prevX;

		tailY[i] = prevY;

		prevX = prev2X;

		prevY = prev2Y;

	}

	switch (dir) {

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

	if (x >= width) x = 0; else if (x < 0) x = width - 1;

	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < nTail; i++)

		if (tailX[i] == x && tailY[i] == y)
			gameover = true;

	if (x == fruitX && y == fruitY) {

		score += 10;

		fruitX = rand() % width;

		fruitY = rand() % height;

		nTail++;

	}

}

int main()
{
	int scorecopy = 0;
	Setup();

	while (!gameover) {

		Draw();

		Input();

		algorithm();
	}
	return 0;

}