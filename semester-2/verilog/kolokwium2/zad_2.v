`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:20:27 06/05/2023 
// Design Name: 
// Module Name:    zad_2 
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
module zad_2(
    input iCLK,
    output reg [7:0] seg,
    output reg [2:0] baza
    );

reg [4:0] rStan = 10;

reg [22:0] rCnt = 0;
reg sCLK1s = 1;

always @(posedge iCLK) //zegar 1s
	begin
		rCnt = rCnt +1;
		if (rCnt >= 23'd10000000)
		begin
			rCnt =0;
			sCLK1s = !sCLK1s;
		end
	end

always @(posedge sCLK1s) //ruch
	begin
		rStan = rStan + 1;
		if (rStan >= 4'd10) rStan = 4'd0;
	end

always @(posedge sCLK1s)
	begin
		
		case(rStan)
		4'd0 : 
		
			begin
				baza = 3'b110;
				seg = 8'b10111111;
			end
		4'd1 : 
			begin
				seg = 8'b01111111;
			end
		4'd2 : 
			begin
				baza = 3'b101;
			end
		4'd3 : 
			begin
				baza = 3'b011;
			end
		4'd4 : 
			begin
				seg = 8'b11111011;
			end
		4'd5 : 
			begin
				seg = 8'b11110111;
			end
		4'd6 : 
			begin
				seg = 8'b11101111; 
			end
		4'd7 : 
			begin
				baza = 3'b101;
			end
		4'd8 : 
			begin
				baza = 3'b110;
			end
		4'd9 : 
			begin
				seg = 8'b11011111;
			end
	endcase
end

endmodule
