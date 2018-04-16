#include <inc/memlayout.h>
#include <kern/kheap.h>
#include <kern/memory_manager.h>

//NOTE: All kernel heap allocations are multiples of PAGE_SIZE (4KB)

//=================================================================================//
//============================ REQUIRED FUNCTION ==================================//
//=================================================================================//
 uint32 f =KERNEL_HEAP_START;
 struct Arr
 {
 	uint32 start;
 	int size;
 };
 int j=0;
 struct Arr Array[1000];
 void* kmalloc(unsigned int size)
{

	//TODO: [PROJECT 2017 - [1] Kernel Heap] kmalloc()
	// Write your code here, remove the panic and write your code
	//panic("kmalloc() is not implemented yet...!!");

	//NOTE: Allocation is continuous increasing virtual address
	//NOTE: All kernel heap allocations are multiples of PAGE_SIZE (4KB)
	//refer to the project presentation and documentation for details
   uint32 new_start = f;
   size=ROUNDUP(size,PAGE_SIZE);
    Array[j].size=size;
   uint32 max_size= f+size;
   if(KERNEL_HEAP_MAX-f>size)
   {
   for(uint32 i=f;i<max_size;i+=PAGE_SIZE)
   {
	 uint32 *ptr_table = NULL;
     struct Frame_Info* ptr_frame_info;
     int r= allocate_frame(&ptr_frame_info);
     if(r == E_NO_MEM)
     {
    	 return NULL;
     }
	 r = map_frame(ptr_page_directory, ptr_frame_info, (void*)i,PERM_PRESENT|PERM_WRITEABLE);
	 if(r == E_NO_MEM)
	 {
		 free_frame(ptr_frame_info);
	     return NULL;
	 }
	 f += PAGE_SIZE;
   }
   Array[j].start=new_start;
   j++;
   return (void*)new_start;

   }
	//TODO: [PROJECT 2017 - BONUS1] Implement a Kernel allocation strategy
	// Instead of the continuous allocation/deallocation, implement both
	// FIRST FIT and NEXT FIT strategies
	// use "isKHeapPlacementStrategyFIRSTFIT() ..." functions to check the current strategy



	//change this "return" according to your answer
    return NULL;
}
void kfree(void* virtual_address)
{
	//TODO: [PROJECT 2017 - [1] Kernel Heap] kfree()
	// Write your code here, remove the panic and write your code
//	panic("kfree() is not implemented yet...!!");


	    for(int i=0;i<j;i++)
	{
	    if (virtual_address==(void*)Array[i].start)
		    {
		   uint32 VA=Array[i].start+Array[i].size;
		   for(uint32 k= (uint32)virtual_address;k<VA;k+=PAGE_SIZE)
		   {
			unmap_frame(ptr_page_directory,(uint32*)k);
		   }
			Array[i].size=0;
			Array[i].start=0;
	     }
	}


	//you need to get the size of the given allocation using its address
	//refer to the project presentation and documentation for details

}

unsigned int kheap_virtual_address(unsigned int physical_address)
{
	//TODO: [PROJECT 2017 - [1] Kernel Heap] kheap_virtual_address()
	// Write your code here, remove the panic and write your code
	//panic("kheap_virtual_address() is not implemented yet...!!");

	//return the virtual address corresponding to given physical_address
	//refer to the project presentation and documentation for details
	 struct Frame_Info *PA_frame = NULL;
    PA_frame =to_frame_info(physical_address); //??????????
     for (int i=KERNEL_HEAP_START;i<=f;i+=PAGE_SIZE)
     {
      struct Frame_Info*VA_frame = NULL;
      uint32 *Ptr= NULL;
      VA_frame = get_frame_info(ptr_page_directory ,(void *)i,&Ptr);
      if(PA_frame == VA_frame)
    	     return i;
     }
	//change this "return" according to your answer
	return 0;
}

unsigned int kheap_physical_address(unsigned int virtual_address)
{
	 uint32 phys;
	//TODO: [PROJECT 2017 - [1] Kernel Heap] kheap_physical_address()
	// Write your code here, remove the panic and write your code


	//panic("kheap_physical_address() is not implemented yet...!!");
	 uint32 offset=virtual_address & 0x00000FFF;
	        uint32 *ptr_table=NULL;
	    get_page_table(ptr_page_directory,(void*)virtual_address,&ptr_table);
	      if(ptr_table==NULL)
	           {
	         	  return -1;
	           }
	       int tableIndex = PTX(virtual_address);
	       int present = ptr_table[tableIndex] & PERM_PRESENT;
	           if (present!=0)
	          {
	        	uint32 VA = (ptr_table[tableIndex] & 0xFFFFF000);
	             VA += offset;
	           	return VA;}
	           	return 0;


	//return the physical address corresponding to given virtual_address
	//refer to the project presentation and documentation for details

	//change this "return" according to your answer

}


//=================================================================================//
//============================== BONUS FUNCTION ===================================//
//=================================================================================//
// krealloc():

//	Attempts to resize the allocated space at "virtual_address" to "new_size" bytes,
//	possibly moving it in the heap.
//	If successful, returns the new virtual_address, in which case the old virtual_address must no longer be accessed.
//	On failure, returns a null pointer, and the old virtual_address remains valid.

//	A call with virtual_address = null is equivalent to kmalloc().
//	A call with new_size = zero is equivalent to kfree().

void *krealloc(void *virtual_address, uint32 new_size)
{
	//TODO: [PROJECT 2017 - BONUS2] Kernel Heap Realloc
	// Write your code here, remove the panic and write your code
	return NULL;
	panic("krealloc() is not implemented yet...!!");


}
