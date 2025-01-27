#pragma once

#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/uponor_smatrix145/uponor_smatrix.h"
#include "esphome/core/component.h"

namespace esphome {
namespace uponor_smatrix145 {

class UponorSmatrixTextSensor : public text_sensor::TextSensor, public Component, public UponorSmatrixDevice { 
  SUB_TEXT_SENSOR(timer_datetime)
  SUB_TEXT_SENSOR(timer_calibration_mode)
  SUB_TEXT_SENSOR(timer_heating_mode)
  SUB_TEXT_SENSOR(timer_vacation_mode)  

 public:
  void dump_config() override;

 protected:
  void on_device_data(const UponorSmatrixData *data, size_t data_len) override;
  
  uint16_t time_part1_;
  uint16_t time_part2_;
  uint16_t time_part3_;
  uint16_t time_year_{0};
  uint16_t time_month_{0};
  uint16_t time_day_{0};
  uint16_t time_hour_{0};
  uint16_t time_minute_{0};
  uint16_t time_second_{0};
  
};

}  // namespace uponor_smatrix145
}  // namespace esphome
