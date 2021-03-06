/*****************************************************************************
*
* File: SmsDebugger.h
*
* Project: Osmose emulator.
*
* Description: This class will handle built-in debugger. 
*
* Author: Vedder Bruno
* Date: 16/10/2004, 18h00
*
* URL: http://bcz.emu-france.com/
*****************************************************************************/
#ifndef SMS_DEBUGGER_H
#define SMS_DEBUGGER_H

#include "Definitions.h"
#include "MemoryMapper.h"
#include "IOMapper.h"
#include "SmsEnvironment.h"
#include "z80_disasm/Z80Dasm.h"
#include "VDP.h"
#include "DebugEventListener.h"

using namespace std;

#define MAX_BREAKPOINTS 16

class SmsDebugger : public DebugEventListener
{
public:

    SmsDebugger();
    void setCPU(Z80 *c) {cpu = c;}
    void setMemoryMapper(MemoryMapper *mm) {mem = mm;}
    void setEnvironment(SmsEnvironment *se){env = se;}
    void setVDP(VDP *vd) {v = vd;}
    void setIOMapper(IOMapper *im){iom = im;}
    void setDasm(Z80Dasm *d){dasm = d;}    
    void enter();
    
	/* DebugEventListener interface implementation. */
	void sendDebugEvent(int event_type, char* src, char *message);

protected:

    MemoryMapper   *mem;
    SmsEnvironment *env;
    VDP	           *v;  
    IOMapper       *iom;
    Z80Dasm 	   *dasm;
    Z80 	       *cpu;

private:

    int  scanlineBreakpoint;
    bool any_breakpoint;	      /* Flag to avoid bp search.	 */
    bool end_session;		      /* Have we leaved the debugger ?   */
    bool breakpoint_on_irq;
	bool breakpoint_on_enable_interrupt;
	bool breakpoint_on_disable_interrupt;
    bool cpu_steping;				
	int breakpoints[MAX_BREAKPOINTS]; /* INTeger chose to allow -1 value */
    unsigned int bp_index;	      /* Index in circular buffer of bp. */
    void help();
    void dpr();
    void dvdpr();
    void vdpi();
    void dvram();
    void dumpRegisters();
    void clearBreakpoints();
    void addBreakpoint(int add);
    void listBreakpoints();
    void setScanlineBreakpoint(int scanline);
    void exec_cmd(char *cmd, int param1);
    void exec_cmd(char *cmd, int param1, int param2);
    void unknownCommand();
};
#endif
