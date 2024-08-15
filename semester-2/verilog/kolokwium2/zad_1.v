`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:26:39 06/05/2023 
// Design Name: 
// Module Name:    zad_1 
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
module zad_1(
		input iCLK,
		output reg [7:0] seg,
		output reg [2:0] baza
    );

reg [3:0] rStan = 6;

reg [2:0] baza_temp = 3'b001;

reg [22:0] rCnt = 0;
reg sCLK1s = 1;

always @(posedge iCLK) //zegar 1s
	begin
		rCnt = rCnt +1;
		if (rCnt >= 23'd6000000)
		begin
			rCnt =0;
			sCLK1s = !sCLK1s;
		end
	end

always @(posedge sCLK1s) //ruch
	begin
		rStan = rStan + 1;
		if (rStan >= 4'd6) rStan = 4'd0;
	end
	
always @(rStan)
	begin
		if (rStan == 4'd0) 
			begin
				baza = 3'b110;
				seg = 8'b00111001;
			end
		if (rStan == 4'd1) 
			begin
				baza = 3'b101;
				seg = 8'b00111001;
			end
		if (rStan == 4'd2) 
			begin
				baza = 3'b011;
				seg = 8'b00111001;
			end
		if (rStan == 4'd3) 
			begin
				seg = 8'b11000101;
			end
		if (rStan == 4'd4) 
			begin
				baza = 3'b101;
				seg = 8'b11000101;
			end
		if (rStan == 4'd5) 
			begin
				baza = 3'b110;
				seg = 8'b11000101;
			end
	end

endmodule
