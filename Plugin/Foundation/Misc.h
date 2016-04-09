﻿#ifndef utj_Misc_h
#define utj_Misc_h

#ifdef utjWindows
    #define utjDLLExt ".dll"
#else 
    #ifdef utjMac
        #define utjDLLExt ".dylib"
    #else
        #define utjDLLExt ".so"
    #endif
#endif

namespace utj {

typedef void* module_t;
module_t    DLLLoad(const char *path);
void        DLLUnload(module_t mod);
void*       DLLGetSymbol(module_t mod, const char *name);
void        DLLAddSearchPath(const char *path);
const char* DLLGetDirectoryOfCurrentModule();

void*       AlignedAlloc(size_t size, size_t align);
void        AlignedFree(void *p);

double      GetCurrentTimeSec();

// execute command and **wait until it ends**
// return exit-code
int         Execute(const char *command);

typedef std::pair<std::string, std::string> StringPair;
StringPair SplitDirFile(const std::string &path);
StringPair SplitFileExt(const std::string &path);
void Glob(const char *pattern, const std::function<void(const char*)>& f);


// -------------------------------------------------------------
// Math functions
// -------------------------------------------------------------

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

template<class Int>
inline u16 u16_be(Int v_)
{
    u16 v = (u16)v_;
    return ((v >> 8) & 0xFF) | ((v & 0xFF) << 8);
}

template<class Int>
inline u32 u32_be(Int v_)
{
    u32 v = (u32)v_;
    return ((v >> 24) & 0xFF) | (((v >> 16) & 0xFF) << 8) | (((v >> 8) & 0xFF) << 16) | ((v & 0xFF) << 24);
}

template<class Int>
inline u64 u64_be(Int v_)
{
    u64 v = (u64)v_;
    return
        ((v >> 56) & 0xFF) | (((v >> 48) & 0xFF) << 8) | (((v >> 40) & 0xFF) << 16) | (((v >> 32) & 0xFF) << 24) |
        (((v >> 24) & 0xFF) << 32) | (((v >> 16) & 0xFF) << 40) | (((v >> 8) & 0xFF) << 48) | ((v & 0xFF) << 56);
}

// i.e:
//  roundup<16>(31) : 32
//  roundup<16>(32) : 32
//  roundup<16>(33) : 48
template<int N, class IntType>
inline IntType roundup(IntType v)
{
    return v + (N - v % N);
}

// i.e: 
//  ceildiv(31, 16) : 2
//  ceildiv(32, 16) : 2
//  ceildiv(33, 16) : 3
template<class IntType>
inline IntType ceildiv(IntType a, IntType b)
{
    return a / b + (a%b == 0 ? 0 : 1);
}

} // namespace utj

#endif // utj_Misc_h
