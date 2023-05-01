#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

	char line[255];
	char *token[5], *rs_str, *rt_str, *rd_str, *immediate_str, *shamt_str;
	int tokencount, i, opcode, shamt, func;
	unsigned int instruction;
	int rs, rt, rd, immediate;

	FILE *sourcefile;
	FILE *outputfile;

	sourcefile = fopen(argv[1], "r");
	outputfile = fopen("test.out", "w");

  	// read one line at a time until exhausted
 	while(fgets(line, sizeof(line), sourcefile) != NULL) {
 	
 	  //separate oneline into different pieces using the delimiter \t (tab)
		token[0] = strtok(line, "\t");
		i = 0;
		while(token[i] != NULL) {
			i++;
			token[i] = strtok(NULL, "\t");
		}
 	
    		// if the first character is not \t (tab)
		if (line[0]!='\t') {
		        // it is a labell add YOUR CODE
		        // remember the name and address/location of the label (symbol table)
    		}
		else if (strncmp(token[0], ".data", strlen(".data")) == 0) {
			// Data section; add YOUR CODE
		        // Nothing to write to the outputfile but address=0
    		}
		else if (strncmp(token[0], ".text", strlen(".text")) == 0) {
			// Text section begins; add YOUR CODE
		        // Write to the outputfile with zero's so that the next address is 512
    		}
		else if (strncmp(token[0], ".space", strlen(".space")) == 0) {
			// add YOUR CODE
	        	// Write to the outputfile with zero's (token[1] count)
    		}
		else if (strncmp(token[0], ".word", strlen(".word")) == 0) {
			// add YOUR CODE
		        // Write to the outputfile with token[1]
    		}
    
		//otherwise, it is a regular MIPS instruction
		else if (strncmp(token[0], "add", 4) == 0) {
			// "add" instruction; this is completed for your reference
			// You need to do the similar for other instuctions

			// token[0]="add", token[1]="$1,$2,$3", for example 
			opcode = 0;
			shamt = 0;
			func = 32;

			// now, toekn[1] is split into three pieces 
			rd_str = strtok(token[1], "$");
			rs_str = strtok(NULL, "$");
			rt_str = strtok(NULL, "$");

			rd = atoi(rd_str);
			rs = atoi(rs_str);
			rt = atoi(rt_str);
	
			// this is just for your reference
			printf("rs=%d, rt=%d, rd=%d\n", rs, rt, rd);

			// the next step is put those pieces together to encode a 32-bit instruction
			instruction = (opcode<<26) + (rs<<21) + (rt<<16) + (rd<<11) + (shamt<<6) + func;
			if (fwrite(&instruction, sizeof(int), 1, outputfile) != 1) {
				perror("Error writing file\n");
				return(-1);
			}
			}
		else if (strncmp(token[0], "sub", 3) == 0) {
			// "sub" instruction; this is completed for your reference
			// You need to do the similar for other instuctions

			// token[0]="sub", token[1]="$1,$2,$3", for example 
			opcode = 0;
			shamt = 0;
			func = 34;

			// now, toekn[1] is split into three pieces 
			rd_str = strtok(token[1], "$");
			rs_str = strtok(NULL, "$");
			rt_str = strtok(NULL, "$");

			rd = atoi(rd_str);
			rs = atoi(rs_str);
			rt = atoi(rt_str);
	
			// this is just for your reference
			printf("rs=%d, rt=%d, rd=%d\n", rs, rt, rd);

			// the next step is put those pieces together to encode a 32-bit instruction
			instruction = (opcode<<26) + (rs<<21) + (rt<<16) + (rd<<11) + (shamt<<6) + func;
			if (fwrite(&instruction, sizeof(int), 1, outputfile) != 1) {
				perror("Error writing file\n");
				return(-1);
			}
			}
		else if (strncmp(token[0], "sll", 3) == 0) {
			// "sll" instruction; this is completed for your reference
			// You need to do the similar for other instuctions

			// token[0]="sll", token[1]="$1,$2,shamt", for example 
			opcode = 0;
			func = 0;

			// now, toekn[1] is split into two pieces 
			rd_str = strtok(token[1], "$");
			rt_str = strtok(NULL, ",");
			shamt_str = strtok(NULL, ",");
			
			rd = atoi(rd_str);
			rt = atoi(rt_str);
			shamt = atoi(shamt_str);
	
			// this is just for your reference
			printf("rt=%d, rd=%d, shamt=%d\n", rt, rd, shamt);

			// the next step is put those pieces together to encode a 32-bit instruction
			instruction = (opcode<<26) + (rt<<16) + (rd<<11) + (shamt<<6) + func;
			if (fwrite(&instruction, sizeof(int), 1, outputfile) != 1) {
				perror("Error writing file\n");
				return(-1);
			}
			}
		else if (strncmp(token[0], "srl", 3) == 0) {
			// "srl" instruction; this is completed for your reference
			// You need to do the similar for other instuctions

			// token[0]="srl", token[1]="$1,$2,shamt", for example 
			opcode = 0;
			func = 2;

			// now, toekn[1] is split into two pieces 
			rd_str = strtok(token[1], "$");
			rt_str = strtok(NULL, ",");
			shamt_str = strtok(NULL, ",");
			
			rd = atoi(rd_str);
			rt = atoi(rt_str);
			shamt = atoi(shamt_str);
	
			// this is just for your reference
			printf("rt=%d, rd=%d, shamt=%d\n", rt, rd, shamt);

			// the next step is put those pieces together to encode a 32-bit instruction
			instruction = (opcode<<26) + (rt<<16) + (rd<<11) + (shamt<<6) + func;
			if (fwrite(&instruction, sizeof(int), 1, outputfile) != 1) {
				perror("Error writing file\n");
				return(-1);
			}
			}
		else if (strncmp(token[0], "slt", 3) == 0) {
			// "slt" instruction; this is completed for your reference
			// You need to do the similar for other instuctions

			// token[0]="slt", token[1]="$1,$2,$3", for example 
			opcode = 0;
			shamt = 0;
			func = 42;

			// now, toekn[1] is split into three pieces 
			rd_str = strtok(token[1], "$");
			rs_str = strtok(NULL, "$");
			rt_str = strtok(NULL, "$");

			rd = atoi(rd_str);
			rs = atoi(rs_str);
			rt = atoi(rt_str);
	
			// this is just for your reference
			printf("rs=%d, rt=%d, rd=%d\n", rs, rt, rd);

			// the next step is put those pieces together to encode a 32-bit instruction
			instruction = (opcode<<26) + (rs<<21) + (rt<<16) + (rd<<11) + (shamt<<6) + func;
			if (fwrite(&instruction, sizeof(int), 1, outputfile) != 1) {
				perror("Error writing file\n");
				return(-1);
			}
			}
		else if (strncmp(token[0], "addi", 5) == 0) {
			// "addi" instruction; this is completed for your reference
			// You need to do the similar for other instuctions

			// token[0]="addi", token[1]="$1,$2,45", for example 
			opcode = 8;

			// now, toekn[1] is split into three pieces 
			rs_str = strtok(token[1], "$");
			rd_str = strtok(NULL, ",");
			immediate_str = strtok(NULL, ",");
			
			
			rs = atoi(rs_str);
			rd = atoi(rd_str);
			immediate = atoi(immediate_str);
	
			// this is just for your reference
			printf("rs=%d, rd=%d, immediate=%d\n", rs, rd, immediate);

			// the next step is put those pieces together to encode a 32-bit instruction
			instruction = (opcode<<26) + (rs<<21) + (rd<<16) + immediate;
			if (fwrite(&instruction, sizeof(int), 1, outputfile) != 1) {
				perror("Error writing file\n");
				return(-1);
			}
			}
		else if (strncmp(token[0], "lui", 4) == 0) {
			// "lui" instruction; this is completed for your reference
			// You need to do the similar for other instuctions

			// token[0]="lui", token[1]="$1,45", for example 
			opcode = 15;

			// now, toekn[1] is split into two pieces 
			rt_str = strtok(token[1], "$");
			printf("rt=%d, immediate=%d\n", rt, immediate);
			immediate_str = strtok(NULL, ",");
			
			rt = atoi(rt_str);
			immediate = atoi(immediate_str);
	
			// this is just for your reference
			printf("rt=%d, immediate=%d\n", rt, immediate);

			// the next step is put those pieces together to encode a 32-bit instruction
			instruction = (opcode<<26) + (rt<<16) + immediate;
			if (fwrite(&instruction, sizeof(int), 1, outputfile) != 1) {
				perror("Error writing file\n");
				return(-1);
			}
			}
		else if (strncmp(token[0], "ori", 3) == 0) {
			// "ori" instruction; this is completed for your reference
			// You need to do the similar for other instuctions

			// token[0]="ori", token[1]="$1,$2,45", for example 
			opcode = 13;

			// now, toekn[1] is split into three pieces 
			rs_str = strtok(token[1], "$");
			rt_str = strtok(NULL, ",");
			immediate_str = strtok(NULL, ",");
			
			rs = atoi(rs_str);
			rt = atoi(rt_str);
			immediate = atoi(immediate_str);
	
			// this is just for your reference
			printf("rs=%d, rt=%d, immediate=%d\n", rs, rt, immediate);

			// the next step is put those pieces together to encode a 32-bit instruction
			instruction = (opcode<<26) + (rs<<21) + (rt<<16) + immediate;
			if (fwrite(&instruction, sizeof(int), 1, outputfile) != 1) {
				perror("Error writing file\n");
				return(-1);
			}
			}
		else if (strncmp(token[0], "lw", 3) == 0) {
			// "lw" instruction; this is completed for your reference
			// You need to do the similar for other instuctions

			// token[0]="lw", token[1]="$1,100($2)", for example 
			opcode = 35;

			// now, toekn[1] is split into three pieces 
			rt_str = strtok(token[1], ",");
			immediate_str = strtok(NULL, "(");
			rs_str = strtok(NULL, "$");
			rs_str = strtok(rs_str, ")");
			rt_str = strtok(rt_str, "$");
			
			rs = atoi(rs_str);
			immediate = atoi(immediate_str);
			rt = atoi(rt_str);
	
			// this is just for your reference
			printf("rs=%d, immediate=%d, rt=%d\n", rs, immediate, rt);

			// the next step is put those pieces together to encode a 32-bit instruction
			instruction = (opcode<<26) + (rs<<21) + (rt<<16) + immediate;
			if (fwrite(&instruction, sizeof(int), 1, outputfile) != 1) {
				perror("Error writing file\n");
				return(-1);
			}
			}
		else if (strncmp(token[0], "sw", 3) == 0) {
			// "sw" instruction; this is completed for your reference
			// You need to do the similar for other instuctions

			// token[0]="sw", token[1]="$1,100($2)", for example 
			opcode = 44;

			// now, toekn[1] is split into three pieces 
			rt_str = strtok(token[1], ",");
			immediate_str = strtok(NULL, "(");
			rs_str = strtok(NULL, "$");
			rs_str = strtok(rs_str, ")");
			rt_str = strtok(rt_str, "$");
			
			rs = atoi(rs_str);
			immediate = atoi(immediate_str);
			rt = atoi(rt_str);
	
			// this is just for your reference
			printf("rs=%d, immediate=%d, rt=%d\n", rs, immediate, rt);

			// the next step is put those pieces together to encode a 32-bit instruction
			instruction = (opcode<<26) + (rs<<21) + (rt<<16) + immediate;
			if (fwrite(&instruction, sizeof(int), 1, outputfile) != 1) {
				perror("Error writing file\n");
				return(-1);
			}
		}
	}
	fclose(sourcefile);
	fclose(outputfile);
}

