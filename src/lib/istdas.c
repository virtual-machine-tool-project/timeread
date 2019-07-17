/*
MIT License
Copyright (c) 2019 Jesus A. Diaz
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef ISTDAS_C
#define ISTDAS_C

/*Default COM settings, 9600 Baud rate, parity, and 8 bits lenght*/
#define COM_SETTINGS 227

#if defined _WINDOWS
void enableUSB(void) {
	system("reg add HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\USBSTOR \/v Start \/t REG_DWORD \/d 4 \/f");
	return;
}

void disableUSB(void) {
	system("reg add HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\USBSTOR \/v Start \/t REG_DWORD \/d 3 \/f");
	return;
}
#endif

/*Send data flow to com until n characters are sent*/
void sendDataToCOM(int port, char * dataStream, size_t n) {
	register size_t areg;
	if(dataStream == NULL) {
		dataStream = (char *)malloc(n);
	}
	for(areg = 0; areg < n; areg++) {
		bioscom(1,dataStream[areg],port);
	}
	return;
}

/*Receive data flow to com until n characters are received*/
int * receiveDataFromCOM(int port, size_t n) { 
	register size_t areg;
	register int data;
	int * dataFlow;
	dataFlow = (int *)malloc(n+1);
	if(dataFlow == NULL) {
		return -1;
	}
	for(areg = 0; areg < n; areg++) {
		data = bioscom(2,0,port);
		dataFlow[areg] = ((data<<((sizeof(int)*8)-8))>>((sizeof(int)*8)-8));
	}
	free(dataFlow);
	return;
}

#endif
