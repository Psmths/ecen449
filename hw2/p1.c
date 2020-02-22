#include <stdio.h>
#include <string.h>

//alloc_mat
//Function to allocate memory for an entire matrix. Inputs
//are the rows and columns of the matrix in int type. Function
//returns pointer to the start of the matrix in memory. 
double** alloc_mat(int r, int c){
    int total_size = r*c; //Get the total number of doubles needed
    double** mat = malloc(total_size * sizeof(double)); //Allocate it
    printf("Matrix of size %d x %d allocated!\n",r,c);
}

double** populate_matrix(FILE** data, double** mat, int r, int c){
    double readval;
    printf("Scanning in matrix...\n");
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            fscanf(*data,"%f",readval);
	    printf("%f",readval);
	    mat[i][j] = readval;
	}
    }
}

main() {
    FILE *m1,*m2,*out; //File pointers
    int aw,ah,bw,bh,cw,ch; //Matrix A/B/C (w)idth/(h)eight

    //Open all associated files
    m1 = fopen("./inA.txt", "r");
    m2 = fopen("./inA.txt", "r");
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
    double** matA = alloc_mat(ah,aw);
    double** matB = alloc_mat(bh,bw);
    double** matC = alloc_mat(ch,cw);

    matA = populate_matrix(&m1,matA,ah,aw);

    fclose(m1);
    fclose(m2);
}
