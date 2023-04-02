#include <iostream>
#include <cstring>
using namespace std;

class Playfair {
	char mTable[5][5]; // ��ȣ���̺� �������
	string mPair;  // 'Q/Z' ����
	string mKey;   // ��ȣŰ ����
public:
	Playfair(string mKey, string mPair); // ������
	void makeTable(); // ��ȣ���̺� ����� �Լ�
	void showTable(); // ��ȣ���̺� ����ϴ� �Լ�
	void makeEncryption(string mEncryption); // ��ȣȭ��Ű�� �Լ�
private:
	string _txt; // ��ȣȭ�� ���ڿ� ����
	bool getCharPos(char l, int& a, int& b); // ��ȣ���̺� �ӿ��� ������ ��ġ�� �˷��ִ� �Լ�
	char getChar(int a, int b); // ��ġ(a,b)�� �ش��ϴ� ��ȣ���̺� ���ڸ� ��ȯ�ϴ� �Լ�
	void getTextReady(string t); // ��ȣȭ�� ���ڿ��� ���� �غ� �۾� �Լ�
	void display(); // ��ȣȭ�� ���ڿ� ���
};

Playfair::Playfair(string mKey, string mPair) {
	this->mKey = mKey;
	this->mPair = mPair;
}
void Playfair::makeTable() {
	// mKey�� mPair�� �̿��Ͽ� mTable�� ���弼��. (5 X 5 �� ǥ���Ͻÿ�)
	mKey += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string nk = "";

	// key���� �ߺ��Ǵ� ���ڸ� �����ϰ�, 'Q'�� 'Z'�� ���� ���� ���
	for (string::iterator si = mKey.begin(); si != mKey.end(); si++)

	{
		*si = toupper(*si);
		if (*si < 65 || *si > 90) continue;
		if (*si == toupper(mPair[2])) // 'Q'�� 'Z'�� ���� ���� ���
			continue;
		if (nk.find(*si) == -1) // �ߺ����� ���� ��쿡�� mTable�� �߰�
			nk += *si;
	}
	copy(nk.begin(), nk.end(), &mTable[0][0]);
}
void Playfair::showTable() {
	// mTable�� �ִ� ������ 5 X 5 �� ȭ�鿡 ����Ͻÿ�.
	cout << "��ȣ���̺�\n=========" << endl;
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			cout << mTable[y][x] << " "; // 5x5 ��ȣ���̺� ���
		}
		cout << endl;
	}
}

// ��ġ(a,b)�� �ش��ϴ� ��ȣ���̺� ���ڸ� ��ȯ�ϴ� �Լ�
char Playfair::getChar(int a, int b)
{
	return mTable[(b + 5) % 5][(a + 5) % 5];
}

// ��ȣ���̺� �ӿ��� ������ ��ġ(a,b)�� �˷��ִ� �Լ�
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

// ��ȣȭ�� ���ڿ��� ���� �غ� �۾� �Լ�
void Playfair::getTextReady(string t)
{
	for (string::iterator si = t.begin(); si != t.end(); si++)
	{
		*si = toupper(*si); // ���ڿ��� �빮�ڷ� �ٲ۴�.
		if (*si < 65 || *si > 90) continue; // �빮�ڰ� �ƴ� ���ڸ� skip
		if (*si == toupper(mPair[2])) // ���ڿ��� Z�� Q�� �ٲپ� �ش�.
			*si = toupper(mPair[0]);
		_txt += *si; // ���� ó���� ���� _txt�� �Էµ� ���ڿ� ����
	}

	string ntxt = "";
	size_t len = _txt.length();
	for (size_t x = 0; x < len; x += 2) // 
	{
		ntxt += _txt[x];
		if (x + 1 < len)
		{
			// ������ �ΰ� �� �������� ��, ���ڰ� ������ ���� ���̿� 'X'�� �߰���Ŵ
			if (_txt[x] == _txt[x + 1]) ntxt += 'X';
			ntxt += _txt[x + 1];
		}
	}
	_txt = ntxt;

	// ������ ���ڰ� �ϳ� ������ �ڿ� 'X'�� �߰���Ŵ
	if (_txt.length() & 1) _txt += 'X';
}

// ��ȣȭ��Ű�� �Լ�
void Playfair::makeEncryption(string message) {
	int a, b, c, d;
	string ntxt;

	getTextReady(message); // ���� message�� ��ȣȭ�ϱ� ���� �غ� �۾� ����

	// �غ�� ���ڿ��� ���� ��ȸ�ϸ鼭 ��ȣȭ ��Ģ�� ���� ���ڸ� �ٲپ� ��
	for (string::const_iterator ti = _txt.begin(); ti != _txt.end(); ti++)
	{
		if (getCharPos(*ti++, a, b)) // ù���� ��ġ(a,b) ����
			if (getCharPos(*ti, c, d)) // �ι�° ���� ��ġ(c,d) ����
			{
				// ���ڰ� ���� ���� �ִٸ� �� ĭ �ؿ� ��ġ�� ���ڷ� �ٲߴϴ�.
				if (a == c) { ntxt += getChar(a, b + 1); ntxt += getChar(c, d + 1); }
				// ���ڰ� ���� �࿡ �ִٸ� ���������� �� ĭ ��ġ�� ���ڷ� �ٲߴϴ�.
				else if (b == d) { ntxt += getChar(a + 1, b); ntxt += getChar(c + 1, d); }
				// ���ڰ� ���� �ٸ� ��� ���� �ִٸ� ���� ���� �ǵ����Ͽ� ������ ��ġ�� ���ڷ� �ٲߴϴ�.
				else { ntxt += getChar(c, b); ntxt += getChar(a, d); }
			}
	}
	_txt = ntxt; // ��ȣȭ�� ���ڸ� �ٽ� ����

	display(); // ��ȣȭ�� ���ڿ� ���
}

// ��ȣȭ�� ���ڿ� ���
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
	Playfair pfair("assainator", "Q/Z"); // Playfair ��ü ����
	pfair.makeTable(); // ��ȣ���̺� ����
	pfair.showTable(); // ��ȣ���̺� ���

	string message = "My major is computer engineering"; // ��ȣȭ�� �޽���
	cout << "\n\nINPUT Message: " << message << endl;
	pfair.makeEncryption(message); // ��ȣȭ �۾� �����ϰ� ��ȣȭ�� �޽��� ���
	//good
	return 0;
}