//practice dynamic array
#include<iostream>
#include "myList.h"

using namespace std;

List::List()
{
	m_length = 0;
	m_pList = nullptr;
}

List::List(int item)
{
	m_pList = new int[1];
	m_pList[0] = item;
	m_length = 1;
}

List::~List()
{
	delete[] m_pList;
}

void List::append(int item)
{
	int* ptemp = new int[m_length+1];
	for (int i = 0; i < m_length; ++i) {
		ptemp[i] = m_pList[i];
	}
	ptemp[m_length] = item;
	delete[] m_pList;
	m_pList = ptemp;
	ptemp = nullptr;
	m_length++;
}

void List::display()const
{
	if (m_length > 0) {
		for (int i = 0; i < m_length; ++i) {
			cout << m_pList[i] << ",";
		}
		cout << endl;
	}
}

int List::getLen()const
{
	return m_length;
}

ostream& operator << (ostream& cout, const List& list) {
	list.display();
	return cout;
}