Achieved output as expected.

But at the start of output we are getting some unwanted value such as 000 and random numbers.
Also before the values before PC adecreae obatined in the decreased format which is due to the declartion of halt cycle as an int.



Suggestions:

Q7. My partner and I are struggling trying to figure out what read_pipeline_registers() portion of the skeleton code is trying to say.

A7. Each stage carries out its own operations and the result is written into the pipeline register at the end of the cycle.
In the beginning of the next cycle (actually about the same time as the end of the previous cycle), the pipeline register is used to initialize the signals on the next stage.
For example, in cycle 1, pc is 1000 initially and is added by 4, resulting in 1004 in IF stage (IF_pc4 in the figure). This value is written to the IF/ID pipeline register at the end of cycle 1 (the signal name if not shown in the figure but, you can name it as IFID_pc4). In the beginning of cycle 2, this is written to ID_pc4.
I.e.,
carryout_operations() {
  IF_pc = pc+4;
  ...
}
update_pipeline_registers() {
  IFID_pc4 = IF_pc4; 
  ....
}
read_pipeline_registers() {
  ID_pc4 = IFID_pc4;
  ...
}
***
Q8. I am unable to handle bnop2.out file. I tried all forms of debugging and found out it was because of a data hazard for $3 and it was not possible to execute properly using only 2 NOP instructions.
A8. That's because you did not take into account the fact that writing and reading (registers) happens during the first and second half of a cycle, respectively. I.e., register reading (rs and rt) in carryout_operations() must happen later than register writing (rd) in update_pc_reg_mem(). However, in the skeleton program, the former proceeds the latter.
An easy fix is to bring the register writing part of the latter to the former, particularly before the register reading.
carryout_operations();  // including register writing
update_pc_reg_mem(); // except register writing

Q9. The main problem is that for example we are running the file basic.asm then after running the code our output is not getting stop after 5 cycles but it is running on and on for many  cycles.
A9. The last instruction of the basic.asm is "halt" (12). If you use the skeleton program, cycles_to_halt is set to 4 upon the halt instruction and the program should stop after 4 more cycles. Why don;t you print the "cycles_to_halt" variable to debug?
while (true) {
  ....
  if (IF_inst == 12) cycles_to_halt = 4;
  if (cycles_to_halt > 0) cycles_to_halt --;
  if (cycles_to_halt == 0) break;
  printf("d ", cycles_to_halt); // just for debugging purpose
}
***
