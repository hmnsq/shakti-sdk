/***************************************************************************
* Project                               : shakti devt board
* Name of the file                      : mq2.c
* Brief Description of file             : Demonstrates the usage of MQ2 gas sensor.
* Name of Student                       : Kolan Nikshith Reddy
* Email ID                              : cs20m030@smail.iitm.ac.in
* Name of mentor                        : Kottesswaran Ekambaram
* Email ID of Mentor                    : kottee.1@gmail.com

 Copyright (C) 2020  IIT Madras. All rights reserved.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.

***************************************************************************/
/**
@file mq2.c
@brief  write data to flash by xadc
@detail Contains driver codes to read and write flash using SPI interface.
*/

#include <stdint.h>
#include "xadc_driver.h"
#include "uart.h"
#include <math.h>

//0x41250 is the address for A0 pin
//0x41254 is the address for A1 pin
//0x41258 is the address for A2 pin
//0x4125c is the address for A3 pin


/** 
 * @fn int main()
 * @brief Calls the xadc apis to read temperature and onchip voltage.
 * @return none
 */



//only pins a0 to a3 work.
//a0 41250, a1 254, a2 258, a3 25c address


int RL_VALUE = 5;     //define the load resistance on the board, in kilo ohms
int RO_CLEAN_AIR_FACTOR = 9.83;  
int CALIBARAION_SAMPLE_TIMES = 5; 
int CALIBRATION_SAMPLE_INTERVAL = 2;
int READ_SAMPLE_INTERVAL = 2;
int READ_SAMPLE_TIMES = 5;

float LPGCurve[3]  =  {2.3,0.21,-0.47}; 
float COCurve[3]  =  {2.3,0.72,-0.34};   
float SmokeCurve[3] = {2.3,0.53,-0.44};                                                       
float Ro = 10;             

int GAS_LPG = 0;
int GAS_CO = 1;
int GAS_SMOKE = 2;

float lpg = 0;
float co = 0;
float smoke = 0;


int lastReadTime = 0;


float MQResistanceCalculation(int raw_adc) {
   return (((float)RL_VALUE*(1023-raw_adc)/raw_adc));
}


float MQCalibration() {
  float val=0;
 
  for (int i=0;i<CALIBARAION_SAMPLE_TIMES;i++) {  
      int temp = xadc_read_data(0x41250)>>5;          //take multiple samples
    val += MQResistanceCalculation(temp);
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  val = val/CALIBARAION_SAMPLE_TIMES;                   //calculate the average value
 
  val = val/RO_CLEAN_AIR_FACTOR;                        //divided by RO_CLEAN_AIR_FACTOR yields the Ro 
                                                        //according to the chart in the datasheet 
  return val; 
}


float MQRead() {
  int i;
  float rs=0;
  int val = xadc_read_data(0x41250)>>4;

  for (i=0;i<READ_SAMPLE_TIMES;i++) {
    rs += MQResistanceCalculation(val);
    delay(READ_SAMPLE_INTERVAL);
  }
 
  rs = rs/READ_SAMPLE_TIMES;
  return rs;  
}

int MQGetPercentage(float rs_ro_ratio, float *pcurve) {
  return (pow(10,(((log(rs_ro_ratio)-pcurve[1])/pcurve[2]) + pcurve[0])));
}



float MQGetGasPercentage(float rs_ro_ratio, int gas_id) {
  if ( gas_id == GAS_LPG ) {
     return MQGetPercentage(rs_ro_ratio,LPGCurve);
  } else if ( gas_id == GAS_CO ) {
     return MQGetPercentage(rs_ro_ratio,COCurve);
  } else if ( gas_id == GAS_SMOKE ) {
     return MQGetPercentage(rs_ro_ratio,SmokeCurve);
  }    
  return 0;
}

float readLPG(){
        return lpg = MQGetGasPercentage(MQRead()/10,GAS_LPG);
}

float readCO(){
        return co = MQGetGasPercentage(MQRead()/10,GAS_CO);
}

float readSmoke(){
        return smoke = MQGetGasPercentage(MQRead()/10,GAS_SMOKE);
}




void main()
{       
    
    uint32_t value ;
    Ro = MQCalibration();
    printf("\tCalibrating... Ro: %f kohm\n", Ro);

    while(1){
    lpg = readLPG()/100;
    co = readCO()/100;
    smoke = readSmoke()/100;
    printf("LPG: %f ppm,\t CO: %f ppm,\t SMOKE: %f ppm \n", lpg, co, smoke);
    }
   

}






// class MQ2 {
// public: 
// 	MQ2(int pin);
// 	float* read(bool print);
// 	float readLPG();
// 	float readCO();
// 	float readSmoke();
// 	void begin();
// private:
// 	int _pin;
	
	
// 	float MQRead();
// 	float MQGetGasPercentage(float rs_ro_ratio, int gas_id);
// 	int MQGetPercentage(float rs_ro_ratio, float *pcurve);
// 	float MQCalibration();
// 	float MQResistanceCalculation(int raw_adc);

// 	int lastReadTime = 0;
// };

// //#endif
    // for( unsigned int i = 0x41250; i <= 0x4125c; i=i+4 ) {
    //     //printf("");
    //     value = xadc_read_data(i);
    //     //if(value>0){
    //         printf(" value %d\n", value>>4);
    //         printf("value %x temp= %f\n", i,xadc_onchip_temp(value));
    //         printf("value %x voltage= %f\n\n",i, xadc_onchip_voltage(value));		
    //         //c++;
    //     //}
    // }
//	printf("value  c = %d\n", c);		
//		delay(30);

		// uint32_t value = xadc_read_data(0x41000);

		// printf("value 41000 temp= %f\n", xadc_onchip_temp(value));
		// printf("value 41000 voltage= %f\n", xadc_onchip_voltage(value));

		// value = xadc_read_data(0x41004);

		// printf("value 41004 temp= %f\n", xadc_onchip_temp(value));
		// printf("value 41004 voltage= %f\n", xadc_onchip_voltage(value));

		// value = xadc_read_data(0x41008);

		// printf("value 41008 temp= %f\n", xadc_onchip_temp(value));
		// printf("value 41008 voltage= %f\n", xadc_onchip_voltage(value));

		// value = xadc_read_data(0x4100C);

		// printf("value 4100C temp= %f\n", xadc_onchip_temp(value));
		// printf("value 4100C voltage= %f\n", xadc_onchip_voltage(value));

		// value = xadc_read_data(0x41010);

		// printf("value 41010 temp= %f\n", xadc_onchip_temp(value));
		// printf("value 41010 voltage= %f\n", xadc_onchip_voltage(value));


		// value = xadc_read_data(0x41004);
		// printf("value 41004 voltage= %f\n", xadc_onchip_voltage(value));

	//}