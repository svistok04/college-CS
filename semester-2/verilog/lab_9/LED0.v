`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:40:02 05/08/2023 
// Design Name: 
// Module Name:    LED0 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module LED0(
    input iCLK,
    output oLED
    );
	 
	 reg [3:0] rCnt = 0;
	 
	 always @(posedge iCLK) rCnt = rCnt + 1;
	 
	 assign oLED = rCnt[3];

endmodule
