#pragma once

#include "envoy/config/filter/http/dynamic_forward_proxy/v2alpha/dynamic_forward_proxy.pb.h"
#include "envoy/singleton/manager.h"

#include "extensions/common/dynamic_forward_proxy/dns_cache.h"
#include "extensions/filters/http/common/pass_through_filter.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace DynamicForwardProxy {

class ProxyFilterConfig {
public:
  ProxyFilterConfig(
      const envoy::config::filter::http::dynamic_forward_proxy::v2alpha::FilterConfig& proto_config,
      Singleton::Manager& manager);

private:
  const Extensions::Common::DynamicForwardProxy::DnsCacheSharedPtr dns_cache_;
};

using ProxyFilterConfigSharedPtr = std::shared_ptr<ProxyFilterConfig>;

class ProxyFilter : public Http::PassThroughDecoderFilter {
public:
  ProxyFilter(const ProxyFilterConfigSharedPtr& config) : config_(config) {}
  Http::FilterHeadersStatus decodeHeaders(Http::HeaderMap& headers, bool end_stream) override;

private:
  const ProxyFilterConfigSharedPtr config_;
};

} // namespace DynamicForwardProxy
} // namespace HttpFilters
} // namespace Extensions
} // namespace Envoy
