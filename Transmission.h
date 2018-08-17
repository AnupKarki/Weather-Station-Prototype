/*
 * Transmission.h
 *
 *  Created on: Mar 8, 2017
 *      Author: i_anu
 */

#ifndef TRANSMISSION_H_
#define TRANSMISSION_H_


char receiveBufferRF[35];
void transmitInit();

void transmit(char *data);

void receive();

void receiveInit();





#endif /* TRANSMISSION_H_ */
