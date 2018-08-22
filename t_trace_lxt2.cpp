#include <stdint.h>
#include "Vt_trace_lxt2.h"
#include "verilated_lxt2_c.h"

int main()
{
	using namespace std;
	constexpr int SIM_CYCLE = 1000;

	// Init simulation
	Vt_trace_lxt2 *TOP = new Vt_trace_lxt2;
 	VerilatedVcdC *tfp = new VerilatedVcdC;
	vluint64_t sim_time = 0;
	Verilated::traceEverOn(true);
	TOP->trace(tfp, 99);
	tfp->open ("Vt_trace_lxt2.lxt2");
	uint8_t seed = 1;

	// Simulation
#define Eval TOP->eval();tfp->dump(sim_time++);
	TOP->en = 0;
	TOP->clk = 0;
	TOP->rst = 1;
	Eval;
	TOP->rst = 0;
	Eval;
	TOP->rst = 1;
	Eval;
	for (
		int cycle = 0;
		cycle < SIM_CYCLE and not Verilated::gotFinish();
		++cycle
	) {
		TOP->clk = 1;
		TOP->eval();
		TOP->en = (seed >> 3) < 5; // prob = 5/32
		tfp->dump(sim_time++);
		TOP->clk = 0;
		Eval;
		// a simple random
		seed = seed * 163;
	}
	tfp->close();
	delete tfp;
	delete TOP;
	return 0;
}
