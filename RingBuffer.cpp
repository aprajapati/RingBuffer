#include <iostream>
#include <thread>

#include "LockRingBuffer.h"
#include "LockfreeRingBuffer.h"

#define ITERATION 1000000000

CLockRingBuffer buff( 8 ); 

void producer() {
	for( int i = 0; i < ITERATION; ++i ) {
		buff.put( i );
	}
}

void consumer() {
	for( int i = 0; i < ITERATION; ++i ){
		//cout << "G "<< buff.get() << endl;
		buff.get();
	}
}

int main( int argc, char *argv[] ) {
	thread tC(consumer);
	thread tP(producer);

	tP.join();
	tC.join();

	return 0;
}
		




