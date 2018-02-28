//practice dynamic array
//

#ifndef MYLIST_H
#define MYLIST_H

class List {

	int* m_pList;
	int m_length;

public:
	List();
	List(int item);
	~List();
	void append(int item);
	void display() const;
	int getLen()const;
};

// to overload << , the left side can not be the List type, must use global function
// in header files can not using namespace, so must add std::
std::ostream& operator << (std::ostream&, const List&);


#endif
