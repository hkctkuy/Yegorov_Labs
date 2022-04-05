#include<iostream>

using namespace std;
class Account {
protected:
	int cardNumber;
	char* name;
	char* timeCreate;
	double balance;
	int references = 0;
	static const int max_balance = 999999;
public:

	Account() {
		balance = 0;
		cardNumber = 0;
		name = new char[20];
		timeCreate = new char[20];
	}

	Account(const char n[], const char s[], int number, double money) {
		balance = money;
		cardNumber = number;
		name = new char[20];
		timeCreate = new char[20];
		for (int i = 0; i < 21; i++) {
			if ((n[i] == 0) || (i == 20)) {
				name[i] = 0;
				break;
			}
			name[i] = n[i];
		}
		for (int i = 0; i < 21; i++) {
			if ((s[i] == 0) || (i == 20)) {
				timeCreate[i] = 0;
				break;
			}
			timeCreate[i] = s[i];
		}
	}

	Account(const Account& sc) {
		balance = sc.balance;
		cardNumber = sc.cardNumber;
		name = new char[20];
		timeCreate = new char[20];
		for (int i = 0; i < 21; i++) {
			if ((sc.name[i] == 0) || (i == 20)) {
				name[i] = 0;
				break;
			}
			name[i] = sc.name[i];
		}
		for (int i = 0; i < 21; i++) {
			if ((sc.timeCreate[i] == 0) || (i == 20)) {
				timeCreate[i] = 0;
				break;
			}
			timeCreate[i] = sc.timeCreate[i];
		}
	}
	static int get_max_balance() {
		return max_balance;
	}

	Account& operator= (const Account& sc) {
		if (this != &sc) {
			for (int i = 0; i < 21; i++) {
				if ((sc.name[i] == 0) || (i == 20)) {
					name[i] = 0;
					break;
				}
				name[i] = sc.name[i];
			}
			for (int i = 0; i < 21; i++) {
				if ((sc.timeCreate[i] == 0) || (i == 20)) {
					timeCreate[i] = 0;
					break;
				}
				timeCreate[i] = sc.timeCreate[i];
			}
		}
		return *this;
	}

	virtual const double checkBalance() = 0;
	virtual void deposit(int money) = 0;
	virtual void withdraw(int money) = 0;

	friend ostream& operator<< (ostream& out, const Account& sc) {
		out << sc.name << ' ' << sc.timeCreate << ' ' << sc.cardNumber << ' ' << sc.balance;
		return out;
	}

	const double& operator()(int percent, int years) const
	{
		double money = balance;
		for (int i = 0; i < years; i++) {
			money = money * (1 + percent / 100);
		};
		return money;
	}

	int depositQuantity() {
		return references;
	}

	~Account() {
		delete[] name;
		delete[] timeCreate;
	}

};

class physAccount : public Account
{
public:

	physAccount() {}

	physAccount(const char n[], const char s[], int number, double money) : Account(n, s, number, money) {}

	const double checkBalance() {
		return balance;
	}

	void deposit(int money) {
		static int i = 0;
		i++;
		references = i;
		balance += money;
	}

	void withdraw(int money) {
		if (money > balance) {
			cout << "Недостаточно средств" << endl;
			return;
		}
		balance -= money;
	}
};

class jurAccount : public Account
{
private:
	char* companyName;
	double fee;
public:

	jurAccount() {
		companyName = new char[20];
		fee = 10;
	}

	jurAccount(const char cn[], const char n[], const char s[], int number, double money) : Account(n, s, number, money) {
		companyName = new char[20];
		fee = 10;
		for (int i = 0; i < 21; i++) {
			if ((cn[i] == 0) || (i == 20)) {
				companyName[i] = 0;
				break;
			}
			companyName[i] = cn[i];
		}
	}

	friend ostream& operator<< (ostream& out, const jurAccount& sc) {
		out << sc.companyName << ' ' << sc.name << ' ' << sc.timeCreate << ' ' << sc.cardNumber << ' ' << sc.balance;
		return out;
	}

	const double checkBalance() {
		return balance;
	}

	void deposit(int money) {
		static int i = 0;
		i++;
		references = i;
		balance += money * (1 - fee / 100);
	}

	void withdraw(int money) {
		if (money > balance * (1 - fee / 100)) {
			cout << "Недостаточно средств" << endl;
			return;
		}
		balance -= money;
	}

	~jurAccount() {
		delete[] companyName;
	}
};

int main() {
	jurAccount acc1("qweqw", "asda", "sada", 12, 12);
	physAccount acc2("sdf", "sad", 13, 13);
	acc2.deposit(15);
	acc1.withdraw(12);
	acc1.withdraw(10);
	cout << acc1 << endl;
	cout << acc2 << endl;
	return 0;
}