#ifndef SIMPLE_MEMORY_MANAGER_STACK_ALLOCATOR_GUARD
#define SIMPLE_MEMORY_MANAGER_STACK_ALLOCATOR_GUARD

#include "../common/IAllocator.h"

namespace SimpleMemoryAllocator {

	/**
	* An allocator working like a stack. Therefore, all allocated memory must be deallocated
	* in a LIFO fashion: if you allocated A first and then B, you must first deallocate B before 
	* deallocating A.
	*/
	class StackAllocator : public IAllocator {
	private:
		void* m_top;
		void* m_previousTop;

		void* __allocate(size_t, uint8_t);
		void __deallocate(void*);
	public:
		StackAllocator(size_t);
		StackAllocator(void*, size_t);
		virtual ~StackAllocator();
	};

	struct StackAllocationHeader {
		uint8_t adjustment;
	};

}

#endif