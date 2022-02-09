#ifndef __ZBINBIN_ASYNCLOGGING_H_
#define __ZBINBIN_ASYNCLOGGING_H_
#include "zbinbin/utility/noncopyable.h"
#include <string>
#include <memory>
#include <sstream>
#include <vector>

namespace zbinbin 
{


class AsyncLogger : noncopyable
                  , std::enable_shared_from_this<AsyncLogger>

{

private:


};

}   // namespace zbinbin


#endif  // __ZBINBIN_ASYNCLOGGING_H_
