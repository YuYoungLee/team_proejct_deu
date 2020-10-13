//���� ����. ���� ������ ��ҵ��� ������ �ʿ��� ��ü�� �����ؾ� �ϰų�
//�������� �پ��� ��ü ������ �����ؾ� �� �� ����ü �������� �����ϴ� ������Ʈ�� ����
//��ü ������ �����ϰ� �ϴ� ��

#include <iostream>
using namespace std;


//struct�� ��� public ����
//���� �ؼ���
struct Weapon
{
	int mPower;
};

struct Armor
{
	int mDefence;
};
//�ɸ��� Ŭ���� ���Կ��
//struct �Ƹ�, ������ �ּ�

class Character
{
public:
	Weapon* mWeapon;
	Armor* mArmor;

	//�ش� ĳ������(��ü) �ּҸ� ���� �������
	void DisplayParts()
	{
		cout << "Weapon power" << mWeapon->mPower << endl;
		cout << "Armor defence" << mWeapon->mPower << endl;
	}
};
//����� �Ƹ��� ������ �ּҸ� ���� ����
class CharacterBuilder
{
public:
	//virtual �� ���, ������
	virtual Weapon* CreateWeapon() = 0;
	virtual Armor * CreateArmor() = 0;
};

class CharacterDirector
{
	//Character has - a���� CharacterDirector
	//character ��ü�� �ּҸ� ���� �ɸ����� ����� �Ƹ�, ������ ������ ����.
	CharacterBuilder* mBuilder;
public:

	//����, ������ Ŭ������ �ּҸ� �޾� ��ü ����
	void SetBuilder(CharacterBuilder* newBuilder)
	{
		mBuilder = newBuilder;
	}

	//ĳ���� Ŭ������ ����ϴ� ��� Ŭ������ ĳ���� Ŭ�������� �ٶ󺸰� ��
	Character* CreateCharacter()
	{
		//�ɸ��� Ŭ������ ���� ��ü�� ���� 
		Character* character = new Character();

		character->mWeapon = mBuilder->CreateWeapon();
		character->mArmor = mBuilder->CreateArmor();

		return character;
	}
};

//��� is - a����, ���� ������ Ŭ����
//��ó�� �ɸ��ʹ�.
//�ɸ��͸� ����� ������ �����Ͽ� �ɸ����� ��� ����, �Ƹ��� ������ ����
class ArcherBuilder : public CharacterBuilder
{
public:
	Weapon* CreateWeapon()
	{
		Weapon* weapon = new Weapon();	//��ó ��ü���� ������ ��ü
		weapon->mPower = 200;			//������ ����
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
	Character* character; //Ŭ���� �����͸� ���� ��ü(�ɸ���)�� �ּ�����

	CharacterDirector director;	//�������� ��ü
	//Ŭ���� �ɸ����� ��ü�� �����
	//�ɸ����� ��ü�� �ּҸ� ������, ��ó, �������� ����, ���� ���ݷ��� ������ ������.

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