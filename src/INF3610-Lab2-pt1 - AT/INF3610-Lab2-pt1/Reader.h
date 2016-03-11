///////////////////////////////////////////////////////////////////////////////
//
//	Reader.h
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <systemc.h>
#include "LMBIF.h"

///////////////////////////////////////////////////////////////////////////////
//
//	Class Reader
//
///////////////////////////////////////////////////////////////////////////////
class Reader : public sc_module
{
	public:

		// Ports
		sc_in_clk clk_port; // Horloge
		
		sc_port<LMBIF>	dataPortRAM_port; // Port pour la mémoire de donnée
		
		sc_out<unsigned int> data_port; // Donnée
		sc_in<unsigned int> address_port; // Adresse 
		sc_out<bool> ack_port; // Accusé de réception
		sc_in<bool> request_port; // Requête
		
		// Constructor
		Reader( sc_module_name name );

		// Destructor
		~Reader();

	private:
		SC_HAS_PROCESS(Reader);

		void read_thread();
};

