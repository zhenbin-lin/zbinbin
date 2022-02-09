#ifndef __ZBINBIN_COPYABLE_H_
#define __ZBINBIN_COPYABLE_H_

namespace zbinbin
{

/// A tag class emphasises the objects are copyable.
/// The empty base class optimization applies.
/// Any derived class of copyable should be a value type.
class copyable
{
 protected:
  copyable() = default;
  ~copyable() = default;
};

}  // namespace zbinbin

#endif  // __ZBINBIN_COPYABLE_H_
