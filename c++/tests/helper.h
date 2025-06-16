#pragma once

#include <string_view>
#include <nlohmann/json.hpp>
#ifndef Q_MOC_RUN
#  include <filesystem>
#endif

class TestData final {
 public:
  explicit TestData(char const* dir = QUASAR_API_TEST_DATA_DIR);

  [[nodiscard]] auto root() const -> std::filesystem::path const&;
  [[nodiscard]] auto path_to(std::string_view filename) const -> std::filesystem::path;
  [[nodiscard]] auto json(std::string_view filename) const -> nlohmann::json;

 private:
  std::filesystem::path root_;
};
