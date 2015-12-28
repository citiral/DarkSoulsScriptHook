#pragma once

namespace FunctionCalling {

	template<class A1, class A2>
	void call_void(void(*func)(), A1 arg1, A2 arg2)
	{
		_asm {
			push arg2;
			push arg1;
			call func;
		}
	}

	template<class A1>
	void call_void(void(*func)(), A1 arg1)
	{
		_asm {
			push arg1;
			call func;
		}
	}

	template<class A1>
	void thiscall_void(void(*func)(), void* thispointer, A1 arg1)
	{
		_asm {
			mov ecx, thispointer;
			push arg1;
			call func;
		}
	}

	template<class A1, class A2, class A3>
	void* call_ptr_eax_edx_esi(void(*func)(), A1 val_eax, A2 val_edx, A3 val_esi)
	{
		void* retval = (void*)1;
		_asm {
			mov eax, val_eax;
			mov edx, val_edx;
			mov esi, val_esi;
			call func;
			mov retval, eax;
		}
	}

	template<class A1, class A2, class A3, class A4>
	void* call_ptr_eax_ecx_edx_esi(void(*func)(), A1 val_eax, A2 val_ecx, A3 val_edx, A4 val_esi)
	{
		void* retval = (void*)1;
		_asm {
			mov eax, val_eax;
			mov ecx, val_ecx;
			mov edx, val_edx;
			mov esi, val_esi;
			call func;
			mov retval, eax;
		}
	}
}