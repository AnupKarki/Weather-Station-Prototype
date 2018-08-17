/*
 * rtcInterface.h
 *
 *  Created on: Mar 8, 2017
 *      Author: i_anu
 */

#ifndef RTCINTERFACE_H_
#define RTCINTERFACE_H_

int receiveBytes;
int receiveBuffer[14];

int transmitState = 0;
int bufferPosition = 0;
int dateAndTimeRecieved = 0;

static volatile RTC_C_Calendar myTime;
void rtcInit();

void setRtctime();

#endif /* RTCINTERFACE_H_ */
