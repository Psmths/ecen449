`timescale 1ns / 1ps
module jackpot(
    input [3:0] SWITCHES,
    output [3:0] LEDS,
    input CLOCK,
    input RESET
    );

    reg [23:0] divider;        //Clock division reg
    reg[3:0] outs;            //LED output reg
    reg won = 1'b0;            //True if player has won
    
    
    
    always@(posedge CLOCK or posedge RESET) begin
    
        divider <= divider + 1; //Increment the clock divider
        
        //One hot fashion logic using LSL
        if (won == 1'b0 & divider == 3'hFFF) begin
            outs <= outs << 1;
        end
        //Reset one hot logic
        if(won == 1'b0 & outs == 4'b0000) begin
            outs <= 4'b0001;
        end
        //Manual reset
        if(RESET == 1) begin
            outs <= 4'b0001;
        end
        
        if(won == 1'b1) begin
            outs <= 4'b1111;
        end
        
    end
    
    always@(posedge SWITCHES or posedge RESET) begin
        if(SWITCHES[3:0] == outs[3:0]) begin
            won <= 1'b1;
        else
            won <= 1'b0;    //Triggered during RESET as well!
    end
    
    //Display one hot LEDs
    assign LEDS[3:0] = outs[3:0];
endmodule
