#pragma once

#define MOVING_LENGTH 5


#define TEMP_JSON_INDEX 1
#define SOC_JSON_INDEX 3

typedef struct {
	float temperature;
	float SOC;
}BMS_DATA;

class bms_process_receiver {
public:
	float SOCArray[MOVING_LENGTH] = { 0 };
	float tempArray[MOVING_LENGTH] = { 0 };
	BMS_DATA sampleData = {0, 0};
	float MinSOC, MaxSOC, MinTemp, MaxTemp;
	double SOC_sum = 0, temp_sum = 0;
	BMS_DATA extractData(std::stringstream& IPData);
	void init_minmax(BMS_DATA *sampleData);
	void compute_minmaxSOC(BMS_DATA *sampleData);
	void compute_minmaxTemp(BMS_DATA *sampleData);
	double movingAvg(float *ptrArrNumbers, double *ptrSum, int pos, int len, float nextNum);
};
