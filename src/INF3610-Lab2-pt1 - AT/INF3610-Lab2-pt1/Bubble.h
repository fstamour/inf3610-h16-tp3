///////////////////////////////////////////////////////////////////////////////
//
//	Bubble.h
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <systemc.h>
#include <stdio.h>

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
		sc_inout<unsigned int> data_port; // Donn�e
		sc_out<bool> requestRead_port; // Requ�te au lecteur
		sc_out<bool> requestWrite_port; // Requ�te � l��crivain
		sc_in<bool>	ack_port; // Accus� de r�ception

		// Constructor
		Bubble( sc_module_name name );
		
		// Destructor
		~Bubble();
		
	private:

		// �tat possible du thread de bubble.
		enum state_t {
			INIT,
			READ,
			SORT,
			WRITE,
			END
		};

		/// Variables d'�tats
		state_t state_ = INIT;
		unsigned int nb_data_ = 0;
		unsigned int* data_ = nullptr;
		size_t data_index_ = 0;

		// Process SystemC
		SC_HAS_PROCESS(Bubble);
		
		void thread(void);
		void bubbleSort(unsigned int *ptr, int counter);

		// Helpers
		unsigned int read(unsigned int address);
		void write(unsigned int address, unsigned data);
};

