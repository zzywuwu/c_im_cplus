
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

class MyString {
public: 
    MyString() { 
        _data = nullptr; 
        _len = 0;
		#ifdef DEBUG
        cout << "Constructor is called!\n" << endl;
		#endif
    } 
 
    MyString(const char* p) { 
        _len = strlen (p); 
        _init_data(p); 
		#ifdef DEBUG
        cout << "Constructor is called! this->_data: " << (long)_data << endl;
		#endif
    } 
 
    MyString(const MyString& str) { 
        _len = str._len; 
        _init_data(str._data);
		#ifdef DEBUG
        cout << "Copy Constructor is called! src: " << (long)str._data << " dst: " << (long)_data << endl;
		#endif
    }
 
    ~MyString() { 
        if (_data)
        {
			#ifdef DEBUG
            cout << "DeConstructor is called! this->_data: " << (long)_data << endl; 
			#endif
            free(_data);
        }
        else
        {
			#ifdef DEBUG
            std::cout << "DeConstructor is called!" << std::endl; 
			#endif
        }
    } 
 
    MyString& operator=(const MyString& str) { 
        if (this != &str) { 
            _len = str._len; 
            _init_data(str._data); 
        }
		#ifdef DEBUG
        cout << "Copy Assignment is called! src: " << (long)str._data << " dst" << (long)_data << endl; 
		#endif
        return *this; 
    } 
	
	#if 1
	MyString(MyString &&str) {
		#ifdef DEBUG
		cout << "Move Constructor is called! src: " << (long)str._data << endl;
		#endif
		_len = str._len;
		_data = str._data;
		str._data = nullptr;
	}
	#endif
	
	MyString& operator=(MyString&& str) { 
		#ifdef DEBUG
		cout << "Move Operator= is called! src: " << (long)str._data << endl; 
		#endif
		if (this != &str) { 
			if (_data != nullptr){
				free(_data);
			}
			_len = str._len;
			_data = str._data;
			str._len = 0;
			str._data = nullptr;
		}     
		return *this; 
	}
 
    operator const char *() const {
        return _data;
    }
 
public: 
    char *_data; 
    size_t _len; 
 
    void _init_data(const char *s) { 
        _data = new char[_len+1]; 
        memcpy(_data, s, _len); 
        _data[_len] = '\0'; 
    } 
}; 
 
#if 1
static MyString str11 = "111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";

#endif

MyString foo()
{
    MyString middle("123");
    return middle;
}
 
class A {
public:
	A(MyString& str):_a(str) { 
		cout << "Constructor a\n" << endl;
	}
	/*A(MyString&& str):_a(std::move(str)) { 
		cout << "Constructor a\n" << endl;
	}*/
	A() { }
	MyString get_abc() { 
		//return _a;
		char buf[10240];
		memset(buf,'1',sizeof(buf));
		buf[10240 - 1] = '\0';
		for (int i = 0; i < 10240; i++) {
			buf[i] = 'x';
		}
		MyString tmp(buf);
		//MyString* tmp = new MyString(buf);
		return tmp;
		//return std::move(tmp);
	} 
	MyString& returna() { return _a;}
	MyString _a;
};


void test1(MyString& x) {
	x._data[3] = 'o';
}

void test(const MyString& x) {
	//test1(x);
	printf("%s\n", x._data);
	return;
}

MyString test2() {
	return MyString("xxxxxxx");
}


int main()
{
	A abc(str11);
	
	
	cout << " BEGIN " <<endl;
	//A xxx(MyString("1111"));
	A xxx(test2());
	cout << " END " <<endl;
	
	#if 0
	Timer test22;
	for(int i = 0 ; i < 1; i++) {
		MyString a(abc.get_abc());
		cout << a._data << endl;
	}	
	cout << "ns " << test22.elapsed_nano() << endl;	/*纳秒*/
	cout << "us " << test22.elapsed_micro() << endl;	/*微妙*/
	cout << "ms "<< test22.elapsed() << endl;   /*毫秒*/
	cout << " s "  << test22.elapsed_seconds() << endl;
	#endif
	return 0;	
}

