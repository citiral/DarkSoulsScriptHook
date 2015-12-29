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
		return retval;
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
		return retval;
	}
	
	template<class A1, class A2>
	void call_void_edx_1arg_pop_1(void(*func)(), A1 val_edx, A2 arg1)
	{
		_asm {
			mov edx, val_edx;
			push arg1;
			call func;
			pop edx;
		}
	}

	template<class A1, class A2, class A3>
	void call_void_eax_edx_1arg_pop_1(void(*func)(), A1 val_eax, A2 val_edx, A3 arg1)
	{
		_asm {
			mov eax, val_eax;
			mov edx, val_edx;
			push arg1;
			call func;
			pop edx;
		}
	}

	template<class A1, class A2, class A3>
	void call_void_ecx_edx_edi(void(*func)(), A1 val_ecx, A2 val_edx, A3 val_edi)
	{
		_asm {
			mov ecx, val_ecx;
			mov edx, val_edx;
			mov edi, val_edi;
			call func;
		}
	}
}