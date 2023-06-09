#include <iostream>
#include <cstring>
using namespace std;

class Playfair {
	char mTable[5][5]; // 암호테이블 저장공간
	string mPair;  // 'Q/Z' 저장
	string mKey;   // 암호키 저장
public:
	Playfair(string mKey, string mPair); // 생성자
	void makeTable(); // 암호테이블 만드는 함수
	void showTable(); // 암호테이블 출력하는 함수
	void makeEncryption(string mEncryption); // 암호화시키는 함수
private:
	string _txt; // 암호화된 문자열 저장
	bool getCharPos(char l, int& a, int& b); // 암호테이블 속에서 문자의 위치를 알려주는 함수
	char getChar(int a, int b); // 위치(a,b)에 해당하는 암호테이블 문자를 반환하는 함수
	void getTextReady(string t); // 암호화할 문자열에 대한 준비 작업 함수
	void display(); // 암호화된 문자열 출력
};

Playfair::Playfair(string mKey, string mPair) {
	this->mKey = mKey;
	this->mPair = mPair;
}
void Playfair::makeTable() {
	// mKey와 mPair를 이용하여 mTable을 만드세요. (5 X 5 로 표현하시오)
	mKey += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string nk = "";

	// key에서 중복되는 문자를 제거하고, 'Q'와 'Z'를 같은 문자 취급
	for (string::iterator si = mKey.begin(); si != mKey.end(); si++)

	{
		*si = toupper(*si);
		if (*si < 65 || *si > 90) continue;
		if (*si == toupper(mPair[2])) // 'Q'와 'Z'를 같은 문자 취급
			continue;
		if (nk.find(*si) == -1) // 중복되지 않은 경우에만 mTable에 추가
			nk += *si;
	}
	copy(nk.begin(), nk.end(), &mTable[0][0]);
}
void Playfair::showTable() {
	// mTable에 있는 값들을 5 X 5 로 화면에 출력하시오.
	cout << "암호테이블\n=========" << endl;
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			cout << mTable[y][x] << " "; // 5x5 암호테이블 출력
		}
		cout << endl;
	}
}

// 위치(a,b)에 해당하는 암호테이블 문자를 반환하는 함수
char Playfair::getChar(int a, int b)
{
	return mTable[(b + 5) % 5][(a + 5) % 5];
}

// 암호테이블 속에서 문자의 위치(a,b)를 알려주는 함수
bool Playfair::getCharPos(char l, int& a, int& b)
{
	for (int y = 0; y < 5; y++)
		for (int x = 0; x < 5; x++)
			if (mTable[y][x] == l)
			{
				a = x; b = y; return true;
			}
	return false;
}

// 암호화할 문자열에 대한 준비 작업 함수
void Playfair::getTextReady(string t)
{
	for (string::iterator si = t.begin(); si != t.end(); si++)
	{
		*si = toupper(*si); // 문자열을 대문자로 바꾼다.
		if (*si < 65 || *si > 90) continue; // 대문자가 아닌 문자를 skip
		if (*si == toupper(mPair[2])) // 문자열이 Z면 Q로 바꾸어 준다.
			*si = toupper(mPair[0]);
		_txt += *si; // 다음 처리를 위해 _txt에 입력된 문자열 저장
	}

	string ntxt = "";
	size_t len = _txt.length();
	for (size_t x = 0; x < len; x += 2) // 
	{
		ntxt += _txt[x];
		if (x + 1 < len)
		{
			// 문장을 두개 씩 나누었을 때, 문자가 같으면 문자 사이에 'X'를 추가시킴
			if (_txt[x] == _txt[x + 1]) ntxt += 'X';
			ntxt += _txt[x + 1];
		}
	}
	_txt = ntxt;

	// 마지막 글자가 하나 남으면 뒤에 'X'를 추가시킴
	if (_txt.length() & 1) _txt += 'X';
}

// 암호화시키는 함수
void Playfair::makeEncryption(string message) {
	int a, b, c, d;
	string ntxt;

	getTextReady(message); // 먼저 message를 암호화하기 위한 준비 작업 수행

	// 준비된 문자열에 대해 순회하면서 암호화 규칙에 따라 문자를 바꾸어 줌
	for (string::const_iterator ti = _txt.begin(); ti != _txt.end(); ti++)
	{
		if (getCharPos(*ti++, a, b)) // 첫문자 위치(a,b) 얻어옴
			if (getCharPos(*ti, c, d)) // 두번째 문자 위치(c,d) 얻어옴
			{
				// 문자가 같은 열에 있다면 한 칸 밑에 위치한 문자로 바꿉니다.
				if (a == c) { ntxt += getChar(a, b + 1); ntxt += getChar(c, d + 1); }
				// 문자가 같은 행에 있다면 오른쪽으로 한 칸 위치한 문자로 바꿉니다.
				else if (b == d) { ntxt += getChar(a + 1, b); ntxt += getChar(c + 1, d); }
				// 문자가 서로 다른 행과 열에 있다면 같은 행이 되도록하여 만나는 위치에 문자로 바꿉니다.
				else { ntxt += getChar(c, b); ntxt += getChar(a, d); }
			}
	}
	_txt = ntxt; // 암호화된 문자를 다시 저장

	display(); // 암호화된 문자열 출력
}

// 암호화된 문자열 출력
void Playfair::display()
{
	cout << "Encrypted Msg : " << endl;
	string::iterator si = _txt.begin(); int cnt = 0;
	while (si != _txt.end())
	{
		cout << *si; si++; cout << *si << " "; si++;
		if (++cnt >= 26) cout << endl, cnt = 0;
	}
	cout << endl << endl;
}
int main() {
	Playfair pfair("assainator", "Q/Z"); // Playfair 객체 생성
	pfair.makeTable(); // 암호테이블 생성
	pfair.showTable(); // 암호테이블 출력

	string message = "My major is computer engineering"; // 암호화할 메시지
	cout << "\n\nINPUT Message: " << message << endl;
	pfair.makeEncryption(message); // 암호화 작업 수행하고 암호화된 메시지 출력
	//good
	return 0;
}