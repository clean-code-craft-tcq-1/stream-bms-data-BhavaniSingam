import random
import time,datetime

battery_limits = {"temperature": [0,45,"temperature"],
                    "soc": [20,80,"soc"],
                    }

def generateBatteryParameters():
    battery_params = {}
    temperature_limits = battery_limits['temperature']
    battery_params["temperature"] = random.randint(temperature_limits[0],
                                                         temperature_limits[1])
    soc_limits = battery_limits['soc']
    battery_params["soc"] = random.randint(soc_limits[0],
                                                         soc_limits[1])
    return battery_params

def stream_readings(max_count):
    bms_records_count = 0
    while(bms_records_count < max_count):
        print(format_battery_parameter())
        bms_records_count += 1
        time.sleep(1)
        
