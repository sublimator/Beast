//------------------------------------------------------------------------------
/*
    This file is part of Beast: https://github.com/vinniefalco/Beast
    Copyright 2013, Vinnie Falco <vinnie.falco@gmail.com>

    Portions of this file are from JUCE.
    Copyright (c) 2013 - Raw Material Software Ltd.
    Please visit http://www.juce.com

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#if BEAST_INCLUDE_BEASTCONFIG
#include <BeastConfig.h>
#endif

//==============================================================================
#include <modules/beast_core/native/BasicNativeHeaders.h>
#include <modules/beast_core/beast_core.h>

#include <locale>
#include <cctype>

#if ! BEAST_BSD
 #include <sys/timeb.h>
#endif

#if ! BEAST_ANDROID
 #include <cwctype>
#endif

#if BEAST_WINDOWS
 #include <ctime>
 #include <winsock2.h>
 #include <ws2tcpip.h>

 #if ! BEAST_MINGW
  #include <Dbghelp.h>

  #if ! BEAST_DONT_AUTOLINK_TO_WIN32_LIBRARIES
   #pragma comment (lib, "DbgHelp.lib")
  #endif
 #endif

 #if BEAST_MINGW
  #include <ws2spi.h>
 #endif

#else
 #if BEAST_LINUX || BEAST_ANDROID
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <sys/errno.h>
  #include <unistd.h>
  #include <netinet/in.h>
 #endif

 #if BEAST_LINUX
  #include <langinfo.h>
 #endif

 #include <pwd.h>
 #include <fcntl.h>
 #include <netdb.h>
 #include <arpa/inet.h>
 #include <netinet/tcp.h>
 #include <sys/time.h>
 #include <net/if.h>
 #include <sys/ioctl.h>

 #if ! BEAST_ANDROID && ! BEAST_BSD
  #include <execinfo.h>
 #endif
#endif

#if BEAST_MAC || BEAST_IOS
 #include <xlocale.h>
 #include <mach/mach.h>
#endif

#if BEAST_ANDROID
 #include <android/log.h>
#endif

//------------------------------------------------------------------------------

// If the MSVC debug heap headers were included, disable
// the macros during the juce include since they conflict.
#ifdef _CRTDBG_MAP_ALLOC
#pragma push_macro("calloc")
#pragma push_macro("free")
#pragma push_macro("malloc")
#pragma push_macro("realloc")
#pragma push_macro("_recalloc")
#pragma push_macro("_aligned_free")
#pragma push_macro("_aligned_malloc")
#pragma push_macro("_aligned_offset_malloc")
#pragma push_macro("_aligned_realloc")
#pragma push_macro("_aligned_recalloc")
#pragma push_macro("_aligned_offset_realloc")
#pragma push_macro("_aligned_offset_recalloc")
#pragma push_macro("_aligned_msize")
#undef calloc
#undef free
#undef malloc
#undef realloc
#undef _recalloc
#undef _aligned_free
#undef _aligned_malloc
#undef _aligned_offset_malloc
#undef _aligned_realloc
#undef _aligned_recalloc
#undef _aligned_offset_realloc
#undef _aligned_offset_recalloc
#undef _aligned_msize
#endif

#include <modules/beast_core/diagnostic/FatalError.cpp>
#include <modules/beast_core/diagnostic/SemanticVersion.cpp>
#include <modules/beast_core/diagnostic/UnitTestUtilities.cpp>

#include <modules/beast_core/files/DirectoryIterator.cpp>
#include <modules/beast_core/files/File.cpp>
#include <modules/beast_core/files/FileInputStream.cpp>
#include <modules/beast_core/files/FileOutputStream.cpp>
#include <modules/beast_core/files/FileSearchPath.cpp>
#include <modules/beast_core/files/RandomAccessFile.cpp>
#include <modules/beast_core/files/TemporaryFile.cpp>

#include <modules/beast_core/logging/Logger.cpp>

#include <modules/beast_core/maths/Random.cpp>

#include <modules/beast_core/memory/MemoryBlock.cpp>

#include <modules/beast_core/misc/Result.cpp>

#include <modules/beast_core/streams/FileInputSource.cpp>
#include <modules/beast_core/streams/InputStream.cpp>
#include <modules/beast_core/streams/MemoryOutputStream.cpp>
#include <modules/beast_core/streams/OutputStream.cpp>

#include <modules/beast_core/system/SystemStats.cpp>

#include <modules/beast_core/text/LexicalCast.cpp>
#include <modules/beast_core/text/StringArray.cpp>
#include <modules/beast_core/text/StringPairArray.cpp>

#include <modules/beast_core/thread/DeadlineTimer.cpp>
#include <modules/beast_core/thread/Workers.cpp>

#include <modules/beast_core/time/AtExitHook.cpp>
#include <modules/beast_core/time/Time.cpp>

#if BEAST_MAC || BEAST_IOS
#include <modules/beast_core/native/osx_ObjCHelpers.h>
#endif

#if BEAST_ANDROID
#include "native/android_JNIHelpers.h"
#endif

#if ! BEAST_WINDOWS
#include <modules/beast_core/native/posix_SharedCode.h>
#endif

#if BEAST_MAC || BEAST_IOS
#include <modules/beast_core/native/mac_Files.mm>
#include <modules/beast_core/native/mac_Strings.mm>
#include <modules/beast_core/native/mac_SystemStats.mm>
#include <modules/beast_core/native/mac_Threads.mm>

#elif BEAST_WINDOWS
#include <modules/beast_core/native/win32_ComSmartPtr.h>
#include <modules/beast_core/native/win32_Files.cpp>
#include <modules/beast_core/native/win32_Registry.cpp>
#include <modules/beast_core/native/win32_SystemStats.cpp>
#include <modules/beast_core/native/win32_Threads.cpp>

#elif BEAST_LINUX
#include <modules/beast_core/native/linux_Files.cpp>
#include <modules/beast_core/native/linux_SystemStats.cpp>
#include <modules/beast_core/native/linux_Threads.cpp>

#elif BEAST_BSD
#include <modules/beast_core/native/bsd_Files.cpp>
#include <modules/beast_core/native/bsd_SystemStats.cpp>
#include <modules/beast_core/native/bsd_Threads.cpp>

#elif BEAST_ANDROID
#include "native/android_Files.cpp"
#include "native/android_Misc.cpp"
#include "native/android_SystemStats.cpp"
#include "native/android_Threads.cpp"

#endif

// Has to be outside the beast namespace
extern "C" {
void beast_reportFatalError (char const* message, char const* fileName, int lineNumber)
{
    if (beast::beast_isRunningUnderDebugger())
        beast_breakDebugger;
    beast::FatalError (message, fileName, lineNumber);
    BEAST_ANALYZER_NORETURN
}
}

#ifdef _CRTDBG_MAP_ALLOC
#pragma pop_macro("calloc")
#pragma pop_macro("free")
#pragma pop_macro("malloc")
#pragma pop_macro("realloc")
#pragma pop_macro("_recalloc")
#pragma pop_macro("_aligned_free")
#pragma pop_macro("_aligned_malloc")
#pragma pop_macro("_aligned_offset_malloc")
#pragma pop_macro("_aligned_realloc")
#pragma pop_macro("_aligned_recalloc")
#pragma pop_macro("_aligned_offset_realloc")
#pragma pop_macro("_aligned_offset_recalloc")
#pragma pop_macro("_aligned_msize")
#endif

// Must be outside the namespace
#include <modules/beast_core/system/BoostPlaceholdersFix.cpp>