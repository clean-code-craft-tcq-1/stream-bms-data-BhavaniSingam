#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include<iostream>
#include <stdlib.h>
#include <sstream>
#include "../bms_receiver.h"
#include "catch.hpp"

TEST_CASE("data reception test") {
  
  bms_process_receiver testObj;
  BMS_DATA* sampleData;
  std::string teststring = "{'temperature': 15, 'soc': 59}";
  REQUIRE(validate_data(teststring));
  std::stringstream IPData;
  IPData << "{'temperature': 15, 'soc': 59}";
  sampleData = testObj.extractData(IPData);
  REQUIRE( sampleData->SOC == 59 );
  REQUIRE( sampleData->temperature == 15 );
  
}
