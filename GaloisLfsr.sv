module GaloisLfsr(
	input logic clk,
	input logic rst,
	input logic en,
	output [4:0] state
);
	logic [4:0] state_w;

	always_comb begin
		state_w[4] = state[0];
		state_w[3] = state[4];
		state_w[2] = state[3] ^ state[0];
		state_w[1] = state[2];
		state_w[0] = state[1];
	end

	always_ff @(posedge clk or negedge rst) begin
		if (!rst)    state <= 'b1;
		else if (en) state <= state_w;
	end
endmodule
