
#include <iostream>
#include <locale>
#include <chrono>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace std::chrono;

typedef unsigned long long u64;

class Timer
{
public:
	Timer() : m_begin(high_resolution_clock::now()) { }
	void reset() { m_begin = high_resolution_clock::now(); }

	//默认输出毫秒
	u64 elapsed() const {
		return duration_cast<chrono::milliseconds>(high_resolution_clock::now() - m_begin).count();
	}

	//默认输出秒
	double elapsed_second() const {
		return duration_cast<duration<double>>(high_resolution_clock::now() - m_begin).count();
	}

	//微秒
	u64 elapsed_micro() const {
		return duration_cast<chrono::microseconds>(high_resolution_clock::now() - m_begin).count();
	}

	//纳秒
	u64 elapsed_nano() const {
		return duration_cast<chrono::nanoseconds>(high_resolution_clock::now() - m_begin).count();
	}

	//秒
	u64 elapsed_seconds() const {
		return duration_cast<chrono::seconds>(high_resolution_clock::now() - m_begin).count();
	}

	//分
	u64 elapsed_minutes() const {
		return duration_cast<chrono::minutes>(high_resolution_clock::now() - m_begin).count();
	}

	//时
	u64 elapsed_hours() const {
		return duration_cast<chrono::hours>(high_resolution_clock::now() - m_begin).count();
	}

private:
	time_point<high_resolution_clock> m_begin;
};

#define DEBUG

void testreplace(string &str) {
	int strlen = str.size();
	for (int i = 0; i < strlen;) {
		if (str[i] == '$') {
			switch(str[i + 1]) {
				case 'N':
					str.replace(i, 2, "zzy");
					break;
				case 'n':
					str.replace(i, 2, "zzy");
					break;
				default:
					break;
			}
			i = i + 3;
		}
		else {
			int pos1 = str.find('$', i);
			if (pos1 != -1) {
				i = pos1;
			}
			else
				break;
		}
	}
}

void testnew(const string &str) {
	string ret;
	int strlen = str.size();
	int pos = 0;
repeat:
	if (str[pos] == '$') {
		
		switch(str[pos + 1]) {
			case 'N':
				ret += "zzy";
				break;
			case 'n':
				ret += "zzy";
				break;
			default:
				break;
		}
		pos = pos + 2;
		goto repeat;
	}
	else {
		
		int pos1 = str.find('$', pos);
		if (pos1 != -1) {
			ret += str.substr(pos, pos1 - pos);
			pos = pos1;
			goto repeat;
		}
		else {
			ret += str.substr(pos, strlen - pos);
		}
	}

	//cout << ret << endl;
}

int main()
{
	Timer time;
	//const string str("0123456789$n0123456789$n0123456789$n0123456789");
	for (int i = 0; i < 10000 ; i++) {
		string str("0123456789$n0123456789$n0123456789$n0123456789");
		testreplace(str);
		//testnew(str);
	}
	cout << "ns " << time.elapsed_nano() << endl;	/*纳秒*/
	cout << "us " << time.elapsed_micro() << endl;	/*微妙*/
	cout << "ms "<< time.elapsed() << endl;   /*毫秒*/
	cout << " s "  << time.elapsed_seconds() << endl;
	return 0;	
}

