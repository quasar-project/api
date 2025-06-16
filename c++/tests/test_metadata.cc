#include <catch2/catch_all.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <quasar/api/metadata.h>
#include <helper.h>

auto data = TestData();

using namespace Catch::Matchers;

TEST_CASE("Image metadata", "[metadata]") {
  SECTION("JSON") {
    SECTION("Serialize") {
      SECTION("Basic") {
        auto const metadata = quasar::ImageMetadata();

        REQUIRE(metadata.to_json() == data.json("empty_metadata.json"));
      }  // Basic

      SECTION("Migrate legacy") {
        auto const metadata = quasar::ImageMetadata::from_json(
          data.json("m1-30-10-2024_11-26-41-meta.json")
        );

        REQUIRE(metadata.to_json() == data.json("migrated_metadata.json"));
      }
    }  // Serialize

    SECTION("Deserialize") {
      SECTION("Basic") {
        auto const metadata = quasar::ImageMetadata::from_json(data.json("empty_metadata.json"));

        REQUIRE(metadata.kind() == quasar::ImageKind::Undefined);
        REQUIRE(metadata.to_json() == data.json("empty_metadata.json"));
      }  // Basic

      SECTION("Legacy") {
        auto const metadata = quasar::ImageMetadata::from_json(
          data.json("m1-30-10-2024_11-26-41-meta.json")
        );

        REQUIRE(metadata.kind() == quasar::ImageKind::Strip);
        REQUIRE_THAT(metadata.latitude(), WithinAbs(54.3916570672569, 0.0001));
        REQUIRE_THAT(metadata.longitude(), WithinAbs(48.76908306785768, 0.0001));
        REQUIRE_THAT(metadata.velocity(), WithinAbs(147.08477783203125 / 3.6, 0.0001));
        REQUIRE_THAT(metadata.altitude(), WithinAbs(290.6500244140625, 0.0001));
        REQUIRE_THAT(metadata.angle(), WithinAbs(0.4095519185066223, 0.0001));
        REQUIRE_THAT(metadata.dx(), WithinAbs(1.0, 0.0001));
        REQUIRE_THAT(metadata.dy(), WithinAbs(1.0, 0.0001));
        REQUIRE_THAT(metadata.width(), WithinAbs(2000.0, 0.0001));
        REQUIRE_THAT(metadata.height(), WithinAbs(3735.0, 0.0001));
        REQUIRE_THAT(metadata.near_edge(), WithinAbs(100.0, 0.0001));
        REQUIRE_THAT(metadata.frame_shift(), WithinAbs(-200.0, 0.0001));
        REQUIRE_THAT(metadata.drift_angle(), WithinAbs(-0.15541914105415344, 0.0001));
        REQUIRE_THAT(metadata.divergence_angle(), WithinAbs(0.3488888740539551, 0.0001));
        REQUIRE(metadata.frequency_interpolation_coefficient() == 1.0f);
        REQUIRE(metadata.sar_mode() == 1);
        REQUIRE(metadata.time_offset() == std::chrono::duration<double>(1.0));
        REQUIRE(metadata.time_duration() == std::chrono::duration<double>(0.5));
        REQUIRE(metadata.library_version() == std::array<std::uint16_t, 3> {1, 6, 0});
        REQUIRE(metadata.timestamp() == std::chrono::system_clock::from_time_t(0));
      }
    }  // Deserialize
  }  // JSON
}  // Image metadata
