`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:01:29 05/08/2023 
// Design Name: 
// Module Name:    LED_1ms 
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
module LED_1ms(
	input iCLK,
	output reg oLED
);
	initial oLED = 0;
	reg [23:0] rCnt=0;
	
	always @(posedge iCLK) 
		begin 
			rCnt = rCnt + 1;
			if (rCnt >= 24'd6000000)
				begin 
					rCnt = 1;
					oLED = !oLED;
				end
		end	
endmodule
