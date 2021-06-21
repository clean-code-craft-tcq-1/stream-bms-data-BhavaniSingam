#include "stdafx.h"
#include<iostream>
#include <stdlib.h>
#include <sstream>
#include "bms_receiver.h"
#define SOC_STRING "soc"
#define TEMP_STRING "temperature"

char validate_data(std::string sample)
{
	if ((sample.find(SOC_STRING) == std::string::npos) || (sample.find(TEMP_STRING) == std::string::npos))
		return false;
	else
		return true;
}

void bms_process_receiver::init_minmax(BMS_DATA *sampleData)
{
	MinSOC = sampleData->SOC;
	MaxSOC = sampleData->SOC;
	MinTemp = sampleData->temperature;
	MaxTemp = sampleData->temperature;
}

void bms_process_receiver::compute_minmaxSOC(BMS_DATA *sampleData)
{
	if (MinSOC > sampleData->SOC)
		MinSOC = sampleData->SOC;
	if (MaxSOC < sampleData->SOC)
		MaxSOC = sampleData->SOC;
}

void bms_process_receiver::compute_minmaxTemp(BMS_DATA *sampleData)
{
	if (MinTemp > sampleData->temperature)
		MinTemp = sampleData->temperature;
	if (MaxTemp < sampleData->temperature)
		MaxTemp = sampleData->temperature;
}


BMS_DATA* bms_process_receiver::extractData(std::stringstream& IPData)
{
	
	std::string subString[5];
	std::string sample = IPData.str();
	if (validate_data(sample))
		return NULL;

	for (int iter = 0; iter < 5; iter++)
	{
		IPData >> subString[iter];
	}
	bms_params.temperature = std::stof(subString[TEMP_JSON_INDEX]);
	bms_params.SOC = std::stof(subString[SOC_JSON_INDEX]);
	return &bms_params;
}

double bms_process_receiver::movingAvg(float *ptrArrNumbers, double *ptrSum, int pos, int len, float nextNum)
{
	//Subtract the oldest number from the prev sum, add the new number
	*ptrSum = *ptrSum - ptrArrNumbers[pos] + nextNum;
	//Assign the nextNum to the position in the array
	ptrArrNumbers[pos] = nextNum;
	//return the average
	return *ptrSum / len;
}
