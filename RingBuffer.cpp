#include <iostream>
#include <thread>
#include <atomic>

typedef unsigned long uint64;

#define pause ;
#define ITERATION 10000000

using namespace std;

class CRingBuffer {
	atomic<uint64_t> h;
	atomic<uint64_t> t;
	 uint   s;
	 int   *b;
	 int   MASK;

	public:
	CRingBuffer( uint size ){
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
		//cout << "Getting element at " << _h << endl;
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
		//cout << "Putting element at " << _t << endl;
	}
};

CRingBuffer buff( 8 ); 

void producer() {
	for( int i = 0; i < ITERATION; ++i ) {
		//cout << "P " << i << endl;
		buff.put( i );
	}
}

void consumer() {
	for( int i = 0; i < ITERATION; ++i ){
		cout << "G "<< buff.get() << endl;
	}
}

int main( int argc, char *argv[] ) {


	thread tC(consumer);
	thread tP(producer);

	tP.join();
	tC.join();

	return 0;
}
		




