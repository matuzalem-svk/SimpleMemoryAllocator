#include "LinearAllocator.h"

using namespace SimpleMemoryAllocator;

LinearAllocator::LinearAllocator(size_t memorySize) : IAllocator(nullptr, memorySize), m_firstFree(m_start) { }

LinearAllocator::LinearAllocator(void* memoryPtr, size_t memorySize) : IAllocator(memoryPtr, memorySize), m_firstFree(m_start) { }

LinearAllocator::~LinearAllocator() {
	m_firstFree = nullptr;
}

void* LinearAllocator::__allocate(size_t size, uint8_t alignment) {
	throw_assert(size > 0, "allocated size must be larger than 0");

	uint8_t adjustment = MemoryUtils::getNextAddressAdjustment(m_firstFree, alignment);

	// don't allocate if we need to allocate more than we have free
	if (m_usedMemory + size + adjustment > m_size) return nullptr;

	void* alignedAddress = MemoryUtils::addToPointer(m_firstFree, adjustment);
	m_firstFree = MemoryUtils::addToPointer(alignedAddress, size);
	m_usedMemory += size + adjustment;
	++m_numAllocations;

	return alignedAddress;
}

void LinearAllocator::__deallocate(void* ptr) {
	throw_assert(false, "method deallocate() is not usable in a linear allocator, use method clear() instead");
}

void LinearAllocator::clear() {
	m_numAllocations = 0;
	m_usedMemory = 0;
	m_firstFree = m_start;
}