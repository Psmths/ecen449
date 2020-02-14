module hw1_circuit_structural(
    input A, B, C, D,
    output E, F
    );
    
    wire X,Y,Z; //Internal wires
    
    //The following represent all the logic
    //gates seen in the diagram.
    not(X, A);
    and(Y, A, B);
    or(Z, Y, C);
    or(E, X, Z);
    nand(F,Z,D);
    
endmodule

module hw1_circuit_dataflow(
    input A, B, C, D,
    output E, F
    );

    assign E = ~A | (C | (B & A)); //E output
    assign F = ~(D & (C | (A & B))); //F output
    
endmodule


module hw1_circuit_behavioral(
    input A, B, C, D,
    output E, F
    );
    
    wire X,Y,Z; //Internal wires
    
    always@(A or B or C or D) //Sensitive to all inputs 
    begin
        X = ~A;
        Y = A & B;
        Z = Y | C;
        F = ~(Z & D);
        E = X | Z;
    end
    
endmodule