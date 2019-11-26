#include "phoneBook.h"

int main() {
	phonebook pb; int num = 0;
	pb.file_Load();
	while (num != 5) {
		cout << "==========================================" << endl;
		cout << "1. 전화번호 추가" << endl;
		cout << "2. 전화번호 삭제" << endl;
		cout << "3. 전화번호 검색" << endl;
		cout << "4. 저장된 전화번호 출력" << endl;
		cout << "5. 프로그램 종료" << endl;
		cout << "==========================================" << endl;
		cout << "실행하고 싶은 번호를 입력해 주세요>> "; cin >> num;
		switch (num) {
		case 1: {	// 추가
			pb.Add_Member();
			break;
		}
		case 2: {	// 삭제
			pb.Delete_Member();
			break;
		}
		case 3: {	// 검색
			pb.Search_Member();
			break;
		}
		case 4: {	// 출력
			pb.print_list();
			break;
		}
		case 5:		// 종료
			break;

		default: {
			cout << "잘못 입력하셨습니다." << endl;
			cin.clear();	// 입력버퍼 비우기
			cin.ignore(INT_MAX, '\n');	// 잘못된 입력일 경우 버퍼를 비워 무한반복을 예방한다.
		}
		}
		
		
	}
	pb.file_Save();
	return 0;
}