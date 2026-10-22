#!/usr/bin/env python3

#***************************************************************************
#* Project                               :  shakti devt board
#* Name of the file                      :  burn_to_flash.c
#* Brief Description of file             :  Execute elf that copies target elf to Flash
#* Name of Author                        :  Anand Kumar S
#* Email ID                              :  007334@imail.iitm.ac.in
#
#    Copyright (C) 2019  IIT Madras. All rights reserved.
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
#***************************************************************************

#To open gdb. 
తః pygdbmi.gdbcontroller దిగుమతి GdbController
#To use gdb commands and get gdb console outputs.
తః pygdbmi దిగుమతి gdbmiparser
#To name log files.
తః datetime దిగుమతి datetime
#To verify gdb console outputs.
దిగుమతి re
# To handle arguments to the script
దిగుమతి sys
#To start openocd session
దిగుమతి os
దిగుమతి సమయం

తరగతి GDB:
	నిర్వచనం __init__(self):
		self.gdbmi = ఏమీలేదు
		self.timeout = 10
		self.command=""
		self.opLog=ఏమీలేదు 

	నిర్వచనం gdb_ప్రారంభం(self,gdb_మార్గం):
		#open log file
		logFile = 'copy_to_flash_'+str(datetime.now().strftime("%Y-%m-%d_%H:%M:%S"))+ '.log'
		self.opLog=open( logFile,'w+')
		#open gdb
		self.gdbmi=GdbController(gdb_మార్గం_2=gdb_మార్గం, gdb_వాదనలు=ఏమీలేదు, సమయం_గమ్యం_check_for_additional_output_sec=4.5, rr=అబద్ధం, verbose=అబద్ధం)
		#print('started gdb')

	నిర్వచనం gdbSendCommand(self,command):
		self.command=command
		ఒకవేళ self.gdbmi అయిన ఏమీలేదు:
			తిరిగి అబద్ధం
		#send command and get output.
		response = self.gdbmi.లిఖ(command,timeout_sec=self.timeout)
		ఒకవేళ పొడవు(response) == 0:
			తిరిగి అబద్ధం
		తిరిగి response

	నిర్వచనం gdbClose(self):
		#close gdb
		ఒకవేళ self.gdbmi అయిన ఏమీలేదు:
			తిరిగి అబద్ధం
		self.gdbmi.send_signal_గమ్యం_gdb("SIGINT")
		self.gdbmi.send_signal_గమ్యం_gdb(2)
		self.gdbmi.అంతరాయం_gdb()
		ప్రతిజ్ఞా self.gdbmi.exit() అయిన ఏమీలేదు
		ప్రతిజ్ఞా self.gdbmi.gdb_process అయిన ఏమీలేదు
		self.opLog.close()
		తిరిగి నిజం

	నిర్వచనం get_Response_Type_సందేశం(self,response):
		Type_సందేశం=""
		type_సందేశం_అంకె = str(response).లెక్క("payload")
		#get exact gdb console response.
		కొరకు పంక్తి లో శ్రేణి( type_సందేశం_అంకె ):
			ఒకవేళ (str(response[పంక్తి]['type'])) == "console":
				Type_సందేశం += (str(response[పంక్తి]['payload']))
		self.opLog.లిఖ("The output of "+self.command+" :\n"+Type_సందేశం+"\n")
		తిరిగి Type_సందేశం	
	
	నిర్వచనం gdbSendSignal(self,sig):
		ఒకవేళ self.gdbmi అయిన ఏమీలేదు:
			తిరిగి అబద్ధం
		self.gdbmi.send_signal_గమ్యం_gdb(sig)

ఒకవేళ __name__ == "__main__":
	ముద్రించు("Starting copy to Flash\n")
	elf = "file "+ sys.argv[1]
	మార్గం_గమ్యం_sdk = os.getenv("SHAKTISDK")
	ఒకవేళ మార్గం_గమ్యం_sdk == ఏమీలేదు:
		ముద్రించు("Set environmental variable SHAKTISDK")
		exit()
	ముద్రించు(మార్గం_గమ్యం_sdk)
	#openocd = path_to_sdk +'/shakti-tools/bin/openocd'
	openocd = 'openocd'
	openocd_config = మార్గం_గమ్యం_sdk +'/bsp/third_party/artix7_35t/ftdi.cfg'
	#gdb = path_to_sdk+'/shakti-tools/bin/riscv32-unknown-elf-gdb'
	gdb = 'riscv32-unknown-elf-gdb'
	elf = "file "+ sys.argv[1]
	command = []
	#command.append(gdb)
	command.append("target remote localhost:3333")
	command.append("set remotetimeout unlimited")
	command.append(elf)
	command.append("load")
	command.append("compare-sections")
	command.append("load")
	command.append("compare-sections")
	command.append("continue")
#create a openocd connection in background
	os.system(openocd+' -f '+openocd_config +' &')
	gdbObject = GDB()
	gdbObject.gdb_ప్రారంభం(gdb)
#execute commands 
	కొరకు cmd లో command:
		response = gdbObject.gdbSendCommand(cmd)
		ఒకవేళ (response == అబద్ధం):
			ముద్రించు("\n cmd %s failed\n",cmd)
			ఆపు
		gdbObject.get_Response_Type_సందేశం(response)
#close gdb
	సమయం.సుషుప్తి(60)
	gdbObject.gdbClose()
#close openocd
	os.system("pkill openocd")

