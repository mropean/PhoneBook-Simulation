#include "phoneBook.h"

int main() {
	phonebook pb; int num = 0;
	pb.file_Load();
	while (num != 5) {
		cout << "==========================================" << endl;
		cout << "1. ��ȭ��ȣ �߰�" << endl;
		cout << "2. ��ȭ��ȣ ����" << endl;
		cout << "3. ��ȭ��ȣ �˻�" << endl;
		cout << "4. ����� ��ȭ��ȣ ���" << endl;
		cout << "5. ���α׷� ����" << endl;
		cout << "==========================================" << endl;
		cout << "�����ϰ� ���� ��ȣ�� �Է��� �ּ���>> "; cin >> num;
		switch (num) {
		case 1: {	// �߰�
			pb.Add_Member();
			break;
		}
		case 2: {	// ����
			pb.Delete_Member();
			break;
		}
		case 3: {	// �˻�
			pb.Search_Member();
			break;
		}
		case 4: {	// ���
			pb.print_list();
			break;
		}
		case 5:		// ����
			break;

		default: {
			cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
			cin.clear();	// �Է¹��� ����
			cin.ignore(INT_MAX, '\n');	// �߸��� �Է��� ��� ���۸� ��� ���ѹݺ��� �����Ѵ�.
		}
		}
		
		
	}
	pb.file_Save();
	return 0;
}