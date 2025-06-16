#include <catch2/catch_all.hpp>

#include <quasar/api/metadata.h>

TEST_CASE("Image metadata", "[metadata]") {
  SECTION("JSON") {
    auto constexpr basic_metadata_json = R"({
  "nav": {
    "coordinates": [0.0000000000, 0.0000000000],
    "velocity": 0.0000,
    "altitude": 0.0000,
    "azimuth": 0.0000
  },
  "resolution": {
    "dx": 0.000000,
    "dy": 0.000000
  },
  "dimensions": {
    "lx": 0.000000,
    "ly": 0.000000,
    "x0": 0.000000,
    "y0": 0.000000
  },
  "drift_angle": 0.000000,
  "div": 0.000000,
  "mode": 0,
  "fic": 0.000000,
  "time_offset": 0.000000,
  "time_duration": 0.000000,
  "image_type": "Undefined"
})";
    SECTION("Serialize") {
      SECTION("Basic") {
        auto const metadata = quasar::ImageMetadata();

        REQUIRE_THAT(metadata.to_json(), Catch::Matchers::ContainsSubstring(basic_metadata_json));
      } // Basic
    } // Serialize

    SECTION("Deserialize") {
      SECTION("Basic") {
        auto const metadata = quasar::ImageMetadata::from_json(basic_metadata_json);

        REQUIRE(metadata.kind() == quasar::ImageKind::Undefined);
        REQUIRE_THAT(metadata.to_json(), Catch::Matchers::ContainsSubstring(basic_metadata_json));
      } // Basic
    } // Deserialize
  } // JSON
} // Image metadata