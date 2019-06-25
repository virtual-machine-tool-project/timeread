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

/*Faster version of strlen*/
size_t strlenf(char * string)
{
	register size_t a;
	while(!(string[a] == 0))
	{
		a++;
	}
	return a;
}

/*Get how many letters are in an array of characters*/
size_t strlet(char * string, char letter)
{
	register unsigned int a;
	register unsigned int b = 0;
	for(a = 0; a < strlenf(string); a++)
	{
		if(string[a] == letter)
		{
			result++;
		}
	}
	return b;
}

#endif
