`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   13:03:23 05/08/2023
// Design Name:   LED_1ms
// Module Name:   C:/Studenci/zv53855/lab_9/LED_1ms_tb.v
// Project Name:  lab_9
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: LED_1ms
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module LED_1ms_tb;

	// Inputs
	reg iCLK;

	// Outputs
	wire oLED;

	// Instantiate the Unit Under Test (UUT)
	LED_1ms uut (
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

