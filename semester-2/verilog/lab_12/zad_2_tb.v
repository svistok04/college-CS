`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   13:33:56 06/05/2023
// Design Name:   zad_2
// Module Name:   C:/Studenci/zv53855/lab_12/zad_2_tb.v
// Project Name:  lab_12
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: zad_2
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module zad_2_tb;

	// Inputs
	reg iCLK;

	// Outputs
	wire [7:0] seg;
	wire [2:0] baza;

	// Instantiate the Unit Under Test (UUT)
	zad_2 uut (
		.iCLK(iCLK), 
		.seg(seg), 
		.baza(baza)
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

