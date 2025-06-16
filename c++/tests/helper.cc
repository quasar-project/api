#include <helper.h>

#include <fstream>

TestData::TestData(char const* dir)
  : root_(dir) {}

auto TestData::root() const -> std::filesystem::path const& { return this->root_; }

auto TestData::path_to(std::string_view const filename) const -> std::filesystem::path {
  return this->root() / filename;
}

auto TestData::json(std::string_view const filename) const -> nlohmann::json {
  auto ifs = std::ifstream(this->path_to(filename).string(), std::ios::binary);
  return nlohmann::json::parse(ifs);
}
