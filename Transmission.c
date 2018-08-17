/*
 * Transmission.c
 *
 *  Created on: Mar 8, 2017
 *      Author: i_anu
 */

#include "Transmission.h"
#include "driverlib.h"
#include "nRF24L01.h"
#include "msprf24.h"
volatile unsigned int user;

void transmitInit()
{
    uint8_t addr[5];
    /*Initial Values for NRF24L01+ library config variables*/
    rf_crc = RF24_EN_CRC | RF24_CRCO; // CRC enabled, 16-bit
    rf_addr_width      = 5;
    rf_speed_power     = RF24_SPEED_1MBPS | RF24_POWER_0DBM;
    rf_channel         = 60;

    msprf24_init();

    msprf24_set_pipe_packetsize(0, 32);
        msprf24_open_pipe(0, 1);  // Open pipe#0 with Enhanced ShockBurst enabled for receiving Auto-ACKs
            // Note: Pipe#0 is hardcoded in the transceiver hardware as the designated "pipe" for a TX node to receive
            // auto-ACKs.  This does not have to match the pipe# used on the RX side.

        // Transmit to 'rad01' (0x72 0x61 0x64 0x30 0x31)
        msprf24_standby();
        user = msprf24_current_state();
        addr[0] = 0xDE; addr[1] = 0xAD; addr[2] = 0xBE; addr[3] = 0xEF; addr[4] = 0x00;
        w_tx_addr(addr);
        w_rx_addr(0, addr);  // Pipe 0 receives auto-ack's, autoacks are sent back to the TX addr so the PTX node
                             // needs to listen to the TX addr on pipe#0 to receive them.
}

void transmit(char  *data)
{   int i;
    uint8_t addr[5];
    uint8_t buf[32];
    for(i=0;i<500000;i++);
                        strcpy(buf,data);
                        w_tx_payload(32, buf);
                        msprf24_activate_tx();


                        if (rf_irq & RF24_IRQ_FLAGGED) {
                            rf_irq &= ~RF24_IRQ_FLAGGED;

                            msprf24_get_irq_reason();
                            if (rf_irq & RF24_IRQ_TX){
                                MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN1);
                                MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0);
                            }
                            if (rf_irq & RF24_IRQ_TXFAILED){
                                MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN0);
                                MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN1);
                            }

                            msprf24_irq_clear(rf_irq);
                            user = msprf24_get_last_retransmits();
                        }

}

void receiveInit()
{
    uint8_t addr[5];
    /* Initial values for nRF24L01+ library config variables */
        rf_crc = RF24_EN_CRC | RF24_CRCO; // CRC enabled, 16-bit
        rf_addr_width      = 5;
        rf_speed_power     = RF24_SPEED_1MBPS | RF24_POWER_0DBM;
        rf_channel         = 60;

        msprf24_init();
        msprf24_set_pipe_packetsize(0, 32);
        msprf24_open_pipe(0, 1);  // Open pipe#0 with Enhanced ShockBurst

        // Set our RX address
        addr[0] = 0xDE; addr[1] = 0xAD; addr[2] = 0xBE; addr[3] = 0xEF; addr[4] = 0x00;
        w_rx_addr(0, addr);

        // Receive mode
        if (!(RF24_QUEUE_RXEMPTY & msprf24_queue_state())) {
            flush_rx();
        }
        msprf24_activate_rx();
}

void receive(){
    uint8_t buf[32];
    char s[35];
    if (rf_irq & RF24_IRQ_FLAGGED) {
                rf_irq &= ~RF24_IRQ_FLAGGED;
                msprf24_get_irq_reason();
            }
            if (rf_irq & RF24_IRQ_RX || msprf24_rx_pending()) {
                r_rx_payload(32, buf);
                msprf24_irq_clear(RF24_IRQ_RX);
                memcpy(receiveBufferRF,buf,sizeof(buf));
                //user = buf[0];
                //printf("Receiving \n");
                //printf("%c \r",buf);
                //printf("%s \r\n",s);


            } else {
               // user = 0xFF;
            }


}




