///////////////////////////////////////////////////////////////////////////////
//
//	Bubble.h
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <systemc.h>
#include <stdio.h>
#include "InterfaceRead.h"
#include "InterfaceWrite.h"	 //	à décommenter au moment opportun


///////////////////////////////////////////////////////////////////////////////
//
//	Class Bubble
//
///////////////////////////////////////////////////////////////////////////////
class Bubble : public sc_module
{
	public: 
		// Ports    
		/*
		
		À compléter
		
		*/
		sc_in_clk clk_port; // Horloge
		/* Pour la parti AT
		sc_out<unsigned int> address_port; // Adresse		
		// TODO sc_inout?
		sc_in<unsigned int> data_port; // Donnée
		sc_out<bool> requestRead_port; // Requête au lecteur
		sc_out<bool> requestWrite_port; // Requête à l’écrivain
		sc_in<bool>	ack_port; // Accusé de réception
		*/
	
		/*** Partie UT ***/ 
		sc_port<InterfaceRead> readPort;
		sc_port<InterfaceWrite> writePort;

		// Constructor
		Bubble( sc_module_name name );
		
		// Destructor
		~Bubble();
		
	private:
		// Process SystemC
		SC_HAS_PROCESS(Bubble);
		
		void thread(void);
		void bubbleSort(unsigned int *ptr, int counter);
};

