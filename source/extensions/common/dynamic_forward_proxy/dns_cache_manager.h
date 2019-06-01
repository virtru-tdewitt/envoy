#pragma once

#include "envoy/config/common/dynamic_forward_proxy/v2alpha/dns_cache.pb.h"
#include "envoy/singleton/manager.h"

#include "extensions/common/dynamic_forward_proxy/dns_cache.h"

namespace Envoy {
namespace Extensions {
namespace Common {
namespace DynamicForwardProxy {

/**
 * fixfix
 */
DnsCacheSharedPtr
getCache(const envoy::config::common::dynamic_forward_proxy::v2alpha::DnsCacheConfig& config,
         Singleton::Manager& singleton_manager);

} // namespace DynamicForwardProxy
} // namespace Common
} // namespace Extensions
} // namespace Envoy
