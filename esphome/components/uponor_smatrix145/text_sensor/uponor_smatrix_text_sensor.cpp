#include "uponor_smatrix_text_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace uponor_smatrix145 {

static const char *const TAG = "uponor_smatrix145.text_sensor";

void UponorSmatrixTextSensor::dump_config() {
  ESP_LOGCONFIG(TAG, "Uponor Smatrix Text Sensor\n"
                     "  Device address: 0x%04X 0x%04X", this->system_address_, this->address_);
  LOG_TEXT_SENSOR("  ", "Datetime", this->timer_datetime_text_sensor_);
  LOG_TEXT_SENSOR("  ", "Auto calibration", this->timer_calibration_mode_text_sensor_);
  LOG_TEXT_SENSOR("  ", "Heating Mode", this->timer_heating_mode_text_sensor_);
  LOG_TEXT_SENSOR("  ", "Vacation Mode", this->timer_vacation_mode_text_sensor_);
}

void UponorSmatrixTextSensor::on_device_data(const UponorSmatrixData *data, size_t data_len) {
  for (size_t i = 0; i < data_len; i++) {
    switch (data[i].id) {
      // I143
      case UPONOR_ID_DATETIME1:	   
//  uint16_t time1 = (year & 0x7F) << 7 | (month & 0x0F) << 3 | (day_of_week & 0x07);
//  uint16_t time2 = (day_of_month & 0x1F) << 11 | (hour & 0x1F) << 6 | (minute & 0x3F);
//  uint16_t time3 = second;        
//[2024-08-29 09:20:58][I][uponor_smatrix145.sensor:058]: Timer time 1: 0x0C43
//[2024-08-29 09:20:58][I][uponor_smatrix145.sensor:067]: Timer time 2: 0xEA53
//[2024-08-29 09:20:58][I][uponor_smatrix145.sensor:072]: Timer time 3: 0x0012
        this->time_part1_ = data[i].value;
        this->time_year_ = ((data[i].value >> 7) & 0x007F) + 0x07D0;  //2000 -> 0x07D0
        this->time_month_ = (data[i].value >> 3) & 0x000F;
        break;
      case UPONOR_ID_DATETIME2:
        this->time_part2_ = data[i].value;
        this->time_day_ = (data[i].value >> 11) & 0x001F;		 
        this->time_hour_ = (data[i].value >> 6) & 0x001F;
        this->time_minute_ = data[i].value & 0x003F;
        break;
      case UPONOR_ID_DATETIME3:       
        this->time_part3_ = data[i].value;		
        this->time_second_ = data[i].value & 0x003F;		
        if (this->timer_datetime_text_sensor_ != nullptr)
		  if (this->time_second_ % 10 == 0) {
			  this->timer_datetime_text_sensor_->publish_state(str_sprintf("%04d-%02d-%02d %02d:%02d:%02d", 
					this->time_year_, this->time_month_, this->time_day_, this->time_hour_, this->time_minute_, this->time_second_));
		  }
		break;        
      case UPONOR_ID_TIMER_HEATING_MODE:
        if (this->timer_calibration_mode_text_sensor_ != nullptr)
        {
          this->timer_calibration_mode_text_sensor_->publish_state((data[i].value & 0x0001) == 1 ? "AUTO" : "OFF");		  
        }
        if (this->timer_heating_mode_text_sensor_ != nullptr)
        {
          this->timer_heating_mode_text_sensor_->publish_state(((data[i].value & 0x0008) == 0x0008) ? "OFF" : "ON");		  
        }
        if (this->timer_vacation_mode_text_sensor_ != nullptr)
          this->timer_vacation_mode_text_sensor_->publish_state(((data[i].value & 0x0400) == 0x0400) ? "ON" : "OFF");
        break;
    }
  }
}

}  // namespace uponor_smatrix145
}  // namespace esphome
