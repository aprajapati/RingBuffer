#include <dispatch/dispatch.h>

typedef unsigned long uint64;

using namespace std;

class CLockRingBuffer {
	uint64_t h;
	uint64_t t;
	uint   s;
	int   *b;
	int   MASK; 
	dispatch_semaphore_t	spP;
	dispatch_semaphore_t	spG;

	public:
	CLockRingBuffer( uint size ){
		s=size;
		h=t=0;
		b=new int[s];
		MASK=(s-1);
		spP = dispatch_semaphore_create(10);
		spG = dispatch_semaphore_create(0);
	}

	~CLockRingBuffer() {
		dispatch_release(spG);
		dispatch_release(spP);
	}


	int get(){
		
		dispatch_semaphore_wait(spG,DISPATCH_TIME_FOREVER);	
		int r = b[h & MASK];
		h++;
		dispatch_semaphore_signal(spP);
		return r;
	}

	void put( int v ){
		dispatch_semaphore_wait(spP,DISPATCH_TIME_FOREVER);
		b[t & MASK]=v;
		t++;
		dispatch_semaphore_signal(spG);
	}
};


