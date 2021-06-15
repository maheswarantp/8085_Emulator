# 8085_Emulator

This is a 8085 emulator written in cpp using OOP concepts. Contribute if u want to.

![Intel 8085](/assets/8085.jpg)

Our plan is split into three phases

## Phase 1

- A, BC, DE, HL Registers
- ADD, SUB, LDA, STA, MOV, MVI, INC, DCR instructions
- JUMP Instructions (JNZ, JZ, JC, JNC)


### What is done?
- A, B, C, D, E, H, L 8 bit registers
- MVI, STA, LDA, ADD, SUB, MOV, RST, LXI, LHLD
- 16 bit register pairs (BC, DE, HL)
- DATA TRANSFER GROUP DONE

### What is tbd?
- Jump instructions (JZ, JNZ, JC, JNC)
- PC, Stack pointer, INX/DCX

# Phase 2
- Implement the program counter and the simulation logic
- Implement stack pointer
- Work on GUI start

# Phase 3
- Timing diagram evaluation (possible with built in sleep modules to emulate clock cycles)
- Variable frequency??
- TBD.