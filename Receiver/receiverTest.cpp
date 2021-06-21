#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include<iostream>
#include <stdlib.h>
#include <sstream>
#include "../sender/bms_sender.h"
#include "../test-exec/catch.hpp"

TEST_CASE("data generation test") {

	BMS_generator_tester * tester_obj = new BMS_generator_tester;
	BMS_DATA testData;
	for (int noOfIter = 0; noOfIter < 50; noOfIter++) 
	{
		testData = tester_obj->pushToTest(tester_obj->Output_JSON_Data());
		REQUIRE(tester_obj->Validate_Range(testData.SOC, MIN_SOC, MAX_SOC));
		REQUIRE(tester_obj->Validate_Range(testData.temperature, MIN_TEMP, MAX_TEMP));
	}
}
