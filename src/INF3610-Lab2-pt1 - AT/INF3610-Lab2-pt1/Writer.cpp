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
		//Attendre une requête
		do{
			wait(clk_port->posedge_event());
		} while (!request_port.read());

		//Lire la valeur de l’adresse
		unsigned int addr = address_port.read();

		//Lire la donnée
		unsigned int data = data_port.read();

		// On écrit la donnée à l’adresse spécifée.
		//cout << "[Writer] About to write " << data << " at address " << addr << endl;
		dataPortRAM_port->Write(addr, data);

		// Envoyer un accusé de réception
		ack_port.write(true);

		// On attend que bubble mette request_port à false.
		// cout << "[Writer] About to wait on request port == false." << endl;
		do{
			wait(clk_port->posedge_event());
		} while (request_port.read());

		// cout << "[Writer] About to remove the ack." << endl;
		// Enlever l’accusé de réception
		ack_port.write(false);
	}
}
