//---------------------------------------------------------------------------
#pragma hdrstop
#include "modbusmod.hpp"


#pragma warn -8057

static  THeap heap(TSysInfo().GetPageSize()<<8);
 DWORD alloc_size = 0;

// void * operator new   (size_t sz)
// {
//  void * ptr =  heap.Alloc(sz,0);
//  if(ptr)
//     alloc_size+=sz;
//  return ptr;
// }
//  void * operator new[] (size_t sz)
// {
//  void * ptr =  heap.Alloc(sz,0);
//  if(ptr)
//     alloc_size+=sz;
//  return ptr;
// }
//
// void   operator delete (void * ptr)
// {
//  if(ptr && heap.Validate(ptr,0))
//  {
//    size_t sz = heap.MemSize(ptr,0);
//    alloc_size-=sz;
//    heap.Free(ptr,0);
//  }
// }
//
// void   operator delete [] (void * ptr)
// {
//  if(ptr /*&& heap.Validate(ptr,0)*/)
//  {
//    size_t sz = heap.MemSize(ptr,0);
//    alloc_size-=sz;
//    heap.Free(ptr,0);
//  }
// }

 DWORD       __fastcall TModbusModem::get_mem_used()
 {
  return heap.IsValid() ? heap.GetMemoryUsed() : GKH_RET_ERROR;
 }




LRESULT WINAPI module_main(DWORD cmd,LPARAM p1,LPARAM p2)
{
  LRESULT ret = 0;
       switch(cmd)
       {
        case GKME_CMD_GET_MODULETYPE:
			ret = MT_MODEM_MODBUS;break;//MT_MODEM
        case GKME_CMD_CREATE_HANDLE :
        {
            TModbusModem * mod =new TModbusModem;
            ret  = (LRESULT)(*(TGKHandleBased*)(mod))();
            if(!ret)
             delete mod;
        }
        break;
       }
       return ret;
}
#pragma warn .8057
