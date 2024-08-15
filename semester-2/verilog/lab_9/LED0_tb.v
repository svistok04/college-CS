`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   12:41:26 05/08/2023
// Design Name:   LED0
// Module Name:   C:/Studenci/zv53855/lab_9/LED0_tb.v
// Project Name:  lab_9
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: LED0
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module LED0_tb;

	// Inputs
	reg iCLK;

	// Outputs
	wire oLED;

	// Instantiate the Unit Under Test (UUT)
	LED0 uut (
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
      
	always #41.67 iCLK = !iCLK;
		
endmodule

