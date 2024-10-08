// Copyright 2013 The Emscripten Authors.  All rights reserved.
// Emscripten is available under two separate licenses, the MIT license and the
// University of Illinois/NCSA Open Source License.  Both these licenses can be
// found in the LICENSE file.

#include <stdio.h>
#include <string.h>
#include <emscripten.h>
#include <assert.h>
#include <wchar.h>

typedef unsigned int utf32;
typedef unsigned short utf16;

EM_JS_DEPS(deps, "$UTF32ToString,$stringToUTF32");

// This code tests that Unicode std::wstrings can be marshalled between C++ and JS.
int main() {
  // U+2603 is snowman,
  // U+20AC is the Euro sign,
  // U+2007C is a Chinese Han character that looks like three raindrops.
  wchar_t wstr[] = L"abc\u2603\u20AC\U0002007C123 --- abc\u2603\u20AC\U0002007C123";
  size_t wstr_len = wcslen(wstr);

  printf("sizeof(wchar_t): %d.\n", (int)sizeof(wchar_t));

  if (sizeof(wchar_t) == 4) {
    utf32 *memory = malloc(wstr_len*sizeof(utf32));

    EM_ASM({
      var str = UTF32ToString($0);
      out(str);
      var numBytesWritten = stringToUTF32(str, $1, Number($2));
      if (numBytesWritten != 23*4) throw 'stringToUTF32 wrote an invalid length ' + numBytesWritten;
    }, wstr, memory, (wstr_len+1)*sizeof(utf32));

    // Compare memory to confirm that the string is intact after taking a route
    // through JS side.
    const utf32 *srcPtr = (const utf32 *)(wstr);
    for (int i = 0;; ++i) {
      assert(memory[i] == srcPtr[i]);
      if (srcPtr[i] == 0)
        break;
    }

    EM_ASM({
      var str = UTF32ToString($0);
      out(str);
      var numBytesWritten = stringToUTF32(str, $1, Number($2));
      if (numBytesWritten != 5*4) throw 'stringToUTF32 wrote an invalid length ' + numBytesWritten;
    }, wstr, memory, 6*sizeof(utf32));
    assert(memory[5] == 0);

    free(memory);
  } else {
    // sizeof(wchar_t) == 2, and we're building with -fshort-wchar.
    utf16 *memory = malloc((2*wstr_len+1) * sizeof(utf16));

    EM_ASM({
      var str = UTF16ToString($0);
      out(str);
      var numBytesWritten = stringToUTF16(str, $1, $2);
      if (numBytesWritten != 25*2) throw 'stringToUTF16 wrote an invalid length ' + numBytesWritten;
    }, wstr, memory, (2*wstr_len+1)*sizeof(utf16));

    // Compare memory to confirm that the string is intact after taking a route
    // through JS side.
    const utf16 *srcPtr = (const utf16 *)(wstr);
    for (int i = 0;; ++i) {
      assert(memory[i] == srcPtr[i]);
      if (srcPtr[i] == 0)
        break;
    }

    EM_ASM({
      var str = UTF16ToString($0);
      out(str);
      var numBytesWritten = stringToUTF16(str, $1, $2);
      if (numBytesWritten != 5*2) throw 'stringToUTF16 wrote an invalid length ' + numBytesWritten;
    }, wstr, memory, 6*sizeof(utf16));
    assert(memory[5] == 0);

    free(memory);
  }

  printf("OK.\n");
}
