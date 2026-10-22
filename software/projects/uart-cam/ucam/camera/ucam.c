/***************************************************************************
* Project                               :  shakti devt board
* Name of the file                      :  ucam.c
* Brief Description of file             :  Device driver to communicate with ucam-III module
* Name of Author                        :  P Girinath, Shivaram Prasad Meesa
* Email ID                              :  palanigirinath@gmail.com, shivaramprasadmeesa@gmail.com

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
  @file ucam.c
  @brief Device driver to communicate with ucam-III module
  @details Contains implementation of init_cam() and get_pic() functions
**/




#అన్తర్భావ "ucam.h"

/** @fn assert_check(int bool,int track)
 * @brief assert function, exits if assert failed.
 * @param int bool-false or true
 * @param int track - 0 if host, 1 if camera
 */
శూన్య assert_check(పూర్ణాంకం bool,పూర్ణాంకం track) {
    ఒకవేళ(bool) తిరిగి;
    ఒకవేళ(track) 
      రాయి("Camera response error!!\n");
    లేకపోతే {
      రాయి("Host response error!!\nIs host connected?");
      తిరిగి;
    }
    నిష్క్రమించు(-1);
}

/** @fn delay_milli(unsigned long milli_seconds)
 * @brief delay function 
 * @param unsigned long milli_seconds - delay for given milliseconds
 */
శూన్య delay_milli(గుర్తులేని దీర్ఘ milli_seconds)
{
	గుర్తులేని దీర్ఘ cntr1 = milli_seconds;
	గుర్తులేని దీర్ఘ tmpCntr;

	అయితే (cntr1--) {
		tmpCntr = 1000;
		అయితే (tmpCntr--);
	}
}

/** @fn send(const uint8_t* str,int len)
 * @brief function to send command to camera
 * @param const uint8_t* str-pointer to command string  
 * @param int len- length of command string
 */
శూన్య send(స్థిరరాశి uint8_t* str,పూర్ణాంకం len){
  పూర్ణాంకం i;
  flush_uart(CAM);
  కొరకు(i =0;i<len;i++){
    write_uart_character(CAM,*str);
    str++;
  }
}

/** @fn recieve_ack(int cmdno,int pid)
 * @brief Read 6 bytes and check whether they match with ACK_COMMAND of specific cmdno,pid
 * @param int cmdno-command number of ACK 
 * @param int pid- packet ID
 */
శూన్య recieve_ack(పూర్ణాంకం cmdno,పూర్ణాంకం pid)
{
  uint8_t str[6]; 
  పూర్ణాంకం i = 0;
  కొరకు(i=0;i<6;i++){
    read_uart_character(CAM,(str+i));
  }
  uint8_t cc = (uint8_t)cmdno; 
  uint8_t pn[] = {(uint8_t)(pid>>8),(uint8_t)(pid%256)};
  uint8_t ack_ex[] = {(uint8_t)(0xAA),(uint8_t)(0x0E),cc,str[3],pn[1],pn[0]};
  assert_check(strcmp(ack_ex,str)==0,1);
}

/** @fn get_ack(int cmdno,int pid, uint8_t str[])
 * @brief Fill ACK command with given specifics
 * @param int cmdno-command number of ACK 
 * @param int pid- packet ID 
 * @param uint8_t str[]- pointer to command string
 */
శూన్య get_ack(పూర్ణాంకం cmdno,పూర్ణాంకం pid, uint8_t str[])
{
  str[0] = (uint8_t)(0xAA);
  str[1] = (uint8_t)(0x0E);
  str[2] = (uint8_t)cmdno;
  str[3] = 0;
  str[4] = (uint8_t)(pid%256);
  str[5] = (uint8_t) (pid>>8);
}

/** @fn recieve_gen(uint8_t str[],int len)
 * @brief function to read len bytes from camera
 * @param uint8_t str[]- pointer to string 
 * @param int len - number of bytes to recieve from camera
 */
శూన్య recieve_gen(uint8_t str[],పూర్ణాంకం len)
{
  పూర్ణాంకం i;
  కొరకు(i = 0;i < len; i++)
  {
    read_uart_character(CAM,str+i);
  }
}

/** @fn recieve_img(int count,int limit)
 * @brief Function to recieve one data packet from camera
 * @param int count- Packet ID of current packet 
 * @param int limit- number of bytes in current packet
 */ 
శూన్య recieve_img(పూర్ణాంకం లెక్క,పూర్ణాంకం హద్దు){
  uint8_t ptr[256];
  పూర్ణాంకం i=0;
  uint8_t ack_తాత్కాలిక[6];
  get_ack(0,లెక్క,ack_తాత్కాలిక);
  send(ack_తాత్కాలిక, 6);
  // if limit=6 it means we don't expect any data bytes
  ఒకవేళ(హద్దు==6) తిరిగి;
  అయితే(1){
    read_uart_character(CAM,(ptr+i));
    i++;
    ఒకవేళ(i==హద్దు) ఆపు;
  }
  కొరకు(పూర్ణాంకం j=4;j<i-2;j++){
    write_uart_character(HOST,ptr[j]);
  }
}

/** @fn init_cam()
 * @brief Function to wake up camera
 * @return int - 0 if success, -1 if error
 */ 
పూర్ణాంకం init_cam()
{
  పూర్ణాంకం delay_సమయం = 4;
  పూర్ణాంకం no=0;
  స్థిరరాశి uint8_t  sync_command[] = {(uint8_t)(0xAA),(uint8_t)(0x0D), (uint8_t)(0x0),(uint8_t)(0x0),(uint8_t)(0x0),(uint8_t)(0x0)};
  స్థిరరాశి uint8_t  ack_command[] = {(uint8_t)(0xAA),(uint8_t)(0x0E), (uint8_t)(0x0D),(uint8_t)(0x0),(uint8_t)(0x0),(uint8_t)(0x0)};
  స్థిరరాశి uint8_t  ack_command_జవాబు[] = {(uint8_t)(0xAA),(uint8_t)(0x0E), (uint8_t)(0x0),(uint8_t)(0x0),(uint8_t)(0x0),(uint8_t)(0x0)};
  ప్రారంభం:
  {
    no++;
    రాయి("Round : %d\n",no);
    send(sync_command,6);
    delay_milli(delay_సమయం++); 
    ఒకవేళ(CAM->స్థితి_3 & STS_RX_NOT_ఖాళీలు)
    {
        // code to read 12 characters from the buffer and if it matches with the ACK and sync commands go to succes
        పూర్ణాంకం i;
        కొరకు(i = 0;i<6;i++) 
        {
           uint8_t ch;
           read_uart_character(CAM,&ch);
           ఒకవేళ(i == 3)కొనసాగు; // don't care xx thing
           ఒకవేళ(ch != ack_command[i]) వెళ్ళు fail;
        }
        కొరకు(i = 0;i<6;i++)
        {
            uint8_t ch;
            read_uart_character(CAM,&ch);
            ఒకవేళ(ch != sync_command[i]) వెళ్ళు fail;
        }
        వెళ్ళు success;
    }
  }
  fail:
  ఒకవేళ(delay_సమయం>15000) {
    రాయి("Can't wake up camera! Is camera connected?\n");
    తిరిగి -1;
  }
  వెళ్ళు ప్రారంభం;
  success:
  flush_uart(CAM);
  send(ack_command_జవాబు,6);
  రాయి("\n synchronisation process done waiting for 2 seconds for stabilisation \n");
  delay(2);
  రాయి("\n you are all set \n");
  తిరిగి 0;
}

/** @fn send_full_reset()
 * @brief Send Full reset to camera
 */ 
శూన్య send_నిండిన_reset() {
  uint8_t reset_command[] = {(uint8_t)(0xAA),(uint8_t)(0x08),(uint8_t)(0x0),(uint8_t)(0x0),(uint8_t)(0x0),(uint8_t)(0x0)};
  send(reset_command,6);
  recieve_ack(8,0);
}

/** @fn get_pic(int mode)
 * @brief Function to get picture
 * @param int mode - 0 for one image, 1 for continuous
 */ 
శూన్య get_pic(పూర్ణాంకం బహుళకం)
{
  //INITIAL_command : AA 01 00 07 xx 07 ( specific for JPEG,640x480 xx=don't care )
  uint8_t initial_command[] = {(uint8_t)(0xAA),(uint8_t)(0x1),(uint8_t)(0x0),(uint8_t)(0x7),(uint8_t)(0x3),(uint8_t)(0x7)};
  send(initial_command,6);
  recieve_ack(1,0);

  //SET_PACKAGE_SIZE_command : AA 06 08 00 01 00 (size=256)
  uint8_t సమితి_package_command[] = {(uint8_t)(0xAA),(uint8_t)(0x6),(uint8_t)(0x8),(uint8_t)(0x0),(uint8_t)(0x1),(uint8_t)(0x0)};
  send(సమితి_package_command,6);
  recieve_ack(6,0);

  //GET_PICTURE_command : AA 04 05 00 00 00 ( Current JPEG  )
  uint8_t get_pic_command[] = {(uint8_t)(0xAA),(uint8_t)(0x4),(uint8_t)(0x5),(uint8_t)(0x0),(uint8_t)(0x0),(uint8_t)(0x0)};
  
  ప్రారంభం : 
  send(get_pic_command,6);
  recieve_ack(4,0);
  uint8_t దత్తాంశం_2[6];
  recieve_gen(దత్తాంశం_2,6);

  //DATA_command : AA 0A 05 xx yy zz ( current JPEG mode )
  assert_check(దత్తాంశం_2[0]==0xAA,1);
  assert_check(దత్తాంశం_2[1]==0xA,1);
  assert_check(దత్తాంశం_2[2]==0x5,1);

  దీర్ఘ no_యొక్క_pg = (పూర్ణాంకం)దత్తాంశం_2[3] + (((దీర్ఘ)దత్తాంశం_2[4])<<8) + (((దీర్ఘ)దత్తాంశం_2[5])<<16) ;
  రాయి("New size : %ld\n",no_యొక్క_pg);

  // Send data to host
  flush_uart(HOST);
  కొరకు(పూర్ణాంకం i=0;i<6;i++)
    write_uart_character(HOST,దత్తాంశం_2[i]);

  పూర్ణాంకం counter = no_యొక్క_pg/250 ;
  పూర్ణాంకం i = 0;
  అక్షరం recv;
  //Wait for HOST to confirm that DATA_command is recieved.
  //Host should reply with 'K'
  read_uart_character(HOST,&recv);
  assert_check(recv=='K',0);
  కొరకు(i=0;i<counter;i++){
    recieve_img(i,256);
  }
  recieve_img(counter,6+(no_యొక్క_pg%250));
  ఒకవేళ(no_యొక్క_pg%250 != 0) {     
    uint8_t ack_తాత్కాలిక[6];
    get_ack(0,counter+1,ack_తాత్కాలిక);
    send(ack_తాత్కాలిక, 6);
  }
  //Wait for HOST to confirm that image is recieved.
  //Host should reply with 'O'
  read_uart_character(HOST,&recv);
  assert_check(recv=='O',0);
  రాయి("Imgdone\n");

  ఒకవేళ(బహుళకం) వెళ్ళు ప్రారంభం;
}
