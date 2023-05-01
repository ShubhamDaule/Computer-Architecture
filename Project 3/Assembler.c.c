#include<stdio.h>
#include<stdlib.h>

int PC, DM, cycles_to_halt;
int register_array[32] = {0};
int memory_array[256] = {0};
FILE *sourcefile;

int IF_pc, IF_pc4, IF_pc_next, IF_inst = 0;
int ID_rs, ID_rt, ID_rd, ID_ctrl, ID_opcode, ID_func, ID_shamt, ID_pc4, ID_inst, ID_immed, ID_extnd, ID_rd1, ID_rd2 = 0;
int IFID_pc4, IFID_inst = 0;
int EX_ctrl, EX_func, EX_rd1, EX_rd, EX_rd2, EX_rt, EX_pc4, EX_extnd, EX_offset, EX_btgt, EX_zero, EX_RegRd, EX_ALUOut, EX_ALU2 = 0;
int EXID_pc4, EXID_rd1, EXID_rd2, EXID_extnd, EXID_rt, EXID_rd, EXID_ctrl = 0;
int EX_ALUSrc, EX_RegDst, EX_ALUOp = 0;
int WB_memout, WB_RegRd, WB_wd, WB_ALUOut, WB_ctrl = 0;
int WB_RegWrite, WB_MemtoReg = 0;
int MEMWB_memout, MEMWB_ALUOut, MEMWB_RegRd, MEMWB_ctrl = 0;
int MEM_pcSrc = 0;
int MEM_MemWrite, MEM_MemRead, MEM_Branch = 0;
int MEM_ALUOut, MEM_zero, MEM_ctrl, MEM_btgt, MEM_memout, MEM_WD, MEM_rd2, MEM_RegRd = 0;
int EXMEM_btgt, EXMEM_zero, EXMEM_ALUOut, EXMEM_rd2, EXMEM_RegRd, EXMEM_ctrl = 0;

void initialize(void);
void read_pipeline_registers(void);
void carryout_operations(void);
void update_pc_reg_mem(void);
void update_pipeline_registers(void);
void print_results(void);

int main(int argc, char *argv[])
{
	sourcefile = fopen(argv[1], "rb");
	initialize();
	PC = 512;
	cycles_to_halt = 1000;

	while(1)
	{
		read_pipeline_registers();
		carryout_operations();
		update_pc_reg_mem();
		update_pipeline_registers();
		print_results();
		if(IF_inst == 12)
			cycles_to_halt = 4;
		if(cycles_to_halt > 0)
			cycles_to_halt --;
		if(cycles_to_halt == 0)
			break;
		printf("%d", cycles_to_halt); // just for debugging purpose
	}

}

void print_results(void)
{

	printf("PC = %x\n", PC-4);

	printf("DM = %x\n", DM);
	for(int i=0; i<16; i++)
	printf("%d ", memory_array[i]);	
	printf("\n");
	printf("RegFile\t\t");
	for(int i=0; i<16; i++)
		printf("%d ", register_array[i]);	
	printf("\n");
	
	printf("IF/ID (pc4, inst)\t\t\t\t %x %x\n", IFID_pc4, IFID_inst);

	printf("ID/EX (pc4, rd1, rd2, extnd, rt, rd, ctrl)\t %x %x %x %x %x %x %x\n", EXID_pc4, EXID_rd1, EXID_rd2, EXID_extnd, EXID_rt, EXID_rd, EXID_ctrl);

	printf("EX/MEM (btgt, zero, ALUOut, rd2, RegRd, ctrl)\t %x %x %x %x %x %x\n", EXMEM_btgt, EXMEM_zero, EXMEM_ALUOut, EXMEM_rd2, EXMEM_RegRd, EXMEM_ctrl);

	printf("MEM/WB (memout, ALUOut, RegRd, ctrl)\t\t %x %x %x %x\n", MEMWB_memout, MEMWB_ALUOut, MEMWB_RegRd, MEMWB_ctrl);

	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

}
void update_pipeline_registers(void)
{
	IFID_pc4=IF_pc4;
	IFID_inst=IF_inst;

	EXID_pc4 = ID_pc4;
	EXID_rd1 = ID_rd1;
	EXID_rd2 = ID_rd2;
	EXID_extnd = ID_extnd;
	EXID_rt = ID_rt;
	EXID_rd = ID_rd;
	EXID_ctrl = ID_ctrl;

	EXMEM_btgt = EX_btgt;
	EXMEM_zero = EX_zero;
	EXMEM_ALUOut = EX_ALUOut;
	EXMEM_rd2 = EX_rd2;
	EXMEM_RegRd = EX_RegRd;
	EXMEM_ctrl = EX_ctrl;

	MEMWB_memout = MEM_memout; 
	MEMWB_ALUOut = MEM_ALUOut;
	MEMWB_RegRd = MEM_RegRd;
	MEMWB_ctrl = MEM_ctrl;
}

void update_pc_reg_mem(void)
{
	PC = IF_pc_next;
	
	MEM_MemWrite = (MEM_ctrl >> 5) & 1;
	if(MEM_MemWrite)
		memory_array[MEM_ALUOut/4] = MEM_rd2;

	WB_RegWrite = (WB_ctrl >> 7) & 1;
	if(WB_RegWrite)
		register_array[WB_RegRd] = WB_wd;	
}
void carryout_operations(void)
{
	IF_pc = PC;
	IF_pc4 = IF_pc + 4;
	IF_pc_next = IF_pc4;
	IF_inst = memory_array[(PC/4)-1];

	ID_opcode = (ID_inst & 0xFC000000) >> 26;
	ID_rs = (ID_inst & 0x03E00000) >> 21;
	ID_rt = (ID_inst & 0x001F0000) >> 16;
	ID_rd = (ID_inst & 0x0000F800) >> 11;
	ID_shamt = (ID_inst & 0x000007C0) >> 6;
	ID_func = (ID_inst & 0x0000003F);
	ID_immed = (ID_inst & 0x0000FFFF);

	if(ID_immed & 0x00008000)
		ID_immed = ID_immed | 0xFFFF0000;
		ID_extnd = ID_immed;
	if(ID_opcode == 0)//R-Type
		ID_ctrl = 0x588;
	else if(ID_opcode == 0x23)//LW
		ID_ctrl = 0x2C0;
	else if(ID_opcode == 0x2B)//SW
		ID_ctrl = 0x220;
	else if(ID_opcode == 0x4)//BEQ
		ID_ctrl = 0x014;
	else if(ID_opcode == 0x5)//BNE
		ID_ctrl = 0x6;
	else if(ID_opcode == 0x8)//ADDI
		ID_ctrl = 0x380;

	if((ID_opcode == 0) && (ID_func == 0 || ID_func == 2))
	{
		ID_rd1 = register_array[ID_rt];
		ID_rd2 = ID_shamt;	
	}
	else
	{
		ID_rd1 = register_array[ID_rs];
		ID_rd2 = register_array[ID_rt];
	}
	EX_offset = EX_extnd * 4;
	EX_btgt = EX_pc4 + EX_offset;
	EX_func = (EX_extnd & 0x0000003F);

	EX_RegDst = (EX_ctrl >> 10) & 1;
	if(EX_RegDst == 0)
		EX_RegRd = EX_rt;
	else
		EX_RegRd = EX_rd;

	EX_ALUSrc = (EX_ctrl >> 9) & 1;
	if(EX_ALUSrc == 0)
		EX_ALU2 = EX_rd2;
	else
		EX_ALU2 = EX_extnd;

	if(EX_ctrl == 1416)//R-Type
	{
		if(EX_func == 32)// add
			EX_ALUOut = EX_rd1 + EX_ALU2;
		else if (EX_func == 34)// sub
			EX_ALUOut = EX_rd1 - EX_ALU2;
		else if (EX_func == 0)// sll
			EX_ALUOut = EX_rd1 << EX_ALU2;
		else if (EX_func == 2) // srl
			EX_ALUOut = EX_rd1 >> EX_ALU2;
		else if (EX_func == 42) // slt
		{
			if(EX_rd1 < EX_ALU2)
				EX_ALUOut = 1;
			else
				EX_ALUOut = 0;
		}
		else if (EX_func == 12) // halt
			EX_ALUOut = 0;
	}
	else if ((EX_ctrl==704) || (EX_ctrl==544) || (EX_ctrl==896))// lw,sw,addi
		EX_ALUOut = EX_rd1 + EX_ALU2;
	 //beq or bne
	if(EX_ALUOut == 0)
		EX_zero = 1;
	MEM_MemRead = (MEM_ctrl >> 6) & 1;
	if(MEM_MemRead)
		MEM_memout = memory_array[MEM_ALUOut/4];
	WB_MemtoReg = (WB_ctrl >> 8) & 1;
	if(WB_MemtoReg == 0)
		WB_wd = WB_memout;
	else
		WB_wd = WB_ALUOut;
	
}

void read_pipeline_registers(void)
{
	ID_pc4 = IFID_pc4;
	ID_inst = IFID_inst;

	EX_pc4 = EXID_pc4;
	EX_rd1 = EXID_rd1;
	EX_rd2 = EXID_rd2;
	EX_extnd = EXID_extnd;
	EX_rt = EXID_rt;
	EX_rd = EXID_rd;
	EX_ctrl = EXID_ctrl;

	MEM_btgt = EXMEM_btgt;
	MEM_zero = EXMEM_zero;
	MEM_ALUOut = EXMEM_ALUOut;
	MEM_rd2 = EXMEM_rd2;
	MEM_RegRd = EXMEM_RegRd;
	MEM_ctrl = EXMEM_ctrl;

	WB_memout = MEMWB_memout;
	WB_ALUOut = MEMWB_ALUOut;
	WB_RegRd = MEMWB_RegRd;
	WB_ctrl = MEMWB_ctrl;
}

void initialize(void)
{
	int i;


	for(i=0; i<256; i++)
	{
		fread(&memory_array[i], sizeof(int), 1, sourcefile);
		printf("%x ", memory_array[i]);
		if(memory_array[i] == 12)
			break;
	}
	return;
}
