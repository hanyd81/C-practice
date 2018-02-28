// main 
#include <iostream>
#include "myList.h"

using namespace std;

int main()
{
	List l1;
	l1.display();
	List l2(1);
	l2.display();
	l2.append(3);
	l1.append(2);
	l1.append(3);
	l1.append(4);

	cout << l1;
	cout << l2;

	char c;
	cin >> c;
	return 0;
}