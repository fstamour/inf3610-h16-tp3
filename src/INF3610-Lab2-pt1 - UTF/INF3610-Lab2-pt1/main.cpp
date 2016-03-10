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

#define RAMSIZE 40
// TODO 0x400

// Global variables
bool m_bError = false;

///////////////////////////////////////////////////////////////////////////////
//
//	Main
//
///////////////////////////////////////////////////////////////////////////////
int sc_main(int arg_count, char **arg_value)
{
	int sim_units = 2; //SC_NS 
	
	// Components
	DataRAM ram("ram", "chiffre.hex", RAMSIZE, false);
	Reader reader("Lecteur");
	Writer writer("Ecrivain");
	Bubble bubble("TriABulle");
	
	/*** Connexions ***/

	bubble.readPort(reader);
	bubble.writePort(writer);
	reader.dataPortRAM_port(ram);
	writer.dataPortRAM_port(ram);

	/*** Démarrage de l'application ***/
	if (!m_bError)
	{
		cout << "Demarrage de la simulation." << endl;	
		sc_start( -1, sc_core::sc_time_unit(sim_units) );
		cout << endl << "Simulation s'est terminee a " << sc_time_stamp() << endl;
	}
	// Fin du programme
	return 0;
}
