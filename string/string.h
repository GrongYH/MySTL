#pragma once
#include<algorithm>
#include<assert.h>
#include<string.h>


namespace stringstl
{
	class string
	{
	public:
		typedef char* iterator;
		iterator begin()
		{
			return _str;
		}

		iterator end()
		{
			return _str + _size;
		}

		typedef const char* const_iterator;
		const_iterator begin() const
		{
			return _str;
		}
		const_iterator end() const
		{
			return _str + _size;
		}


		//string(const string& s) :_str(new char[strlen(s._str) + 1])
		//{
		//	//�������_strָ��һƬ��s._str��ͬ��С�Ŀռ�
		//	strcpy(_str, s._str);
		//}

		/*string(const char* str = "") : _size(strlen(str)), _capacity(_size), _str(new char[_capacity + 1])
		{
			strcpy(_str, str);
		}*/
		
		string(const char* str = "")
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];

			strcpy(_str, str);
		}

		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = 0;
			_capacity = 0;
		}

		const char* c_str() const
		{
			return _str;
		}

		//string& operator=(const string& s)
		//{
		//	if (this != &s)
		//	{
		//		delete[] _str;
		//		_str = new char[strlen(s._str) + 1];
		//		strcpy(_str, s._str);
		//	}
		//	//*this ��ʱ��û����������˷������ÿ������Ч��
		//	//*this ��ʱ��û����������˷������ÿ������Ч��
		//	return *this;
		//}

		void swap(string& s)
		{
			std::swap(_str,s._str);
			std::swap(_size,s._size);
			std::swap(_capacity,s._capacity);
		}

		string(const string& s):_str(nullptr),_size(0),_capacity(0)
		{
			//�������_str�ÿգ����������ֵ��tmp(_str)����ʱ�ᱨ��
			//�ȵ�����ͨ���캯������һ����ʱ����tmp��tmp�ڵ�_strָ��һƬ��s._str��С�����ݶ���ͬ�Ŀռ�
			string tmp(s._str);
			//������_strָ��һƬ��s._str��С�����ݶ���ͬ�Ŀռ䣬��ʵ����string�࿽������ʱ�����
			swap(tmp);
		}

		string& operator=(string s)
		{
			//���ι�����s�ȵ��ÿ������츴����ʵ�Σ��ٽ�s._str��_str����
			//��ʱ���ܴ����ã���ΪҪ�ı�s��ֵ
			swap(s);
			return *this;
		}
		//_str[i]�ܸı䣬����õ�char&
		char& operator[](size_t i)
		{
			assert(i < _size);
			return _str[i];
		}
		//_str[i]���ܸı䣬����õ�const char&
		const char& operator[](size_t i) const
		{
			assert(i < _size);
			return _str[i];
		}

		size_t size() const //ʹ��const������Ե���
		{
			return _size;
		}

		size_t capacity() const //ʹ��const������Ե���
		{
			return _capacity;
		}

		//��ɾ
		void push_back(char ch)
		{
			if (_size == _capacity)
			{
				reserve(_capacity == 0? 4:_capacity * 2);
			}
			_str[_size++] = ch;
		}
		void append(const char* str)
		{
			if (_size + strlen(str) > _capacity)
			{
				reserve(_size + strlen(str));
			}
			strcpy(_str + _size, str);
			_size += strlen(str);
		}

		//���ռ䣬��չ_capcity,�˴���Ƶ�Ϊֻ���ݲ�����
		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				strcpy(tmp,_str);
				delete[] _str;
				_str = tmp;
				_capacity = n;
			}
		}

		//�ı�_size��ͬʱ��ʼ��
		void resize(size_t n, char val = '\0')
		{
			if (n < _size)
			{
				_size = n;
				_str[n] = '\0';
			}
			else 
			{
				if (n > _capacity)
				{
					reserve(n);
				}
				for (size_t i = _size; i < n; i++)
				{
					_str[i] = val;
				}
				_str[n] = '\0';
				_size = n;
			}
		}
		//+=����
		string& operator+=(const char* str)
		{
			append(str);
			return *this;
		}
		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}

		string& insert(size_t pos, char ch)
		{
			assert(pos <= _size && pos >= 0);
			if (_size == _capacity)
			{
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}
			size_t end = _size;
			//��\0����Ų���������Ҫ����"\0"
			while (end >= pos)
			{
				_str[end + 1] = _str[end];
				if (end == 0)
				{
					break;
				}
				--end;
			}
			_str[pos] = ch;
			_size++;
			return *this;
		}

		string& insert(size_t pos, const char* str)
		{
			assert(pos >= 0 && pos < _size);
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			size_t end = _size;
			//posλ�ü������Ķ�Ҫ�����ƶ�
			while (end >= pos)
			{
				_str[end + len] = _str[end];
				if (end == 0)
				{
					break;
				}
				end--;
			}
			strncpy(_str + pos, str, len); //strncpy���Կ��Ƹ��Ƶ��ַ���
			_size += len;
			return *this;
		}

		string& erease(size_t pos, size_t len = npos)
		{
			//posλ�õ�lenλ��֮ǰ���ַ�����������posλ�õ��ַ���
			size_t leftLen = len - pos;
			if (leftLen > _size - pos)
			{
				_size = pos;
				_str[_size] = '\0';
			}
			else
			{
				strcpy(_str + pos, _str + pos + len);
				_size -= len;
			}
			return *this;
		}

		bool operator>(const char* str);
		bool operator<(const char* str);
		bool operator==(const char* str);
		bool operator>=(const char* str);
		bool operator<=(const char* str);
		bool operator!=(const char* str);

	private:
		char* _str;
		size_t _size;
		size_t _capacity;
		static const size_t npos;
	};

	 const size_t string::npos = -1;
}
