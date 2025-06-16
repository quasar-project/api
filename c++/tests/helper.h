#pragma once

#include <cstddef>
#include <vector>
#include <string_view>
#include <nlohmann/json.hpp>
#ifndef Q_MOC_RUN
#  include <filesystem>
#endif

class TestData final {
 public:
  explicit TestData(char const* dir = QUASAR_API_TEST_DATA_DIR);

  [[nodiscard]] std::filesystem::path const& root() const;
  [[nodiscard]] std::filesystem::path path_to(std::string_view filename) const;
  [[nodiscard]] nlohmann::json json(std::string_view filename) const;
  [[nodiscard]] std::vector<std::byte> binary_data(std::string_view filename) const;

 private:
  std::filesystem::path root_;
};
