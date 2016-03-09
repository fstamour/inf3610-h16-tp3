///////////////////////////////////////////////////////////////////////////////
//
//	main.cpp
//
///////////////////////////////////////////////////////////////////////////////
#include <systemc.h>
#include "Bubble.h"
#include "Reader.h"
#include "Writer.h"
#include "DataRAM.h"

#define RAMSIZE 0x400

// Global variables
bool m_bError = false;

///////////////////////////////////////////////////////////////////////////////
//
//	Main
//
///////////////////////////////////////////////////////////////////////////////
int sc_main(int arg_count, char **arg_value)
{
	// Variables
	int sim_units = 2; //SC_NS 
	
	// Components
	/*

	À compléter

	*/
	DataRAM ram("ram", "chiffre.hex", RAMSIZE, false);
	Reader reader("Lecteur");
	Writer writer("Ecrivain");
	Bubble bubble("TriABulle");

	sc_clock clk("Horloge", sc_time(500, SC_MS));

	
	// Connexions
	/*

	À compléter

	*/
	/// Clock
	bubble.clk_port(clk);
	reader.clk_port(clk);
	writer.clk_port(clk);
	// Not DataRam

	// Rendu la
	sc_signal<unsigned int> buf1;
	//bubble.data_port(buf1);
	reader.data_port(buf1);

	// Démarrage de l'application
	if (!m_bError)
	{
		cout << "Demarrage de la simulation." << endl;	
		sc_start( -1, sc_core::sc_time_unit(sim_units) );
		cout << endl << "Simulation s'est terminee a " << sc_time_stamp() << endl;
	}
	// Fin du programme
	return 0;
}
