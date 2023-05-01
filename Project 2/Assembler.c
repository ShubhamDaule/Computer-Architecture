#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {

	char line[255];
	char *token[5], *rs_str, *rt_str, *rd_str, *immediate_str, *shamt_str;
	int tokencount, i, opcode, shamt, func, Shub, Shiv;
	unsigned int instruction;
	char label_name[100][20], label_index=0, beq_label[20], bne_label[20], jump_label[20];
	int rs, rt, rd, immediate, outputfile_ptr=0, zero_padding=0, word_padding;
	long label_address[100], beq_addr=0, bne_addr=0, jump_addr=0, PC=0, output_ptr=0, shub_address=0;

	FILE *sourcefile;
	FILE *outputfile;
 	int address, label_addr,offset;

  	sourcefile = fopen(argv[1], "r");
  	outputfile = fopen("test.out", "w");

  while(fgets(line, sizeof(line), sourcefile) != NULL) {
 	

    token[0] = strtok(line, "\t");
    i = 0;
    while(token[i] != NULL) {
      i++;
      token[i] = strtok(NULL, "\t");
    }

    if (line[0]!='\t') {

      /////////
    }
    else if(strncmp(token[0], ".data", strlen(".data")) == 0)
	{
	rewind(outputfile);
	}
	else if (strncmp(token[0], ".text", strlen(".text")) == 0)
	{
	outputfile_ptr = ftell(outputfile);
	shub = (512 -  outputfile_ptr)/4;
	for(shiv = 0; shiv < shub; shiv++)
	fwrite(&zero_padding, sizeof(int), 1, outputfile);

}
	else if (strncmp(token[0], ".space", strlen(".space")) == 0)
	{
	shub = atoi(token[1]);
	for(shiv = 0; shiv < shub; shiv++)
	fwrite(&zero_padding, sizeof(int), 1, outputfile);
	}
	else if (strncmp(token[0], ".word", strlen(".word")) == 0)
	{
	word_padding = atoi(token[1]);
	fwrite(&word_padding, sizeof(int), 1, outputfile);
	}
  }
  fclose(sourcefile);

  sourcefile = fopen(argv[1], "r");

  while(fgets(line, sizeof(line), sourcefile) != NULL) {

    token[0] = strtok(line, "\t");
    i = 0;
    while(token[i] != NULL) {
      i++;
      token[i] = strtok(NULL, "\t");
    }
 	
    if (line[0]!='\t') {
     
      continue;
    }
   else if(strncmp(token[0], ".data", strlen(".data")) == 0)
{
rewind(outputfile);
address = 0;
}
else if (strncmp(token[0], ".text", strlen(".text")) == 0)
{
outputfile_ptr = ftell(outputfile);
shub = (512 -  outputfile_ptr)/4;
for(shiv = 0; shiv < shub; shiv++)
fwrite(&zero_padding, sizeof(int), 1, outputfile);

}
else if (strncmp(token[0], ".space", strlen(".space")) == 0)
{
shub = atoi(token[1]);
for(shiv = 0; shiv < shub; shiv++)
fwrite(&zero_padding, sizeof(int), 1, outputfile);
}
else if (strncmp(token[0], ".word", strlen(".word")) == 0)
{
word_padding = atoi(token[1]);
fwrite(&word_padding, sizeof(int), 1, outputfile);
address = address + 4;

}
		
		
		else if (strncmp(token[0], "add", 4) == 0) {
			
			opcode = 0;
			shamt = 0;
			func = 32;

			rd_str = strtok(token[1], "$");
			rs_str = strtok(NULL, "$");
			rt_str = strtok(NULL, "$");

			rd = atoi(rd_str);
			rs = atoi(rs_str);
			rt = atoi(rt_str);
	
			printf("rs=%d, rt=%d, rd=%d\n", rs, rt, rd);

			instruction = (opcode<<26) + (rs<<21) + (rt<<16) + (rd<<11) + (shamt<<6) + func;
			if (fwrite(&instruction, sizeof(int), 1, outputfile) != 1) {
				perror("Error writing file\n");
				return(-1);
			}
			address = address + 4;
			}
			
		else if (strncmp(token[0], "sub", 3) == 0) {
	
			opcode = 0;
			shamt = 0;
			func = 34;

			rd_str = strtok(token[1], "$");
			rs_str = strtok(NULL, "$");
			rt_str = strtok(NULL, "$");

			rd = atoi(rd_str);
			rs = atoi(rs_str);
			rt = atoi(rt_str);
	
			printf("rs=%d, rt=%d, rd=%d\n", rs, rt, rd);

			instruction = (opcode<<26) + (rs<<21) + (rt<<16) + (rd<<11) + (shamt<<6) + func;
			if (fwrite(&instruction, sizeof(int), 1, outputfile) != 1) {
				perror("Error writing file\n");
				return(-1);
			}
			address = address + 4;
			}
			
		else if (strncmp(token[0], "sll", 3) == 0) {
			opcode = 0;
			func = 0;

			rd_str = strtok(token[1], "$");
			rt_str = strtok(NULL, ",");
			shamt_str = strtok(NULL, ",");
			
			rd = atoi(rd_str);
			rt = atoi(rt_str);
			shamt = atoi(shamt_str);
	
			printf("rt=%d, rd=%d, shamt=%d\n", rt, rd, shamt);

			instruction = (opcode<<26) + (rt<<16) + (rd<<11) + (shamt<<6) + func;
			if (fwrite(&instruction, sizeof(int), 1, outputfile) != 1) {
				perror("Error writing file\n");
				return(-1);
			}
			address = address + 4;
			}
			
		else if (strncmp(token[0], "srl", 3) == 0) {
			opcode = 0;
			func = 2;

			rd_str = strtok(token[1], "$");
			rt_str = strtok(NULL, ",");
			shamt_str = strtok(NULL, ",");
			
			rd = atoi(rd_str);
			rt = atoi(rt_str);
			shamt = atoi(shamt_str);
			printf("rt=%d, rd=%d, shamt=%d\n", rt, rd, shamt);

			instruction = (opcode<<26) + (rt<<16) + (rd<<11) + (shamt<<6) + func;
			if (fwrite(&instruction, sizeof(int), 1, outputfile) != 1) {
				perror("Error writing file\n");
				return(-1);
			}
			address = address + 4;
			}
			
		else if (strncmp(token[0], "slt", 3) == 0) {
			opcode = 0;
			shamt = 0;
			func = 42;

			rd_str = strtok(token[1], "$");
			rs_str = strtok(NULL, "$");
			rt_str = strtok(NULL, "$");

			rd = atoi(rd_str);
			rs = atoi(rs_str);
			rt = atoi(rt_str);
	
			printf("rs=%d, rt=%d, rd=%d\n", rs, rt, rd);

			instruction = (opcode<<26) + (rs<<21) + (rt<<16) + (rd<<11) + (shamt<<6) + func;
			if (fwrite(&instruction, sizeof(int), 1, outputfile) != 1) {
				perror("Error writing file\n");
				return(-1);
			}
			address = address + 4;
			}
			
		else if (strncmp(token[0], "addi", 5) == 0) {
			opcode = 8;

			rt_str = strtok(token[1], "$");
			rs_str = strtok(NULL, ",");
			immediate_str = strtok(NULL, ",");
			
			
			rt = atoi(rt_str);
			rs = atoi(rs_str);
			immediate = atoi(immediate_str);
	
			printf("rs=%d, rt=%d, immediate=%d\n", rs, rt, immediate);

			instruction = (opcode<<26) + (rs<<21) + (rd<<16) + immediate;
			if (fwrite(&instruction, sizeof(int), 1, outputfile) != 1) {
				perror("Error writing file\n");
				return(-1);
			}
			address = address + 4;
			}
			
		else if (strncmp(token[0], "lui", 4) == 0) {
			opcode = 15;

			rt_str = strtok(token[1], "$");
			immediate_str = strtok(NULL, ",");
			
			rt = atoi(rt_str);
			immediate = atoi(immediate_str);
	
			printf("rt=%d, immediate=%d\n", rt, immediate);

			instruction = (opcode<<26) + (rt<<16) + immediate;
			if (fwrite(&instruction, sizeof(int), 1, outputfile) != 1) {
				perror("Error writing file\n");
				return(-1);
			}
			address = address + 4;
			}
			
		else if (strncmp(token[0], "ori", 3) == 0) {
			opcode = 13;

			rt_str = strtok(token[1], "$");
			rs_str = strtok(NULL, ",");
			immediate_str = strtok(NULL, ",");
			
			rt = atoi(rt_str);
			rs = atoi(rs_str);
			immediate = atoi(immediate_str);

			printf("rs=%d, rt=%d, immediate=%d\n", rs, rt, immediate);

			instruction = (opcode<<26) + (rs<<21) + (rt<<16) + immediate;
			if (fwrite(&instruction, sizeof(int), 1, outputfile) != 1) {
				perror("Error writing file\n");
				return(-1);
			}
			address = address + 4;
			}
			
		else if (strncmp(token[0], "lw", 3) == 0) {
			opcode = 35;

			rt_str = strtok(token[1], ",");
			immediate_str = strtok(NULL, "(");
			rs_str = strtok(NULL, "$");
			rs_str = strtok(rs_str, ")");
			rt_str = strtok(rt_str, "$");
			
			rs = atoi(rs_str);
			immediate = atoi(immediate_str);
			rt = atoi(rt_str);
	
			printf("rs=%d, immediate=%d, rt=%d\n", rs, immediate, rt);

			instruction = (opcode<<26) + (rs<<21) + (rt<<16) + immediate;
			if (fwrite(&instruction, sizeof(int), 1, outputfile) != 1) {
				perror("Error writing file\n");
				return(-1);
			}
			address = address + 4;
			}
			
		else if (strncmp(token[0], "sw", 3) == 0) {
			opcode = 44;

			rt_str = strtok(token[1], ",");
			immediate_str = strtok(NULL, "(");
			rs_str = strtok(NULL, "$");
			rs_str = strtok(rs_str, ")");
			rt_str = strtok(rt_str, "$");
			
			rs = atoi(rs_str);
			immediate = atoi(immediate_str);
			rt = atoi(rt_str);
	
			printf("rs=%d, immediate=%d, rt=%d\n", rs, immediate, rt);

			instruction = (opcode<<26) + (rs<<21) + (rt<<16) + immediate;
			if (fwrite(&instruction, sizeof(int), 1, outputfile) != 1) {
				perror("Error writing file\n");
				return(-1);
			}
			address = address + 4;
			}
			
		//////////////////////////////////////////////////////////////
    		// PHASE 2 - label hadning in j ///////////////////////////////
    		///////////////////////////////////////////////////////////////
    		else if (strncmp(token[0],"j",strlen(token[0])) == 0)
			{
			sscanf(token[1],"%s",jump_label);

			opcode = 2;
			for(shub = 0; shub <= label_index; shub++)
			{
			if (strncmp(jump_label,label_name[shub], strlen(label_name[shub])-2) == 0)
			break;
			}
			PC = ftell(outputfile);
			jump_addr=label_address[shub];
			jump_addr=((PC+4) & 4026531840) | (jump_addr & 268435455);

			offset = (jump_addr/4);

			instruction = (opcode<<26) + offset;
			if (fwrite(&instruction, sizeof(int), 1, outputfile) != 1) {
			perror("Error writing file\n");
			}
			}

		else if (strncmp(token[0], "beq", strlen(token[0])) == 0)
			{
			sscanf(token[1], "$%d,$%d,%s",&rs,&rt,beq_label);

			opcode = 4;
			for(shub = 0; shub <= label_index; shub++)
			{
			if(strncmp(beq_label, label_name[shub], strlen(label_name[shub])-2) ==0)
			break;
			}

			PC = ftell(outputfile);
			beq_addr = label_address[shub];
			offset = (beq_addr - PC - 4) / 4;

			instruction = (opcode << 26) + (rs << 21) + (rt << 16) + (offset &65535);
			if (fwrite(&instruction, sizeof(int), 1, outputfile) != 1) {
			perror("Error writing file\n");
			return(-1);
			}
			}

		else if (strncmp(token[0], "bne", strlen(token[0])) == 0)
			{
			sscanf(token[1], "$%d,$%d,%s",&rs,&rt,bne_label);

			opcode = 5;
			for(shub = 0; shub <= label_index; shub++)
			{
			if(strncmp(bne_label, label_name[shub], strlen(label_name[shub])-2) == 0)
			break;
			}
			
			PC = ftell(outputfile);
			bne_addr = label_address[shub];
			offset = (bne_addr - PC - 4) / 4;

			instruction = (opcode << 26) + (rs << 21) + (rt << 16) + (offset &65535);
			if (fwrite(&instruction, sizeof(int), 1, outputfile) != 1) {
			perror("Error writing file\n");
			return(-1);
			}
			}
				fclose(sourcefile);
				fclose(outputfile);
			}
			}
			

