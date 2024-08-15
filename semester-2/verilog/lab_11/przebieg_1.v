`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:03:40 05/29/2023 
// Design Name: 
// Module Name:    przebieg_1 
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
module przebieg_1(
    input iCLK,
    output reg oLED
    );

	initial oLED = 0;
	reg [3:0] rStan = 12;
	reg [21:0] rCnt = 0;
	reg sCLK100ms = 1;

	wire mROM[11:0];
	
	assign mROM[0] = 1;
	assign mROM[1] = 1;
	assign mROM[2] = 1;
	assign mROM[3] = 0;
	assign mROM[4] = 0;
	assign mROM[5] = 1;
	assign mROM[6] = 1;
	assign mROM[7] = 0;
	assign mROM[8] = 0;
	assign mROM[9] = 1;
	assign mROM[10] = 0;
	assign mROM[11] = 0;

	always @(posedge iCLK)
		begin
			rCnt = rCnt + 1;
			if (rCnt >= 22'd2500000)
				begin
					rCnt = 0;
					sCLK100ms = !sCLK100ms;
				end
		end
		
	always@(posedge sCLK100ms)
		begin
			rStan = rStan + 1;
			if(rStan >= 4'd12) rStan = 4'd0;
		end
	
	always@(rStan)
		begin
				oLED = mROM[rStan];
		end

endmodule
