#include <iostream>
#include <algorithm>
#include <stack>
#include <map>
using namespace std;


stack<char> operSta, numSta;
map<char, int> operMap;


void init();
void trimSpace(string &str);
void scan(const char c);
void inputNum(const char c);
void inputOper(const char c);
void sweep();
void showStack(stack<char> &sta);


int main()
{
	init();

	// Get a string
	string midfixStr;
	cout << "Enter a midfix string: ";
	cin >> midfixStr;

	// Trim spaces
	trimSpace(midfixStr);

	// Convert midfix to postfix
	for (int i = 0, len = midfixStr.length(); i < len; ++i)
	{
		char tmp = midfixStr.at(i);
		scan(tmp);
	}
	// Do last things
	sweep();

	// Show result
	showStack(numSta);
}

void init()
{
	operMap.insert(make_pair('(', 10));
	operMap.insert(make_pair(')', 0));
	operMap.insert(make_pair('+', 2));
	operMap.insert(make_pair('-', 2));
	operMap.insert(make_pair('*', 4));
	operMap.insert(make_pair('/', 4));
}

void trimSpace(string &str)
{
	auto itor = remove_if(str.begin(), str.end(), ::isspace);
	str.erase(itor, str.end());
}

void scan(const char c)
{
	if (c >= '0' && c <= '9') inputNum(c);
	else if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/') inputOper(c);
	else 
	{
		cout << "Find invalid character, can not parse!" << endl;
		exit(-1);
	}
}

void inputNum(const char c)
{
	numSta.push(c);
}

void inputOper(const char c)
{
	// Check if the underlying container has no elements
	if (operSta.empty()) 
	{
		operSta.push(c);
		return;
	}

	// Has elements
	char topC = operSta.top();
	int priNew = operMap.at(c);
	int priTop = operMap.at(topC);

	// Is '(' or the priority is higher than the top element
	if (priNew > priTop || topC == '(' || c == '(') 
	{
		operSta.push(c);
		return;
	}

	// If the input element is ')'
	if (c == ')')
	{
		char tmp;
		while ((tmp = operSta.top()) != '(')
		{
			operSta.pop();
			numSta.push(tmp);
		}
		operSta.pop();
		return;
	}

	// If the priority is lower than the top element
	operSta.pop();
	numSta.push(topC);

	// Recursive
	inputOper(c);
}

void sweep()
{
	while (!operSta.empty())
	{
		char tmp = operSta.top();
		operSta.pop();
		numSta.push(tmp);
	}
}

void showStack(stack<char> &sta)
{
	stack<char> tmpSta;
	
	while (!sta.empty())
	{
		char c = sta.top();
		sta.pop();
		tmpSta.push(c);
	}

	// Reverse
	while (!tmpSta.empty())
	{
		char c = tmpSta.top();
		tmpSta.pop();
		sta.push(c);

		cout << c << " ";
	}
	cout << endl;
}


