#pragma once

#include <functional>

#include "envoy/common/pure.h"

#include "absl/strings/string_view.h"

namespace Envoy {
namespace Extensions {
namespace Common {
namespace DynamicForwardProxy {

/**
 * fixfix
 */
class DnsCache {
public:
  /**
   * fixfix
   */
  class LoadDnsCacheCallbacks {
  public:
    virtual ~LoadDnsCacheCallbacks() = default;

    /**
     * fixfix
     */
    virtual void onComplete() PURE;
  };

  /**
   * fixfix
   */
  class LoadDnsCacheHandle {
  public:
    virtual ~LoadDnsCacheHandle() = default;
  };

  using LoadDnsCacheHandlePtr = std::unique_ptr<LoadDnsCacheHandle>;

  /**
   * fixfix
   */
  class AddUpdateCallbacksHandle {
  public:
    virtual ~AddUpdateCallbacksHandle() = default;
  };

  using AddUpdateCallbacksHandlePtr = std::unique_ptr<AddUpdateCallbacksHandle>;

  virtual ~DnsCache() = default;

  /**
   * fixfix
   */
  virtual LoadDnsCacheHandlePtr loadDnsCache(absl::string_view host,
                                             LoadDnsCacheCallbacks& callbacks) PURE;

  /**
   * fixfix
   */
  using UpdateCallbacks = std::function<void()>;
  virtual AddUpdateCallbacksHandlePtr addUpdateCallbacks(const UpdateCallbacks& callbacks) PURE;

  /**
   * fixfix
   */
  // fixfixvirtual const std::list<Upstream::HostConstSharedPtr>& hosts() PURE;
};

using DnsCacheSharedPtr = std::shared_ptr<DnsCache>;

} // namespace DynamicForwardProxy
} // namespace Common
} // namespace Extensions
} // namespace Envoy
