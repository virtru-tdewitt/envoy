licenses(["notice"])  # Apache 2

load(
    "//bazel:envoy_build_system.bzl",
    "envoy_package",
)
load(
    "//test/extensions:extensions_build_system.bzl",
    "envoy_extension_cc_test",
)

envoy_package()

envoy_extension_cc_test(
    name = "proxy_filter_integration_test",
    srcs = ["proxy_filter_integration_test.cc"],
    extension_name = "envoy.filters.http.dynamic_forward_proxy",
    deps = [
        #"//source/common/buffer:buffer_lib",
        #"//source/common/http:header_map_lib",
        "//source/extensions/filters/http/dynamic_forward_proxy:config",
        #"//source/extensions/filters/http/grpc_http1_reverse_bridge:filter_lib",
        "//test/integration:http_integration_lib",
        #"//test/mocks/upstream:upstream_mocks",
        #"//test/test_common:utility_lib",
    ],
)
