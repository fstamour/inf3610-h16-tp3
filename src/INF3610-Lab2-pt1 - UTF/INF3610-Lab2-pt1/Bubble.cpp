///////////////////////////////////////////////////////////////////////////////
//
//	Bubble.cpp
//
///////////////////////////////////////////////////////////////////////////////
#include "Bubble.h"


///////////////////////////////////////////////////////////////////////////////
//
//	Constructeur
//
///////////////////////////////////////////////////////////////////////////////
Bubble::Bubble( sc_module_name name )
/* └ complÚter */
{
	/*
	
	└ complÚter
	
	*/
}


///////////////////////////////////////////////////////////////////////////////
//
//	Destructeur
//
///////////////////////////////////////////////////////////////////////////////
Bubble::~Bubble()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//	thread
//
///////////////////////////////////////////////////////////////////////////////
void Bubble::thread(void)
{
	/*
	
	└ complÚter
	
	*/

}


///////////////////////////////////////////////////////////////////////////////
//
//	bubbleSort
//
///////////////////////////////////////////////////////////////////////////////
void Bubble::bubbleSort(unsigned int *ptr, int counter)
{
	// Variable
	unsigned int tmp = 0;
	
	for (int i = 1; i < counter; ++i){
		for (int j = 0; j < counter - i; ++j){
			if (ptr[j] > ptr[j + 1]){
				// Changing position
				tmp = ptr[j];
				ptr[j] = ptr[j + 1];
				ptr[j + 1] = tmp;
			}
	
		}
	}
	// Display
	for (int i = 0; i < counter; i++)
		cout << ptr[i] << endl;
}
