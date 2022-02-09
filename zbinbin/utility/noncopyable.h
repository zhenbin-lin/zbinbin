#ifndef __ZBINBIN_NONCOPYABLE_H_
#define __ZBINBIN_NONCOPYABLE_H_

namespace zbinbin
{

class noncopyable
{
 public:
  noncopyable(const noncopyable&) = delete;
  void operator=(const noncopyable&) = delete;

 protected:
  noncopyable() = default;
  ~noncopyable() = default;
};

}  // namespace zbinbin

#endif  // __ZBINBIN_NONCOPYABLE_H_
