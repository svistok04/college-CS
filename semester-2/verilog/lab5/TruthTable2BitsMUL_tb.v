`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   12:39:28 03/27/2023
// Design Name:   mainMUL2BitsGates
// Module Name:   C:/Studenci/zv53855/lab5/MUL2BitsGates_tb.v
// Project Name:  lab5
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: mainMUL2BitsGates
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module TruthTable2BitsMUL_tb;

	// Inputs
	reg [1:0] iA;
	reg [1:0] iB;

	// Outputs
	wire [3:0] oY;

	// Instantiate the Unit Under Test (UUT)
	TruthTable2BitsMUL uut (
		.oY(oY), 
		.iA(iA), 
		.iB(iB)
	);

	initial begin

		iA = 2'b00; iB = 2'b00; #20
		iA = 2'b00; iB = 2'b01; #20
		iA = 2'b00; iB = 2'b10; #20
		iA = 2'b00; iB = 2'b11; #20
		iA = 2'b01; iB = 2'b00; #20
		iA = 2'b01; iB = 2'b01; #20
		iA = 2'b01; iB = 2'b10; #20
		iA = 2'b01; iB = 2'b11; #20
		iA = 2'b10; iB = 2'b00; #20
		iA = 2'b10; iB = 2'b01; #20
		iA = 2'b10; iB = 2'b10; #20
		iA = 2'b10; iB = 2'b11; #20
		iA = 2'b11; iB = 2'b00; #20
		iA = 2'b11; iB = 2'b01; #20
		iA = 2'b11; iB = 2'b10; #20
		iA = 2'b11; iB = 2'b11; #20
		iA = 2'b00; iB = 2'b00;

	end
      
endmodule


