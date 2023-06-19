/*****************************************************************
* lab1.cmd
******************************************************************/
MEMORY

{
	VECS:	o=00000000h	l=00000200h	/* interrupt vectors */
	PMEM:	o=00000200h l=0000FE00h /*Internal RAM (L2) mem */
	BMEM:	o=80000000h l=01000000h /* CEO, SDRAM, 16 MBytes */
}
SECTIONS
{
	.intvecs	>	0h
	.text		>	BMEM
	.rtdx_text	>	BMEM
	.far		>	BMEM
	.stack		>	BMEM
	.bss		>	BMEM
	.cinit		>	BMEM
	.pinit		>	BMEM
	.cio		>	BMEM
	.const		>	BMEM
	.data		>	BMEM
	.rtdx_data	>	BMEM
	.switch		>	BMEM
	.system		>	BMEM
}