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
void phonebook::count_increase() { count++; }	// 전화번호부 인원수 증가
void phonebook::count_decrease() { count--; }	// 전화번호부 인원수 감소
void phonebook::init(lists* phead) { // 헤드노드 초기화
	phead->data.name = phead->data.nickname = phead->data.number = { NULL };
	phead->llink = phead;
	phead->rlink = phead;
}

//****************************************** ↑클래스 멤버 변수 건드리기↑ *******************************************************//
//****************************************** ↓클래스 멤버 함수 건드리기↓ *******************************************************//

void phonebook::Add_Member() {	// 새로운 데이터를 노드 newnode의 오른쪽에 삽입한다.
	lists* newnode = new lists;	// 새로운 노드 생성
	sdata* tmp = new sdata; // 구조체: 데이터값을 복사할 용도
	int check = 0;
	cout << "==========================================" << endl;
	cout << "이름: "; cin >> tmp->name; // 특수문자, 숫자 등 이름이 아닌 문자가 입력되었을시 종료
	if (checking_name(tmp->name) == false) {
		delete newnode, tmp;
		return;
	}
	cout << "전화번호: "; cin >> tmp->number;	//  숫자가 아닌 문자가 입력되었을시 종료
	if (checking_number(tmp->number) == false) {
		delete newnode, tmp;
		return;
	}
	cout << "별명: >>"; cin >> tmp->nickname;	// 별명은 딱히 필요하지 않음 입력된 데이터가 아니라면 처음부터 시작
	
	cout << "==========================================" << endl;
	cout << "입력하신 정보" << endl;
	cout << "이름: \t" << tmp->name << endl;
	cout << "전화번호: " << tmp->number << endl;
	cout << "별명: \t" << tmp->nickname << endl;
	cout << "==========================================" << endl;
	
	cout << "위 정보가 맞으시다면 1번을 틀리셨다면 2번을 입력해주세요." << endl;
	cout << ">> "; cin >> check;
	if (check == 2) {
		delete newnode, tmp;
		cout << "메뉴로 돌아갑니다." << endl;
		return;
	}
	else if (check != 1 && check != 2) {			// 1, 2번이 아닌 경우 함수 종료
		cout << "1번 또는 2번을 입력해주셔야 합니다. 메뉴로 돌아갑니다..." << endl;
		delete newnode, tmp;
		return;
	}

	newnode->data.name = tmp->name;
	newnode->data.number = tmp->number;
	newnode->data.nickname = tmp->nickname;
	//  데이터 집어넣기 코드

	/* 연결리스트의 주소를 설정해주는 방법 */
	//노드의 위치를 결정할 함수
	if (empty() == true) {	// 리스트가 비어있다면
		newnode->llink = head;
		newnode->rlink = head;
		// 새로운 노드의 왼쪽 링크와 오른쪽 링크를 head의 주소값으로 저장

		head->llink = newnode;
		head->rlink = newnode;
		// 헤드노드의 왼쪽 링크와 오른쪽 링크를 newnode의 주소값으로 저장
	}

	if (empty() == false) {	// 리스트가 비어있지 않다면
		lists* now;
		now = head;
		for (now = now->rlink; ; now = now->rlink) {
			int res = newnode->data.name.compare(now->data.name);
			if (res < 0) {	// 앞에 노드보다 사전순으로 앞에올시
				if (now->llink == head) {	// 앞노드가 처음노드 일시
					newnode->llink = now->llink;
					newnode->rlink = now->llink->rlink;
					now->llink->rlink = newnode;
					now->llink = newnode;
					break;
				}	// 그게 아니라면
				// 앞에 노드와 뒤의 노드를 새로운 노드에게 연결해준다
				newnode->rlink = now->llink->rlink;
				newnode->llink = now->llink;
				now->llink->rlink = newnode;
				now->llink = newnode;
				break;
			}
			else if (res > 0 && now->rlink == head) {	// 앞에 노드보다 사전순으로 뒤에갈시 무시하면 되지만 그 뒤에가 헤드를 가리킬시
				newnode->rlink = now->rlink;
				newnode->llink = now->rlink->llink;
				now->rlink->llink = newnode;
				now->rlink = newnode;
				break;
			}

		}

	}

	count_increase(); // 몇명 추가되었는지 알수있게하는 count 변수 증가용 함수
	delete tmp;
}

bool phonebook::empty() {
	if (count == 0) // 헤드의 왼쪽포인터가 가지는 주소값과 오른쪽포인터가 가지는 주소값이 같으면
		return true;	// 비어있으므로 true 리턴
	else return false;	// 비어있지 않으면 false 리턴
}

bool phonebook::checking_name(string String) {		// 이름 문자열 확인
	int size = String.length();		// 문자열의 길이로 초기화
	for (int repeat = 0, ask_num = 0; repeat < size; repeat++) {	// 이름에 영어가 들어가있을시 사용자에게 물어보고 결과 입력을 기다림
																	// 영어로 들어가 있을시 일일이 물어봐야하는 어려움, 그러므로 한글만 입력바람
		if (String[repeat] >= (char)65 && String[repeat] <= (char)90 || String[repeat] >= (char)97 && String[repeat] <= (char)122) {
			cout << "이름에 영어가 들어가 있습니다. 그대로 진행 합니까?" << endl;
			cout << "들어간 문자 : " << String[repeat] << endl;
			cout << "1. 예" << " 2. 아니오(메뉴로)" << endl;
			cout << ">> "; cin >> ask_num;
			if (ask_num == 2) return false;
		}
	}
	for (int repeat = 0, ask_num = 0; repeat < size; repeat++) {	// 숫자와 특수문자가 들어가 있을시 false리턴하여 전화번호부 종료
		if (String[repeat] >= (char)33 && String[repeat] <= 64 || String[repeat] >= 91 && String[repeat] <= 96 || String[repeat] >= 123 && String[repeat] <= 126) {
			cout << "문자열에 숫자 또는 특수문자가 들어가있습니다." << endl;
			return false;
		}
	}
	return true; 
}

bool phonebook::checking_number(string String) {		// 전화번호 문자열 확인
	lists* now;
	now = head;
	int size = String.length();
	for (int repeat = 0, ask_num = 0; repeat < size; repeat++) {
		if (!(String[repeat] >= (char)48 && String[repeat] <= (char)57)) {	// 
			cout << "전화번호에 숫자가아닌 다른문자가 입력되었습니다 다시 시도해 주십시오." << endl;
			return false;
		}
	}
	for (int i = 0, index = 0; i < count; i++) {
		if ((index = now->data.number.find(String)) != -1) {
			cout << "전화번호부 안에 동일한 전화번호가 있습니다. 다시 시도해 주십시오." << endl;
			return false;
		}
		now = now->rlink;
	}
	return true;
}

//****************************************** ↑클래스 멤버함수 "추가" 에 관련된 함수들↑ ********************************************************************//
//****************************************** ↓클래스 멤버함수 "삭제"와 "검색"에 필요한 '탐색' 함수↓ *******************************************************//
lists* phonebook::Explore(string ckecking, int num) {
	lists* now, * find[20];		// find 포인터 배열은 찾는 이름이 겹칠시 각 인덱스 번호로 주소값 저장 0번 인덱스는 생략
	int index, find_index, find_accept, ask_num, repeat = 0;
	now = head;
	switch (num) {
	case 1: {
		cout << "==========================================" << endl;
		cout << "이름으로 검색을 시작합니다." << endl;
		cout << "검색된 이름과 데이터의 목록입니다. 원하는 번호를 선택하여 주세요." << endl;
		for (find_index = 1, find_accept = 1, now = now->rlink; repeat < count; repeat++) {
			index = now->data.name.find(ckecking);
			if (index != -1) {
				find[find_index] = now;
				cout << find_accept << "." << "이름: " << now->data.name << "\t전화번호: " << now->data.number << "\t별명: " << now->data.nickname << endl;
				find_index++; find_accept++;
			}
			now = now->rlink;
		}
		cin >> ask_num;
		cout << "==========================================" << endl;
		if ((index = find[ask_num]->data.name.size()) == 0) {
			cout << "잘못된 번호를 입력하셨습니다. 프로그램을 종료하겠습니다." << endl; exit(1);
		}
		cout << "선택하신 번호의 데이터는 아래와 같습니다." << endl;
		cout << find[ask_num]->data.name << " " << find[ask_num]->data.number << " " << find[ask_num]->data.nickname << endl;
		return find[ask_num];
	}
	case 2: {
		cout << "==========================================" << endl;
		cout << "전화번호로 검색을 시작합니다." << endl;
		cout << "검색된 전화번호와 데이터의 목록입니다. 원하는 번호를 선택하여 주세요." << endl;
		for (find_index = 1, find_accept = 1, now = now->rlink; repeat < count; repeat++) {
			index = now->data.number.find(ckecking);
			if (index != -1) {
				find[find_index] = now;
				cout << find_accept << "." << "이름: " << now->data.name << "\t전화번호: " << now->data.number << "\t별명: " << now->data.nickname << endl;
				find_index++; find_accept++;
			}
			now = now->rlink;
		}
		cin >> ask_num;
		cout << "==========================================" << endl;
		if ((index = find[ask_num]->data.name.size()) == 0) {
			cout << "잘못된 번호를 입력하셨습니다. 프로그램을 종료하겠습니다." << endl; exit(1);
		}
		cout << "선택하신 번호의 데이터는 아래와 같습니다." << endl;
		cout << find[ask_num]->data.name << " " << find[ask_num]->data.number << " " << find[ask_num]->data.nickname << endl;
		return find[ask_num];
	}
	case 3: {
		cout << "==========================================" << endl;
		cout << "별명으로 검색을 시작합니다." << endl;
		cout << "검색된 별명과 데이터의 목록입니다. 원하는 번호를 선택하여 주세요." << endl;
		for (find_index = 1, find_accept = 1, now = now->rlink; repeat < count; repeat++) {
			index = now->data.nickname.find(ckecking);
			if (index != -1) {
				find[find_index] = now;
				cout << find_accept << "." << "이름: " << now->data.name << "\t번호: " << now->data.number << "\t별명: " << now->data.nickname << endl;
				find_index++; find_accept++;
			}
			now = now->rlink;
		}
		cin >> ask_num;
		cout << "==========================================" << endl;
		if ((index = find[ask_num]->data.name.size()) == 0) {
			cout << "잘못된 번호를 입력하셨습니다. 프로그램을 종료하겠습니다." << endl; exit(1);
		}
		cout << "선택하신 번호의 데이터는 아래와 같습니다." << endl;
		cout << find[ask_num]->data.name << " " << find[ask_num]->data.number << " " << find[ask_num]->data.nickname << endl;
		return find[ask_num];
	}
	}
}
//****************************************** ↓클래스 멤버함수 "삭제"와 "검색" 함수↓ *******************************************************//

void phonebook::Delete_Member() {
	int how;
	string what;
	lists* del;
	cout << "==========================================" << endl;
	cout << "어떤 방식으로 찾기를 시작 하시겠습니까?" << endl;
	cout << "1. 이름" << " 2. 번호" << " 3. 별명" << endl;
	cout << ">> "; cin >> how;
	cout << "==========================================" << endl;
	if (how == 1) {
		cout << "==========================================" << endl;
		cout << "삭제를 원하는 이름을 입력해주세요: ";	cin >> what;
		if (checking_name(what) == false) {
			return;
		}
		del = Explore(what, how);
		del->llink->rlink = del->rlink;
		del->rlink->llink = del->llink;
		delete del;
		cout << "삭제되었습니다." << endl;
		count_decrease();
		cout << "==========================================" << endl;
	}
	else if (how == 2) {
		cout << "==========================================" << endl;
		cout << "삭제를 원하는 번호를 입력해주세요: ";	cin >> what;
		if (checking_number(what) == false) {
			return;
		}
		del = Explore(what, how);
		del->llink->rlink = del->rlink;
		del->rlink->llink = del->llink;
		delete del;
		cout << "삭제되었습니다." << endl;
		count_decrease();
		cout << "==========================================" << endl;
	}
	else if (how == 3) {
		cout << "==========================================" << endl;
		cout << "삭제를 원하는 별명을 입력해주세요: ";	cin >> what;
		del = Explore(what, how);
		del->llink->rlink = del->rlink;
		del->rlink->llink = del->llink;
		delete del;
		cout << "삭제되었습니다." << endl;
		count_decrease();
		cout << "==========================================" << endl;
	}
	else {
		cout << "잘못 입력하셨습니다. 메뉴로 돌아갑니다." << endl;
		return;
	}
}

void phonebook::Search_Member() {
	int how;
	string what;
	lists* search;
	cout << "==========================================" << endl;
	cout << "어떤 방식으로 찾기를 시작 하시겠습니까?" << endl;
	cout << "1. 이름" << " 2. 번호" << " 3. 별명" << endl;
	cout << ">> "; cin >> how;
	if (how == 1) {
		cout << "==========================================" << endl;
		cout << "검색을 원하는 이름을 입력해 주세요" << endl; cin >> what;
		if (checking_name(what) == false) {
			return;
		}
		search = Explore(what, how);
		cout << "==========================================" << endl;
		cout << "검색이 완료되었습니다" << endl;
		cout << "이름: " << search->data.name << endl;
		cout << "번호: " << search->data.number << endl;
		cout << "별명: " << search->data.nickname << endl;
		cout << "==========================================" << endl;
		return;
	}
	else if (how == 2) {
		cout << "==========================================" << endl;
		cout << "검색을 원하는 번호를 입력해 주세요" << endl; cin >> what;
		if (checking_number(what) == false) {
			return;
		}
		search = Explore(what, how);
		cout << "==========================================" << endl;
		cout << "검색이 완료되었습니다" << endl;
		cout << "이름: " << search->data.name << endl;
		cout << "번호: " << search->data.number << endl;
		cout << "별명: " << search->data.nickname << endl;
		cout << "==========================================" << endl;
		return;
	}
	else if (how == 3) {
		cout << "==========================================" << endl;
		cout << "검색을 원하는 별명을 입력해 주세요" << endl; cin >> what;
		search = Explore(what, how);
		cout << "==========================================" << endl;
		cout << "검색이 완료되었습니다" << endl;
		cout << "이름: " << search->data.name << endl;
		cout << "번호: " << search->data.number << endl;
		cout << "별명: " << search->data.nickname << endl;
		cout << "==========================================" << endl;
		return;
	}
	else {
		cout << "잘못 입력하셨습니다. 메뉴로 돌아갑니다." << endl;
		return;
	}
}

//****************************************** ↓클래스 멤버함수 "출력" 함수↓ *******************************************************//

void phonebook::print_list() {
	lists* now;
	cout << "==========================================" << endl;
	cout << "총 인원: " << count << "명" << endl;
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
	if (file_Size(Read) <= 0) {	// 파일이 비어있거나 없으면 (0 또는 -1이면)
		cout << "불러올 파일이 없습니다. 새로 작성합니다." << endl;
		return;					// 불러올 데이터가 없으니 종료
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
	cout << "파일을 불러왔습니다." << endl;
	cout << "출력메뉴를 실행해 확인해 주시기 바랍니다." << endl;
}

void phonebook::file_Save() {
	ofstream save("phonebook.txt");
	lists* now, * before;
	int index, find_index, find_accept, ask_num, repeat = 0;
	now = head;
	now = now->rlink;
	save << endl;
	cout << "데이터들이 \"phonebook.txt\" 파일에 저장되었습니다." << endl;
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