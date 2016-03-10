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
	// wait(clk_port->posedge_event());
	cout << "[Bubble] Thread." << endl;

	while (1) {
		switch (state_)
		{
		case Bubble::INIT:
			cout << "[Bubble] Init." << endl;
			/// Lit le premier mot et alloue le tableau data_
			nb_data_ = read(0);
			data_ = new unsigned int[nb_data_];
			if (!data_) {
				cerr << "[Bubble] ERROR Unable to create an array of " << nb_data_ << " elements (unsigned int).\n";
				sc_stop();
			}
			/*cout << "[Bubble] nb_data_: " << nb_data_ << endl;
			cout << "[Bubble] data_: " << data_ << endl;
			cout << "[Bubble] data_index_: " << data_index_ << endl;*/
			state_ = Bubble::READ;
			break;
		case Bubble::READ:
		{
			cout << "[Bubble] Read loop." << endl;
			unsigned int addr = data_index_ * 4;
			cout << "[Bubble] Read(" << addr << ") = ";
			data_[data_index_] = read(addr);
			cout << data_[data_index_] << endl;
			data_index_++;
			if (data_index_ >= nb_data_) {
				state_ = Bubble::SORT;
			}
		}
			break;
		case Bubble::SORT:			
			cout << "[Bubble] Sort." << endl;
			bubbleSort(data_, nb_data_);
			data_index_ = 1;
			state_ = Bubble::END; // TODO Write
			break;
		case Bubble::WRITE:
			cout << "[Bubble] Write loop." << endl;
			break;

		default:
			cerr << "[Bubble] ERROR Invalid state." << endl;
		case Bubble::END:
			delete[] data_;
			sc_stop();
			return;
		}
	}
#if 0
	/*** Read ***/
	// cout << hex;
	for (size_t i = 4, data_index = 0; i < (nb_data + 1) * 4; i += 4, ++data_index) {
		data[data_index] = read(i);
		cout << "[Bubble] Read(" << i << ") = " << data[data_index] << endl;
	}

	
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
	//	writePort->Write(i, data[data_index]);
	}

#endif
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



// Helper
unsigned int Bubble::read(unsigned int address) {
	// Envoyer l’adresse à être lue
	address_port.write(address);

	// Envoyer une requête
	requestRead_port.write(true);
	
	// cout << "[Bubble] About wait the ack. " << endl;
	// Attendre un accusé de réception
	do {
		wait(clk_port->posedge_event());
	} while (!ack_port.read());

	// cout << "[Bubble] About to read data at addr: " << address << endl;
	// Lire la donnée reçue
	unsigned int data = data_port.read();
	// cout << "[Bubble] Got data: " << data << endl;

	// Enlever la requête
	requestRead_port.write(false);
	// cout << "[Bubble] Request removed." << endl;

	do {
		wait(clk_port->posedge_event());
	} while (ack_port.read());

	return data;
}
