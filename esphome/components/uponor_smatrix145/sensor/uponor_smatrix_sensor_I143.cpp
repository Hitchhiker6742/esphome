#include "uponor_smatrix_sensor_I143.h"
#include "esphome/core/log.h"

namespace esphome {
namespace uponor_smatrix145 {

static const char *const TAG = "uponor_smatrix145.sensor";

void UponorSmatrixSensorI143::dump_config() {
  ESP_LOGCONFIG(TAG, "Uponor Smatrix Timer I143");
  ESP_LOGCONFIG(TAG, "  Device address: 0x%04X 0x%04X", this->system_address_, this->address_);
  //LOG_SENSOR("  ", "Temperature", this->temperature_sensor_);
  //LOG_SENSOR("  ", "External Temperature", this->external_temperature_sensor_);
  //LOG_SENSOR("  ", "Humidity", this->humidity_sensor_);
  //LOG_SENSOR("  ", "Target Temperature", this->target_temperature_sensor_);
}

void UponorSmatrixSensorI143::on_device_data(const UponorSmatrixData *data, size_t data_len) {
  ESP_LOGI("I143", "Data received");
  for (int i = 0; i < data_len; i++) {
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
	    //ESP_LOGI("   ", "Target Temperature 0x%04X", data[i].value);
        if (this->target_temperature_sensor_ != nullptr)
          this->target_temperature_sensor_->publish_state(raw_to_celsius(data[i].value));
        break;
    }
  }
}

}  // namespace uponor_smatrix145
}  // namespace esphome
