#include "phoneBook.h"

long file_Size(ifstream& file) {
	file.seekg(0, ios::end);
	long length = file.tellg();
	return length;
}

phonebook::phonebook() {
	count = 0;
	head = new lists;
	init(head);
}
void phonebook::count_increase() { count++; }	// ��ȭ��ȣ�� �ο��� ����
void phonebook::count_decrease() { count--; }	// ��ȭ��ȣ�� �ο��� ����
void phonebook::init(lists* phead) { // ����� �ʱ�ȭ
	phead->data.name = phead->data.nickname = phead->data.number = { NULL };
	phead->llink = phead;
	phead->rlink = phead;
}

//****************************************** ��Ŭ���� ��� ���� �ǵ帮��� *******************************************************//
//****************************************** ��Ŭ���� ��� �Լ� �ǵ帮��� *******************************************************//

void phonebook::Add_Member() {	// ���ο� �����͸� ��� newnode�� �����ʿ� �����Ѵ�.
	lists* newnode = new lists;	// ���ο� ��� ����
	sdata* tmp = new sdata; // ����ü: �����Ͱ��� ������ �뵵
	int check = 0;
	cout << "==========================================" << endl;
	cout << "�̸�: "; cin >> tmp->name; // Ư������, ���� �� �̸��� �ƴ� ���ڰ� �ԷµǾ����� ����
	if (checking_name(tmp->name) == false) {
		delete newnode, tmp;
		return;
	}
	cout << "��ȭ��ȣ: "; cin >> tmp->number;	//  ���ڰ� �ƴ� ���ڰ� �ԷµǾ����� ����
	if (checking_number(tmp->number) == false) {
		delete newnode, tmp;
		return;
	}
	cout << "����: >>"; cin >> tmp->nickname;	// ������ ���� �ʿ����� ���� �Էµ� �����Ͱ� �ƴ϶�� ó������ ����
	
	cout << "==========================================" << endl;
	cout << "�Է��Ͻ� ����" << endl;
	cout << "�̸�: \t" << tmp->name << endl;
	cout << "��ȭ��ȣ: " << tmp->number << endl;
	cout << "����: \t" << tmp->nickname << endl;
	cout << "==========================================" << endl;
	
	cout << "�� ������ �����ôٸ� 1���� Ʋ���̴ٸ� 2���� �Է����ּ���." << endl;
	cout << ">> "; cin >> check;
	if (check == 2) {
		delete newnode, tmp;
		cout << "�޴��� ���ư��ϴ�." << endl;
		return;
	}
	else if (check != 1 && check != 2) {			// 1, 2���� �ƴ� ��� �Լ� ����
		cout << "1�� �Ǵ� 2���� �Է����ּž� �մϴ�. �޴��� ���ư��ϴ�..." << endl;
		delete newnode, tmp;
		return;
	}

	newnode->data.name = tmp->name;
	newnode->data.number = tmp->number;
	newnode->data.nickname = tmp->nickname;
	//  ������ ����ֱ� �ڵ�

	/* ���Ḯ��Ʈ�� �ּҸ� �������ִ� ��� */
	//����� ��ġ�� ������ �Լ�
	if (empty() == true) {	// ����Ʈ�� ����ִٸ�
		newnode->llink = head;
		newnode->rlink = head;
		// ���ο� ����� ���� ��ũ�� ������ ��ũ�� head�� �ּҰ����� ����

		head->llink = newnode;
		head->rlink = newnode;
		// ������� ���� ��ũ�� ������ ��ũ�� newnode�� �ּҰ����� ����
	}

	if (empty() == false) {	// ����Ʈ�� ������� �ʴٸ�
		lists* now;
		now = head;
		for (now = now->rlink; ; now = now->rlink) {
			int res = newnode->data.name.compare(now->data.name);
			if (res < 0) {	// �տ� ��庸�� ���������� �տ��ý�
				if (now->llink == head) {	// �ճ�尡 ó����� �Ͻ�
					newnode->llink = now->llink;
					newnode->rlink = now->llink->rlink;
					now->llink->rlink = newnode;
					now->llink = newnode;
					break;
				}	// �װ� �ƴ϶��
				// �տ� ���� ���� ��带 ���ο� ��忡�� �������ش�
				newnode->rlink = now->llink->rlink;
				newnode->llink = now->llink;
				now->llink->rlink = newnode;
				now->llink = newnode;
				break;
			}
			else if (res > 0 && now->rlink == head) {	// �տ� ��庸�� ���������� �ڿ����� �����ϸ� ������ �� �ڿ��� ��带 ����ų��
				newnode->rlink = now->rlink;
				newnode->llink = now->rlink->llink;
				now->rlink->llink = newnode;
				now->rlink = newnode;
				break;
			}

		}

	}

	count_increase(); // ��� �߰��Ǿ����� �˼��ְ��ϴ� count ���� ������ �Լ�
	delete tmp;
}

bool phonebook::empty() {
	if (count == 0) // ����� ���������Ͱ� ������ �ּҰ��� �����������Ͱ� ������ �ּҰ��� ������
		return true;	// ��������Ƿ� true ����
	else return false;	// ������� ������ false ����
}

bool phonebook::checking_name(string String) {		// �̸� ���ڿ� Ȯ��
	int size = String.length();		// ���ڿ��� ���̷� �ʱ�ȭ
	for (int repeat = 0, ask_num = 0; repeat < size; repeat++) {	// �̸��� ��� �������� ����ڿ��� ����� ��� �Է��� ��ٸ�
																	// ����� �� ������ ������ ��������ϴ� �����, �׷��Ƿ� �ѱ۸� �Է¹ٶ�
		if (String[repeat] >= (char)65 && String[repeat] <= (char)90 || String[repeat] >= (char)97 && String[repeat] <= (char)122) {
			cout << "�̸��� ��� �� �ֽ��ϴ�. �״�� ���� �մϱ�?" << endl;
			cout << "�� ���� : " << String[repeat] << endl;
			cout << "1. ��" << " 2. �ƴϿ�(�޴���)" << endl;
			cout << ">> "; cin >> ask_num;
			if (ask_num == 2) return false;
		}
	}
	for (int repeat = 0, ask_num = 0; repeat < size; repeat++) {	// ���ڿ� Ư�����ڰ� �� ������ false�����Ͽ� ��ȭ��ȣ�� ����
		if (String[repeat] >= (char)33 && String[repeat] <= 64 || String[repeat] >= 91 && String[repeat] <= 96 || String[repeat] >= 123 && String[repeat] <= 126) {
			cout << "���ڿ��� ���� �Ǵ� Ư�����ڰ� ���ֽ��ϴ�." << endl;
			return false;
		}
	}
	return true; 
}

bool phonebook::checking_number(string String) {		// ��ȭ��ȣ ���ڿ� Ȯ��
	lists* now;
	now = head;
	int size = String.length();
	for (int repeat = 0, ask_num = 0; repeat < size; repeat++) {
		if (!(String[repeat] >= (char)48 && String[repeat] <= (char)57)) {	// 
			cout << "��ȭ��ȣ�� ���ڰ��ƴ� �ٸ����ڰ� �ԷµǾ����ϴ� �ٽ� �õ��� �ֽʽÿ�." << endl;
			return false;
		}
	}
	for (int i = 0, index = 0; i < count; i++) {
		if ((index = now->data.number.find(String)) != -1) {
			cout << "��ȭ��ȣ�� �ȿ� ������ ��ȭ��ȣ�� �ֽ��ϴ�. �ٽ� �õ��� �ֽʽÿ�." << endl;
			return false;
		}
		now = now->rlink;
	}
	return true;
}

//****************************************** ��Ŭ���� ����Լ� "�߰�" �� ���õ� �Լ���� ********************************************************************//
//****************************************** ��Ŭ���� ����Լ� "����"�� "�˻�"�� �ʿ��� 'Ž��' �Լ��� *******************************************************//
lists* phonebook::Explore(string ckecking, int num) {
	lists* now, * find[20];		// find ������ �迭�� ã�� �̸��� ��ĥ�� �� �ε��� ��ȣ�� �ּҰ� ���� 0�� �ε����� ����
	int index, find_index, find_accept, ask_num, repeat = 0;
	now = head;
	switch (num) {
	case 1: {
		cout << "==========================================" << endl;
		cout << "�̸����� �˻��� �����մϴ�." << endl;
		cout << "�˻��� �̸��� �������� ����Դϴ�. ���ϴ� ��ȣ�� �����Ͽ� �ּ���." << endl;
		for (find_index = 1, find_accept = 1, now = now->rlink; repeat < count; repeat++) {
			index = now->data.name.find(ckecking);
			if (index != -1) {
				find[find_index] = now;
				cout << find_accept << "." << "�̸�: " << now->data.name << "\t��ȭ��ȣ: " << now->data.number << "\t����: " << now->data.nickname << endl;
				find_index++; find_accept++;
			}
			now = now->rlink;
		}
		cin >> ask_num;
		cout << "==========================================" << endl;
		if ((index = find[ask_num]->data.name.size()) == 0) {
			cout << "�߸��� ��ȣ�� �Է��ϼ̽��ϴ�. ���α׷��� �����ϰڽ��ϴ�." << endl; exit(1);
		}
		cout << "�����Ͻ� ��ȣ�� �����ʹ� �Ʒ��� �����ϴ�." << endl;
		cout << find[ask_num]->data.name << " " << find[ask_num]->data.number << " " << find[ask_num]->data.nickname << endl;
		return find[ask_num];
	}
	case 2: {
		cout << "==========================================" << endl;
		cout << "��ȭ��ȣ�� �˻��� �����մϴ�." << endl;
		cout << "�˻��� ��ȭ��ȣ�� �������� ����Դϴ�. ���ϴ� ��ȣ�� �����Ͽ� �ּ���." << endl;
		for (find_index = 1, find_accept = 1, now = now->rlink; repeat < count; repeat++) {
			index = now->data.number.find(ckecking);
			if (index != -1) {
				find[find_index] = now;
				cout << find_accept << "." << "�̸�: " << now->data.name << "\t��ȭ��ȣ: " << now->data.number << "\t����: " << now->data.nickname << endl;
				find_index++; find_accept++;
			}
			now = now->rlink;
		}
		cin >> ask_num;
		cout << "==========================================" << endl;
		if ((index = find[ask_num]->data.name.size()) == 0) {
			cout << "�߸��� ��ȣ�� �Է��ϼ̽��ϴ�. ���α׷��� �����ϰڽ��ϴ�." << endl; exit(1);
		}
		cout << "�����Ͻ� ��ȣ�� �����ʹ� �Ʒ��� �����ϴ�." << endl;
		cout << find[ask_num]->data.name << " " << find[ask_num]->data.number << " " << find[ask_num]->data.nickname << endl;
		return find[ask_num];
	}
	case 3: {
		cout << "==========================================" << endl;
		cout << "�������� �˻��� �����մϴ�." << endl;
		cout << "�˻��� ����� �������� ����Դϴ�. ���ϴ� ��ȣ�� �����Ͽ� �ּ���." << endl;
		for (find_index = 1, find_accept = 1, now = now->rlink; repeat < count; repeat++) {
			index = now->data.nickname.find(ckecking);
			if (index != -1) {
				find[find_index] = now;
				cout << find_accept << "." << "�̸�: " << now->data.name << "\t��ȣ: " << now->data.number << "\t����: " << now->data.nickname << endl;
				find_index++; find_accept++;
			}
			now = now->rlink;
		}
		cin >> ask_num;
		cout << "==========================================" << endl;
		if ((index = find[ask_num]->data.name.size()) == 0) {
			cout << "�߸��� ��ȣ�� �Է��ϼ̽��ϴ�. ���α׷��� �����ϰڽ��ϴ�." << endl; exit(1);
		}
		cout << "�����Ͻ� ��ȣ�� �����ʹ� �Ʒ��� �����ϴ�." << endl;
		cout << find[ask_num]->data.name << " " << find[ask_num]->data.number << " " << find[ask_num]->data.nickname << endl;
		return find[ask_num];
	}
	}
}
//****************************************** ��Ŭ���� ����Լ� "����"�� "�˻�" �Լ��� *******************************************************//

void phonebook::Delete_Member() {
	int how;
	string what;
	lists* del;
	cout << "==========================================" << endl;
	cout << "� ������� ã�⸦ ���� �Ͻðڽ��ϱ�?" << endl;
	cout << "1. �̸�" << " 2. ��ȣ" << " 3. ����" << endl;
	cout << ">> "; cin >> how;
	cout << "==========================================" << endl;
	if (how == 1) {
		cout << "==========================================" << endl;
		cout << "������ ���ϴ� �̸��� �Է����ּ���: ";	cin >> what;
		if (checking_name(what) == false) {
			return;
		}
		del = Explore(what, how);
		del->llink->rlink = del->rlink;
		del->rlink->llink = del->llink;
		delete del;
		cout << "�����Ǿ����ϴ�." << endl;
		count_decrease();
		cout << "==========================================" << endl;
	}
	else if (how == 2) {
		cout << "==========================================" << endl;
		cout << "������ ���ϴ� ��ȣ�� �Է����ּ���: ";	cin >> what;
		if (checking_number(what) == false) {
			return;
		}
		del = Explore(what, how);
		del->llink->rlink = del->rlink;
		del->rlink->llink = del->llink;
		delete del;
		cout << "�����Ǿ����ϴ�." << endl;
		count_decrease();
		cout << "==========================================" << endl;
	}
	else if (how == 3) {
		cout << "==========================================" << endl;
		cout << "������ ���ϴ� ������ �Է����ּ���: ";	cin >> what;
		del = Explore(what, how);
		del->llink->rlink = del->rlink;
		del->rlink->llink = del->llink;
		delete del;
		cout << "�����Ǿ����ϴ�." << endl;
		count_decrease();
		cout << "==========================================" << endl;
	}
	else {
		cout << "�߸� �Է��ϼ̽��ϴ�. �޴��� ���ư��ϴ�." << endl;
		return;
	}
}

void phonebook::Search_Member() {
	int how;
	string what;
	lists* search;
	cout << "==========================================" << endl;
	cout << "� ������� ã�⸦ ���� �Ͻðڽ��ϱ�?" << endl;
	cout << "1. �̸�" << " 2. ��ȣ" << " 3. ����" << endl;
	cout << ">> "; cin >> how;
	if (how == 1) {
		cout << "==========================================" << endl;
		cout << "�˻��� ���ϴ� �̸��� �Է��� �ּ���" << endl; cin >> what;
		if (checking_name(what) == false) {
			return;
		}
		search = Explore(what, how);
		cout << "==========================================" << endl;
		cout << "�˻��� �Ϸ�Ǿ����ϴ�" << endl;
		cout << "�̸�: " << search->data.name << endl;
		cout << "��ȣ: " << search->data.number << endl;
		cout << "����: " << search->data.nickname << endl;
		cout << "==========================================" << endl;
		return;
	}
	else if (how == 2) {
		cout << "==========================================" << endl;
		cout << "�˻��� ���ϴ� ��ȣ�� �Է��� �ּ���" << endl; cin >> what;
		if (checking_number(what) == false) {
			return;
		}
		search = Explore(what, how);
		cout << "==========================================" << endl;
		cout << "�˻��� �Ϸ�Ǿ����ϴ�" << endl;
		cout << "�̸�: " << search->data.name << endl;
		cout << "��ȣ: " << search->data.number << endl;
		cout << "����: " << search->data.nickname << endl;
		cout << "==========================================" << endl;
		return;
	}
	else if (how == 3) {
		cout << "==========================================" << endl;
		cout << "�˻��� ���ϴ� ������ �Է��� �ּ���" << endl; cin >> what;
		search = Explore(what, how);
		cout << "==========================================" << endl;
		cout << "�˻��� �Ϸ�Ǿ����ϴ�" << endl;
		cout << "�̸�: " << search->data.name << endl;
		cout << "��ȣ: " << search->data.number << endl;
		cout << "����: " << search->data.nickname << endl;
		cout << "==========================================" << endl;
		return;
	}
	else {
		cout << "�߸� �Է��ϼ̽��ϴ�. �޴��� ���ư��ϴ�." << endl;
		return;
	}
}

//****************************************** ��Ŭ���� ����Լ� "���" �Լ��� *******************************************************//

void phonebook::print_list() {
	lists* now;
	cout << "==========================================" << endl;
	cout << "�� �ο�: " << count << "��" << endl;
	now = head;
	now = now->rlink;
	for (int i = 0; i < count; i++) {
		cout << now->data.name << "\t" << now->data.number << "\t" << now->data.nickname << endl;
		now = now->rlink;
	}
}

void phonebook::file_Load() {
	const char* file = "phonebook.txt";
	ifstream Read(file);
	lists* now, * newnode;
	now = head;
	if (file_Size(Read) <= 0) {	// ������ ����ְų� ������ (0 �Ǵ� -1�̸�)
		cout << "�ҷ��� ������ �����ϴ�. ���� �ۼ��մϴ�." << endl;
		return;					// �ҷ��� �����Ͱ� ������ ����
	}
	
	Read.seekg(0, ios::beg);
	while (!Read.eof()) {
		newnode = new lists;
		now->rlink = newnode;
		newnode->llink = now;
		Read >> newnode->data.name;
		Read >> newnode->data.number;
		Read >> newnode->data.nickname;
		now = now->rlink;
		count_increase();
	}
	now->rlink = head;
	cout << "������ �ҷ��Խ��ϴ�." << endl;
	cout << "��¸޴��� ������ Ȯ���� �ֽñ� �ٶ��ϴ�." << endl;
}

void phonebook::file_Save() {
	ofstream save("phonebook.txt");
	lists* now, * before;
	int index, find_index, find_accept, ask_num, repeat = 0;
	now = head;
	now = now->rlink;
	save << endl;
	cout << "�����͵��� \"phonebook.txt\" ���Ͽ� ����Ǿ����ϴ�." << endl;
	for (int i = 0; i < count; i++) {
		if (i == (count - 1)) {
			save << now->data.name << " " << now->data.number << " " << now->data.nickname;
			before = now;
			now = now->rlink;
			delete before;
			return;
		}
		save << now->data.name << " " << now->data.number << " " << now->data.nickname << endl;
		before = now;
		now = now->rlink;
		delete before;
	}
}

phonebook::~phonebook() { delete head; }