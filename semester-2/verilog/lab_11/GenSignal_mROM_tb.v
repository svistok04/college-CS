`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   13:01:06 05/29/2023
// Design Name:   GenSignal_mROM
// Module Name:   C:/Studenci/zv53855/lab_11/GenSignal_mROM_tb.v
// Project Name:  lab_11
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: GenSignal_mROM
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module GenSignal_mROM_tb;

	// Inputs
	reg iCLK;

	// Outputs
	wire oLED;

	// Instantiate the Unit Under Test (UUT)
	GenSignal_mROM uut (
		.iCLK(iCLK), 
		.oLED(oLED)
	);

	initial begin
		// Initialize Inputs
		iCLK = 0;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here

	end
	
   always #10 iCLK = !iCLK;
	
endmodule

