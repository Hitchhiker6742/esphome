#include "uponor_smatrix_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace uponor_smatrix145 {

static const char *const TAG = "uponor_smatrix145.sensor";

void UponorSmatrixSensor::dump_config() {
  ESP_LOGCONFIG(TAG, "Uponor Smatrix Sensor\n"
                     "  Device address: 0x%04X 0x%04X", this->system_address_, this->address_);
  LOG_SENSOR("  ", "Temperature", this->temperature_sensor_);
  LOG_SENSOR("  ", "External Temperature", this->external_temperature_sensor_);
  LOG_SENSOR("  ", "Humidity", this->humidity_sensor_);
  LOG_SENSOR("  ", "Target Temperature", this->target_temperature_sensor_);
  LOG_SENSOR("  ", "Target Temperature Brutto", this->target_temperature_brutto_sensor_);
}

void UponorSmatrixSensor::on_device_data(const UponorSmatrixData *data, size_t data_len) {
  for (size_t i = 0; i < data_len; i++) {
    switch (data[i].id) {
      case UPONOR_ID_ROOM_TEMP:
        if (this->temperature_sensor_ != nullptr)
          this->temperature_sensor_->publish_state(raw_to_celsius(data[i].value));
        break;
      case UPONOR_ID_EXTERNAL_TEMP:
        if (this->external_temperature_sensor_ != nullptr)
          this->external_temperature_sensor_->publish_state(raw_to_celsius(data[i].value));
        break;
      case UPONOR_ID_HUMIDITY:
        if (this->humidity_sensor_ != nullptr)
          this->humidity_sensor_->publish_state(data[i].value & 0x00FF);
        break;
      case UPONOR_ID_TARGET_TEMP:
		    this->target_temperature_ = raw_to_celsius(data[i].value);
        if (this->target_temperature_brutto_sensor_ != nullptr) 
        {
		      this->target_temperature_brutto_sensor_->publish_state(this->target_temperature_);
		    }
  		  if (this->target_temperature_sensor_ != nullptr) 
        {
          if (this->climate_preset_mode_ == ECO_PRESET_ON) 
            // During ECO mode, the thermostat automatically substracts the setback value from the setpoint,
            // so we need to add it here first
            this->target_temperature_sensor_->publish_state(this->target_temperature_ -= this->eco_setback_);		    
          else
            this->target_temperature_sensor_->publish_state(this->target_temperature_);
        }
        break;
      case UPONOR_ID_TARGET_TEMP_MIN:
        if (this->target_temperature_low_sensor_ != nullptr)
          this->target_temperature_low_sensor_->publish_state(raw_to_celsius(data[i].value));
        break;
      case UPONOR_ID_TARGET_TEMP_MAX:
        if (this->target_temperature_high_sensor_ != nullptr)
          this->target_temperature_high_sensor_->publish_state(raw_to_celsius(data[i].value));
        break;

      // I143
      case UPONOR_ID_DATETIME1:     
//  uint16_t time1 = (year & 0x7F) << 7 | (month & 0x0F) << 3 | (day_of_week & 0x07);
//  uint16_t time2 = (day_of_month & 0x1F) << 11 | (hour & 0x1F) << 6 | (minute & 0x3F);
//  uint16_t time3 = second;        
//[2024-08-29 09:20:58][I][uponor_smatrix145.sensor:058]: Timer time 1: 0x0C43
//[2024-08-29 09:20:58][I][uponor_smatrix145.sensor:067]: Timer time 2: 0xEA53
//[2024-08-29 09:20:58][I][uponor_smatrix145.sensor:072]: Timer time 3: 0x0012
        // this->time_part1_ = data[i].value;
        // this->time_year_ = ((data[i].value >> 7) & 0x007F) + 0x07D0;  //2000 -> 0x07D0
        // if (this->timer_year_sensor_ != nullptr)
        //   this->timer_year_sensor_->publish_state(this->time_year_);  //2000 -> 0x07D0
        // this->time_month_ = (data[i].value >> 3) & 0x000F;
        // if (this->timer_month_sensor_ != nullptr)    
        //   this->timer_month_sensor_->publish_state(this->time_month_);
        // //ESP_LOGI(TAG, "Timer time 1: 0x%04X", data[i].value);    
        // if (this->timer_timepart1_sensor_ != nullptr)
        //   this->timer_timepart1_sensor_->publish_state(this->time_part1_);    
        break;
      case UPONOR_ID_DATETIME2:
        // this->time_part2_ = data[i].value;
        // this->time_day_ = (data[i].value >> 11) & 0x001F;     
        // if (this->timer_day_sensor_ != nullptr)
        //   this->timer_day_sensor_->publish_state(this->time_day_);     
        // this->time_hour_ = (data[i].value >> 6) & 0x001F;
        // if (this->timer_hour_sensor_ != nullptr)
        //   this->timer_hour_sensor_->publish_state(this->time_hour_);        
        // this->time_minute_ = data[i].value & 0x003F;
        // if (this->timer_minute_sensor_ != nullptr)
        //   this->timer_minute_sensor_->publish_state(this->time_minute_);           
        // //ESP_LOGI(TAG, "Timer time 2: 0x%04X", data[i].value);    
        // if (this->timer_timepart2_sensor_ != nullptr)
        //   this->timer_timepart2_sensor_->publish_state(this->time_part2_);    
        break;
      case UPONOR_ID_DATETIME3:       
        // this->time_part3_ = data[i].value;    
        // this->time_second_ = data[i].value & 0x003F;
        // if (this->timer_second_sensor_ != nullptr)
        //   this->timer_second_sensor_->publish_state(this->time_second_);    
        //ESP_LOGI(TAG, "Timer time 3: 0x%04X", data[i].value);    
        break;        
    
    //only to test setting values to timer
    // if (this->target_temperature_sensor_ != nullptr)
        //   this->target_temperature_sensor_->publish_state(raw_to_celsius(data[i].value));      
    // if (this->temp_timer_eco_mode_ > 0 && this->send_timer_eco_mode_ > 0 && this->send_timer_eco_mode_ != this->temp_timer_eco_mode_)
    // {
      // UponorSmatrixData data[] = {{UPONOR_ID_TIMER_HEATING_MODE, this->send_timer_eco_mode_}};
            // ESP_LOGI(TAG, "Retry Send Data for heating mode 0x%02X from 0x%04X to 0x%04X", UPONOR_ID_TIMER_HEATING_MODE, this->temp_timer_eco_mode_, this->send_timer_eco_mode_);
            // this->send(data, sizeof(data) / sizeof(data[0]));      
    // }
    // if (data[i].value == 0 || data[i].value == 30)
    // {
      // ESP_LOGI("   ", "actual UPONOR_ID_TIMER_HEATING_MODE 0x%04X", this->temp_timer_eco_mode_);
      // if ((this->temp_timer_eco_mode_ & 0x0008) == 0x0000)
        // //Setzen
        // this->send_timer_eco_mode_ = (this->temp_timer_eco_mode_ | 0x0008);
      // else
        // //löschen
        // this->send_timer_eco_mode_ = (this->temp_timer_eco_mode_ & 0x0007);
      // ESP_LOGI("   ", "new UPONOR_ID_TIMER_HEATING_MODE 0x%04X", this->send_timer_eco_mode_);
            // UponorSmatrixData data[] = {{UPONOR_ID_TIMER_HEATING_MODE, this->send_timer_eco_mode_}};
            // ESP_LOGI(TAG, "Send Data for heating mode 0x%02X 0x%04X", UPONOR_ID_TIMER_HEATING_MODE, this->send_timer_eco_mode_);
            // this->send(data, sizeof(data) / sizeof(data[0]));      
    // }    
        break;
      case UPONOR_ID_ECO_SETBACK:
		this->eco_setback_ = raw_to_celsius2(data[i].value);
		if (this->eco_setback_sensor_ != nullptr)
			this->eco_setback_sensor_->publish_state(this->eco_setback_);
        break;		
      case UPONOR_ID_MODE1:
	    //this->climate_preset_mode_ = ((data[i].value & 0x0008) == 0x0008) ? climate::CLIMATE_PRESET_ECO : climate::CLIMATE_PRESET_NONE;
      this->climate_preset_mode_ = gbl_timer_eco_mode;
		if (this->climate_preset_mode_sensor_ != nullptr)
			this->climate_preset_mode_sensor_->publish_state(this->climate_preset_mode_);		
		//ESP_LOGI(TAG, "Device address: 0x%04X 0x%04X - UPONOR_ID_MODE1(0x3E): 0x%04X", this->system_address_, this->address_, data[i].value); 
        break;
      case UPONOR_ID_MODE2:
	    //ESP_LOGI(TAG, "Device address: 0x%04X 0x%04X - UPONOR_ID_MODE2(0x3F): 0x%04X", this->system_address_, this->address_, data[i].value); 		
        break;
		
      case UPONOR_ID_TIMER_VACATION_TEMP:
        if (this->timer_vacation_target_temperature_sensor_ != nullptr)
          this->timer_vacation_target_temperature_sensor_->publish_state(raw_to_celsius(data[i].value));
        break;
      case UPONOR_ID_TIMER_ECO_SETBACK:
        if (this->timer_eco_setback_sensor_ != nullptr)
          this->timer_eco_setback_sensor_->publish_state(raw_to_celsius2(data[i].value));
        break;
      case UPONOR_ID_TIMER_HEATING_MODE:
        if (this->timer_autocalibration_mode_sensor_ != nullptr)
          this->timer_autocalibration_mode_sensor_->publish_state(data[i].value & 0x0001);
        
        gbl_timer_eco_mode = ((data[i].value & 0x0008) == 0x0008) ? ECO_PRESET_ON : ECO_PRESET_OFF;
        if (this->timer_eco_mode_sensor_ != nullptr)
    {
          this->timer_eco_mode_sensor_->publish_state(((data[i].value & 0x0008) == 0x0008) ? ECO_PRESET_ON : ECO_PRESET_OFF);      
          
    }
        if (this->timer_vacation_mode_sensor_ != nullptr)
          this->timer_vacation_mode_sensor_->publish_state(data[i].value & 0x0400);
        break;

    }
  }
}

}  // namespace uponor_smatrix145
}  // namespace esphome
