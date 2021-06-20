/**
 * @author Hans Liu (hans@dkmt.io)
 * @since 2021-06-20
 */

#pragma once

#ifndef DK_DECLARE_UNCOPYABLE
#define DK_DECLARE_UNCOPYABLE(ClassName)                                       \
  ClassName(const ClassName&) = delete;                                        \
  ClassName(ClassName&&) = delete;                                             \
  ClassName& operator=(const ClassName&) = delete;                             \
  ClassName& operator=(ClassName&&) = delete
#endif
