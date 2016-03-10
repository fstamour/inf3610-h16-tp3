///////////////////////////////////////////////////////////////////////////////
//
//	Bubble.h
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <systemc.h>
#include <stdio.h>

/*
#include "InterfaceRead.h"
#include "InterfaceWrite.h"	 //	à décommenter au moment opportun
*/

///////////////////////////////////////////////////////////////////////////////
//
//	Class Bubble
//
///////////////////////////////////////////////////////////////////////////////
class Bubble : public sc_module
{
	public: 
		// Ports   
		sc_in_clk clk_port; // Horloge

		sc_out<unsigned int> address_port; // Adresse		
		// TODO sc_inout?
		sc_in<unsigned int> data_port; // Donnée
		sc_out<bool> requestRead_port; // Requête au lecteur
		sc_out<bool> requestWrite_port; // Requête à l’écrivain
		sc_in<bool>	ack_port; // Accusé de réception

		// Constructor
		Bubble( sc_module_name name );
		
		// Destructor
		~Bubble();
		
	private:

		enum state_t {
			INIT,
			READ,
			SORT,
			WRITE,
			END
		};

		state_t state_ = INIT;
		unsigned int nb_data_ = 0;
		unsigned int* data_ = nullptr;
		size_t data_index_ = 1;

		// Process SystemC
		SC_HAS_PROCESS(Bubble);
		
		void thread(void);
		void bubbleSort(unsigned int *ptr, int counter);

		unsigned int read(unsigned int address);
		// TODO unsigned int write(unsigned int address, unsigned data);
};

