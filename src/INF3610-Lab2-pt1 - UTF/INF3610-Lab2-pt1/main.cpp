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

	/* Pour la partie AT
	sc_buffer<unsigned int> 
		data_buf("data_buf"),
		address_buf("address_buf");
	bubble.data_port(data_buf);
	reader.data_port(data_buf);

	bubble.address_port(address_buf);
	reader.address_port(address_buf);

	sc_buffer<bool>
		requestRead_buf("requestRead_buf"),
		requestWrite_buf("requestWrite_buf"),
		ack_buf("ack_buf");

	bubble.requestRead_port(requestRead_buf);
	bubble.requestWrite_port(requestWrite_buf);
	bubble.ack_port(ack_buf);
	reader.request_port(requestRead_buf);
	reader.ack_port(ack_buf);*/

	bubble.readPort(reader);
	bubble.writePort(writer);
	reader.dataPortRAM_port(ram);
	writer.dataPortRAM_port(ram);

	


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
