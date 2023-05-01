#include<stdio.h>
#include<stdlib.h>
int i, PC, cycles_to_halt;
int reg_array[32] ={0};
int memory[256] ={0};
FILE *source_file;
int FETCH_PC, FETCH_PC_4, FETCH_PC_nxt, FETCH_instr = 0;
int DECODE_ctrl, DECODE_opcd, DECODE_fnctn, DECODE_shamt, DECODE_PC4, DECODE_rs, DECODE_rt, DECODE_immd, DECODE_extnd, DECODE_rd, DECODE_instr, DECODE_RD1, DECODE_RD2 =0;
int EXECUTE_ctrl, EXECUTE_fctn, EXECUTE_PC_4, EXECUTE_extd, EXECUTE_offset, EXECUTE_gtbt, EXECUTE_zero, EXECUTE_RD1, EXECUTE_RD2, EXECUTE_rt, EXECUTE_rd, EXECUTE_RegRd, EXECUTE_aout, EXECUTE_ALU2 =0;
int MMRY_ALUOUT, MMRY_ctrl, MMRY_btgt, MMRY_zero, MMRY_WD, MMRY_RD2, MMRY_memout, MMRY_RegRd =0;
int WRTBCK_mout, WRTBCK_aout, WRTBCK_RegRd, WRTBCK_wd, WRTBCK_ctrl =0;
int DECODEFETCH_PC4, DECODEFETCH_instr =0;
int EXECUTEDECODE_PC_4, EXECUTEDECODE_RD1, EXECUTEDECODE_RD2, EXECUTEDECODE_extd, EXECUTEDECODE_rt, EXECUTEDECODE_rd, EXECUTEDECODE_ctrl =0;
int MMRYEXECUTE_btgt, MMRYEXECUTE_zero, MMRYEXECUTE_aout, MMRYEXECUTE_RD2, MMRYEXECUTE_RegRd, MMRYEXECUTE_ctrl =0;
int WRTBCKMMRY_mout, WRTBCKMMRY_aout, WRTBCKMMRY_RegRd, WRTBCKMMRY_ctrl =0;
int MMRY_PCSrc = 0;
int WRTBCK_Reg_Write, WRTBCK_Memto_Reg = 0;
int EXECUTE_ALU_Src, EXECUTE_Reg_Dst, EXECUTE_ALU_Op = 0;
int MMRY_MemWrite, MMRY_Mem_Read, MMRY_Branch = 0;
void initialize(void);
int read_pipeline_registers(void);
int carryout_operations(void);
int update_pc_reg_mem(void);
int update_pipeline_registers(void);
int print_results(void);
int main(int argc, char *argv[])
{
	source_file = fopen(argv[1], "rb");
	initialize();
	PC =512;
	cycles_to_halt =1000;
	while(1)
	{
		read_pipeline_registers();
		carryout_operations();
		update_pc_reg_mem();
		update_pipeline_registers();
		print_results();
		if(FETCH_instr ==12)
			cycles_to_halt =4;
		if(cycles_to_halt > 0)
			cycles_to_halt--;
		if(cycles_to_halt ==0)
			break;
	}
}
int read_pipeline_registers(void)
{
	DECODE_PC4 = DECODEFETCH_PC4;
	DECODE_instr = DECODEFETCH_instr;
	EXECUTE_RD1 = EXECUTEDECODE_RD1;
	EXECUTE_RD2 = EXECUTEDECODE_RD2;
	EXECUTE_extd = EXECUTEDECODE_extd;
	EXECUTE_PC_4 = EXECUTEDECODE_PC_4;
	EXECUTE_rt = EXECUTEDECODE_rt;
	EXECUTE_rd = EXECUTEDECODE_rd;
	EXECUTE_ctrl = EXECUTEDECODE_ctrl;
	MMRY_btgt = MMRYEXECUTE_btgt;
	MMRY_zero = MMRYEXECUTE_zero;
	MMRY_ALUOUT = MMRYEXECUTE_aout;
	MMRY_RD2 = MMRYEXECUTE_RD2;
	MMRY_RegRd = MMRYEXECUTE_RegRd;
	MMRY_ctrl = MMRYEXECUTE_ctrl;
	WRTBCK_mout = WRTBCKMMRY_mout;
	WRTBCK_aout = WRTBCKMMRY_aout;
	WRTBCK_RegRd = WRTBCKMMRY_RegRd;
	WRTBCK_ctrl = WRTBCKMMRY_ctrl;
}
int carryout_operations(void)
{
	FETCH_PC = PC;
	FETCH_PC_4 = FETCH_PC + 4;
	FETCH_PC_nxt = FETCH_PC_4;
	FETCH_instr = memory[(PC/4)-1];
	DECODE_opcd = (DECODE_instr & 4227858432) >> 26;
	DECODE_rs = (DECODE_instr & 65011712) >> 21;
	DECODE_rt = (DECODE_instr & 2031616) >> 16;
	DECODE_rd = (DECODE_instr & 63488) >> 11;
	DECODE_shamt = (DECODE_instr & 1984) >> 6;
	DECODE_fnctn = (DECODE_instr & 63);
	DECODE_immd = (DECODE_instr & 65535);
	if(DECODE_immd & 32768)
	DECODE_immd = DECODE_immd | 4294901760;
	DECODE_extnd = DECODE_immd;
	if(DECODE_opcd == 0)
		DECODE_ctrl = 1416;
	else if(DECODE_opcd == 35)
		DECODE_ctrl = 704;
	else if(DECODE_opcd == 43)
		DECODE_ctrl = 544;
	else if(DECODE_opcd == 4)
		DECODE_ctrl = 20;
	else if(DECODE_opcd == 5)
		DECODE_ctrl = 6;
	else if(DECODE_opcd == 8)
		DECODE_ctrl = 896;
	if((DECODE_opcd == 0) && (DECODE_fnctn == 0 || DECODE_fnctn == 2))
	{
		DECODE_RD1 = reg_array[DECODE_rt];
		DECODE_RD2 = DECODE_shamt;	
	}
	else
	{
		DECODE_RD1 = reg_array[DECODE_rs];
		DECODE_RD2 = reg_array[DECODE_rt];
	}

	EXECUTE_offset = EXECUTE_extd * 4;
	EXECUTE_gtbt = EXECUTE_PC_4 + EXECUTE_offset;
	EXECUTE_fctn = (EXECUTE_extd & 63);

	EXECUTE_Reg_Dst = (EXECUTE_ctrl >>10) &1;
	if(EXECUTE_Reg_Dst ==0)
		{
		EXECUTE_RegRd =EXECUTE_rt;
		}	
	else
		{
		EXECUTE_RegRd =EXECUTE_rd;
		}
	EXECUTE_ALU_Src = (EXECUTE_ctrl >>9) &1;
	if(EXECUTE_ALU_Src == 0)
		{
		EXECUTE_ALU2 = EXECUTE_RD2;
		}
	else
		{
		EXECUTE_ALU2 = EXECUTE_extd;
		}
	if(EXECUTE_ctrl ==1416)
	{
		if(EXECUTE_fctn ==32)
			EXECUTE_aout = EXECUTE_RD1 + EXECUTE_ALU2;
		else if (EXECUTE_fctn ==34)
			EXECUTE_aout = EXECUTE_RD1 - EXECUTE_ALU2;
		else if (EXECUTE_fctn ==0)
			EXECUTE_aout = EXECUTE_RD1 << EXECUTE_ALU2;
		else if (EXECUTE_fctn ==2) 
			EXECUTE_aout = EXECUTE_RD1 >> EXECUTE_ALU2;
		else if (EXECUTE_fctn ==42) 
		{
			if(EXECUTE_RD1 < EXECUTE_ALU2)
				{
				EXECUTE_aout =1;
				}
			else
				EXECUTE_aout =0;
		}
		else if (EXECUTE_fctn ==12)
			EXECUTE_aout =0;
	}
	else if ((EXECUTE_ctrl ==704) || (EXECUTE_ctrl ==544) || (EXECUTE_ctrl ==896))
		EXECUTE_aout = EXECUTE_RD1 + EXECUTE_ALU2;
	if(EXECUTE_aout ==0)
		EXECUTE_zero =1;
	MMRY_Mem_Read = (MMRY_ctrl >>6) &1;
	if(MMRY_Mem_Read)
		MMRY_memout = memory[MMRY_ALUOUT/4];
	WRTBCK_Memto_Reg = (WRTBCK_ctrl >>8) &1;
	if(WRTBCK_Memto_Reg ==0)
		WRTBCK_wd = WRTBCK_mout;
	else
		WRTBCK_wd = WRTBCK_aout;
}
int update_pc_reg_mem(void)
{
	PC = FETCH_PC_nxt;
	MMRY_MemWrite = (MMRY_ctrl >> 5)&1;
	if(MMRY_MemWrite)
		memory[MMRY_ALUOUT/4] = MMRY_RD2;
	WRTBCK_Reg_Write = (WRTBCK_ctrl >>7) &1;
	if(WRTBCK_Reg_Write)
		reg_array[WRTBCK_RegRd] = WRTBCK_wd;
}
int update_pipeline_registers(void)
{
	DECODEFETCH_PC4 = FETCH_PC_4;
	DECODEFETCH_instr = FETCH_instr;
	EXECUTEDECODE_PC_4 = DECODE_PC4;
	EXECUTEDECODE_RD1 = DECODE_RD1;
	EXECUTEDECODE_RD2 = DECODE_RD2;
	EXECUTEDECODE_extd = DECODE_extnd;
	EXECUTEDECODE_rt = DECODE_rt;
	EXECUTEDECODE_rd = DECODE_rd;
	EXECUTEDECODE_ctrl = DECODE_ctrl;
	MMRYEXECUTE_btgt = EXECUTE_gtbt;
	MMRYEXECUTE_zero = EXECUTE_zero;
	MMRYEXECUTE_aout = EXECUTE_aout;
	MMRYEXECUTE_RD2 = EXECUTE_RD2;
	MMRYEXECUTE_RegRd = EXECUTE_RegRd;
	MMRYEXECUTE_ctrl = EXECUTE_ctrl;
	WRTBCKMMRY_mout = MMRY_memout; 
	WRTBCKMMRY_aout = MMRY_ALUOUT;
	WRTBCKMMRY_RegRd = MMRY_RegRd;
	WRTBCKMMRY_ctrl = MMRY_ctrl;
	if (MMRY_PCSrc==1) 
	{
		MMRYEXECUTE_ctrl = 0; 
		EXECUTEDECODE_ctrl = 0; 
		DECODEFETCH_instr =0; 
	}
}
int print_results(void)
{
	printf("PC = %x\n", PC-4);
	printf("DM");
	i = 0;
	while(i <16)
	{
	printf("%d ", memory[i]);
	i++;
	}	
	printf("\n");
	printf("RegFile");
	i = 0;
	while(i <16)
	{
	printf("%d ", reg_array[i]);
	i++;
	}
	printf("\n");
	printf("IF/ID (PC4, inst) %x %x\n", DECODEFETCH_PC4, DECODEFETCH_instr);
	printf("ID/EX (PC4, rd1, rd2, extend, rt, rd, ctrl)%x %x %x %x %x %x %x\n", EXECUTEDECODE_PC_4, EXECUTEDECODE_RD1, EXECUTEDECODE_RD2, EXECUTEDECODE_extd, EXECUTEDECODE_rt, EXECUTEDECODE_rd, EXECUTEDECODE_ctrl);
	printf("EX/MEM (btgt, zero, ALUOut, rd2, RegRd, ctrl)%x %x %x %x %x %x\n", MMRYEXECUTE_btgt, MMRYEXECUTE_zero, MMRYEXECUTE_aout, MMRYEXECUTE_RD2, MMRYEXECUTE_RegRd, MMRYEXECUTE_ctrl);
	printf("MEM/WB (memout, ALUOut, RegRd, ctrl)%x %x %x %x\n", WRTBCKMMRY_mout, WRTBCKMMRY_aout, WRTBCKMMRY_RegRd, WRTBCKMMRY_ctrl);
	printf("\n");
}
void initialize(void)
{
	int i;
	for(i=0; i<256; i++)
	{
		fread(&memory[i], sizeof(int), 1, source_file);
		{
		if(memory[i] == 12)
			{
			break;
			}
	}
	}
	return;
}

