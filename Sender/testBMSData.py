import unittest
import GenerateBMSData
class test_streaming_bms_data(unittest.TestCase):
    def test_format_battery_parameter(self):
        bms_param = GenerateBMSData.generateBatteryParameters()
        self.assertTrue(bms_param['temperature'])
        self.assertTrue(bms_param['soc'])
    def test_stream_bms_reading_send(self):
        GenerateBMSData.stream_readings(50)
        
       
if __name__ == '__main__':
    unittest.main()
