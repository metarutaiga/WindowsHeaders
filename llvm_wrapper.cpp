#include <new>
#include <memory>
#include <string>
#include <vector>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//------------------------------------------------------------------------------
extern "C" const int _fltused = 1;
//------------------------------------------------------------------------------
#pragma data_seg(".tls")
#pragma data_seg(".tls$ZZZ")
#pragma data_seg()
#pragma section(".CRT$XLA", long, read)
#pragma section(".CRT$XLZ", long, read)
#pragma section(".rdata$T", long, read)
extern "C" ULONG _tls_index = 0;
extern "C" __declspec(allocate(".tls"))     char _tls_start = 0;
extern "C" __declspec(allocate(".tls$ZZZ")) char _tls_end = 0;
extern "C" __declspec(allocate(".CRT$XLA")) const PIMAGE_TLS_CALLBACK __xl_a = 0;
extern "C" __declspec(allocate(".CRT$XLZ")) const PIMAGE_TLS_CALLBACK __xl_z = 0;
extern "C" __declspec(allocate(".rdata$T")) const IMAGE_TLS_DIRECTORY _tls_used =
{
#if defined(_WIN64)
    (ULONGLONG) &_tls_start,
    (ULONGLONG) &_tls_end,
    (ULONGLONG) &_tls_index,
    (ULONGLONG)(&__xl_a + 1),
#else
    (ULONG_PTR) &_tls_start,
    (ULONG_PTR) &_tls_end,
    (ULONG_PTR) &_tls_index,
    (ULONG_PTR)(&__xl_a + 1),
#endif
    (ULONG)0,
    (ULONG)0,
};
//------------------------------------------------------------------------------
#pragma section(".CRT$XCA", long, read)
#pragma section(".CRT$XCZ", long, read)
#pragma section(".CRT$XIA", long, read)
#pragma section(".CRT$XIZ", long, read)
#pragma section(".CRT$XPA", long, read)
#pragma section(".CRT$XPZ", long, read)
#pragma section(".CRT$XTA", long, read)
#pragma section(".CRT$XTZ", long, read)
typedef void (*_PVFV)();
extern "C" __declspec(allocate(".CRT$XCA")) const _PVFV __xc_a = 0;
extern "C" __declspec(allocate(".CRT$XCZ")) const _PVFV __xc_z = 0;
extern "C" __declspec(allocate(".CRT$XIA")) const _PVFV __xi_a = 0;
extern "C" __declspec(allocate(".CRT$XIZ")) const _PVFV __xi_z = 0;
extern "C" __declspec(allocate(".CRT$XPA")) const _PVFV __xp_a = 0;
extern "C" __declspec(allocate(".CRT$XPZ")) const _PVFV __xp_z = 0;
extern "C" __declspec(allocate(".CRT$XTA")) const _PVFV __xt_a = 0;
extern "C" __declspec(allocate(".CRT$XTZ")) const _PVFV __xt_z = 0;
#pragma comment(linker, "/merge:.CRT=.rdata")
//------------------------------------------------------------------------------
static void _initterm(const _PVFV* ppfn, const _PVFV* end)
{
    do
    {
        if (_PVFV pfn = *++ppfn)
        {
            pfn();
        }
    } while (ppfn < end);
}
//------------------------------------------------------------------------------
extern "C" BOOL WINAPI _DllMainCRTStartup(HANDLE handle, DWORD reason, LPVOID preserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        _initterm(&__xi_a, &__xi_z);
        _initterm(&__xc_a, &__xc_z);
        break;

    case DLL_PROCESS_DETACH:
        _initterm(&__xp_a, &__xp_z);
        _initterm(&__xt_a, &__xt_z);
        break;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    }
    return TRUE;
}
//------------------------------------------------------------------------------
#if defined(_HAVE_WINMAIN_)
extern "C" IMAGE_DOS_HEADER __ImageBase;
extern "C" void wWinMainCRTStartup()
{
    _DllMainCRTStartup(NULL, DLL_PROCESS_ATTACH, NULL);
    STARTUPINFOW startupInfo;
    GetStartupInfoW(&startupInfo);
    int showWindowMode = startupInfo.dwFlags & STARTF_USESHOWWINDOW ? startupInfo.wShowWindow : SW_SHOWDEFAULT;
    int result = wWinMain((HINSTANCE)&__ImageBase, NULL, GetCommandLineW(), showWindowMode);
    _DllMainCRTStartup(NULL, DLL_PROCESS_DETACH, NULL);
    TerminateProcess(GetCurrentProcess(), result);
}
#endif
//==============================================================================
//  new / delete
//==============================================================================
void* operator new(size_t size)
{
    return malloc(size);
}
void* operator new[](size_t size)
{
    return malloc(size);
}
//------------------------------------------------------------------------------
void operator delete(void* ptr) noexcept
{
    free(ptr);
}
void operator delete(void* ptr, size_t size) noexcept
{
    free(ptr);
}
void operator delete[](void* ptr) noexcept
{
    free(ptr);
}
void operator delete[](void* ptr, size_t size) noexcept
{
    free(ptr);
}
//------------------------------------------------------------------------------
#if defined(_LIBCPP_VERSION)
_LIBCPP_BEGIN_NAMESPACE_STD
    template class _LIBCPP_CLASS_TEMPLATE_INSTANTIATION_VIS __basic_string_common<true>;
    template class _LIBCPP_CLASS_TEMPLATE_INSTANTIATION_VIS basic_string<char>;
    template class _LIBCPP_CLASS_TEMPLATE_INSTANTIATION_VIS __vector_base_common<true>;
    __shared_count::~__shared_count() {}
    __shared_weak_count::~__shared_weak_count() {}
    void __shared_weak_count::__release_weak() _NOEXCEPT
    {
        if (__atomic_load_n(&__shared_weak_owners_, __ATOMIC_ACQUIRE) == 0)
            __on_zero_shared_weak();
        else if (__atomic_add_fetch(&__shared_weak_owners_, -1, __ATOMIC_ACQ_REL) == -1)
            __on_zero_shared_weak();
    }
    __shared_weak_count* __shared_weak_count::lock() _NOEXCEPT
    {
        long object_owners = __atomic_load_n(&__shared_owners_, __ATOMIC_SEQ_CST);
        while (object_owners != -1)
        {
            if (__atomic_compare_exchange_n(&__shared_owners_,
                                            &object_owners,
                                            object_owners + 1,
                                            true,
                                            __ATOMIC_SEQ_CST,
                                            __ATOMIC_SEQ_CST))
                return this;
        }
        return nullptr;
    }
    const void* __shared_weak_count::__get_deleter(const type_info&) const _NOEXCEPT
    {
        return nullptr;
    }
_LIBCPP_END_NAMESPACE_STD
#endif
//------------------------------------------------------------------------------
