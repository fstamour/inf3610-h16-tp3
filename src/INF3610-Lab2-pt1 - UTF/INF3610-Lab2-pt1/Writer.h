///////////////////////////////////////////////////////////////////////////////
//
//	Writer.h
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <systemc.h>
#include "LMBIF.h"
#include "InterfaceWrite.h"

///////////////////////////////////////////////////////////////////////////////
//
//	Class Writer
//
///////////////////////////////////////////////////////////////////////////////
class Writer : public sc_module, public InterfaceWrite /* � compl�ter */
{
public:
	// Ports
	/*

	� compl�ter

	*/
	sc_in_clk clk_port; // Horloge
	sc_port<LMBIF>	dataPortRAM_port;

	// Constructor
	Writer(sc_module_name name);

	// Destructor
	~Writer();

	// M�thode
	virtual void Write(unsigned int addr, unsigned int data);

private:
	SC_HAS_PROCESS(Writer);

	void write_thread();

	/*

	� compl�ter

	*/

};

