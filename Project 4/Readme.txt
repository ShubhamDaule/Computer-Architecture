Output is not achieved for branch.

FOr some outputs we are getting wrong result for instruction. 


Suggestions:


Q1. The first Q&A project 3 seems not working for project 4.
  int i, data, inst;
  FILE *sourcefile;
  sourcefile = fopen(argv[1], "rb");
  for (i=0; i<128; i++) // skip data section
        fread(&data, sizeof(int), 1, sourcefile);
  while (1){
        fread(&inst, sizeof(int), 1, sourcefile);
        if (inst == 12) break;
 //your code
  }

A1. Unlike project 3, instructions are not always executed in sequence in project 4 due to branch. It is recommended to copy both data and instruction (text segment) to memory first. Then, use the memory to execute instructions. I.e.,

  int i, data, inst, pc;
  FILE *sourcefile;
  sourcefile = fopen(argv[1], "rb");
  for (i=0; i<256; i++) 
        fread(&memory[i], sizeof(int), 1, sourcefile);
  pc = 128;

  while (1){
        //fread(&inst, sizeof(int), 1, sourcefile);
        inst = memory[pc];
        if (inst == 12) break;
 //your code
  }


Q2. For the updated skeleton code in the read_pipeline_registers() and update_pc_mem() for example, the order of the stages is flipped from the original skeleton. Does this matter if we have the initial setup in order of how to diagram is represented?

A2. In principle, your correct. Each stage should be independent with each other. But I flipped the order because of two reasons:
(i) register reading (ID) must be followed by register writing (WB) and
(ii) PC update (IF) must be followed by MEM_PCSrc evaluation (MEM).
I.e., in carryout_operations(), 
(i)
       if (WB_RegWrite==1) register[WB_RegRd] = _______;  
and then,
       ID_rd1 = register[...];
       ID_rd2 = register[...];
(ii)
       MEM_PCSrc = _______;  
and then,
       if (MEM_PCSrc==0) ...
*****
