`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:42:20 05/29/2023 
// Design Name: 
// Module Name:    GenSignal 
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
module GenSignal(
    input iCLK,
    output reg oLED
    );
	 
	 initial oLED = 0;
	 reg [3:0] rStan = 12;
	 reg [21:0] rCnt = 0;
	 reg sCLK100ms = 1;
	 
	 always @(posedge iCLK)
		begin
				rCnt = rCnt + 1;
				if (rCnt >= 22'd2500000)
					begin 
						rCnt = 0;
						sCLK100ms = !sCLK100ms;
					end
		end
		
always @(posedge sCLK100ms)
	begin 
		rStan = rStan + 1;
		if (rStan >= 4'd12) rStan = 4'd0;
	end
	
always @(rStan) 
	begin
		/*
		case(rStan)
			4'd0 : oLED = 1;
			4'd1 : oLED = 0;
			4'd2 : oLED = 0;
			4'd3 : oLED = 1;
			4'd4 : oLED = 0;
			4'd5 : oLED = 1;
			4'd6 : oLED = 0;
			4'd7 : oLED = 0;
			4'd8 : oLED = 0;
			4'd9 : oLED = 0;
			4'd10 :oLED = 1;
			4'd11 :oLED = 0;
			default:oLED = 0;
		endcase
		*/
		oLED = 0;
			if ( rStan == 4'd0 ) oLED = 1;
			if ( rStan == 4'd1 ) oLED = 0;
			if ( rStan == 4'd2 ) oLED = 0;
			if ( rStan == 4'd3 ) oLED = 1;
			if ( rStan == 4'd4 ) oLED = 0;
			if ( rStan == 4'd5 ) oLED = 1;
			if ( rStan == 4'd6 ) oLED = 0;
			if ( rStan == 4'd7 ) oLED = 0;
			if ( rStan == 4'd8 ) oLED = 0;
			if ( rStan == 4'd9 ) oLED = 0;
			if ( rStan == 4'd10 ) oLED = 1;
			if ( rStan == 4'd11 ) oLED = 0;
	end

endmodule
