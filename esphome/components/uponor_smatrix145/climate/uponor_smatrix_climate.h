#pragma once

#include "esphome/components/climate/climate.h"
#include "esphome/components/uponor_smatrix145/uponor_smatrix.h"
#include "esphome/core/component.h"

namespace esphome {
namespace uponor_smatrix145 {

static const uint8_t SEND_RETRY_MAX = 5;

class UponorSmatrixClimate : public climate::Climate, public Component, public UponorSmatrixDevice {
 public:
  void dump_config() override;
  void loop() override;

 protected:
  climate::ClimateTraits traits() override;
  void control(const climate::ClimateCall &call) override;
  void on_device_data(const UponorSmatrixData *data, size_t data_len) override;

  uint32_t last_data_;
  float min_temperature_{5.0f};
  float max_temperature_{35.0f};  
  uint16_t eco_setback_value_raw_{0x0000};
  uint16_t target_temperature_raw_;
  uint16_t lastset_target_temperature_raw_;
  float lastset_target_temperature_{0.0f};  
  uint8_t send_retry_count_;  

private:
  void send_data(float temperature, bool retry);
  optional<climate::ClimatePreset> last_preset_;
};

}  // namespace uponor_smatrix145
}  // namespace esphome
