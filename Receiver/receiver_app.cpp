// receiver_app.cpp : Defines the entry point for the console application.
//

#include<iostream>
#include <stdlib.h>
#include <sstream>
#include "bms_receiver.h"
using namespace std;

int main()
{
	BMS_DATA sampleData = {0,0};
	BOOL firstdata = true;
	std::stringstream InputData;
	bms_process_receiver recvObj;
	long avgCalcCount = 0;
	double SOC_avg = 0,temp_avg = 0;
	int position = 0;

	while (1)
	{
		avgCalcCount++;
		InputData.clear();
		string input;
		getline(cin, input);
		InputData << input;
		sampleData = recvObj.extractData(InputData);
		
		if(firstdata)
		{
			recvObj.init_minmax(&sampleData);
		}
		else
		{
			recvObj.compute_minmax(&sampleData);
		}
		if (avgCalcCount >= MOVING_LENGTH)
		{
			SOC_avg = recvObj.movingAvg(recvObj.SOCArray, &recvObj.SOC_sum, position, MOVING_LENGTH, sampleData.SOC);
			temp_avg = recvObj.movingAvg(recvObj.tempArray, &recvObj.temp_sum, position, MOVING_LENGTH, sampleData.temperature);
		}

		position++;
		if (position >= MOVING_LENGTH) {
			position = 0;
		}

		printf("MinSOC = %02.2f, MaxSOC = %02.2f, MinTemperature = %02.2f, Maxtemperature = %02.2f, AvgSOC = %02.2f, Avgtemp = %02.2f \n", \
			recvObj.MinSOC, recvObj.MaxSOC, recvObj.MinTemp, recvObj.MaxTemp, SOC_avg, temp_avg);
	}
	return 0;
}
