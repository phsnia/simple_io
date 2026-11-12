/**
 * @file: type.hpp
 */
#ifndef TYPE_HPP
#define TYPE_HPP

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

typedef uint8_t     u8;
typedef uint16_t    u16;
typedef uint32_t    u32;
typedef uint64_t    u64;

typedef int8_t      i8;
typedef int16_t     i16;
typedef int32_t     i32;
typedef int64_t     i64;

typedef size_t      usz;
typedef ptrdiff_t   isz;

typedef float   f32;
typedef double  f64;

typedef u8      Bool;
#define TRUE 1
#define FALSE 0

#endif // TYPE_HPP
