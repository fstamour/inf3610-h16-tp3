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
	
	// � utiliser OBLIGATOIREMENT dans la d�claration de votre horloge
	const sc_core::sc_time_unit simTimeUnit = SC_NS;
	const int clk_freq = 4000;	
	sc_clock clk("Horloge", sc_time(clk_freq, simTimeUnit));
	
	/*** Components ***/
	DataRAM ram("ram", "chiffre.hex", RAMSIZE, false);
	Reader reader("Lecteur");
	Writer writer("Ecrivain");
	Bubble bubble("TriABulle");

	/*** Connections ***/
	/// Clock
	bubble.clk_port(clk);
	reader.clk_port(clk);
	writer.clk_port(clk);

	/// Ram
	reader.dataPortRAM_port(ram);
	writer.dataPortRAM_port(ram);
	
	/// Data
	sc_signal<unsigned int, SC_MANY_WRITERS> data_buf("data_buf");
	sc_signal<unsigned int>	address_buf("address_buf");
	bubble.data_port(data_buf);
	reader.data_port(data_buf);
	writer.data_port(data_buf);

	/// Address
	bubble.address_port(address_buf);
	reader.address_port(address_buf);
	writer.address_port(address_buf);

	/// Request
	sc_signal <bool>
		requestRead_buf("requestRead_buf"),
		requestWrite_buf("requestWrite_buf");
	
	bubble.requestRead_port(requestRead_buf);
	reader.request_port(requestRead_buf);

	bubble.requestWrite_port(requestWrite_buf);
	writer.request_port(requestWrite_buf);

	/// ACK
	sc_signal<bool, SC_MANY_WRITERS> ack_buf("ack_buf");
	bubble.ack_port(ack_buf);	
	reader.ack_port(ack_buf);
	writer.ack_port(ack_buf);


	// D�marrage de l'application
	if (!m_bError)
	{
		cout << "D�marrage de la simulation." << endl;
		sc_start( -1, sc_core::sc_time_unit(sim_units) );
		cout << endl << "Simulation s'est termin�e � " << sc_time_stamp();
	}
	// Fin du programme
	return 0;
}
