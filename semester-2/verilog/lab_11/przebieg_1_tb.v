`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   13:04:54 05/29/2023
// Design Name:   przebieg_1
// Module Name:   C:/Studenci/zv53855/lab_11/przebieg_1_tb.v
// Project Name:  lab_11
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: przebieg_1
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module przebieg_1_tb;

	// Inputs
	reg iCLK;

	// Outputs
	wire oLED;

	// Instantiate the Unit Under Test (UUT)
	przebieg_1 uut (
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

