`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   13:52:30 04/17/2023
// Design Name:   behawiralny
// Module Name:   C:/Studenci/zv53855/kolowkium1/behawiralny_tb.v
// Project Name:  kolowkium1
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: behawiralny
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module behawiralny_tb;

	// Inputs
	reg iA;
	reg iB;
	reg iC;
	reg iD;

	// Outputs
	wire oY;

	// Instantiate the Unit Under Test (UUT)
	behawiralny uut (
		.iA(iA), 
		.iB(iB), 
		.iC(iC), 
		.iD(iD), 
		.oY(oY)
	);

	initial begin
	
			iA = 0; iB = 0; iC = 0; iD = 0; #10
			iA = 0; iB = 0; iC = 0; iD = 1; #10
			iA = 0; iB = 0; iC = 1; iD = 0; #10
			iA = 0; iB = 0; iC = 1; iD = 1; #10
			iA = 0; iB = 1; iC = 0; iD = 0; #10
			iA = 0; iB = 1; iC = 0; iD = 1; #10
			iA = 0; iB = 1; iC = 1; iD = 0; #10
			iA = 0; iB = 1; iC = 1; iD = 1; #10
			iA = 1; iB = 0; iC = 0; iD = 0; #10
			iA = 1; iB = 0; iC = 0; iD = 1; #10
			iA = 1; iB = 0; iC = 1; iD = 0; #10
			iA = 1; iB = 0; iC = 1; iD = 1; #10
			iA = 1; iB = 1; iC = 0; iD = 0; #10
			iA = 1; iB = 1; iC = 0; iD = 1; #10
			iA = 1; iB = 1; iC = 1; iD = 0; #10
			iA = 1; iB = 1; iC = 1; iD = 1;
	end
      
endmodule

