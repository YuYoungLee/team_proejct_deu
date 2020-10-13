//빌더 패턴. 여러 복잡한 요소들의 조합이 필요한 객체를 생성해야 하거나
//여러개의 다양한 객체 집합을 생성해야 할 때 개개체 생성만을 전담하는 컴포넌트를 정의
//객체 생성을 간편하게 하는 것

#include <iostream>
using namespace std;


//struct를 사용 public 형태
//관계 해석중
struct Weapon
{
	int mPower;
};

struct Armor
{
	int mDefence;
};
//케릭터 클래스 포함요소
//struct 아머, 웨폰의 주소

class Character
{
public:
	Weapon* mWeapon;
	Armor* mArmor;

	//해당 캐릭터의(객체) 주소를 통해 정보출력
	void DisplayParts()
	{
		cout << "Weapon power" << mWeapon->mPower << endl;
		cout << "Armor defence" << mWeapon->mPower << endl;
	}
};
//무기와 아머의 정보를 주소를 통해 참조
class CharacterBuilder
{
public:
	//virtual 을 사용, 공부중
	virtual Weapon* CreateWeapon() = 0;
	virtual Armor * CreateArmor() = 0;
};

class CharacterDirector
{
	//Character has - a관계 CharacterDirector
	//character 객체는 주소를 통해 케릭터의 요소인 아머, 무기의 정보가 담긴다.
	CharacterBuilder* mBuilder;
public:

	//아쳐, 워리어 클래스의 주소를 받아 객체 생성
	void SetBuilder(CharacterBuilder* newBuilder)
	{
		mBuilder = newBuilder;
	}

	//캐릭터 클래스를 상속하는 모든 클래스는 캐릭터 클래스만을 바라보게 됨
	Character* CreateCharacter()
	{
		//케릭터 클래스를 통해 객체를 생성 
		Character* character = new Character();

		character->mWeapon = mBuilder->CreateWeapon();
		character->mArmor = mBuilder->CreateArmor();

		return character;
	}
};

//상속 is - a관계, 아쳐 워리어 클래스
//아처는 케릭터다.
//케릭터를 만드는 빌더를 참조하여 케릭터의 요소 무기, 아머의 값들을 설정
class ArcherBuilder : public CharacterBuilder
{
public:
	Weapon* CreateWeapon()
	{
		Weapon* weapon = new Weapon();	//아처 객체안의 무기의 객체
		weapon->mPower = 200;			//무기의 정보
		return weapon;
	}

	Armor* CreateArmor()
	{
		Armor* armor = new Armor();
		armor->mDefence = 200;
		return armor;
	}
};

class WarriorBuilder : public CharacterBuilder
{
public:
	Weapon* CreateWeapon()
	{
		Weapon* weapon = new Weapon();
		weapon->mPower = 200;
		return weapon;
	}

	Armor* CreateArmor()
	{
		Armor* armor = new Armor();
		armor->mDefence = 200;
		return armor;
	}
};

int main()
{
	Character* character; //클래스 포인터를 통해 객체(케릭터)의 주소참조

	CharacterDirector director;	//감독자의 객체
	//클래스 케릭터의 객체를 만들기
	//케릭터의 객체의 주소를 가지고, 아처, 워리어의 정보, 방어력 공격력의 정보를 가진다.

	ArcherBuilder archer;
	director.SetBuilder(&archer);
	character = director.CreateCharacter();
	character->DisplayParts();

	WarriorBuilder warrior;
	director.SetBuilder(&warrior);
	character = director.CreateCharacter();
	character->DisplayParts();

	return 0;
}