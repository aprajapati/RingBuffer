#include <atomic>

typedef unsigned long uint64;

#define pause __asm("pause");

using namespace std;

class CLockfreeRingBuffer {
	atomic<uint64_t> h;
	atomic<uint64_t> t;
	 uint   s;
	 int   *b;
	 int   MASK;

	public:
	CLockfreeRingBuffer( uint size ){
		s=size;
		h=t=0;
		b=new int[s];
		MASK=(s-1);
	}

	int get(){
		uint64_t _h = h.load();
		uint64_t _t = t.load();
		while( _h == _t ) {
			_h = h.load();
			_t = t.load();
			pause;
		}
		int r = b[_h & MASK];
		_h = h.fetch_add(1);
		return r;
	}

	void put( int v ){
		uint64_t _h = h.load();
		uint64_t _t = t.load();
		while((_t-_h) >= s )  {
			_h = h.load();
			_t = t.load();
			pause;
		}
		b[_t & MASK]=v;
		_t = t.fetch_add(1);
	}
};


