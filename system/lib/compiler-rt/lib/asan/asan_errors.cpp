//===-- asan_errors.cpp -----------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file is a part of AddressSanitizer, an address sanity checker.
//
// ASan implementation for error structures.
//===----------------------------------------------------------------------===//

#include "asan_errors.h"
#include "asan_descriptions.h"
#include "asan_mapping.h"
#include "asan_report.h"
#include "asan_stack.h"
#include "sanitizer_common/sanitizer_stackdepot.h"

namespace __asan {

void ErrorGeneric::Print() {
}

void ErrorDeadlySignal::Print() {
}

void ErrorDoubleFree::Print() {

}

void ErrorNewDeleteTypeMismatch::Print() {
  
}

void ErrorFreeNotMalloced::Print() {
 
}

void ErrorAllocTypeMismatch::Print() {
  
}

void ErrorMallocUsableSizeNotOwned::Print() {
  
}

void ErrorSanitizerGetAllocatedSizeNotOwned::Print() {
  
}

void ErrorCallocOverflow::Print() {
  
}

void ErrorReallocArrayOverflow::Print() {
 
}

void ErrorPvallocOverflow::Print() {
  
}

void ErrorInvalidAllocationAlignment::Print() {
  
}

void ErrorInvalidAlignedAllocAlignment::Print() {
  
}

void ErrorInvalidPosixMemalignAlignment::Print() {
  
}

void ErrorAllocationSizeTooBig::Print() {
  
}

void ErrorRssLimitExceeded::Print() {
  
}

void ErrorOutOfMemory::Print() {
  
}

void ErrorStringFunctionMemoryRangesOverlap::Print() {
  
}

void ErrorStringFunctionSizeOverflow::Print() {
  
}

void ErrorBadParamsToAnnotateContiguousContainer::Print() {
  
}

void ErrorBadParamsToAnnotateDoubleEndedContiguousContainer::Print() {
  
}

void ErrorODRViolation::Print() {
  
}

void ErrorInvalidPointerPair::Print() {
  
}

ErrorGeneric::ErrorGeneric(u32 tid, uptr pc_, uptr bp_, uptr sp_, uptr addr,
                           bool is_write_, uptr access_size_)
    : ErrorBase(tid),
      addr_description(addr, access_size_, /*shouldLockThreadRegistry=*/false),
      pc(pc_),
      bp(bp_),
      sp(sp_),
      access_size(access_size_),
      is_write(is_write_),
      shadow_val(0) {
  
}

}  // namespace __asan
