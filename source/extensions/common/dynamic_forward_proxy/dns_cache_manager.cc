#include "extensions/common/dynamic_forward_proxy/dns_cache_manager.h"

namespace Envoy {
namespace Extensions {
namespace Common {
namespace DynamicForwardProxy {

SINGLETON_MANAGER_REGISTRATION(dns_cache_manager);

DnsCacheSharedPtr
getCache(const envoy::config::common::dynamic_forward_proxy::v2alpha::DnsCacheConfig& /*config*/,
         Singleton::Manager& /*singleton_manager*/) {
  ASSERT(false); // fixfix
}

} // namespace DynamicForwardProxy
} // namespace Common
} // namespace Extensions
} // namespace Envoy
