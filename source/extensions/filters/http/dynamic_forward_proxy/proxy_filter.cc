#include "extensions/filters/http/dynamic_forward_proxy/proxy_filter.h"

#include "extensions/common/dynamic_forward_proxy/dns_cache_manager.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace DynamicForwardProxy {

ProxyFilterConfig::ProxyFilterConfig(
    const envoy::config::filter::http::dynamic_forward_proxy::v2alpha::FilterConfig& proto_config,
    Singleton::Manager& singleton_manager)
    : dns_cache_(Common::DynamicForwardProxy::getCache(proto_config.dns_cache_config(),
                                                       singleton_manager)) {}

Http::FilterHeadersStatus ProxyFilter::decodeHeaders(Http::HeaderMap&, bool) {
  ASSERT(false); // fixfix
}

} // namespace DynamicForwardProxy
} // namespace HttpFilters
} // namespace Extensions
} // namespace Envoy
