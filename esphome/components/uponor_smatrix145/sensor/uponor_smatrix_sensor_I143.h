#pragma once

#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uponor_smatrix145/uponor_smatrix.h"
#include "esphome/core/component.h"

namespace esphome {
namespace uponor_smatrix145 {

class UponorSmatrixSensorI143 : public sensor::Sensor, public Component, public UponorSmatrixDevice {
  SUB_SENSOR(temperature)
  SUB_SENSOR(external_temperature)
  SUB_SENSOR(humidity)
  SUB_SENSOR(target_temperature)

 public:
  void dump_config() override;

 protected:
  void on_device_data(const UponorSmatrixData *data, size_t data_len) override;
};

}  // namespace uponor_smatrix145
}  // namespace esphome
