/* © Quirk (babhishek21). Free for reference and educational purposes.
	I take no responsibilty as to the outcomes of running this code. */

#include <iostream>
#include <stdio.h>

using namespace std;

int Z(unsigned long int); // refer FCTRL

int main() {
	unsigned long int T,N,tok; // refer FCTRL
	int foo; // foo:cypher; tok:counter token
	
	scanf("%lu", &T);
	
	for(tok=0;tok<T;tok++) {
		scanf("%lu", &N);
		foo = Z(N);
		printf("%lu\n", foo);
	}

	cin.ignore();
	return 0;
}

int Z(unsigned long int N) {
	int num2,num5,tot2, tot5; //num*=num_* as int; tot* = tot*+num*
	double num_2=N, num_5=N; // To stop truncation
	int poo,boo;

	for(boo=0,tot2=0;num_2>1;boo++) {
		num_2 = num_2/2;
		num2 = num_2;
	
		tot2 = tot2 + num2;
	}

	for(boo=0,tot5=0;num_5>1;boo++) {
		num_5 = num_5/5;
		num5 = num_5;

		tot5 = tot5 + num5;
	}

	if (tot2 >= tot5) {
		return tot5; 
	} else {
		return tot2;
	}

}