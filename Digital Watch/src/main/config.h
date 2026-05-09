



#ifndef _CONFIG_H_
#define _CONFIG_H_


#define 	OPR_TIME  		(8) /*
			The entire time (in s-seconds) is going to last
			for OPR_TIME
			*/ 
#define		F_OVERFLOW		((F_CPU) / (1024UL * 124) - 1) /*
			The number of times/frequency of the TIMER0 overflow
			in a single second
			*/
#define 	HOUR_OVF		(13)

#define 	MINUTE_OVF		(60)

#define 	LONG_CLICK		(125)

#define 	SHORT_CLICK		(20)

#endif /* _CONFIG_H_ */