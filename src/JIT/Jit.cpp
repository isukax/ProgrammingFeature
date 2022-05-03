// https://jablogs.com/detail/23687

#include <stdio.h>
#include <windows.h>

using byte = unsigned char;
using pfunc = void(*)();

int arg1;
int arg2;
int res1;

union funcptr
{
	pfunc x;
	byte* y;
};

int main(void) 
{
	byte* buf = (byte*)VirtualAllocEx(GetCurrentProcess(), 0, 1 << 16, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	if (buf == 0) return 0;

	byte* p = buf;

	*p++ = 0x50; // push eax
	*p++ = 0x52; // push edx

	*p++ = 0xA1; // mov eax, [arg2]
	(int*&)p[0] = &arg2; p += sizeof(int*);

	*p++ = 0x92; // xchg edx,eax

	*p++ = 0xA1; // mov eax, [arg1]
	(int*&)p[0] = &arg1; p += sizeof(int*);

	*p++ = 0xF7; *p++ = 0xEA; // imul edx

	*p++ = 0xA3; // mov [res1],eax
	(int*&)p[0] = &res1; p += sizeof(int*);

	*p++ = 0x5A; // pop edx
	*p++ = 0x58; // pop eax
	*p++ = 0xC3; // ret

	funcptr func;
	func.y = buf;

	arg1 = 123; arg2 = 321; res1 = 0;

	func.x(); // call generated code

	printf("arg1=%i arg2=%i arg1*arg2=%i func(arg1,arg2)=%i\n", arg1, arg2, arg1 * arg2, res1);

	return 0;
}