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
Bubble::Bubble(sc_module_name name): sc_module(name)
{
	SC_THREAD(thread);
	sensitive << clk_port;
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
#if 0
	unsigned int nb_data = readPort->Read(0);
	unsigned int* data = new unsigned int[nb_data];
	if (!data) {
		cerr << "[Bubble] ERROR Unable to create an array of " << nb_data << " elements (unsigned int).\n";
		sc_stop();
	}

	/*** Read ***/
	// cout << hex;
	for (size_t i = 4, data_index = 0; i < (nb_data + 1) * 4; i += 4, ++data_index) {
		data[data_index] = readPort->Read(i);
		// cout << "[Bubble] Read(" << i << ") = " << data[data_index] << endl;
	}

	/*** Sort ***/
	bubbleSort(data, nb_data);

	/// Being extra careful.
	unsigned int previous_data = data[0];
	for (size_t i = 1; i < nb_data; ++i) {
		if (previous_data > data[i]) {
			cerr << "[Bubble] ERROR Data is not sorted.\n";
		}
		previous_data = data[i];
	}

	/*** Write ***/
	for (size_t i = 4, data_index = 0; i < (nb_data + 1) * 4; i += 4, ++data_index) {
		// cout << "[Bubble] Write(" << i << ") = " << data[data_index] << endl;
		writePort->Write(i, data[data_index]);
	}

	delete[] data;
#endif

	sc_stop();
}


///////////////////////////////////////////////////////////////////////////////
//
//	bubbleSort
//
///////////////////////////////////////////////////////////////////////////////
void Bubble::bubbleSort(unsigned int *ptr, int counter)
{
	cout << "*** BubbleSort ***\n";

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
	for (int i = 0; i < counter; i++) {
		cout << ptr[i] << endl;
	}
}
