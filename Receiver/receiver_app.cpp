// receiver_app.cpp : Defines the entry point for the console application.
//

#include<iostream>
#include <stdlib.h>
#include <sstream>
#include "bms_receiver.h"
using namespace std;
bms_process_receiver recvObj;
char firstdata = true;

void update_minmax(BMS_DATA *sampleData)
{
	if (firstdata)
	{
		recvObj.init_minmax(sampleData);
		firstdata = false;
	}
	else
	{
		recvObj.compute_minmaxSOC(sampleData);
		recvObj.compute_minmaxTemp(sampleData);
	}
}

void assignLength(int* movingLength)
{
	*movingLength = (*movingLength <= MOVING_LENGTH) ? *movingLength : MOVING_LENGTH;
}

int main()
{
	BMS_DATA sampleData = {0,0};
	std::stringstream InputData;
	long avgCalcCount = 0;
	double SOC_avg = 0,temp_avg = 0;
	int position = 0, movingLength = 0;

	while (1)
	{
		avgCalcCount++;
		movingLength = avgCalcCount;
		InputData.clear();
		string input;
		getline(cin, input);
		//Sleep(500);
		InputData << input;
		sampleData = recvObj.extractData(InputData);
		update_minmax(&sampleData);
		assignLength(&movingLength);

		SOC_avg = recvObj.movingAvg(recvObj.SOCArray, &recvObj.SOC_sum, position, movingLength, sampleData.SOC);
		temp_avg = recvObj.movingAvg(recvObj.tempArray, &recvObj.temp_sum, position, movingLength, sampleData.temperature);

		position++;
		position = (position >= MOVING_LENGTH) ? position : 0;

		printf("MinSOC = %02.2f, MaxSOC = %02.2f, MinTemperature = %02.2f, Maxtemperature = %02.2f, AvgSOC = %02.2f, Avgtemp = %02.2f \n", \
			recvObj.MinSOC, recvObj.MaxSOC, recvObj.MinTemp, recvObj.MaxTemp, SOC_avg, temp_avg);
	}
	return 0;
}
