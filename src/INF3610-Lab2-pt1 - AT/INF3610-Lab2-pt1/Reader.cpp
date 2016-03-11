///////////////////////////////////////////////////////////////////////////////
//
//	Reader.cpp
//
///////////////////////////////////////////////////////////////////////////////
#include "Reader.h"

///////////////////////////////////////////////////////////////////////////////
//
//	Constructor
//
///////////////////////////////////////////////////////////////////////////////
Reader::Reader(sc_module_name name) : sc_module(name)
{
	SC_THREAD(read_thread);
	sensitive << clk_port;
}

///////////////////////////////////////////////////////////////////////////////
//
//	Destructor
//
///////////////////////////////////////////////////////////////////////////////
Reader::~Reader()
{}


void Reader::read_thread() {
	cout << "[Reader] Thread started." << endl;
	while (1) {
		// On attend une requ�te.	
		do{
			wait(clk_port->posedge_event());
			// cout << "[Reader] CLK!" << endl;
		} while (!request_port.read());
	
	
		// Lire la valeur de l�adresse
		unsigned int addr = address_port.read();
		//cout << "[Reader] About to read at address " << addr << endl;

		// Demander � la m�moire la donn�e � l�adresse lue
		unsigned int data = dataPortRAM_port->Read(addr);

		// On �crit la donn�e lue...
		data_port.write(data);

		// Envoyer un accus� de r�ception
		ack_port.write(true);

		//cout << "[Reader] About to wait on request port == false." << endl;
		// On attend que bubble mette request_port � false.
		do{
			wait(clk_port->posedge_event());
		} while (request_port.read());

		//cout << "[Reader] About to remove the ack." << endl;
		// Enlever l�accus� de r�ception
		ack_port.write(false);
	}
}
