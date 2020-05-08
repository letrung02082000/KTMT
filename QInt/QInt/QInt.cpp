#include"QInt.h"

int GetBit(int x, int i) {
	return (x >> (31 - i) & 1);
}

int SetBit1(int x, int i) {
	return (x | (1 << (31 - i)));
}

QInt operator + (QInt a, QInt b) {
	int bit1[128], bit2[128], bit[128];
	int s = 0, i = 127, j = 127;
	QInt result;
	result.data[0] = 0;
	result.data[1] = 0;
	result.data[2] = 0;
	result.data[3] = 0;
	for (int i = 0; i < 128; ++i) {
	bit1[i] = GetBit(a.data[i / 32], i % 32);
	}
	for (int i = 0; i < 128; ++i) {
		bit2[i] = GetBit(b.data[i / 32], i % 32);
	}
	while (i >= 0 || j >= 0 || s == 1) {
		if (i >= 0)
			s += bit1[i];
		else
			s += 0;
		if (j >= 0) 
			s += bit2[j];
		else
			s += 0;
		bit[i] = s % 2;
		s /= 2;
		--i;
		--j;
	}
	for (int i = 0; i < 128; ++i) {
		if (bit[i] == 1) {
			SetBit1(result.data[i / 32], i % 32);
		}
	}
	return result;
}


string Div2(string s) {
	int carry = 0;
	string result, temp;
	bool remove = true;
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] % 2 == 0) {
			temp += to_string(((int)(s[i] - '0') + carry) / 2);
			carry = 0;
		}
		else {
			temp += to_string(((int)(s[i] - '0') + carry) / 2);
			carry = 10;
		}
	}

	for (int i = 0; i < temp.length(); ++i) {
		if (temp.length() == 1 && temp[0] == '0') {
			return temp;
		}

		if (temp[i] == '0' && remove) {
			continue;
		}
		else {
			result += temp[i];
			remove = false;
		}
	}
	return result;
}

void ScanQInt(QInt& x) {
	x.data[0] = 0;
	x.data[1] = 0;
	x.data[2] = 0;
	x.data[3] = 0;

	int bit[128];
	string num, s;
	cout << "Nhap QInt: ";
	cin >> num;
	if (num[0] == '-') {
		bit[0] = 1;
		s = num.erase(0, 1);
	}
	else {
		bit[0] = 0;
		s = num;
	}
	while (s != "0") {
		for (int i = 0; i < 127; ++i) {
			int endInt = (int)(s[s.length() - 1] - '0');
			if (endInt % 2 == 0) {
				bit[127 - i] = 0;
			}
			else {
				bit[127 - i] = 1;
			}
			s = Div2(s);
		}
	}
	if (num[0] == '-') {

		//bu 1
		for (int i = 1; i < 128; ++i) {
			if (bit[i] == 0)
				bit[i] = 1;
			else
				bit[i] = 0;
		}

		//bu 2
		int bit1[1] = { 1 }, bit2[128];
		int i = 127, j = 0, s = 0;
		while (i >= 0 || j >= 0 || s == 1) {
			if (i >= 0)
				s += bit[i];
			else
				s += 0;
			if (j >= 0)
				s += bit1[j];
			else
				s += 0;
			bit2[i] = s % 2;
			s /= 2;
			--i;
			--j;
		}
		for (int i = 0; i < 128; ++i) {
			if (bit2[i] == 1) {
				x.data[i / 32] = SetBit1(x.data[i / 32], i % 32);
			}
		}


	}
	else {
		for (int i = 0; i < 128; ++i) {
			if (bit[i] == 1) {
				x.data[i / 32] = SetBit1(x.data[i / 32], i % 32);
			}
		}
	}
}

int multiply(int x, int result[], int size) {
	int carry = 0;
	for (int i = 0; i < size; ++i) {
		int temp = result[i] * x + carry;
		result[i] = temp % 10;
		carry = temp / 10;
	}
	while (carry) {
		result[size] = carry % 10;
		carry /= 10;
		size++;
	}
	return size;
}

int power(int result[], int x, int n) {
	if (n == 0) {
		result[0] = 1;
		return 1;
	}
	int temp = x;
	int temp_size = 0;
	while (temp != 0) {
		result[temp_size++] = temp % 10;
		temp = temp / 10;
	}
	for (int i = 2; i <= n; ++i) {
		temp_size = multiply(x, result, temp_size);
	}
	return temp_size;
}

int add(int int1[], int size1, int int2[], int size2) {
	int size = 0;
	if (size1 < size2) {
		int carry = 0;
		size = size2;
		for (int i = 0; i < size1; ++i) {
			int sum = (int1[i] + int2[i] + carry);
			int1[i] = sum % 10;
			carry = sum / 10;
		}
		for (int i = size1; i < size2; ++i) {
			int sum = int2[i] + carry;
			int1[i] = sum % 10;
			carry = sum / 10;
		}
		if (carry) {
			int1[size2] = carry;
			++size;
		}
	}
	else {
		int carry = 0;
		size = size1;
		for (int i = 0; i < size2; ++i) {
			int sum = (int1[i] + int2[i] + carry);
			int1[i] = sum % 10;
			carry = sum / 10;
		}
		for (int i = size2; i < size1; ++i) {
			int sum = (int1[i] + carry);
			int1[i] = sum % 10;
			carry = sum / 10;
		}
		if (carry) {
			int1[size1] = carry;
			++size;
		}
	}
	return size;
}

void PrintQInt(QInt x) {
	int bit[128];
	int sum[39];
	int temp[39];
	for (int i = 0; i < 128; ++i) {
		bit[i] = GetBit(x.data[i / 32], i % 32);
	}
	for (int i = 0; i < 128; ++i) {
		if (bit[i] == 1) {
			int size = power(temp, 2, 127 - i);
			add(sum, 39, temp, size);
		}
	}
	for (int i = 0; i < 39; ++i) {
		cout << sum[38 - i];
	}
}