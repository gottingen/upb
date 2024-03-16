#include <string>

#include <google/protobuf/compiler/plugin.h>
#include <google/protobuf/compiler/command_line_interface.h>
#include <hs/generator.h>

#define PACKAGE_STRING "protoc-gen-hs 0.1.0"

int main(int argc, char* argv[]) {
  google::protobuf::compiler::hs::CGenerator hs_generator;

  std::string invocation_name = argv[0];
  std::string invocation_basename = invocation_name.substr(invocation_name.find_last_of("/") + 1);
  const std::string standalone_name = "protoc-c";

  if (invocation_basename == standalone_name) {
    google::protobuf::compiler::CommandLineInterface cli;
    cli.RegisterGenerator("--hs_out", &hs_generator, "Generate hs files.");
    cli.SetVersionInfo(PACKAGE_STRING);
    return cli.Run(argc, argv);
  }

  return google::protobuf::compiler::PluginMain(argc, argv, &hs_generator);
}
