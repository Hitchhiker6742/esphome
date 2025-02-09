import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import (
    CONF_EXTERNAL_TEMPERATURE,
    CONF_HUMIDITY,
    CONF_TEMPERATURE,
	CONF_TARGET_TEMPERATURE,
	CONF_TARGET_TEMPERATURE_LOW,
	CONF_TARGET_TEMPERATURE_HIGH,	
    CONF_ID,
    CONF_TYPE,
    DEVICE_CLASS_HUMIDITY,
    DEVICE_CLASS_TEMPERATURE,	
    STATE_CLASS_MEASUREMENT,
	STATE_CLASS_NONE,
    UNIT_CELSIUS,
    UNIT_PERCENT,
)

from .. import (
    uponor_smatrix_ns,
    UponorSmatrixDevice,
    UPONOR_SMATRIX_DEVICE_SCHEMA,
    register_uponor_smatrix_device,
)

DEPENDENCIES = ["uponor_smatrix145"]

TYPE_I_143 = "I-143"
TYPE_T_144 = "T-144"
TYPE_T_149 = "T-149"

CONF_TARGET_TEMPERATURE_BRUTTO = "target_temperature_brutto"
CONF_ECO_SETBACK = "eco_setback"
CONF_CLIMATE_PRESET_MODE = "climate_preset_mode"
CONF_TIMER_ECO_SETBACK = "timer_eco_setback"
CONF_TIMER_ECO_MODE = "timer_eco_mode"
#CONF_TIMER_YEAR = "timer_year"
#CONF_TIMER_MONTH = "timer_month"
#CONF_TIMER_DAY = "timer_day"
#CONF_TIMER_HOUR = "timer_hour"
#CONF_TIMER_MINUTE = "timer_minute"
#CONF_TIMER_SECOND = "timer_second"
#CONF_TIMER_TIMEPART1 = "timer_timepart1"
#CONF_TIMER_TIMEPART2 = "timer_timepart2"

UponorSmatrixSensor = uponor_smatrix_ns.class_(
    "UponorSmatrixSensor",
    sensor.Sensor,
    cg.Component,
    UponorSmatrixDevice,
)
#UponorSmatrixSensorI143 = uponor_smatrix_ns.class_(
#    "UponorSmatrixSensorI143",
#    sensor.Sensor,
#    cg.Component,
#    UponorSmatrixDevice,
#)

CONFIG_SCHEMA = cv.typed_schema(
    {        
        TYPE_I_143: cv.COMPONENT_SCHEMA.extend(
            {
                #cv.GenerateID(): cv.declare_id(UponorSmatrixSensorI143),
                cv.GenerateID(): cv.declare_id(UponorSmatrixSensor),
                cv.Optional(CONF_TIMER_ECO_SETBACK): sensor.sensor_schema(
                    unit_of_measurement=UNIT_CELSIUS,
                    accuracy_decimals=1,
                    device_class=DEVICE_CLASS_TEMPERATURE,
                    state_class=STATE_CLASS_MEASUREMENT,
                ),		
                cv.Optional(CONF_TIMER_ECO_MODE): sensor.sensor_schema(                    
                    state_class=STATE_CLASS_MEASUREMENT,
                ),		
                #cv.Optional(CONF_TIMER_YEAR): sensor.sensor_schema(                    
                #    state_class=STATE_CLASS_NONE,
                #),		
                #cv.Optional(CONF_TIMER_MONTH): sensor.sensor_schema(                    
                #    state_class=STATE_CLASS_NONE,
                #),		
                #cv.Optional(CONF_TIMER_DAY): sensor.sensor_schema(                    
                #    state_class=STATE_CLASS_NONE,
                #),		
                #cv.Optional(CONF_TIMER_HOUR): sensor.sensor_schema(                    
                #    state_class=STATE_CLASS_NONE,
                #),		
                #cv.Optional(CONF_TIMER_MINUTE): sensor.sensor_schema(                    
                #    state_class=STATE_CLASS_NONE,
                #),		
                #cv.Optional(CONF_TIMER_SECOND): sensor.sensor_schema(                    
                #    state_class=STATE_CLASS_NONE,
                #),					
                #cv.Optional(CONF_TIMER_TIMEPART1): sensor.sensor_schema(                                        
				#	state_class=STATE_CLASS_NONE,
                #),					
                #cv.Optional(CONF_TIMER_TIMEPART2): sensor.sensor_schema(                                        
				#	state_class=STATE_CLASS_NONE,
                #),					
            }
        ).extend(UPONOR_SMATRIX_DEVICE_SCHEMA),            
        TYPE_T_144: cv.COMPONENT_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(UponorSmatrixSensor),
                cv.Optional(CONF_TEMPERATURE): sensor.sensor_schema(
                    unit_of_measurement=UNIT_CELSIUS,
                    accuracy_decimals=1,
                    device_class=DEVICE_CLASS_TEMPERATURE,
                    state_class=STATE_CLASS_MEASUREMENT,
                ),
                cv.Optional(CONF_TARGET_TEMPERATURE): sensor.sensor_schema(
                    unit_of_measurement=UNIT_CELSIUS,
                    accuracy_decimals=1,
                    device_class=DEVICE_CLASS_TEMPERATURE,
                    state_class=STATE_CLASS_MEASUREMENT,
                ),		
                cv.Optional(CONF_TARGET_TEMPERATURE_BRUTTO): sensor.sensor_schema(
                    unit_of_measurement=UNIT_CELSIUS,
                    accuracy_decimals=1,
                    device_class=DEVICE_CLASS_TEMPERATURE,
                    state_class=STATE_CLASS_MEASUREMENT,
                ),
                cv.Optional(CONF_TARGET_TEMPERATURE_LOW): sensor.sensor_schema(
                    unit_of_measurement=UNIT_CELSIUS,
                    accuracy_decimals=1,
                    device_class=DEVICE_CLASS_TEMPERATURE,
                    state_class=STATE_CLASS_MEASUREMENT,
                ),		
                cv.Optional(CONF_TARGET_TEMPERATURE_HIGH): sensor.sensor_schema(
                    unit_of_measurement=UNIT_CELSIUS,
                    accuracy_decimals=1,
                    device_class=DEVICE_CLASS_TEMPERATURE,
                    state_class=STATE_CLASS_MEASUREMENT,
                ),
                cv.Optional(CONF_ECO_SETBACK): sensor.sensor_schema(
                    unit_of_measurement=UNIT_CELSIUS,
                    accuracy_decimals=1,
                    device_class=DEVICE_CLASS_TEMPERATURE,
                    state_class=STATE_CLASS_MEASUREMENT,
                ),		
                cv.Optional(CONF_CLIMATE_PRESET_MODE): sensor.sensor_schema(                    
                    state_class=STATE_CLASS_MEASUREMENT,
                ),						
            }
        ).extend(UPONOR_SMATRIX_DEVICE_SCHEMA),
        TYPE_T_149: cv.COMPONENT_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(UponorSmatrixSensor),
                cv.Optional(CONF_TEMPERATURE): sensor.sensor_schema(
                    unit_of_measurement=UNIT_CELSIUS,
                    accuracy_decimals=1,
                    device_class=DEVICE_CLASS_TEMPERATURE,
                    state_class=STATE_CLASS_MEASUREMENT,
                ),
                cv.Optional(CONF_EXTERNAL_TEMPERATURE): sensor.sensor_schema(
                    unit_of_measurement=UNIT_CELSIUS,
                    accuracy_decimals=1,
                    device_class=DEVICE_CLASS_TEMPERATURE,
                    state_class=STATE_CLASS_MEASUREMENT,
                ),
                cv.Optional(CONF_HUMIDITY): sensor.sensor_schema(
                    unit_of_measurement=UNIT_PERCENT,
                    accuracy_decimals=0,
                    device_class=DEVICE_CLASS_HUMIDITY,
                    state_class=STATE_CLASS_MEASUREMENT,
                ),
                cv.Optional(CONF_TARGET_TEMPERATURE): sensor.sensor_schema(
                    unit_of_measurement=UNIT_CELSIUS,
                    accuracy_decimals=1,
                    device_class=DEVICE_CLASS_TEMPERATURE,
                    state_class=STATE_CLASS_MEASUREMENT,
                ),		
                cv.Optional(CONF_TARGET_TEMPERATURE_BRUTTO): sensor.sensor_schema(
                    unit_of_measurement=UNIT_CELSIUS,
                    accuracy_decimals=1,
                    device_class=DEVICE_CLASS_TEMPERATURE,
                    state_class=STATE_CLASS_MEASUREMENT,
                ),
                cv.Optional(CONF_TARGET_TEMPERATURE_LOW): sensor.sensor_schema(
                    unit_of_measurement=UNIT_CELSIUS,
                    accuracy_decimals=1,
                    device_class=DEVICE_CLASS_TEMPERATURE,
                    state_class=STATE_CLASS_MEASUREMENT,
                ),		
                cv.Optional(CONF_TARGET_TEMPERATURE_HIGH): sensor.sensor_schema(
                    unit_of_measurement=UNIT_CELSIUS,
                    accuracy_decimals=1,
                    device_class=DEVICE_CLASS_TEMPERATURE,
                    state_class=STATE_CLASS_MEASUREMENT,
                ),		
                cv.Optional(CONF_ECO_SETBACK): sensor.sensor_schema(
                    unit_of_measurement=UNIT_CELSIUS,
                    accuracy_decimals=1,
                    device_class=DEVICE_CLASS_TEMPERATURE,
                    state_class=STATE_CLASS_MEASUREMENT,
                ),		
                cv.Optional(CONF_CLIMATE_PRESET_MODE): sensor.sensor_schema(                    
                    state_class=STATE_CLASS_MEASUREMENT,
                ),						
            }
        ).extend(UPONOR_SMATRIX_DEVICE_SCHEMA),        
    },
    default_type=TYPE_T_149,
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await register_uponor_smatrix_device(var, config)

    if config[CONF_TYPE] == TYPE_I_143:
        if timer_eco_setback_config := config.get(CONF_TIMER_ECO_SETBACK):
            sens = await sensor.new_sensor(timer_eco_setback_config)
            cg.add(var.set_timer_eco_setback_sensor(sens))
        if timer_eco_mode_config := config.get(CONF_TIMER_ECO_MODE):
            sens = await sensor.new_sensor(timer_eco_mode_config)
            cg.add(var.set_timer_eco_mode_sensor(sens))
        #if timer_year_config := config.get(CONF_TIMER_YEAR):
        #    sens = await sensor.new_sensor(timer_year_config)
        #    cg.add(var.set_timer_year_sensor(sens))
        #if timer_month_config := config.get(CONF_TIMER_MONTH):
        #    sens = await sensor.new_sensor(timer_month_config)
        #    cg.add(var.set_timer_month_sensor(sens))
        #if timer_day_config := config.get(CONF_TIMER_DAY):
        #    sens = await sensor.new_sensor(timer_day_config)
        #    cg.add(var.set_timer_day_sensor(sens))
        #if timer_hour_config := config.get(CONF_TIMER_HOUR):
        #    sens = await sensor.new_sensor(timer_hour_config)
        #    cg.add(var.set_timer_hour_sensor(sens))
        #if timer_minute_config := config.get(CONF_TIMER_MINUTE):
        #    sens = await sensor.new_sensor(timer_minute_config)
        #    cg.add(var.set_timer_minute_sensor(sens))
        #if timer_second_config := config.get(CONF_TIMER_SECOND):
        #    sens = await sensor.new_sensor(timer_second_config)
        #    cg.add(var.set_timer_second_sensor(sens))
        #if timer_timepart1_config := config.get(CONF_TIMER_TIMEPART1):
        #    sens = await sensor.new_sensor(timer_timepart1_config)
        #    cg.add(var.set_timer_timepart1_sensor(sens))
        #if timer_timepart2_config := config.get(CONF_TIMER_TIMEPART2):
        #    sens = await sensor.new_sensor(timer_timepart2_config)
        #    cg.add(var.set_timer_timepart2_sensor(sens))
    if config[CONF_TYPE] == TYPE_T_144:
        if temperature_config := config.get(CONF_TEMPERATURE):
            sens = await sensor.new_sensor(temperature_config)
            cg.add(var.set_temperature_sensor(sens))
        if target_temperature_config := config.get(CONF_TARGET_TEMPERATURE):
            sens = await sensor.new_sensor(target_temperature_config)
            cg.add(var.set_target_temperature_sensor(sens))
        if target_temperature_brutto_config := config.get(CONF_TARGET_TEMPERATURE_BRUTTO):
            sens = await sensor.new_sensor(target_temperature_brutto_config)
            cg.add(var.set_target_temperature_brutto_sensor(sens))
        if target_temperature_low_config := config.get(CONF_TARGET_TEMPERATURE_LOW):
            sens = await sensor.new_sensor(target_temperature_low_config)
            cg.add(var.set_target_temperature_low_sensor(sens))
        if target_temperature_high_config := config.get(CONF_TARGET_TEMPERATURE_HIGH):
            sens = await sensor.new_sensor(target_temperature_high_config)
            cg.add(var.set_target_temperature_high_sensor(sens))
        if eco_setback_sensor_config := config.get(CONF_ECO_SETBACK):
            sens = await sensor.new_sensor(eco_setback_sensor_config)
            cg.add(var.set_eco_setback_sensor(sens))
        if climate_preset_mode_config := config.get(CONF_CLIMATE_PRESET_MODE):
            sens = await sensor.new_sensor(climate_preset_mode_config)
            cg.add(var.set_climate_preset_mode_sensor(sens))
    if config[CONF_TYPE] == TYPE_T_149:
        if temperature_config := config.get(CONF_TEMPERATURE):
            sens = await sensor.new_sensor(temperature_config)
            cg.add(var.set_temperature_sensor(sens))
        if external_temperature_config := config.get(CONF_EXTERNAL_TEMPERATURE):
            sens = await sensor.new_sensor(external_temperature_config)
            cg.add(var.set_external_temperature_sensor(sens))
        if humidity_config := config.get(CONF_HUMIDITY):
            sens = await sensor.new_sensor(humidity_config)
            cg.add(var.set_humidity_sensor(sens))
        if target_temperature_config := config.get(CONF_TARGET_TEMPERATURE):
            sens = await sensor.new_sensor(target_temperature_config)
            cg.add(var.set_target_temperature_sensor(sens))
        if target_temperature_brutto_config := config.get(CONF_TARGET_TEMPERATURE_BRUTTO):
            sens = await sensor.new_sensor(target_temperature_brutto_config)
            cg.add(var.set_target_temperature_brutto_sensor(sens))
        if target_temperature_low_config := config.get(CONF_TARGET_TEMPERATURE_LOW):
            sens = await sensor.new_sensor(target_temperature_low_config)
            cg.add(var.set_target_temperature_low_sensor(sens))
        if target_temperature_high_config := config.get(CONF_TARGET_TEMPERATURE_HIGH):
            sens = await sensor.new_sensor(target_temperature_high_config)
            cg.add(var.set_target_temperature_high_sensor(sens))
        if eco_setback_sensor_config := config.get(CONF_ECO_SETBACK):
            sens = await sensor.new_sensor(eco_setback_sensor_config)
            cg.add(var.set_eco_setback_sensor(sens))
        if climate_preset_mode_config := config.get(CONF_CLIMATE_PRESET_MODE):
            sens = await sensor.new_sensor(climate_preset_mode_config)
            cg.add(var.set_climate_preset_mode_sensor(sens))
			
