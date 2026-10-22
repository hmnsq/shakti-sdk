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
तः pygdbmi.gdbcontroller आनयन GdbController
#To use gdb commands and get gdb console outputs.
तः pygdbmi आनयन gdbmiparser
#To name log files.
तः datetime आनयन datetime
#To verify gdb console outputs.
आनयन re
# To handle arguments to the script
आनयन sys
#To start openocd session
आनयन os
आनयन time

वर्ग GDB:
	परिभाषा __init__(self):
		self.gdbmi = किमपि_न
		self.timeout = 10
		self.command=""
		self.opLog=किमपि_न 

	परिभाषा gdbStart(self,gdb_मार्गः):
		#open log file
		logFile = 'copy_to_flash_'+str(datetime.now().strftime("%Y-%m-%d_%H:%M:%S"))+ '.log'
		self.opLog=open( logFile,'w+')
		#open gdb
		self.gdbmi=GdbController(gdb_मार्गः_2=gdb_मार्गः, gdb_तर्काः=किमपि_न, time_गन्तव्यम्_check_for_additional_output_sec=4.5, rr=असत्य, verbose=असत्य)
		#print('started gdb')

	परिभाषा gdbSendCommand(self,command):
		self.command=command
		यदि self.gdbmi अस्ति किमपि_न:
			प्रत्यागम असत्य
		#send command and get output.
		response = self.gdbmi.लिख(command,timeout_sec=self.timeout)
		यदि दीर्घता(response) == 0:
			प्रत्यागम असत्य
		प्रत्यागम response

	परिभाषा gdbClose(self):
		#close gdb
		यदि self.gdbmi अस्ति किमपि_न:
			प्रत्यागम असत्य
		self.gdbmi.send_signal_गन्तव्यम्_gdb("SIGINT")
		self.gdbmi.send_signal_गन्तव्यम्_gdb(2)
		self.gdbmi.व्यवधानम्_gdb()
		प्रतिज्ञा self.gdbmi.exit() अस्ति किमपि_न
		प्रतिज्ञा self.gdbmi.gdb_process अस्ति किमपि_न
		self.opLog.close()
		प्रत्यागम सत्य

	परिभाषा get_Response_Type_सन्देशः(self,response):
		Type_सन्देशः=""
		type_सन्देशः_अङ्कः = str(response).गणनम्("payload")
		#get exact gdb console response.
		प्रति पङ्क्तिः अन्तः परिसरः( type_सन्देशः_अङ्कः ):
			यदि (str(response[पङ्क्तिः]['type'])) == "console":
				Type_सन्देशः += (str(response[पङ्क्तिः]['payload']))
		self.opLog.लिख("The output of "+self.command+" :\n"+Type_सन्देशः+"\n")
		प्रत्यागम Type_सन्देशः	
	
	परिभाषा gdbSendSignal(self,sig):
		यदि self.gdbmi अस्ति किमपि_न:
			प्रत्यागम असत्य
		self.gdbmi.send_signal_गन्तव्यम्_gdb(sig)

यदि __name__ == "__main__":
	मुद्रय("Starting copy to Flash\n")
	elf = "file "+ sys.argv[1]
	मार्गः_गन्तव्यम्_sdk = os.getenv("SHAKTISDK")
	यदि मार्गः_गन्तव्यम्_sdk == किमपि_न:
		मुद्रय("Set environmental variable SHAKTISDK")
		exit()
	मुद्रय(मार्गः_गन्तव्यम्_sdk)
	#openocd = path_to_sdk +'/shakti-tools/bin/openocd'
	openocd = 'openocd'
	openocd_config = मार्गः_गन्तव्यम्_sdk +'/bsp/third_party/artix7_35t/ftdi.cfg'
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
	gdbObject.gdbStart(gdb)
#execute commands 
	प्रति cmd अन्तः command:
		response = gdbObject.gdbSendCommand(cmd)
		यदि (response == असत्य):
			मुद्रय("\n cmd %s failed\n",cmd)
			भङ्ग
		gdbObject.get_Response_Type_सन्देशः(response)
#close gdb
	time.सुषुप्ति(60)
	gdbObject.gdbClose()
#close openocd
	os.system("pkill openocd")

