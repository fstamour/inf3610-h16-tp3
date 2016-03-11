///////////////////////////////////////////////////////////////////////////////
//
//	Writer.cpp
//
///////////////////////////////////////////////////////////////////////////////
#include "Writer.h"

///////////////////////////////////////////////////////////////////////////////
//
//	Constructor
//
///////////////////////////////////////////////////////////////////////////////
Writer::Writer(sc_module_name name) : sc_module(name)
{
	SC_THREAD(write_thread);
	sensitive << clk_port;
}

///////////////////////////////////////////////////////////////////////////////
//
//	Destructor
//
///////////////////////////////////////////////////////////////////////////////
Writer::~Writer()
{
}

void Writer::write_thread() {
	cout << "[Writer] Thread started." << endl;
	while (1) {
		// cout << "[Writer] Waiting a request." << endl;
		//Attendre une requ�te
		do{
			wait(clk_port->posedge_event());
		} while (!request_port.read());

		//Lire la valeur de l�adresse
		unsigned int addr = address_port.read();

		//Lire la donn�e
		unsigned int data = data_port.read();

		// On �crit la donn�e � l�adresse sp�cif�e.
		//cout << "[Writer] About to write " << data << " at address " << addr << endl;
		dataPortRAM_port->Write(addr, data);

		// Envoyer un accus� de r�ception
		ack_port.write(true);

		// On attend que bubble mette request_port � false.
		// cout << "[Writer] About to wait on request port == false." << endl;
		do{
			wait(clk_port->posedge_event());
		} while (request_port.read());

		// cout << "[Writer] About to remove the ack." << endl;
		// Enlever l�accus� de r�ception
		ack_port.write(false);
	}
}
