#include "pic32mx.h"
#include "io.h"

int main() {
	while (1) {
		PORTE = ~PORTE;
		delay(1000);
	}
	return 0;
}
