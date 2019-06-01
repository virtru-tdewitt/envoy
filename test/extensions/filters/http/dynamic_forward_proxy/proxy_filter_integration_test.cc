// fixfix#include "common/http/message_impl.h"

//#include "extensions/filters/http/well_known_names.h"

#include "test/integration/http_integration.h"

//#include "test/mocks/http/mocks.h"
//#include "test/test_common/utility.h"

//#include "absl/strings/match.h"
//#include "gtest/gtest.h"

// using Envoy::Http::HeaderValueOf;

// fixfix h1 and h2 tests.

namespace Envoy {
namespace {

class ProxyFilterIntegrationTest : public testing::TestWithParam<Network::Address::IpVersion>,
                                   public HttpIntegrationTest {
public:
  ProxyFilterIntegrationTest() : HttpIntegrationTest(Http::CodecClient::Type::HTTP1, GetParam()) {}

  void SetUp() override {
    setUpstreamProtocol(FakeHttpConnection::Type::HTTP1);

    const std::string filter =
        R"EOF(
name: envoy.filters.http.dynamic_forward_proxy
config: {}
            )EOF";
    config_helper_.addFilter(filter);

    HttpIntegrationTest::initialize();
  }
};

INSTANTIATE_TEST_SUITE_P(IpVersions, ProxyFilterIntegrationTest,
                         testing::ValuesIn(TestEnvironment::getIpVersionsForTest()),
                         TestUtility::ipTestParamsToString);

// fixfix
TEST_P(ProxyFilterIntegrationTest, RequestWithBody) {
  codec_client_ = makeHttpConnection(lookupPort("http"));
  Http::TestHeaderMapImpl request_headers{{":method", "POST"},
                                          {":path", "/test/long/url"},
                                          {":scheme", "http"},
                                          {":authority", "localhost"}};
  auto response =
      sendRequestAndWaitForResponse(request_headers, 1024, default_response_headers_, 1024);
  checkSimpleRequestSuccess(1024, 1024, response.get());
}

} // namespace
} // namespace Envoy
