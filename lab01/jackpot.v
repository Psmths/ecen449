`timescale 1ns / 1ps
module jackpot(
    input [3:0] SWITCHES,
    output [3:0] LEDS,
    input CLOCK,
    input BTN0
    );
    
    parameter x = 64;

    reg [32:0] divider;        //Clock division reg
    reg[3:0] outs;            //LED output reg
    reg won;            //True if player has won
    reg internal_clock;
    
    
    
    always@(posedge CLOCK) begin
        divider <= divider + 1; //Increment the clock divider
        
        internal_clock <= divider[24];
        
    end
    
    
    always@(posedge internal_clock) 
    begin
    
        if (BTN0 == 1'b1) 
            begin
                outs <= 4'b0001;
            end
        
        else
        
            if (won) 
                begin
                    if(divider >= 4'h00FF)
                        begin
                            outs <= 4'b1111;
                        end
                    else
                        begin
                            outs <=4'b0000;
                        end
                end
            
            else 
                begin
                    case(outs)
                        4'b0001:outs<=4'b0010;
                        4'b0010:outs<=4'b0100;
                        4'b0100:outs<=4'b1000;
                        4'b1000:outs<=4'b0001;
                    endcase
                end
    end
    
    always@(SWITCHES or BTN0) 
        begin
            if(SWITCHES[3:0] == outs[3:0]) 
                begin
                    won <= 1'b1;
                end
            if(BTN0)
                begin
                    won <= 1'b0;
                end
        end
    
    //Display one hot LEDs
    assign LEDS[3:0] = outs[3:0];
endmodule
