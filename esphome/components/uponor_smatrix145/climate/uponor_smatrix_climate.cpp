#include "uponor_smatrix_climate.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace uponor_smatrix145 {

static const char *const TAG = "uponor_smatrix145.climate";

void UponorSmatrixClimate::dump_config() {
  LOG_CLIMATE("", "Uponor Smatrix Climate", this);
  ESP_LOGCONFIG(TAG, "  Device address: 0x%04X 0x%04X", this->system_address_, this->address_);
}

void UponorSmatrixClimate::loop() {
  const uint32_t now = millis();

  // Publish state after all update packets are processed
  if (this->last_data_ != 0 && (now - this->last_data_ > 100) && this->target_temperature_raw_ != 0) {
    //float temp = raw_to_celsius((this->preset == climate::CLIMATE_PRESET_ECO)
    float temp = raw_to_celsius((gbl_timer_eco_mode == ECO_PRESET_ON)   
                                     ? (this->target_temperature_raw_ - this->eco_setback_value_raw_)
                                     : this->target_temperature_raw_);
    //float temp = raw_to_celsius(this->target_temperature_raw_);
    float step = this->get_traits().get_visual_target_temperature_step();
    this->target_temperature = roundf(temp / step) * step;
    this->publish_state();
    this->last_data_ = 0;
  }
}

climate::ClimateTraits UponorSmatrixClimate::traits() {
  auto traits = climate::ClimateTraits();
  traits.set_supports_current_temperature(true);
  traits.set_supports_current_humidity(true);
  traits.set_supported_modes({climate::CLIMATE_MODE_HEAT});
  traits.set_supports_action(true);
  traits.set_supported_presets({climate::CLIMATE_PRESET_ECO, climate::CLIMATE_PRESET_NONE});
  traits.set_visual_min_temperature(this->min_temperature_);
  traits.set_visual_max_temperature(this->max_temperature_);
  traits.set_visual_current_temperature_step(0.1f);
  traits.set_visual_target_temperature_step(0.5f);
  return traits;
}

void UponorSmatrixClimate::control(const climate::ClimateCall &call) {
  //ESP_LOGI(TAG, "Control entered");
  // if (call.get_target_temperature().has_value()) {
    // this->lastset_target_temperature_raw_ = celsius_to_raw(*call.get_target_temperature());
    // if (this->preset == climate::CLIMATE_PRESET_ECO) {
      // // During ECO mode, the thermostat automatically substracts the setback value from the setpoint,
      // // so we need to add it here first
      // this->lastset_target_temperature_raw_ += this->eco_setback_value_raw_;
    // }

    // send_retry_count_ = 0;
    // // For unknown reasons, we need to send a null setpoint first for the thermostat to react
    // UponorSmatrixData data[] = {{UPONOR_ID_TARGET_TEMP, 0}, {UPONOR_ID_TARGET_TEMP, lastset_target_temperature_raw_}};
    // ESP_LOGI(TAG, "Send Data for target temperature");
	  // this->send(data, sizeof(data) / sizeof(data[0]));
  // }
  // if (call.get_preset().has_value()) {
	//   ESP_LOGI(TAG, "GetPreset %d", *call.get_preset());  
	//   this->set_preset_(*call.get_preset());
  //   if (this->last_preset_ != this->preset && this->lastset_target_temperature_ != 0.0f)
  //   {
  //     this->last_preset_ = this->preset;
  //     send_data(this->lastset_target_temperature_, false);
  //   }
  // }

  if (call.get_target_temperature().has_value()) {    
    ESP_LOGI(TAG, "GetTargetTemperature %d", *call.get_target_temperature());  
	  send_data(*call.get_target_temperature(), false);
    // uint16_t temp = celsius_to_raw(this->lastset_target_temperature_);
    // if (this->preset == climate::CLIMATE_PRESET_ECO) {
    //   // During ECO mode, the thermostat automatically substracts the setback value from the setpoint,
    //   // so we need to add it here first
    //   //temp += this->eco_setback_value_raw_;
    // }
    // this->lastset_target_temperature_raw_ = temp;
    // send_retry_count_ = 0;
    // // For unknown reasons, we need to send a null setpoint first for the thermostat to react
    // UponorSmatrixData data[] = {{UPONOR_ID_TARGET_TEMP, 0}, {UPONOR_ID_TARGET_TEMP, temp}};
    // this->send(data, sizeof(data) / sizeof(data[0]));
  }
}

void UponorSmatrixClimate::send_data(float temperature, bool retry = false)
{
  ESP_LOGI(TAG, "Send Temperature %f", temperature);  
  this->lastset_target_temperature_ = temperature;
  uint16_t temp = celsius_to_raw(temperature);
  //if (this->preset == climate::CLIMATE_PRESET_ECO) {
  if (gbl_timer_eco_mode == ECO_PRESET_ON) 
  {
    // During ECO mode, the thermostat automatically substracts the setback value from the setpoint,
    // so we need to add it here first
    temp += this->eco_setback_value_raw_;
  }
  this->lastset_target_temperature_raw_ = temp;
  
  if (!retry) send_retry_count_ = 0;
  
  // For unknown reasons, we need to send a null setpoint first for the thermostat to react
  UponorSmatrixData data[] = {{UPONOR_ID_TARGET_TEMP, 0}, {UPONOR_ID_TARGET_TEMP, temp}};
  this->send(data, sizeof(data) / sizeof(data[0]));
}

void UponorSmatrixClimate::on_device_data(const UponorSmatrixData *data, size_t data_len) {
  for (int i = 0; i < data_len; i++) {
    switch (data[i].id) {
      case UPONOR_ID_TARGET_TEMP_MIN:
        this->min_temperature_ = raw_to_celsius(data[i].value);
        break;
      case UPONOR_ID_TARGET_TEMP_MAX:
        this->max_temperature_ = raw_to_celsius(data[i].value);
        break;
      case UPONOR_ID_TARGET_TEMP:
        // Ignore invalid values here as they are used by the controller to explicitely request the setpoint from a
        // thermostat
        if (data[i].value != UPONOR_INVALID_VALUE) {
          this->target_temperature_raw_ = data[i].value;
          // float temp = raw_to_celsius((this->preset == climate::CLIMATE_PRESET_ECO)
          //                               ? (this->target_temperature_raw_ - this->eco_setback_value_raw_)
          //                               : this->target_temperature_raw_);                                                            
          float temp = raw_to_celsius((gbl_timer_eco_mode == ECO_PRESET_ON)
                                        ? (this->target_temperature_raw_ - this->eco_setback_value_raw_)
                                        : this->target_temperature_raw_);                                                            
          //Set if never was set by control to device value
          if (this->lastset_target_temperature_ == 0.0f) this->lastset_target_temperature_ = temp;
          
          if (temp != this->lastset_target_temperature_ && this->send_retry_count_ < SEND_RETRY_MAX) 
          {
            ESP_LOGI(TAG, "Send Data for target temperature again %f (temp) != %f (target)", temp, this->lastset_target_temperature_);
            this->send_retry_count_++;
            ESP_LOGI(TAG, "Send Data for target temperature again %d of %d", this->send_retry_count_, SEND_RETRY_MAX);
            send_data(this->lastset_target_temperature_, true);
          }
        }
        break;
      case UPONOR_ID_ECO_SETBACK:
        this->eco_setback_value_raw_ = data[i].value;
        break;
      case UPONOR_ID_DEMAND:
        if (data[i].value & 0x1000) {
          this->mode = climate::CLIMATE_MODE_COOL;
          this->action = (data[i].value & 0x0040) ? climate::CLIMATE_ACTION_COOLING : climate::CLIMATE_ACTION_IDLE;
        } else {
          this->mode = climate::CLIMATE_MODE_HEAT;
          this->action = (data[i].value & 0x0040) ? climate::CLIMATE_ACTION_HEATING : climate::CLIMATE_ACTION_IDLE;
        }
        break;
      case UPONOR_ID_MODE1:		
        if (this->last_timer_eco_mode != gbl_timer_eco_mode)
        {
          this->last_timer_eco_mode == gbl_timer_eco_mode;
          if (gbl_timer_eco_mode == ECO_PRESET_ON)
            this->set_preset_(climate::CLIMATE_PRESET_ECO);
          else
            this->set_preset_(climate::CLIMATE_PRESET_NONE);

          send_data(this->lastset_target_temperature_, true);
        }
		// if (this->preset == climate::CLIMATE_PRESET_ECO) {       
			// ESP_LOGD(TAG, "Preset climate::CLIMATE_PRESET_ECO");
		// }
		// else {
			// ESP_LOGD(TAG, "Preset climate::CLIMATE_PRESET_NONE");
		// }
        //this->set_preset_((data[i].value & 0x0008) ? climate::CLIMATE_PRESET_ECO : climate::CLIMATE_PRESET_NONE);
        break;
      case UPONOR_ID_ROOM_TEMP:
        this->current_temperature = raw_to_celsius(data[i].value);
        break;
      case UPONOR_ID_HUMIDITY:
        this->current_humidity = data[i].value & 0x00FF;
    }
  }

  this->last_data_ = millis();
}

}  // namespace uponor_smatrix145
}  // namespace esphome
