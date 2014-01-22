#include "ADXL362.h"

ADXL362::ADXL362(byte range, byte mode){
	SPI.begin();
	SPI.setBitOrder(MSBFIRST);
	SPI.setDataMode(SPI_MODE0);
	reset();
	delay(100);

	setRange(range);
	writeRegister(0x2D, &mode);
	return;
}

void ADXL362::reset(){
	writeRegister(0x1F, &((int)0x52));
	return;
}

int ADXL362::getAccel(char axis){
	int val;
	switch(axis){
		case 'x': case 'X':
			readRegister(0x0E, (byte *)(&val), 2);
			break;
		case 'y': case 'Y':
			readRegister(0x0E, (byte *)(&val), 2);
			break;
		case 'z': case 'Z':
			readRegister(0x0E, (byte *)(&val), 2);
			break;
	}
	return (int)(highByte(val) + (lowByte(val) << 8));
}

void get3Accel(int a[3]){
	readRegister(0x0E, (byte *)a, 6);
	for(int i=0;i<3;i++) a[i] = (int)(highByte(a[i]) + (lowByte(a[i]) << 8));
	return;
}
