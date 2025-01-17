#include <userver/utest/using_namespace_userver.hpp>

/// [Hello service sample - component]
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/storages/secdist/component.hpp>
#include <userver/storages/secdist/provider_component.hpp>
#include <userver/utils/daemon_run.hpp>

namespace samples::hello {

class Hello final : public server::handlers::HttpHandlerBase {
 public:
  // `kName` is used as the component name in static config
  static constexpr std::string_view kName = "handler-hello-sample";

  // Component is valid after construction and is able to accept requests
  using HttpHandlerBase::HttpHandlerBase;

  std::string HandleRequestThrow(
      const server::http::HttpRequest& request,
      server::request::RequestContext&) const override {
    request.GetHttpResponse().SetContentType(http::content_type::kTextPlain);
    return "Hello world!\n";
  }
};

}  // namespace samples::hello
/// [Hello service sample - component]

/// [Hello service sample - main]
int main(int argc, char* argv[]) {
  const auto component_list = components::MinimalServerComponentList()
                                  .Append<samples::hello::Hello>()
                                  .Append<components::DefaultSecdistProvider>()
                                  .Append<components::Secdist>();
  return utils::DaemonMain(argc, argv, component_list);
}
/// [Hello service sample - main]
