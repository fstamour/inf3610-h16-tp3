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
Bubble::Bubble(sc_module_name name) : sc_module(name)
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
	cout << "[Bubble] Thread started." << endl;

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
			state_ = Bubble::READ;
			break;
		case Bubble::READ:
		{
			// cout << "[Bubble] Read loop." << endl;
			unsigned int addr = (data_index_ + 1) * 4;
			cout << "[Bubble] About to read(" << addr << ") = ";
			data_[data_index_] = read(addr);
			cout << data_[data_index_] << endl;
			data_index_++;
			if (data_index_ >= nb_data_) {
				state_ = Bubble::SORT;
			}
		}
			break;
		case Bubble::SORT:			
			cout << "[Bubble] Sorting..." << endl;
			bubbleSort(data_, nb_data_);
			wait(500, SC_MS);
			data_index_ = 0;
			state_ = Bubble::WRITE;
			break;
		case Bubble::WRITE:
			{
				// cout << "[Bubble] Write loop." << endl;
				unsigned int addr = (data_index_ + 1) * 4;
				cout << "[Bubble] About to write(" << addr << ", " << data_[data_index_] << ")\n";
				write(addr, data_[data_index_]);
				data_index_++;
				if (data_index_ >= nb_data_) {
					state_ = Bubble::END;
				}
			}
			break;
		default:
			cerr << "[Bubble] ERROR Invalid state." << endl;
		case Bubble::END:
			delete[] data_;
			sc_stop();
			return;
		}
	}
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

	// Attendre que l'accusé de réception soit enlevé.
	do {
		wait(clk_port->posedge_event());
	} while (ack_port.read());

	return data;
}

// Helper
void Bubble::write(unsigned int address, unsigned data) {
	// Envoyer l’adresse et le data à être écrit.
	address_port.write(address);
	data_port.write(data);

	// Envoyer une requête
	// cout << "[Bubble] Sending a request to writer." << endl;
	requestWrite_port.write(true);

	// Attendre un accusé de réception
	do {
		wait(clk_port->posedge_event());
	} while (!ack_port.read());

	// Enlever la requête
	requestWrite_port.write(false);

	// Attendre que l'accusé de réception soit enlevé.
	do {
		wait(clk_port->posedge_event());
	} while (ack_port.read());
}
