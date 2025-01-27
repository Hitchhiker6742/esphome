#pragma once

#include "esphome/components/sensor/sensor.h"
#include "esphome/components/climate/climate.h"
#include "esphome/components/uponor_smatrix145/uponor_smatrix.h"
#include "esphome/core/component.h"

namespace esphome {
namespace uponor_smatrix145 {

class UponorSmatrixSensor : public sensor::Sensor, public Component, public UponorSmatrixDevice {
  SUB_SENSOR(temperature)
  SUB_SENSOR(external_temperature)
  SUB_SENSOR(humidity)
  SUB_SENSOR(target_temperature)
  SUB_SENSOR(target_temperature_brutto)

  SUB_SENSOR(target_temperature_low)
  SUB_SENSOR(target_temperature_high)
  SUB_SENSOR(unknown_0x0C)
  SUB_SENSOR(unknown_0x35)
  SUB_SENSOR(demand_0x3D)
  SUB_SENSOR(mode1_0x3E)
  SUB_SENSOR(mode2_0x3F)
  SUB_SENSOR(eco_setback)  
  SUB_SENSOR(climate_preset_mode)
  
  SUB_SENSOR(timer_datetime)
  SUB_SENSOR(timer_autocalibration_mode)
  SUB_SENSOR(timer_eco_mode)
  SUB_SENSOR(timer_vacation_mode)
  SUB_SENSOR(timer_vacation_target_temperature)
  SUB_SENSOR(timer_eco_setback)
  SUB_SENSOR(timer_unknown_0x29)
  //SUB_SENSOR(timer_year)
  //SUB_SENSOR(timer_month)
  //SUB_SENSOR(timer_day)
  //SUB_SENSOR(timer_hour)
  //SUB_SENSOR(timer_minute)
  //SUB_SENSOR(timer_second)
  //SUB_SENSOR(timer_timepart1)
  //SUB_SENSOR(timer_timepart2)

 public:
  void dump_config() override;

 protected:
  void on_device_data(const UponorSmatrixData *data, size_t data_len) override;
  
  float target_temperature_;
  float eco_setback_;
  uint16_t climate_preset_mode_;
  //uint16_t time_part1_;
  //uint16_t time_part2_;
  //uint16_t time_part3_;
  //uint16_t time_year_;
  //uint16_t time_month_;
  //uint16_t time_day_;
  //uint16_t time_hour_;
  //uint16_t time_minute_;
  //uint16_t time_second_;
  
};

}  // namespace uponor_smatrix145
}  // namespace esphome
