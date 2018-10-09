int msb(unsigned x) 
{
	union { 
		double a; int b[2]; 
	};
	a = x;
	return (b[1] >> 20) - 1023;
}