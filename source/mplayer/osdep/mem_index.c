#include "mem_index.h"

static u32 _size;
void* alloc_index(u32 size)
{
	unsigned char * heap_pos;
	u32 level;
	
	if(_size==0) return (unsigned char *)SYS_GetArena2Hi();

	size+=128;

	size &= ~0x1f;

	_size=size;
	
	_CPU_ISR_Disable(level);                
    heap_pos = (unsigned char *)( (u32)SYS_GetArena2Hi() - size );
    SYS_SetArena2Hi(heap_pos);
    _CPU_ISR_Restore(level);
    return heap_pos;
}

void free_index()
{
	unsigned char * heap_pos;
	u32 level;

	if(_size==0) return;
	
	_CPU_ISR_Disable(level);                
    heap_pos = (unsigned char *)((u32)SYS_GetArena2Hi() + _size);                               
    SYS_SetArena2Hi(heap_pos);
    _CPU_ISR_Restore(level);
	_size=0;

}



