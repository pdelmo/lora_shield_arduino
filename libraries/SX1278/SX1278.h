/*! \file SX1278.h
    \brief Library for managing Semtech modules

    Copyright (C) 2015 Wireless Open Source
    http://wirelessopensource.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Version:		1.0
    Design:			David Gascón
    Implementation:	Covadonga Albiñana, Yuri Carmona
    sx1278 adapting:		Pedro del Molino

 */

 /*! \def SX1278_h
    \brief The library flag

 */

#ifndef SX1278_h
#define SX1278_h

/******************************************************************************
 * Includes
 ******************************************************************************/

#include <stdlib.h>
#include <stdint.h>
#include <Arduino.h>
#include <SPI.h>

#ifndef inttypes_h
	#include <inttypes.h>
#endif


/******************************************************************************
 * Definitions & Declarations
 *****************************************************************************/

#define SX1278_debug_mode 0

#define SX1278_SS SS

//! MACROS //
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)  // read a bit
#define bitSet(value, bit) ((value) |= (1UL << (bit)))    // set bit to '1'
#define bitClear(value, bit) ((value) &= ~(1UL << (bit))) // set bit to '0'


//! REGISTERS //
//							FSK	Commun	LORA
#define        REG_FIFO        					0x00
#define        REG_OP_MODE        				0x01
#define        REG_BITRATE_MSB    			0x02
#define        REG_BITRATE_LSB    			0x03
#define        REG_FDEV_MSB   				0x04
#define        REG_FDEV_LSB    				0x05
#define        REG_FRF_MSB    					0x06
#define        REG_FRF_MID    					0x07
#define        REG_FRF_LSB    					0x08
#define        REG_PA_CONFIG    				0x09
#define        REG_PA_RAMP    					0x0A
#define        REG_OCP    					0x0B
#define        REG_LNA    					0x0C
#define        REG_RX_CONFIG    			0x0D
#define        REG_FIFO_ADDR_PTR  					0x0D
#define        REG_RSSI_CONFIG   			0x0E
#define        REG_FIFO_TX_BASE_ADDR 		    			0x0E
#define        REG_RSSI_COLLISION    			0x0F
#define        REG_FIFO_RX_BASE_ADDR   					0x0F
#define        REG_RSSI_THRESH    			0x10
#define        REG_FIFO_RX_CURRENT_ADDR   				0x10
#define        REG_RSSI_VALUE_FSK	    		0x11
#define        REG_IRQ_FLAGS_MASK    					0x11
#define        REG_RX_BW		    		0x12
#define        REG_IRQ_FLAGS	    					0x12
#define        REG_AFC_BW		    		0x13
#define        REG_RX_NB_BYTES	    					0x13
#define        REG_OOK_PEAK	    			0x14
#define        REG_RX_HEADER_CNT_VALUE_MSB  				0x14
#define        REG_OOK_FIX	    			0x15
#define        REG_RX_HEADER_CNT_VALUE_LSB  				0x15
#define        REG_OOK_AVG	 			0x16
#define        REG_RX_PACKET_CNT_VALUE_MSB  				0x16
#define        REG_RX_PACKET_CNT_VALUE_LSB  				0x17
#define        REG_MODEM_STAT	  					0x18
#define        REG_PKT_SNR_VALUE	  				0x19
#define        REG_AFC_FEI	  			0x1A
#define        REG_PKT_RSSI_VALUE	  				0x1A
#define        REG_AFC_MSB	  			0x1B
#define        REG_RSSI_VALUE_LORA	  				0x1B
#define        REG_AFC_LSB	  			0x1C
#define        REG_HOP_CHANNEL	  					0x1C
#define        REG_FEI_MSB	  			0x1D
#define        REG_MODEM_CONFIG1	 		 		0x1D
#define        REG_FEI_LSB	  			0x1E
#define        REG_MODEM_CONFIG2	  				0x1E
#define        REG_PREAMBLE_DETECT  			0x1F
#define        REG_SYMB_TIMEOUT_LSB  					0x1F
#define        REG_RX_TIMEOUT1	  			0x20
#define        REG_PREAMBLE_MSB_LORA  					0x20
#define        REG_RX_TIMEOUT2	  			0x21
#define        REG_PREAMBLE_LSB_LORA  					0x21
#define        REG_RX_TIMEOUT3	 			0x22
#define        REG_PAYLOAD_LENGTH_LORA			 		0x22
#define        REG_RX_DELAY	 			0x23
#define        REG_MAX_PAYLOAD_LENGTH 					0x23
#define        REG_OSC		 			0x24
#define        REG_HOP_PERIOD	  					0x24
#define        REG_PREAMBLE_MSB_FSK 			0x25
#define        REG_FIFO_RX_BYTE_ADDR 					0x25
#define        REG_PREAMBLE_LSB_FSK 			0x26
#define        REG_MODEM_CONFIG3	 		 		0x26
#define        REG_SYNC_CONFIG	  			0x27
#define        REG_SYNC_VALUE1	 			0x28
#define	       REG_FEI_MSB						0x28
#define        REG_SYNC_VALUE2	  			0x29
#define	       REG_FEI_MID						0x29
#define        REG_SYNC_VALUE3	  			0x2A
#define	       REG_FEI_LSB						0x2A
#define        REG_SYNC_VALUE4	  			0x2B
#define        REG_SYNC_VALUE5	  			0x2C
#define	       REG_RSSI_WIDEBAND					0x2C
#define        REG_SYNC_VALUE6	  			0x2D
#define        REG_SYNC_VALUE7	  			0x2E
#define        REG_SYNC_VALUE8	  			0x2F
#define        REG_PACKET_CONFIG1	  		0x30
#define        REG_PACKET_CONFIG2	  		0x31
#define        REG_DETECT_OPTIMIZE	  				0x31
#define        REG_PAYLOAD_LENGTH_FSK			0x32
#define        REG_NODE_ADRS	  			0x33
#define        REG_INVERT_IQ						0x33
#define        REG_BROADCAST_ADRS	 		0x34
#define        REG_FIFO_THRESH	  			0x35
#define        REG_SEQ_CONFIG1	  			0x36
#define        REG_SEQ_CONFIG2	  			0x37
#define        REG_DETECTION_THRESHOLD 					0x37
#define        REG_TIMER_RESOL	  			0x38
#define        REG_TIMER1_COEF	  			0x39
#define        REG_SYNC_WORD						0x39
#define        REG_TIMER2_COEF	  			0x3A
#define        REG_IMAGE_CAL	  			0x3B
#define        REG_TEMP		  			0x3C
#define        REG_LOW_BAT	  			0x3D
#define        REG_IRQ_FLAGS1	  			0x3E
#define        REG_IRQ_FLAGS2	  			0x3F
#define        REG_DIO_MAPPING1	  				0x40
#define        REG_DIO_MAPPING2	  				0x41
#define        REG_VERSION	  				0x42
#define        REG_PLL_HOP	  			0x44
#define        REG_TCXO		  				0x4B
#define        REG_PA_DAC	  				0x4D
#define        REG_FORMER_TEMP	  				0x5B
#define        REG_BIT_RATE_FRAC			0x5D
#define        REG_AGC_REF	  				0x61
#define        REG_AGC_THRESH1		  			0x62
#define        REG_AGC_THRESH2		  			0x63
#define        REG_AGC_THRESH3	  				0x64
#define        REG_PLL			  			0x70


// LPD433 (low power device 433 MHz) is a part of ITU region 1 ISM band
/*!
	From 433.050 MHz to 434.790 MHz: BW: 1.74 MHz
	More info: https://en.wikipedia.org/wiki/LPD433
 */

const uint32_t CH_DEFAULT = 0x6c8000; // default channel, center frequency = 434.000MHz

// FREQUENCY CHANNELS (BANDWIDTH 500KHz):
const uint32_t CH_1_BW_500 = 0x6c5345; // channel 1, bandwidth 500KHz, center frequency = 433.3MHz ( 433.050MHz - 433.550MHz )
const uint32_t CH_2_BW_500 = 0x6c7af3; // channel 2, bandwidth 500KHz, center frequency = 433.92MHz ( 433.670MHz - 433.920MHz )
const uint32_t CH_3_BW_500 = 0x6ca2a1; // channel 3, bandwidth 500KHz, center frequency = 434.54MHz ( 434.290MHz - 434.790MHz )

// FREQUENCY CHANNELS (BANDWIDTH 250KHz):
const uint32_t CH_1_BW_250 = 0x6c4b45; // channel 1, bandwidth 250KHz, center frequency = 433.175MHz ( 433.050MHz - 433.300MHz )
const uint32_t CH_2_BW_250 = 0x6c5e57; // channel 2, bandwidth 250KHz, center frequency = 433.473MHz ( 433.348MHz - 433.598MHz )
const uint32_t CH_3_BW_250 = 0x6c716a; // channel 3, bandwidth 250KHz, center frequency = 433.771MHz ( 433.646MHz - 433.896MHz )
const uint32_t CH_4_BW_250 = 0x6c847c; // channel 4, bandwidth 250KHz, center frequency = 434.069MHz ( 433.944MHz - 434.194MHz )
const uint32_t CH_5_BW_250 = 0x6c978f; // channel 5, bandwidth 250KHz, center frequency = 434.367MHz ( 434.242MHz - 434.492MHz )
const uint32_t CH_6_BW_250 = 0x6caaa1; // channel 6, bandwidth 250KHz, center frequency = 434.665MHz ( 434.540MHz - 434.790MHz )

// FREQUENCY CHANNELS (BANDWIDTH 125KHz):
const uint32_t CH_1_BW_125 = 0x6c4745; // channel 1, bandwidth 125KHz, center frequency = 433.1125MHz ( 433.050MHz - 433.175MHz )
const uint32_t CH_2_BW_125 = 0x6c4fe1; // channel 2, bandwidth 125KHz, center frequency = 433.247MHz ( 433.1845MHz - 433.3095MHz )
const uint32_t CH_3_BW_125 = 0x6c587c; // channel 3, bandwidth 125KHz, center frequency = 433.3815MHz ( 433.319MHz - 433.444MHz )
const uint32_t CH_4_BW_125 = 0x6c6118; // channel 4, bandwidth 125KHz, center frequency = 433.516MHz ( 433.4535MHz - 433.5785MHz )
const uint32_t CH_5_BW_125 = 0x6c69b3; // channel 5, bandwidth 125KHz, center frequency = 433.6505MHz ( 433.588MHz - 433.713MHz )
const uint32_t CH_6_BW_125 = 0x6c724f; // channel 6, bandwidth 125KHz, center frequency = 433.785MHz ( 433.7225MHz - 433.8475MHz )
const uint32_t CH_7_BW_125 = 0x6c7af3; // channel 7, bandwidth 125KHz, center frequency = 433.92MHz ( 433.8575MHz - 433.9825MHz )
const uint32_t CH_8_BW_125 = 0x6c8397; // channel 8, bandwidth 125KHz, center frequency = 434.055MHz ( 433.9925MHz - 434.1175MHz )
const uint32_t CH_9_BW_125 = 0x6c8c32; // channel 9, bandwidth 125KHz, center frequency = 434.1895MHz ( 434.127MHz - 434.252MHz )
const uint32_t CH_10_BW_125 = 0x6c94ce; // channel 10, bandwidth 125KHz, center frequency = 434.324MHz ( 434.2615MHz - 434.3865MHz )
const uint32_t CH_11_BW_125 = 0x6c9d6a; // channel 11, bandwidth 125KHz, center frequency = 434.4585MHz ( 434.396MHz - 434.521MHz )
const uint32_t CH_12_BW_125 = 0x6ca605; // channel 12, bandwidth 125KHz, center frequency = 434.593MHz ( 434.5305MHz - 434.6555MHz )
const uint32_t CH_13_BW_125 = 0x6CaeA1; // channel 13, bandwidth 125KHz, center frequency = 434.7275MHz ( 434.665MHz - 434.790MHz )

// FREQUENCY CHANNELS (BANDWIDTH < 125KHz: separate 72.5KHz):
const uint32_t CH_1 = 0x6c4597; // channel 1, center freq = 433.086MHz
const uint32_t CH_2 = 0x6c4a3b; // channel 2, center freq = 433.159MHz
const uint32_t CH_3 = 0x6c4edf; // channel 3, center freq = 433.231MHz
const uint32_t CH_4 = 0x6c5383; // channel 4, center freq = 433.304MHz
const uint32_t CH_5 = 0x6c5827; // channel 5, center freq = 433.376MHz
const uint32_t CH_6 = 0x6c5ccb; // channel 6, center freq = 433.449MHz
const uint32_t CH_7 = 0x6c616f; // channel 7, center freq = 433.521MHz
const uint32_t CH_8 = 0x6c6613; // channel 8, center freq = 433.594MHz
const uint32_t CH_9 = 0x6c6ab7; // channel 9, center freq = 433.666MHz
const uint32_t CH_10 = 0x6c6f5b; // channel 10, center freq = 433.739MHz
const uint32_t CH_11 = 0x6c73ff; // channel 11, center freq = 433.811MHz
const uint32_t CH_12 = 0x6c78a3; // channel 12, center freq = 433.884MHz
const uint32_t CH_13 = 0x6c7d47; // channel 13, center freq = 433.956MHz
const uint32_t CH_14 = 0x6c81eb; // channel 14, center freq = 434.029MHz
const uint32_t CH_15 = 0x6c868f; // channel 15, center freq = 434.101MHz
const uint32_t CH_16 = 0x6c8b33; // channel 16, center freq = 434.174MHz
const uint32_t CH_17 = 0x6c8fd8; // channel 17, center freq = 434.246MHz
const uint32_t CH_18 = 0x6c947c; // channel 18, center freq = 434.319MHz
const uint32_t CH_19 = 0x6c9920; // channel 19, center freq = 434.391MHz
const uint32_t CH_20 = 0x6c9dc4; // channel 20, center freq = 434.464MHz
const uint32_t CH_21 = 0x6ca268; // channel 21, center freq = 434.536MHz
const uint32_t CH_22 = 0x6ca70c; // channel 22, center freq = 434.609MHz
const uint32_t CH_23 = 0x6cabb0; // channel 23, center freq = 434.682MHz
const uint32_t CH_24 = 0x6cb054; // channel 24, center freq = 434.754MHz

//LORA BANDWIDTH:
const uint8_t BW_7_8 = 0x00;
const uint8_t BW_10_4 = 0x01;
const uint8_t BW_15_6 = 0x02;
const uint8_t BW_20_8 = 0x03;
const uint8_t BW_31_2 = 0x04;
const uint8_t BW_41_7 = 0x05;
const uint8_t BW_62_5 = 0x06;
const uint8_t BW_125 = 0x07;
const uint8_t BW_250 = 0x08;
const uint8_t BW_500 = 0x09;

const double SignalBwLog[] =
{
    5.0969100130080564143587833158265,
    5.397940008672037609572522210551,
    5.6989700043360188047862611052755
};

//LORA CODING RATE:
const uint8_t CR_5 = 0x01;	// CR = 4/5
const uint8_t CR_6 = 0x02;	// CR = 4/6
const uint8_t CR_7 = 0x03;	// CR = 4/7
const uint8_t CR_8 = 0x04;	// CR = 4/8

//LORA SPREADING FACTOR:
const uint8_t SF_6 = 0x06;
const uint8_t SF_7 = 0x07;
const uint8_t SF_8 = 0x08;
const uint8_t SF_9 = 0x09;
const uint8_t SF_10 = 0x0A;
const uint8_t SF_11 = 0x0B;
const uint8_t SF_12 = 0x0C;

//LORA MODES:
const uint8_t LORA_SLEEP_MODE = 0x80;
const uint8_t LORA_STANDBY_MODE = 0x81;
const uint8_t LORA_TX_MODE = 0x83;
const uint8_t LORA_RX_MODE = 0x85;
const uint8_t LORA_STANDBY_FSK_REGS_MODE = 0xC1;

//FSK MODES:
const uint8_t FSK_SLEEP_MODE = 0x00;
const uint8_t FSK_STANDBY_MODE = 0x01;
const uint8_t FSK_TX_MODE = 0x03;
const uint8_t FSK_RX_MODE = 0x05;

//OTHER CONSTANTS:

const uint8_t st_SD_ON = 1;
const uint8_t st_SD_OFF = 0;
const uint8_t HEADER_ON = 0;
const uint8_t HEADER_OFF = 1;
const uint8_t CRC_ON = 1;
const uint8_t CRC_OFF = 0;
const uint8_t LORA = 1;
const uint8_t FSK = 0;
const uint8_t BROADCAST_0 = 0x00;
const uint8_t MAX_LENGTH = 255;
const uint8_t MAX_PAYLOAD = 251;
const uint8_t MAX_LENGTH_FSK = 64;
const uint8_t MAX_PAYLOAD_FSK = 60;
const uint8_t ACK_LENGTH = 5;
const uint8_t OFFSET_PAYLOADLENGTH = 5;
const uint8_t OFFSET_RSSI = 137;
const uint8_t NOISE_FIGURE = 6.0;
const uint8_t NOISE_ABSOLUTE_ZERO = 174.0;
const uint16_t MAX_TIMEOUT = 10000;		//10000 msec = 10.0 sec
const uint32_t MAX_WAIT = 12000;		//12000 msec = 12.0 sec
const uint32_t MESH_TIMEOUT = 3600000;  //3600000 msec = 3600 sec = 1 hour
const uint8_t MAX_RETRIES = 5;
const uint8_t CORRECT_PACKET = 0;
const uint8_t INCORRECT_PACKET = 1;

//! Structure :
/*!
 */
struct pack
{
	//! Structure Variable : Packet destination
	/*!
 	*/
	uint8_t dst;

	//! Structure Variable : Packet source
	/*!
 	*/
	uint8_t src;

	//! Structure Variable : Packet number
	/*!
 	*/
	uint8_t packnum;

	//! Structure Variable : Packet length
	/*!
 	*/
	uint8_t length;

	//! Structure Variable : Packet payload
	/*!
 	*/
	uint8_t data[MAX_PAYLOAD];

	//! Structure Variable : Retry number
	/*!
 	*/
	uint8_t retry;
};

/******************************************************************************
 * Class
 ******************************************************************************/

//! SX1278 Class
/*!
	SX1278 Class defines all the variables and functions used to manage
	sx1278 modules.
 */
class SX1278
{

public:

	//! class constructor
  	/*!
	\param void
	\return void
  	 */
   	SX1278();
   	
	//! It puts the module ON
  	/*!
	\param void
	\return void
	 */
	uint8_t ON();

	//! It puts the module OFF
  	/*!
	\param void
	\return void
	 */
	void OFF();

	//! It reads an internal module register.
  	/*!
  	\param byte address : address register to read from.
	\return the content of the register.
	 */
	byte readRegister(byte address);

	//! It writes in an internal module register.
  	/*!
  	\param byte address : address register to write in.
  	\param byte data : value to write in the register.
	 */
	void writeRegister(byte address, byte data);

	//! It clears the interruption flags.
  	/*!
	\param void
	\return void
	 */
	void clearFlags();

	//! It sets the LoRa mode on.
  	/*!
  	It stores in global '_LORA' variable '1' when success
    \return '0' on success, '1' otherwise
	 */
	uint8_t setLORA();

	//! It sets the FSK mode on.
  	/*!
  	It stores in global '_FSK' variable '1' when success
	\return '0' on success, '1' otherwise
	 */
	uint8_t setFSK();

	//! It gets the BW, SF and CR of the module.
  	/*!
	It stores in global '_bandwidth' variable the BW
	It stores in global '_codingRate' variable the CR
	It stores in global '_spreadingFactor' variable the SF
	\return '0' on success, '1' otherwise
	 */
	uint8_t getMode();

	//! It sets the BW, SF and CR of the module.
  	/*!
	It stores in global '_bandwidth' variable the BW
	It stores in global '_codingRate' variable the CR
	It stores in global '_spreadingFactor' variable the SF
	\param uint8_t mode : there is a mode number to different values of
	the	configured parameters with this function.
	\return '0' on success, '1' otherwise
	 */
	int8_t setMode(uint8_t mode);

	//! It gets the header mode configured.
  	/*!
  	It stores in global '_header' variable '0' when header is sent
  	(explicit header mode) or '1' when is not sent (implicit header
  	mode).
	\return '0' on success, '1' otherwise
	 */
	uint8_t	getHeader();

	//! It sets explicit header mode.
  	/*!
  	It stores in global '_header' variable '1' when success
	\return '0' on success, '1' otherwise
	 */
	int8_t	setHeaderON();

	//! It sets implicit header mode.
  	/*!
  	It stores in global '_header' variable '0' when success
	\return '0' on success, '1' otherwise
	 */
	int8_t	setHeaderOFF();

	//! It gets the CRC configured.
  	/*!
  	It stores in global '_CRC' variable '1' enabling CRC generation on
  	payload, or '0' disabling the CRC.
	\return '0' on success, '1' otherwise
	 */
	uint8_t	getCRC();

	//! It sets CRC on.
  	/*!
  	It stores in global '_CRC' variable '1' when success
	\return '0' on success, '1' otherwise
	 */
	uint8_t	setCRC_ON();

	//! It sets CRC off.
  	/*!
  	It stores in global '_CRC' variable '0' when success
	\return '0' on success, '1' otherwise
	 */
	uint8_t	setCRC_OFF();

	//! It is true if the SF selected exists.
  	/*!
	\param uint8_t spr : spreading factor value to check.
	\return 'true' on success, 'false' otherwise
	 */
	boolean	isSF(uint8_t spr);

	//! It gets the SF configured.
  	/*!
	It stores in global '_spreadingFactor' variable the current value of SF
	\return '0' on success, '1' otherwise
	 */
	int8_t	getSF();

	//! It sets the SF.
  	/*!
	It stores in global '_spreadingFactor' variable the current value of SF
	\param uint8_t spr : spreading factor value to set in the configuration.
	\return '0' on success, '1' otherwise
	 */
	uint8_t	setSF(uint8_t spr);

	//! It is true if the BW selected exists.
  	/*!
	\param uint16_t band : bandwidth value to check.
	\return 'true' on success, 'false' otherwise
	 */
	boolean	isBW(uint16_t band);

	//! It gets the BW configured.
  	/*!
	It stores in global '_bandwidth' variable the BW selected
	in the configuration
	\return '0' on success, '1' otherwise
	 */
	int8_t	getBW();

	//! It sets the BW.
  	/*!
	It stores in global '_bandwidth' variable the BW selected
	in the configuration
	\param uint16_t band : bandwidth value to set in the configuration.
	\return '0' on success, '1' otherwise
	 */
	int8_t setBW(uint16_t band);

	//! It is true if the CR selected exists.
  	/*!
	\param uint8_t cod : the coding rate value to check.
	\return 'true' on success, 'false' otherwise
	 */
	boolean	isCR(uint8_t cod);

	//! It gets the CR configured.
  	/*!
	It stores in global '_codingRate' variable the CR selected
	in the configuration
	\return '0' on success, '1' otherwise
	 */
	int8_t	getCR();

	//! It sets the CR.
  	/*!
	It stores in global '_codingRate' variable the CR selected
	in the configuration
	\param uint8_t cod : coding rate value to set in the configuration.
	\return '0' on success, '1' otherwise
	 */
	int8_t	setCR(uint8_t cod);


	//! It is true if the channel selected exists.
  	/*!
	\param uint32_t ch : frequency channel value to check.
	\return 'true' on success, 'false' otherwise
	 */
	boolean isChannel(uint32_t ch);

	//! It gets frequency channel the module is using.
  	/*!
	It stores in global '_channel' variable the frequency channel
	\return '0' on success, '1' otherwise
	 */
	uint8_t getChannel();

	//! It sets frequency channel the module is using.
  	/*!
	It stores in global '_channel' variable the frequency channel
	\param uint32_t ch : frequency channel value to set in the configuration.
	\return '0' on success, '1' otherwise
	 */
	int8_t setChannel(uint32_t ch);

	//! It gets the output power of the signal.
  	/*!
	It stores in global '_power' variable the output power of the signal
	\return '0' on success, '1' otherwise
	 */
	uint8_t getPower();

	//! It sets the output power of the signal.
  	/*!
	It stores in global '_power' variable the output power of the signal
	\param char p : 'M', 'H' or 'L' if you want Maximum, High or Low
	output power signal.
	\return '0' on success, '1' otherwise
	 */
	int8_t setPower(char p);

	//! It sets the output power of the signal.
  	/*!
	It stores in global '_power' variable the output power of the signal
	\param uint8_t pow : value to set as output power.
	\return '0' on success, '1' otherwise
	 */
	int8_t setPowerNum(uint8_t pow);

	//! It gets the preamble length configured.
  	/*!
	It stores in global '_preamblelength' variable the preamble length
	\return '0' on success, '1' otherwise
	 */
	uint8_t getPreambleLength();

	//! It sets the preamble length.
  	/*!
    It stores in global '_preamblelength' variable the preamble length
  	\param uint16_t l : preamble length to set in the configuration.
	\return '0' on success, '1' otherwise
	 */
	uint8_t setPreambleLength(uint16_t l);

	//! It gets the payload length of the last packet to send/receive.
  	/*!
    It stores in global '_payloadlength' variable the payload length of
    the last packet to send/receive.
	\return '0' on success, '1' otherwise
	 */
	uint8_t getPayloadLength();

	//! It sets the packet length to send/receive.
  	/*!
  	It stores in global '_payloadlength' variable the payload length of
    the last packet to send/receive.
	\return '0' on success, '1' otherwise
	 */
	int8_t setPacketLength();

	//! It sets the packet length to send/receive.
  	/*!
  	It stores in global '_payloadlength' variable the payload length of
    the last packet to send/receive.
  	\param uint8_t l : payload length to set in the configuration.
	\return '0' on success, '1' otherwise
	 */
	int8_t setPacketLength(uint8_t l);

	//! It gets the node address of the mote.
  	/*!
  	It stores in global '_nodeAddress' variable the node address
	\return '0' on success, '1' otherwise
	 */
	uint8_t getNodeAddress();

	//! It sets the node address of the mote.
  	/*!
  	It stores in global '_nodeAddress' variable the node address
  	\param uint8_t addr : address value to set as node address.
	\return '0' on success, '1' otherwise
	 */
	int8_t setNodeAddress(uint8_t addr);

	//! It gets the SNR of the latest received packet.
  	/*!
	It stores in global '_SNR' variable the SNR
	\return '0' on success, '1' otherwise
	 */
	int8_t getSNR();

	//! It gets the current value of RSSI.
  	/*!
	It stores in global '_RSSI' variable the current value of RSSI
	\return '0' on success, '1' otherwise
	 */
	uint8_t getRSSI();

	//! It gets the RSSI of the latest received packet.
  	/*!
	It stores in global '_RSSIpacket' variable the RSSI of the latest
	packet received.
	\return '0' on success, '1' otherwise
	 */
	int16_t getRSSIpacket();

	//! It sets the total of retries when a packet is not correctly received.
	/*!
	It stores in global '_maxRetries' variable the number of retries.
  	\param uint8_t ret : number of retries.
	\return '0' on success, '1' otherwise
	 */
	uint8_t setRetries(uint8_t ret);

	//! It gets the maximum current supply by the module.
	/*!
  	 *
	\return '0' on success, '1' otherwise
	 */
	uint8_t getMaxCurrent();

	//! It sets the maximum current supply by the module.
	/*!
	It stores in global '_maxCurrent' variable the maximum current supply.
  	\param uint8_t rate : maximum current supply.
	\return '0' on success, '1' otherwise
	 */
	int8_t setMaxCurrent(uint8_t rate);

	//! It gets the content of the main configuration registers.
  	/*!
	It stores in global '_bandwidth' variable the BW.
	It stores in global '_codingRate' variable the CR.
	It stores in global '_spreadingFactor' variable the SF.
	It stores in global '_power' variable the output power of the signal.
  	It stores in global '_channel' variable the frequency channel.
  	It stores in global '_CRC' variable '1' enabling CRC generation on
  	payload, or '0' disabling the CRC.
  	It stores in global '_header' variable '0' when header is sent
  	(explicit header mode) or '1' when is not sent (implicit header
  	mode).
	It stores in global '_preamblelength' variable the preamble length.
    It stores in global '_payloadlength' variable the payload length of
    the last packet to send/receive.
  	It stores in global '_nodeAddress' variable the node address.
	It stores in global '_temp' variable the module temperature.
	\return '0' on success, '1' otherwise
	 */
	uint8_t getRegs();

	//! It sets the maximum number of bytes from a frame that fit in a packet 
	//! structure.
	/*!
	It stores in global '_payloadlength' variable the maximum number of bytes.
  	\param uint16_t length16 : total frame length.
	\return '0' on success, '1' otherwise
	 */
	uint8_t truncPayload(uint16_t length16);

	//! It writes an ACK in FIFO to send it.
	/*!
	 *
	\return '0' on success, '1' otherwise
	*/
	uint8_t setACK();

	//! It puts the module in reception mode.
  	/*!
  	 *
	\return '0' on success, '1' otherwise
	 */
	uint8_t receive();

	//! It receives a packet before MAX_TIMEOUT.
  	/*!
  	 *
	\return '0' on success, '1' otherwise
	 */
	uint8_t receivePacketMAXTimeout();

	//! It receives a packet before a timeout.
  	/*!
  	 *
	\return '0' on success, '1' otherwise
	 */
	uint8_t receivePacketTimeout();

	//! It receives a packet before a timeout.
  	/*!
  	\param uint32_t wait : time to wait to receive something.
	\return '0' on success, '1' otherwise
	 */
	uint8_t receivePacketTimeout(uint32_t wait);

	//! It receives a packet before MAX_TIMEOUT and reply with an ACK.
  	/*!
  	 *
	\return '0' on success, '1' otherwise
	 */
	uint8_t receivePacketMAXTimeoutACK();

	//! It receives a packet before a timeout and reply with an ACK.
  	/*!
  	 *
	\return '0' on success, '1' otherwise
	 */
	uint8_t receivePacketTimeoutACK();

	//! It receives a packet before a timeout and reply with an ACK.
  	/*!
  	\param uint32_t wait : time to wait to receive something.
	\return '0' on success, '1' otherwise
	 */
	uint8_t receivePacketTimeoutACK(uint32_t wait);

	//! It puts the module in 'promiscuous' reception mode.
  	/*!
  	 *
	\return '0' on success, '1' otherwise
	 */
	uint8_t receiveAll();

	//! It puts the module in 'promiscuous' reception mode with a timeout.
  	/*!
  	\param uint32_t wait : time to wait to receive something.
	\return '0' on success, '1' otherwise
	 */
	uint8_t receiveAll(uint32_t wait);

	//! It checks if there is an available packet and its destination.
  	/*!
  	 *
	\return 'true' on success, 'false' otherwise
	 */
	boolean	availableData();

	//! It checks if there is an available packet and its destination before a 
	//! timeout.
  	/*!
  	 *
  	\param uint32_t wait : time to wait while there is no a valid header 
  	received.
	\return 'true' on success, 'false' otherwise
	 */
	boolean	availableData(uint32_t wait);

	//! It writes a packet in FIFO in order to send it.
	/*!
	\param uint8_t dest : packet destination.
	\param char *payload : packet payload.
	\return '0' on success, '1' otherwise
	*/
	uint8_t setPacket(uint8_t dest, char *payload);

	//! It writes a packet in FIFO in order to send it.
	/*!
	\param uint8_t dest : packet destination.
	\param uint8_t *payload: packet payload.
	\return '0' on success, '1' otherwise
	*/
	uint8_t setPacket(uint8_t dest, uint8_t *payload);

	//! It reads a received packet from the FIFO, if it arrives before ending 
	//! MAX_TIMEOUT time.
	/*!
	 *
	\return '0' on success, '1' otherwise
	*/
	uint8_t getPacketMAXTimeout();

	//! It reads a received packet from the FIFO, if it arrives before ending 
	//! '_sendTime' time.
	/*!
	 *
	\return '0' on success, '1' otherwise
	*/
	int8_t getPacket();

	//! It receives and gets a packet from FIFO, if it arrives before ending 
	//! 'wait' time.
	/*!
	 *
	\param uint32_t wait : time to wait while there is not a complete packet 
	received.
	\return '0' on success, '1' otherwise
	*/
	int8_t getPacket(uint32_t wait);

	//! It sends the packet stored in FIFO before ending MAX_TIMEOUT.
	/*!
	 *
	\return '0' on success, '1' otherwise
	*/
	uint8_t sendWithMAXTimeout();

	//! It sends the packet stored in FIFO before ending _sendTime time.
	/*!
	 *
	\return '0' on success, '1' otherwise
	*/
	uint8_t sendWithTimeout();

	//! It tries to send the packet stored in FIFO before ending 'wait' time.
	/*!
	\param uint32_t wait : time to wait to send the packet.
	\return '0' on success, '1' otherwise
	*/
	uint8_t sendWithTimeout(uint32_t wait);

	//! It tries to send the packet which payload is a parameter before ending 
	//! MAX_TIMEOUT.
	/*!
	\param uint8_t dest : packet destination.
	\param char *payload : packet payload.
	\return '0' on success, '1' otherwise
	*/
	uint8_t sendPacketMAXTimeout(	uint8_t dest, 
									char *payload);

	//! It tries to send the packet which payload is a parameter before ending 
	//! MAX_TIMEOUT.
	/*!
	\param uint8_t dest : packet destination.
	\param uint8_t *payload : packet payload.
	\param uint16_t length : payload buffer length.
	\return '0' on success, '1' otherwise
	*/
	uint8_t sendPacketMAXTimeout(	uint8_t dest, 
									uint8_t *payload, 
									uint16_t length);


	//! It sends the packet which payload is a parameter before ending 
	//! MAX_TIMEOUT.
	/*!
	\param uint8_t dest : packet destination.
	\param char *payload : packet payload.
	\return '0' on success, '1' otherwise
	*/
	uint8_t sendPacketTimeout(	uint8_t dest, 
								char *payload);

	//! It sends the packet which payload is a parameter before ending 
	//! MAX_TIMEOUT.
	/*!
	\param uint8_t dest : packet destination.
	\param uint8_t *payload: packet payload.
	\param uint16_t length : payload buffer length.
	\return '0' on success, '1' otherwise
	*/
	uint8_t sendPacketTimeout(	uint8_t dest, 
								uint8_t *payload, 
								uint16_t length);

	//! It sends the packet which payload is a parameter before ending 'wait' 
	//! time.
	/*!
	\param uint8_t dest : packet destination.
	\param char *payload : packet payload.
	\param uint32_t wait : time to wait.
	\return '0' on success, '1' otherwise
	*/
	uint8_t sendPacketTimeout(	uint8_t dest, 
								char *payload, 
								uint32_t wait);

	//! It sends the packet which payload is a parameter before ending 'wait' 
	//! time.
	/*!
	\param uint8_t dest : packet destination.
	\param uint8_t *payload : packet payload.
	\param uint16_t length : payload buffer length.
	\param uint32_t wait : time to wait.
	\return '0' on success, '1' otherwise
	*/
	uint8_t sendPacketTimeout(	uint8_t dest, 
								uint8_t *payload, 
								uint16_t length, 
								uint32_t wait);

	//! It sends the packet which payload is a parameter before MAX_TIMEOUT, 
	//! and replies with ACK.
	/*!
	\param uint8_t dest : packet destination.
	\param char *payload : packet payload.
	\return '9'  --> The ACK lost (no data available)
			'8'  --> The ACK lost
			'7'  --> The ACK destination incorrectly received
			'6'  --> The ACK source incorrectly received
			'5'  --> The ACK number incorrectly received
			'4'  --> The ACK length incorrectly received
			'3'  --> N-ACK received
			'2'  --> The ACK has not been received
			'1'  --> not used (reserved)
			'0'  --> The ACK has been received with no errors
	*/
	uint8_t sendPacketMAXTimeoutACK(uint8_t dest, 
									char *payload);

	//! It sends the packet which payload is a parameter before MAX_TIMEOUT, 
	//! and replies with ACK.
	/*!
	\param uint8_t dest : packet destination.
	\param uint8_t payload: packet payload.
	\param uint16_t length : payload buffer length.
	\return '9'  --> The ACK lost (no data available)
			'8'  --> The ACK lost
			'7'  --> The ACK destination incorrectly received
			'6'  --> The ACK source incorrectly received
			'5'  --> The ACK number incorrectly received
			'4'  --> The ACK length incorrectly received
			'3'  --> N-ACK received
			'2'  --> The ACK has not been received
			'1'  --> not used (reserved)
			'0'  --> The ACK has been received with no errors
	*/
	uint8_t sendPacketMAXTimeoutACK(uint8_t dest, 
									uint8_t *payload, 
									uint16_t length);

	//! It sends the packet which payload is a parameter before a timeout, 
	//! and replies with ACK.
	/*!
	\param uint8_t dest : packet destination.
	\param char *payload : packet payload.
	\return '9'  --> The ACK lost (no data available)
			'8'  --> The ACK lost
			'7'  --> The ACK destination incorrectly received
			'6'  --> The ACK source incorrectly received
			'5'  --> The ACK number incorrectly received
			'4'  --> The ACK length incorrectly received
			'3'  --> N-ACK received
			'2'  --> The ACK has not been received
			'1'  --> not used (reserved)
			'0'  --> The ACK has been received with no errors
	*/
	uint8_t sendPacketTimeoutACK(	uint8_t dest, 
									char *payload);

	//! It sends the packet which payload is a parameter before a timeout, 
	//! and replies with ACK.
	/*!
	\param uint8_t dest : packet destination.
	\param uint8_t payload: packet payload.
	\param uint16_t length : payload buffer length.
	\return '9'  --> The ACK lost (no data available)
			'8'  --> The ACK lost
			'7'  --> The ACK destination incorrectly received
			'6'  --> The ACK source incorrectly received
			'5'  --> The ACK number incorrectly received
			'4'  --> The ACK length incorrectly received
			'3'  --> N-ACK received
			'2'  --> The ACK has not been received
			'1'  --> not used (reserved)
			'0'  --> The ACK has been received with no errors
	*/
	uint8_t sendPacketTimeoutACK(	uint8_t dest, 
									uint8_t *payload, 
									uint16_t length);

	//! It sends the packet which payload is a parameter before 'wait' time, 
	//! and replies with ACK.
	/*!
	\param uint8_t dest : packet destination.
	\param char *payload : packet payload.
	\param uint32_t wait : time to wait to send the packet.
	\return '9'  --> The ACK lost (no data available)
			'8'  --> The ACK lost
			'7'  --> The ACK destination incorrectly received
			'6'  --> The ACK source incorrectly received
			'5'  --> The ACK number incorrectly received
			'4'  --> The ACK length incorrectly received
			'3'  --> N-ACK received
			'2'  --> The ACK has not been received
			'1'  --> not used (reserved)
			'0'  --> The ACK has been received with no errors
	*/
	uint8_t sendPacketTimeoutACK(	uint8_t dest, 
									char *payload,
									uint32_t wait);

	//! It sends the packet which payload is a parameter before 'wait' time, 
	//! and replies with ACK.
	/*!
	\param uint8_t dest : packet destination.
	\param uint8_t payload: packet payload.
	\param uint16_t length : payload buffer length.
	\param uint32_t wait : time to wait to send the packet.
	\return '9'  --> The ACK lost (no data available)
			'8'  --> The ACK lost
			'7'  --> The ACK destination incorrectly received
			'6'  --> The ACK source incorrectly received
			'5'  --> The ACK number incorrectly received
			'4'  --> The ACK length incorrectly received
			'3'  --> N-ACK received
			'2'  --> The ACK has not been received
			'1'  --> not used (reserved)
			'0'  --> The ACK has been received with no errors
	*/
	uint8_t sendPacketTimeoutACK(uint8_t dest, 
									uint8_t *payload, 
									uint16_t length, 
									uint32_t wait);

	//! It sets the destination of a packet.
  	/*!
  	\param uint8_t dest : value to set as destination address.
	\return '0' on success, '1' otherwise
	 */
	int8_t setDestination(uint8_t dest);

	//! It sets the waiting time to send a packet.
  	/*!
   	It stores in global '_sendTime' variable the time for each mode.
	\return '0' on success, '1' otherwise
	 */
	uint8_t setTimeout();
	
	//! It gets the theoretical value of the time-on-air of the packet
  	/*! \remarks http://www.semtech.com/images/datasheet/sx1278.pdf
   	It stores in global '_sendTime' variable the time for each mode.
	\return float: time on air depending on module settings and packet length
	 */
	float timeOnAir();
	float timeOnAir( uint16_t payloadlength );

	//! It sets the payload of the packet that is going to be sent.
  	/*!
  	\param char *payload : packet payload.
	\return '0' on success, '1' otherwise
	 */
	uint8_t setPayload(char *payload);

	//! It sets the payload of the packet that is going to be sent.
  	/*!
  	\param uint8_t payload: packet payload.
	\return '0' on success, '1' otherwise
	 */
	uint8_t setPayload(uint8_t *payload);

	//! If an ACK is received, it gets it and checks its content.
	/*!
	 *
	\return '8'  --> The ACK lost
			'7'  --> The ACK destination incorrectly received
			'6'  --> The ACK source incorrectly received
			'5'  --> The ACK number incorrectly received
			'4'  --> The ACK length incorrectly received
			'3'  --> N-ACK received
			'2'  --> The ACK has not been received
			'1'  --> not used (reserved)
			'0'  --> The ACK has been received with no errors
	*/
	uint8_t getACK();

 	//! It receives and gets an ACK from FIFO, if it arrives before ending 
 	//! 'wait' time.
	/*!
	 *
	\param uint32_t wait : time to wait while there is no an ACK received.
	\return '8'  --> The ACK lost
			'7'  --> The ACK destination incorrectly received
			'6'  --> The ACK source incorrectly received
			'5'  --> The ACK number incorrectly received
			'4'  --> The ACK length incorrectly received
			'3'  --> N-ACK received
			'2'  --> The ACK has not been received
			'1'  --> not used (reserved)
			'0'  --> The ACK has been received with no errors
	*/
	uint8_t getACK(uint32_t wait);

	//! It sends a packet, waits to receive an ACK and updates the _retries 
	//! value, before ending MAX_TIMEOUT time.
	/*!
	\param uint8_t dest : packet destination.
	\param char *payload : packet payload.
	\return '0' on success, '1' otherwise
	*/
	uint8_t sendPacketMAXTimeoutACKRetries(uint8_t dest, 
											char *payload);

	//! It sends a packet, waits to receive an ACK and updates the _retries 
	//! value, before ending MAX_TIMEOUT time.
	/*!
	\param uint8_t dest : packet destination.
	\param uint8_t *payload : packet payload.
	\param uint16_t length : payload buffer length.
	\return '0' on success, '1' otherwise
	*/
	uint8_t sendPacketMAXTimeoutACKRetries(	uint8_t dest, 
											uint8_t *payload, 
											uint16_t length);

	//! It sends a packet, waits to receive an ACK and updates the _retries value
	/*!
	\param uint8_t dest : packet destination.
	\param char *payload : packet payload.
	\return '0' on success, '1' otherwise
	*/
	uint8_t sendPacketTimeoutACKRetries(uint8_t dest, 
										char *payload);

	//! It sends a packet, waits to receive an ACK and updates the _retries value
	/*!
	\param uint8_t dest : packet destination.
	\param uint8_t *payload : packet payload.
	\param uint16_t length : payload buffer length.
	\return '0' on success, '1' otherwise
	*/
	uint8_t sendPacketTimeoutACKRetries(uint8_t dest, 
										uint8_t *payload, 
										uint16_t length);

	//! It sends a packet, waits to receive an ACK and updates the _retries 
	//! value, before ending 'wait' time.
	/*!
	\param uint8_t dest : packet destination.
	\param char *payload : packet payload.
	\param uint32_t wait : time to wait while trying to send the packet.
	\return '0' on success, '1' otherwise
	*/
	uint8_t sendPacketTimeoutACKRetries(uint8_t dest, 
										char *payload, 
										uint32_t wait);

	//! It sends a packet, waits to receive an ACK and updates the _retries 
	//! value, before ending 'wait' time.
	/*!
	\param uint8_t dest : packet destination.
	\param uint8_t *payload : packet payload.
	\param uint16_t length : payload buffer length.
	\param uint32_t wait : time to wait while trying to send the packet.
	\return '0' on success, '1' otherwise
	*/
	uint8_t sendPacketTimeoutACKRetries(uint8_t dest, 
										uint8_t *payload, 
										uint16_t length, 
										uint32_t wait);

	//! It gets the internal temperature of the module.
	/*!
	It stores in global '_temp' variable the module temperature.
	\return '0' on success, '1' otherwise
	*/
	uint8_t getTemp();
	
	//! It prints the registers related to RX via USB
	/*!
	 * \return void
	*/
	void showRxRegisters();	

	//! It sets the RTC settings with Meshlium timestamp configuration
	/*! This function sends a special Frame to Meshlium (Meshlium's address must 
	 * be '1'), and then Meshlium returns an answer with the timestamp. This 
	 * function parses the info and sets the RTC Time and Date. 
	 * \return  'true' on cad detected, 'false' if not detected
	*/
	bool cadDetected();

	/// Variables /////////////////////////////////////////////////////////////

	//! Variable : SD state.
	//!    st_SD = 00  --> SD_OFF
	//!    st_SD = 01  --> SD_ON
  	/*!
   	*/
	uint8_t st_SD;

	//! Variable : bandwidth configured in LoRa mode.
	//!    bandwidth = 0000  --> BW = 7.8KHz
	//!    bandwidth = 0001  --> BW = 10.4KHz
	//!    bandwidth = 0010  --> BW = 15.6KHz
	//!    bandwidth = 0011  --> BW = 20.8KHz
	//!    bandwidth = 0100  --> BW = 31.2KHz
	//!    bandwidth = 0101  --> BW = 41.7KHz
	//!    bandwidth = 0110  --> BW = 62.5KHz
	//!    bandwidth = 0111  --> BW = 125KHz
	//!    bandwidth = 1000  --> BW = 250KHz
	//!    bandwidth = 1001  --> BW = 500KHz
  	/*!
   	*/
	uint8_t _bandwidth;

	//! Variable : coding rate configured in LoRa mode.
	//!    codingRate = 001  --> CR = 4/5
	//!    codingRate = 010  --> CR = 4/6
	//!    codingRate = 011  --> CR = 4/7
	//!    codingRate = 100  --> CR = 4/8
  	/*!
   	*/
	uint8_t _codingRate;

	//! Variable : spreading factor configured in LoRa mode.
	//!    spreadingFactor = 6   --> SF = 6, 64 chips/symbol
	//!    spreadingFactor = 7   --> SF = 7, 128 chips/symbol
	//!    spreadingFactor = 8   --> SF = 8, 256 chips/symbol
	//!    spreadingFactor = 9   --> SF = 9, 512 chips/symbol
	//!    spreadingFactor = 10  --> SF = 10, 1024 chips/symbol
	//!    spreadingFactor = 11  --> SF = 11, 2048 chips/symbol
	//!    spreadingFactor = 12  --> SF = 12, 4096 chips/symbol
  	/*!
   	*/
	uint8_t _spreadingFactor;

	//! Variable : frequency channel.
	//!    channel = 0x6b0000  --> CH = 1, 428MHz
	//!    channel = 0x6b2000  --> CH = 2, 428.5MHz
	//!    channel = 0x6b4000  --> CH = 3, 429MHz
	//!    channel = 0x6b6000  --> CH = 4, 429.5MHz
	//!    channel = 0x6b8000  --> CH = 5, 430MHz
	//!    channel = 0x6ba000  --> CH = 6, 430.5MHz
	//!    channel = 0x6bc000  --> CH = 7, 431MHz
	//!    channel = 0x6be000  --> CH = 8, 431.5MHz
	//!    channel = 0x6c0000  --> CH = 9, 432MHz
	//!    channel = 0x6c2000  --> CH = 10, 432.5MHz
	//!    channel = 0x6c4000  --> CH = 11, 433MHz
	//!    channel = 0x6c6000  --> CH = 12, 433.5MHz
	//!    channel = 0x6c8000  --> CH = 13, 434MHz
	//!    channel = 0x6ca000  --> CH = 14, 434.5MHz
	//!    channel = 0x6cc000  --> CH = 15, 435MHz
	//!    channel = 0x6ce000  --> CH = 16, 435.5MHz
	//!    channel = 0x6d0000  --> CH = 17, 436MHz
	//!    channel = 0x6d2000  --> CH = 18, 436.5MHz
	//!    channel = 0x6d4000  --> CH = 19, 437MHz
	//!    channel = 0x6d6000  --> CH = 20, 437.5MHz
	//!    channel = 0x6d8000  --> CH = 21, 438MHz
	//!    channel = 0x6da000  --> CH = 22, 438.5MHz
	//!    channel = 0x6dc000  --> CH = 23, 439MHz
	//!    channel = 0x6de000  --> CH = 24, 439.5MHz
  	/*!
   	*/
	uint32_t _channel;

	//! Variable : output power.
	//!
  	/*!
   	*/
	uint8_t _power;

	//! Variable : SNR from the last packet received in LoRa mode.
	//!
  	/*!
   	*/
	int8_t _SNR;

	//! Variable : RSSI current value.
	//!
  	/*!
   	*/
	int8_t _RSSI;

	//! Variable : RSSI from the last packet received in LoRa mode.
	//!
  	/*!
   	*/
	int16_t _RSSIpacket;

	//! Variable : preamble length sent/received.
	//!
  	/*!
   	*/
	uint16_t _preamblelength;

	//! Variable : payload length sent/received.
	//!
  	/*!
   	*/
	uint16_t _payloadlength;

	//! Variable : node address.
	//!
  	/*!
   	*/
	uint8_t _nodeAddress;

	//! Variable : implicit or explicit header in LoRa mode.
	//!
  	/*!
   	*/
	uint8_t _header;

	//! Variable : header received while waiting a packet to arrive.
	//!
  	/*!
   	*/
	uint8_t _hreceived;

	//! Variable : presence or absence of CRC calculation.
	//!
  	/*!
   	*/
	uint8_t _CRC;

	//! Variable : packet destination.
	//!
  	/*!
   	*/
	uint8_t _destination;

	//! Variable : packet number.
	//!
  	/*!
   	*/
	uint8_t _packetNumber;

	//! Variable : indicates if received packet is correct or incorrect.
	//!
  	/*!
   	*/
   	uint8_t _reception;

	//! Variable : number of current retry.
	//!
  	/*!
   	*/
   	uint8_t _retries;

   	//! Variable : maximum number of retries.
	//!
  	/*!
   	*/
   	uint8_t _maxRetries;

   	//! Variable : maximum current supply.
	//!
  	/*!
   	*/
   	uint8_t _maxCurrent;

	//! Variable : indicates FSK or LoRa modem.
	//!
  	/*!
   	*/
	uint8_t _modem;

	//! Variable : array with all the information about a sent packet.
	//!
  	/*!
   	*/
	pack packet_sent;

	//! Variable : array with all the information about a received packet.
	//!
  	/*!
   	*/
	pack packet_received;

	//! Variable : array with all the information about a sent/received ack.
	//!
  	/*!
   	*/
	pack ACK;

	//! Variable : temperature module.
	//!
  	/*!
   	*/
	int _temp;

	//! Variable : current timeout to send a packet.
	//!
  	/*!
   	*/
	uint16_t _sendTime;

};

extern SX1278	sx1278;

#endif
