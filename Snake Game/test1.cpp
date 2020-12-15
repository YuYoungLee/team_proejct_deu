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

//싱글톤
class Singleton {
private:
	Singleton() :total(0) { cout << "private 생성자, Instance Falg:" << instanceFlag << endl; };	// 생성자가 private member 함수

	static bool instanceFlag;
	static Singleton* instance;
	int total;
public:

	static Singleton* getInstance()
	{
		if (!instance) 
		{
			cout << "생성자 실행 및 인스턴스 할당" << endl;
			instanceFlag = true;
			instance = new Singleton();
		}
		return instance;
	}
	~Singleton()
	{
		cout << "public 소멸자" << endl;
	}

	void cummulate(int value) 		  // 입력 파러미터 value를 total에 더하기 
	{
		if (score != total)
		{
			total += value;		  // 변수를 통해 입력받은 값을 더합니다.!
		}
	}
	int getTotal()
	{
		return total;		  // total값을 리턴합니다.
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

//빌더
struct TailLenght
{
	int lenght = 0;
};

struct UserName
{
	string user;
};

//struct 요소 포함
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

//요소들만 포함
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
		nameset->user = "유저 이름 YuYoungLee";
		return nameset;
	}
};

//프로토 타입
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

	//싱글톤 선언
	Singleton* ptr1;
	ptr1 = Singleton::getInstance();

	//빌더 선언
	TailCharacter* character;
	TailDirector director;

	FirstUser user;
	director.SetBuilder(&user);
	character = director.CreateCharacter();
	ptr1->cummulate(10);

	//프로토타입 선언
	ContactName copy1;
	ContactName copy2 = copy1;
	if (score >= 50)
	{
		cout << copy2.copyname << endl;
	}
	for (int i = 0; i < width + 2; i++)
	{
		cout << "-";						//상단 벽
	}
	cout << endl;
	for (int i = 0; i < height; i++) {

		for (int j = 0; j < width; j++) {

			if (j == 0)

				cout << "|";				//왼쪽 벽

			if (i == y && j == x)

				cout << "*";				//뱀 꼬리

			else if (i == fruitY && j == fruitX)

				cout << "$";				//아이탬

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

				cout << "|";					//우측 벽

		}

		cout << endl;

	}

	for (int i = 0; i < width + 2; i++)		//가로 길이만큼
	{
		cout << "-";						//하단벽
	}
	cout << endl;

	cout << "점수:" << score << endl;
	cout << "싱글톤- " << ptr1->getTotal() << endl;
	cout << "빌더- " << character->tail() << endl;
	cout << "빌더- " << character->name() << endl;
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