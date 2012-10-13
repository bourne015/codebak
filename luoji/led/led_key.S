.text
.global _start

_start:
#define	GPMCON  0x7F008820
#define	GPMDAT  0x7F008824
#define	GPMPUD  0x7F008828
#define	GPNCON  0X7F008830
#define	GPNDAT  0X7F008834
#define	GPNPUD  0X7F008838

#	AREA TEST,CODE,READONLY
#	ENTRY
#	CODE32
#START   
	LDR R0,=GPMCON
	LDR R1,=0x11111
	STR R1,[R0]
	LDR R0,=GPMPUD
	MOV R1,#0X00
	STR R1,[R0]
	LDR R0,=GPNCON
	LDR R1,=0XFFFFF000
	STR R1,[R0]

WORKER: LDR R0,=GPMDAT
        LDR R1,=0xEEEEEEEE
        LDR R4,=GPNDAT
        LDR R5,[R4]

LOOP:   STR R1,[R0]
        MOV R2,#0
        MOV R3,#0
        MOV R1,R1,ROR #1

KEY:    LDR R5,[R4]
        CMP R5,#0X7F  
        BEQ KEY

UP:     LDR R5,[R4]
        CMP R5,#0X7F
        BNE UP        
        B LOOP 
      
#        END	
