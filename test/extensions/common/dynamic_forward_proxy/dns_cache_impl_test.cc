#include "extensions/common/dynamic_forward_proxy/dns_cache_impl.h"

#include "test/mocks/network/mocks.h"
#include "test/mocks/thread_local/mocks.h"

using testing::InSequence;
using testing::SaveArg;

// fixfix test inline resolve.

namespace Envoy {
namespace Extensions {
namespace Common {
namespace DynamicForwardProxy {
namespace {

std::list<Network::Address::InstanceConstSharedPtr>
makeAddressList(const std::list<std::string> address_list) {
  std::list<Network::Address::InstanceConstSharedPtr> ret;
  for (const auto& address : address_list) {
    ret.emplace_back(Network::Utility::parseInternetAddress(address));
  }
  return ret;
}

class DnsCacheImplTest : public testing::Test {
public:
  NiceMock<Event::MockDispatcher> dispatcher_;
  Network::MockDnsResolver resolver_;
  NiceMock<ThreadLocal::MockInstance> tls_;
  DnsCacheImpl dns_cache_{dispatcher_, resolver_, tls_};
};

class MockLoadDnsCacheCallbacks : public DnsCache::LoadDnsCacheCallbacks {
public:
  MOCK_METHOD0(onComplete, void());
};

// fixfix
TEST_F(DnsCacheImplTest, ResolveSuccess) {
  InSequence s;

  MockLoadDnsCacheCallbacks callbacks;
  Network::DnsResolver::ResolveCb resolve_cb;
  EXPECT_CALL(resolver_, resolve("foo.com", _, _))
      .WillOnce(DoAll(SaveArg<2>(&resolve_cb), Return(&resolver_.active_query_)));
  DnsCache::LoadDnsCacheHandlePtr handle = dns_cache_.loadDnsCache("foo.com", callbacks);
  EXPECT_NE(handle, nullptr);

  EXPECT_CALL(callbacks, onComplete());
  resolve_cb(makeAddressList({"10.0.0.1"}));
}

// fixfix
TEST_F(DnsCacheImplTest, ResolveFailure) {
  InSequence s;

  MockLoadDnsCacheCallbacks callbacks;
  Network::DnsResolver::ResolveCb resolve_cb;
  EXPECT_CALL(resolver_, resolve("foo.com", _, _))
      .WillOnce(DoAll(SaveArg<2>(&resolve_cb), Return(&resolver_.active_query_)));
  DnsCache::LoadDnsCacheHandlePtr handle = dns_cache_.loadDnsCache("foo.com", callbacks);
  EXPECT_NE(handle, nullptr);

  EXPECT_CALL(callbacks, onComplete());
  resolve_cb(makeAddressList({}));
}

// fixfix
TEST_F(DnsCacheImplTest, CancelResolve) {
  InSequence s;

  MockLoadDnsCacheCallbacks callbacks;
  Network::DnsResolver::ResolveCb resolve_cb;
  EXPECT_CALL(resolver_, resolve("foo.com", _, _))
      .WillOnce(DoAll(SaveArg<2>(&resolve_cb), Return(&resolver_.active_query_)));
  DnsCache::LoadDnsCacheHandlePtr handle = dns_cache_.loadDnsCache("foo.com", callbacks);
  EXPECT_NE(handle, nullptr);

  handle.reset();
  resolve_cb(makeAddressList({"10.0.0.1"}));
}

// fixfix
TEST_F(DnsCacheImplTest, MultipleResolveSameHost) {
  InSequence s;

  MockLoadDnsCacheCallbacks callbacks1;
  Network::DnsResolver::ResolveCb resolve_cb;
  EXPECT_CALL(resolver_, resolve("foo.com", _, _))
      .WillOnce(DoAll(SaveArg<2>(&resolve_cb), Return(&resolver_.active_query_)));
  DnsCache::LoadDnsCacheHandlePtr handle1 = dns_cache_.loadDnsCache("foo.com", callbacks1);
  EXPECT_NE(handle1, nullptr);

  MockLoadDnsCacheCallbacks callbacks2;
  DnsCache::LoadDnsCacheHandlePtr handle2 = dns_cache_.loadDnsCache("foo.com", callbacks2);
  EXPECT_NE(handle2, nullptr);

  EXPECT_CALL(callbacks2, onComplete());
  EXPECT_CALL(callbacks1, onComplete());
  resolve_cb(makeAddressList({"10.0.0.1"}));
}

// fixfix
TEST_F(DnsCacheImplTest, MultipleResolveDifferentHost) {
  InSequence s;

  MockLoadDnsCacheCallbacks callbacks1;
  Network::DnsResolver::ResolveCb resolve_cb1;
  EXPECT_CALL(resolver_, resolve("foo.com", _, _))
      .WillOnce(DoAll(SaveArg<2>(&resolve_cb1), Return(&resolver_.active_query_)));
  DnsCache::LoadDnsCacheHandlePtr handle1 = dns_cache_.loadDnsCache("foo.com", callbacks1);
  EXPECT_NE(handle1, nullptr);

  MockLoadDnsCacheCallbacks callbacks2;
  Network::DnsResolver::ResolveCb resolve_cb2;
  EXPECT_CALL(resolver_, resolve("bar.com", _, _))
      .WillOnce(DoAll(SaveArg<2>(&resolve_cb2), Return(&resolver_.active_query_)));
  DnsCache::LoadDnsCacheHandlePtr handle2 = dns_cache_.loadDnsCache("bar.com", callbacks2);
  EXPECT_NE(handle2, nullptr);

  EXPECT_CALL(callbacks2, onComplete());
  resolve_cb2(makeAddressList({"10.0.0.1"}));

  EXPECT_CALL(callbacks1, onComplete());
  resolve_cb1(makeAddressList({"10.0.0.2"}));
}

} // namespace
} // namespace DynamicForwardProxy
} // namespace Common
} // namespace Extensions
} // namespace Envoy
