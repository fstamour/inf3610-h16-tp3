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
Writer::Writer(sc_module_name name)
/* └ complÚter */
{
	/*

	└ complÚter

	*/
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
	/*

	└ complÚter

	*/
}


/*

└ complÚter

*/

void Writer::write_thread() {
	// dataPortRAM_port->Write(addr, data);
}
