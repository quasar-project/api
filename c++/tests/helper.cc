#include <helper.h>

#include <fstream>

TestData::TestData(char const* dir)
  : root_(dir) {}

std::filesystem::path const& TestData::root() const { return this->root_; }

std::filesystem::path TestData::path_to(std::string_view const filename) const {
  return this->root() / filename;
}

nlohmann::json TestData::json(std::string_view const filename) const {
  auto ifs = std::ifstream(this->path_to(filename).string(), std::ios::binary);
  return nlohmann::json::parse(ifs);
}

std::vector<std::byte> TestData::binary_data(std::string_view const filename) const {
  auto ifs = std::ifstream(this->path_to(filename).string(), std::ios::binary | std::ios::ate);
  auto const size = ifs.tellg();
  ifs.seekg(0, std::ios::beg);
  auto data = std::vector<std::byte>(size);
  ifs.read(reinterpret_cast<char*>(data.data()), size);
  return data;
}
