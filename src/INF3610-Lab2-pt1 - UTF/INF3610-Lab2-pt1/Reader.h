///////////////////////////////////////////////////////////////////////////////
//
//	Reader.h
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <systemc.h>
#include "LMBIF.h"
#include "InterfaceRead.h"

///////////////////////////////////////////////////////////////////////////////
//
//	Class Reader
//
///////////////////////////////////////////////////////////////////////////////
class Reader : public sc_module, public InterfaceRead /* � compl�ter */
{
	public:

		// Ports
		/*
	
		� compl�ter
	
		*/
		sc_in_clk clk_port; // Horloge

		//sc_port<LMBIF>	dataPortRAM_port; // Port pour la m�moire de donn�e
		sc_out<unsigned int> data_port; // Donn�e
		//sc_in<unsigned int> address_port; // Adresse 
		/*sc_out<bool> ack_port; // Accus� de r�ception
		sc_in<bool> request_port; // Requ�te*/

		
		// Constructor
		Reader( sc_module_name name );

		// Destructor
		~Reader();

		// M�thode
		virtual unsigned int Read(unsigned int offset);

		

	private:
		SC_HAS_PROCESS(Reader);

		void read_thread();
	
	/*
		
	� compl�ter
		
	*/

};

