#include <stdio.h>
#include <string.h>

void populate_matrix(int r, int c, FILE *data, float mat[r][c]){
    float readval;
    for (int i = 0; i < r; ++i){
        for (int j = 0; j < c; ++j){
            fscanf(data,"%f",&readval);
            mat[i][j] = readval;
	}
    }
}

void write_matrix(int r, int c, float mat[r][c], FILE *o){
    for (int i = 0; i < r; ++i){
	for (int j = 0; j < c; ++j){
            fprintf(o,"%f\t",mat[i][j]);
	}
	fprintf(o,"\n");
    }
}

void multiply_matrices(int ah, int aw, int bh, int bw, int ch, int cw, float a[ah][aw], float b[bh][bw], float c[ch][cw]){
    for (int i = 0; i < ah; i++){
        for (int j = 0; j < bw; j++){
	    c[i][j] = 0;
            for (int k = 0; k < bh; k++){
                c[i][j] += a[i][k]*b[k][j];
            }
	}
    }
}

main() {
    FILE *m1,*m2,*out; //File pointers
    int aw,ah,bw,bh,cw,ch; //Matrix A/B/C (w)idth/(h)eight

    //Open all associated files
    m1 = fopen("./inA.txt", "r");
    m2 = fopen("./inB.txt", "r");
    out = fopen("./outC.txt","w");
    
    //Get the dimensions of the supplied matrices
    //and place this info into int variables
    fscanf(m1,"%d %d",&ah,&aw);
    fscanf(m2,"%d %d",&bh,&bw);

    //Check if we can perform the multiplication
    if(bh != aw){
        //Cannot perform multiplication. Quit!
        printf("Error: Matrix dimensions incompatible!");
        return;
    }else{
        //Set the dimensions for the output matrix
        ch = ah;
        cw = bh;
    }

    //Pre-allocate memory for all matrices
    float matA[ah][aw];
    float matB[bh][bw];
    float matC[ch][cw];

    populate_matrix(ah,aw,m1,matA);
    populate_matrix(bh,bw,m2,matB);

    multiply_matrices(ah,aw,bh,bw,ch,cw,matA,matB,matC);

    write_matrix(ch,cw,matC,out);
    
    fclose(m1);
    fclose(m2);
}
