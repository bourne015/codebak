#define P1MEMCCMD	(*((volatile unsigned long *)0x7e001004))
#define P1REFRESH	(*((volatile unsigned long *)0x7e001010))
#define P1CASLAT	(*((volatile unsigned long *)0x7e001014))
#define P1T_DQSS	(*((volatile unsigned long *)0x7e001018))
#define P1T_MRD		(*((volatile unsigned long *)0x7e00101c))
#define P1T_RAS		(*((volatile unsigned long *)0x7e001020))
#define P1T_RC		(*((volatile unsigned long *)0x7e001024))
#define P1T_RCD		(*((volatile unsigned long *)0x7e001028))
#define P1T_RFC		(*((volatile unsigned long *)0x7e00102c))
#define P1T_RP		(*((volatile unsigned long *)0x7e001030))
#define P1T_RRD		(*((volatile unsigned long *)0x7e001034))
#define P1T_WR		(*((volatile unsigned long *)0x7e001038))
#define P1T_WTR		(*((volatile unsigned long *)0x7e00103c))
#define P1T_XP		(*((volatile unsigned long *)0x7e001040))
#define P1T_XSR		(*((volatile unsigned long *)0x7e001044))
#define P1T_ESR		(*((volatile unsigned long *)0x7e001048))

#define P1MEMCFG	(*((volatile unsigned long *)0x7e00100c))
#define P1MEMCFG2	(*((volatile unsigned long *)0x7e00104c))
#define P1_chip_0_cfg	(*((volatile unsigned long *)0x7e001200))

#define P1DIRECTCMD	(*((volatile unsigned long *)0x7e001008))
#define MEM_SYS_CFG	(*((volatile unsigned long *)0x7e00f120))

#define P1MEMSTAT	(*((volatile unsigned long *)0x7e001000))
#define HCLK		133
#define nstoclk(ns)	(ns/(1000/HCLK)+1)

void ddr_init(void)
{
	/*set DRAM to config state*/
	P1MEMCCMD = 0x4;
	
	/*write mem timing parameter...*/
	P1REFRESH = nstoclk(7800);
	P1CASLAT = (3 << 1);
	P1T_DQSS = 0x1;
	P1T_MRD = 0x2;
	P1T_RAS = nstoclk(45);
	P1T_RC = nstoclk(68);
	P1T_RCD = (nstoclk(23) | (nstoclk(23)-3) << 3);
	P1T_RFC = (nstoclk(80) | (nstoclk(80)-3) << 5);
	P1T_RP = (nstoclk(23) | (nstoclk(23)-3) << 3);
	P1T_RRD = nstoclk(15);
	P1T_WR = nstoclk(15);
	P1T_WTR = 0x7;
	P1T_XP = 0X1;
	P1T_XSR = nstoclk(120);
	P1T_ESR = nstoclk(120);
	/*set mem cfg,row,cloumn,bits...*/
	P1MEMCFG &= ~(0x7);
	P1MEMCFG |= (0x1 << 1); //10 column address

	P1MEMCFG &= ~(0x38);
	P1MEMCFG |= (0x3 << 3); //14 row
	
	P1MEMCFG &= ~(0x1 << 6);
	
	P1MEMCFG &= ~(0x7 << 15);
	P1MEMCFG |= (0x2 << 15);

	P1MEMCFG &= ~(0xf);
	P1MEMCFG |= (0x5);
	
	P1MEMCFG &= ~(0x3 << 6);
	P1MEMCFG |= (0x1 << 6);

	P1MEMCFG &= ~(0x7 << 8);
	P1MEMCFG |= (0x3 << 8);

	P1MEMCFG &= ~(0x3 << 11);
	P1MEMCFG |= (0x1 << 11);

	P1_chip_0_cfg |= (0x1 << 16);

	P1DIRECTCMD = 0xc0000;
	P1DIRECTCMD = 0x0000;
	P1DIRECTCMD = 0x40000;
	P1DIRECTCMD = 0x40000;
	P1DIRECTCMD = 0xa0000;
	P1DIRECTCMD = 0x80032;

	MEM_SYS_CFG = 0x0;
	
	P1MEMCCMD = 0x00;
	
	while (!((P1MEMSTAT & 0x3) == 0x1));
}
