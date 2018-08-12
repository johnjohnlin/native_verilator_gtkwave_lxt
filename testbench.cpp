#include <memory>
#include <iostream>
#include <random>
#include <algorithm>
#include "VGaloisLfsr.h"
#include "verilated_vcd_c.h"

int main()
{
	using namespace std;
	constexpr int SIM_CYCLE = 1000;

	// Init simulation
	unique_ptr<VGaloisLfsr> TOP(new VGaloisLfsr);
	unique_ptr<VerilatedVcdC> tfp(new VerilatedVcdC);
	vluint64_t sim_time = 0;
	Verilated::traceEverOn(true);
	TOP->trace(tfp.get(), 99);
	tfp->open ("GaloisLfsr.lxt2");
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0,3);

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
		TOP->en = distribution(generator) == 0;
		tfp->dump(sim_time++);
		TOP->clk = 0;
		Eval;
	}
	tfp->close();
	return 0;
}
