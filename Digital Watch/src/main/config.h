



#ifndef _CONFIG_H_
#define _CONFIG_H_


#define 	OPR_TIME  		(8) /*
			The entire time (in s-seconds) is going to last
			for OPR_TIME
			*/ 
#define		F_OVERFLOW		((F_CPU - 256UL) / (256UL * 255)) /*
			The number of times/frequency of the TIMER0 overflow
			in a single second
			*/


#endif /* _CONFIG_H_ */