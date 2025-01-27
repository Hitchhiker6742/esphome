import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor
from esphome.const import (
    CONF_DEVICE_CLASS,
    CONF_ENTITY_CATEGORY,
    CONF_FILTERS,
    CONF_FROM,
    CONF_ICON,
    CONF_ID,
    CONF_TYPE,
    CONF_STATE,
    STATE_CLASS_MEASUREMENT,
    STATE_CLASS_NONE,
    DEVICE_CLASS_TIMESTAMP,
)

from .. import (
    uponor_smatrix_ns,
    UponorSmatrixDevice,
    UPONOR_SMATRIX_DEVICE_SCHEMA,
    register_uponor_smatrix_device,
)

DEPENDENCIES = ["uponor_smatrix145"]

TYPE_I_143 = "I-143"

CONF_TIMER_DATETIME = "timer_datetime"
CONF_TIMER_CALIBRATE_MODE = "timer_calibration_mode"
CONF_TIMER_HEATING_MODE = "timer_heating_mode"
CONF_TIMER_VACATION_MODE = "timer_vacation_mode"

UponorSmatrixTextSensor = uponor_smatrix_ns.class_(
    "UponorSmatrixTextSensor",
    text_sensor.TextSensor,
    cg.Component,
    UponorSmatrixDevice,
)

CONFIG_SCHEMA = cv.typed_schema(
    {        
        TYPE_I_143: cv.COMPONENT_SCHEMA.extend(
            {
                #cv.GenerateID(): cv.declare_id(UponorSmatrixSensorI143),
                cv.GenerateID(): cv.declare_id(UponorSmatrixTextSensor),
                cv.Optional(CONF_TIMER_DATETIME): text_sensor.text_sensor_schema(),
                cv.Optional(CONF_TIMER_CALIBRATE_MODE): text_sensor.text_sensor_schema(),
                cv.Optional(CONF_TIMER_HEATING_MODE): text_sensor.text_sensor_schema(),
                cv.Optional(CONF_TIMER_VACATION_MODE): text_sensor.text_sensor_schema(),
            }
        ).extend(UPONOR_SMATRIX_DEVICE_SCHEMA),            
    },
    default_type=TYPE_I_143,
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await register_uponor_smatrix_device(var, config)

    if config[CONF_TYPE] == TYPE_I_143:
        if timer_datetime_config := config.get(CONF_TIMER_DATETIME):
            sens = await text_sensor.new_text_sensor(timer_datetime_config)
            cg.add(var.set_timer_datetime_text_sensor(sens))
        if timer_calibration_mode_config := config.get(CONF_TIMER_CALIBRATE_MODE):
            sens = await text_sensor.new_text_sensor(timer_calibration_mode_config)
            cg.add(var.set_timer_calibration_mode_text_sensor(sens))
        if timer_heating_mode_config := config.get(CONF_TIMER_HEATING_MODE):
            sens = await text_sensor.new_text_sensor(timer_heating_mode_config)
            cg.add(var.set_timer_heating_mode_text_sensor(sens))
        if timer_vacation_mode_config := config.get(CONF_TIMER_VACATION_MODE):
            sens = await text_sensor.new_text_sensor(timer_vacation_mode_config)
            cg.add(var.set_timer_vacation_mode_text_sensor(sens))
