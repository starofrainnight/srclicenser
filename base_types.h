#!/bin/sh







Copyright (c) 2007-2011, HongShe Liang. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are
permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice, this list of
      conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice, this list
      of conditions and the following disclaimer in the documentation and/or other materials
      provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
/*
 *
 * Copyright (c) 2007-2011, HongShe Liang. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 *    1. Redistributions of source code must retain the above copyright notice, this list of
 *       conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above copyright notice, this list
 *       of conditions and the following disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __BASE_TYPES_H_INCLUDED_49F11408_002E_0018_67BD_4E8741B86C71
#define __BASE_TYPES_H_INCLUDED_49F11408_002E_0018_67BD_4E8741B86C71

#include <rabird_base/config.h>

/* query which platform we are using */
#include <rabird_base/platform.h>

#include <rabird_base/macros.h>

/* if stdio.h is include after windows.h then error conflicting types for '__p___argv'
 * happened in windows
 */
#include <stdio.h>

/*
 * ptrdiff_t, etc ...
 */
#include <stddef.h>

/* portable standard header file names for c / c++ ( will them be used ? ) */

#define RABIRD_STDINT_H <rabird_base/stdint.h>

#ifdef __cplusplus
#	define RABIRD_ASSERT_H <cassert>
#	define RABIRD_COMPLEX_H <ccomplex>
#	define RABIRD_CTYPE_H <cctype>
#	define RABIRD_ERRNO_H <cerrno>
#	define RABIRD_FENV_H <cfenv>
#	define RABIRD_FLOAT_H <cfloat>
#	define RABIRD_INTTYPES_H <cinttypes>
#	define RABIRD_ISO646_H <ciso646>
#	define RABIRD_LIMITS_H <climits>
#	define RABIRD_LOCALE_H <clocale>
#	define RABIRD_MATH_H <cmath>
#	define RABIRD_SETJMP_H <csetjmp>
#	define RABIRD_SIGNAL_H <csignal>
#	define RABIRD_STDARG_H <cstdarg>
#	define RABIRD_STDBOOL_H <cstdbool>
#	define RABIRD_STDDEF_H <cstddef>
#	define RABIRD_STDIO_H <cstdio>
#	define RABIRD_STDLIB_H <cstdlib>
#	define RABIRD_STRING_H <cstring>
#	define RABIRD_TIME_H <ctime>
#	define RABIRD_WCHAR_H <cwchar>
#	define RABIRD_WCTYPE_H <cwctype>
#else
#	define RABIRD_ASSERT_H <assert.h>
#	define RABIRD_COMPLEX_H <complex.h>
#	define RABIRD_CTYPE_H <ctype.h>
#	define RABIRD_ERRNO_H <errno.h>
#	define RABIRD_FENV_H <fenv.h>
#	define RABIRD_FLOAT_H <float.h>
#	define RABIRD_INTTYPES_H <inttypes.h>
#	define RABIRD_ISO646_H <iso646.h>
#	define RABIRD_LIMITS_H <limits.h>
#	define RABIRD_LOCALE_H <locale.h>
#	define RABIRD_MATH_H <math.h>
#	define RABIRD_SETJMP_H <setjmp.h>
#	define RABIRD_SIGNAL_H <signal.h>
#	define RABIRD_STDARG_H <stdarg.h>
#	define RABIRD_STDBOOL_H <stdbool.h>
#	define RABIRD_STDDEF_H <stddef.h>
#	define RABIRD_STDIO_H <stdio.h>
#	define RABIRD_STDLIB_H <stdlib.h>
#	define RABIRD_STRING_H <string.h>
#	define RABIRD_TIME_H <time.h>
#	define RABIRD_WCHAR_H <wchar.h>
#	define RABIRD_WCTYPE_H <wctype.h>
#endif

#ifdef RABIRD_OS_WINDOWS

#	ifdef _MSC_VER
/* disable warnings : this function or variable may be unsafe. Consider using xxx instead */
#		pragma warning( disable : 4996 )
#	endif


/* if we are not using TCC */
#	ifndef __TINYC__
#		include <winsock2.h> /* for WSAIoctl */
#	else
/* #		include <rabird_base/mingw/winsock2.h> */ /* for WSAIoctl may be in TCC? */
#	endif

#	include <tchar.h>
#	include <windows.h>

#	include <rabird_base/stdint.h>
#else /* #ifdef RABIRD_OS_WINDOWS */

#	include <rabird_base/stdint.h>

/* fixed the multiple MIN, MAX defined */
#	ifdef RABIRD_OS_LINUX
#		include <sys/param.h>
#	endif /* #	ifdef RABIRD_OS_LINUX */

#endif /* #ifdef RABIRD_OS_WINDOWS */

#ifdef __cplusplus
#	ifndef EXTERN_C
#		define EXTERN_C extern "C"
#	endif
#	ifndef EXTERN_C_BLOCK_BEGIN
#		define EXTERN_C_BLOCK_BEGIN extern "C" {
#	endif
#	ifndef EXTERN_C_BLOCK_END
#		define EXTERN_C_BLOCK_END }
#	endif
#else
#	ifndef EXTERN_C
#		define EXTERN_C extern
#	endif
#	ifndef EXTERN_C_BLOCK_BEGIN
#		define EXTERN_C_BLOCK_BEGIN
#	endif
#	ifndef EXTERN_C_BLOCK_END
#		define EXTERN_C_BLOCK_END
#	endif
#endif  /* __cplusplus */

#if defined(RABIRD_DLL_EXPORT) || defined(BUILD_DLL)
#	define RABIRD_EXPORT __declspec(dllexport)
#elif defined(RABIRD_DLL_IMPORT)
#	define RABIRD_EXPORT __declspec(dllimport)
#else
#	define RABIRD_EXPORT
#endif

/* #define RABIRD_CDECL __cdecl */
#define RABIRD_API_PARAMETER_NULL
#define RABIRD_COMMON_API( export_flags, invoke_method, result, name, parameters ) export_flags result invoke_method name parameters
#define RABIRD_API( result, name, parameters ) RABIRD_COMMON_API( RABIRD_API_PARAMETER_NULL, RABIRD_API_PARAMETER_NULL, name, parameters )
#define RABIRD_EXPORT_API( result, name, parameters) RABIRD_COMMON_API( RABIRD_EXPORT, RABIRD_API_PARAMETER_NULL, name, parameters )

#ifndef INLINE
#	if defined( _MSC_VER )
#		define INLINE __inline
#	elif defined( __GNUC__ )
#		define INLINE inline
#	elif defined( __BORLANDC__ )
#		define INLINE inline
#	elif defined( __TINYC__ )
#		define INLINE inline
#	else
#		define INLINE
#	endif
#endif /* INLINE */

/* portable thread variant declaration */

#if defined( _MSC_VER )
#	define RABIRD_DECLARE_THREAD_VARIANT( type, name ) __thread type name
#elif defined( __GNUC__ )
#	define RABIRD_DECLARE_THREAD_VARIANT( type, name ) __declspec(thread) type name
#elif defined( __BORLANDC__ )
#	define RABIRD_DECLARE_THREAD_VARIANT( type, name ) type __thread name
#elif defined( __TINYC__ )
#	define RABIRD_DECLARE_THREAD_VARIANT( type, name ) { rabird_this_compiler_do_not_support_thread_variant error; }
#else
#	define RABIRD_DECLARE_THREAD_VARIANT( type, name ) { rabird_this_compiler_do_not_support_thread_variant error; }
#endif

/* additional type definitions */
typedef uint64_t rabird_size_t;
typedef int64_t rabird_ssize_t;
typedef int64_t	 rabird_offset_t;

#ifndef __byte_t_DEFINED
#define __byte_t_DEFINED
typedef uint8_t			byte_t;
#endif

#ifndef __word_t_DEFINED
#define __word_t_DEFINED
typedef uint16_t			word_t;
#endif

#ifndef __dword_t_DEFINED
#define __dword_t_DEFINED
typedef uint32_t			dword_t;
#endif

#ifndef __char_t_DEFINED
#define __char_t_DEFINED
typedef char			char_t;
#endif

#ifndef __uchar_t_DEFINED
#define __uchar_t_DEFINED
typedef unsigned char	uchar_t;
#endif

#ifndef __short_t_DEFINED
#define __short_t_DEFINED
typedef short 			short_t;
#endif

#ifndef __ushort_t_DEFINED
#define __ushort_t_DEFINED
typedef unsigned short	ushort_t;
#endif

#ifndef __int_t_DEFINED
#define __int_t_DEFINED
typedef int 			int_t;
#endif

#ifndef __uint_t_DEFINED
#define __uint_t_DEFINED
typedef unsigned int 	uint_t;
#endif

#ifndef __long_t_DEFINED
#define __long_t_DEFINED
typedef long 			long_t;
#endif

#ifndef __ulong_t_DEFINED
#define __ulong_t_DEFINED
typedef unsigned long 	ulong_t;
#endif

#ifndef __bool_t_DEFINED
#define __bool_t_DEFINED
typedef int8_t 			bool_t;
#endif

#ifndef __fast_bool_t_DEFINED
#define __fast_bool_t_DEFINED
typedef int 			fast_bool_t;
#endif

#if defined(RABIRD_OS_LINUX) && (!defined( __KERNEL__ ))
/* it seems that if we are not in the KERNEL mode, linux will not define
 * these types, but they will use in many headers, so we must deifne them here
 */
#	ifndef __s8_DEFINED
#	define __s8_DEFINED
typedef int8_t s8;
#	endif

#	ifndef __s16_DEFINED
#	define __s16_DEFINED
typedef int16_t s16;
#	endif

#	ifndef __s32_DEFINED
#	define __s32_DEFINED
typedef int32_t s32 ;
#	endif

#	ifndef __u8_DEFINED
#	define __u8_DEFINED
typedef uint8_t u8;
#	endif

#	ifndef __u16_DEFINED
#	define __u16_DEFINED
typedef uint16_t u16;
#	endif

#	ifndef __u32_DEFINED
#	define __u32_DEFINED
typedef uint32_t u32 ;
#	endif
#endif

#ifndef FALSE
#	define FALSE 0
#endif

#ifndef TRUE
#	define TRUE (!(FALSE))
#endif

#ifndef BOOL_VALUE
#	define BOOL_VALUE( value ) ( (value) ? TRUE : FALSE )
#endif

#ifndef NULL
#	if defined(__cplusplus)
#		define NULL 0
#	else
#		define NULL ((void *)0)
#	endif
#endif

#endif /* #ifndef __BASE_TYPES_H_INCLUDED_49F11408_002E_0018_67BD_4E8741B86C71 */
