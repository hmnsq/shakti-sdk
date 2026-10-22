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
തഃ pygdbmi.gdbcontroller ഇറക്കുമതി GdbController
#To use gdb commands and get gdb console outputs.
തഃ pygdbmi ഇറക്കുമതി gdbmiparser
#To name log files.
തഃ datetime ഇറക്കുമതി datetime
#To verify gdb console outputs.
ഇറക്കുമതി re
# To handle arguments to the script
ഇറക്കുമതി sys
#To start openocd session
ഇറക്കുമതി os
ഇറക്കുമതി time

വർഗ്ഗം GDB:
	def __init__(self):
		self.gdbmi = None
		self.timeout = 10
		self.command=""
		self.opLog=None 

	def gdbStart(self,gdbPath):
		#open log file
		logFile = 'copy_to_flash_'+str(datetime.now().strftime("%Y-%m-%d_%H:%M:%S"))+ '.log'
		self.opLog=open( logFile,'w+')
		#open gdb
		self.gdbmi=GdbController(gdb_path=gdbPath, gdb_args=None, time_to_check_for_additional_output_sec=4.5, rr=അസത്യം, verbose=അസത്യം)
		#print('started gdb')

	def gdbSendCommand(self,command):
		self.command=command
		എങ്കിൽ self.gdbmi is None:
			തിരികെ അസത്യം
		#send command and get output.
		response = self.gdbmi.ലിഖ(command,timeout_sec=self.timeout)
		എങ്കിൽ len(response) == 0:
			തിരികെ അസത്യം
		തിരികെ response

	def gdbClose(self):
		#close gdb
		എങ്കിൽ self.gdbmi is None:
			തിരികെ അസത്യം
		self.gdbmi.send_signal_to_gdb("SIGINT")
		self.gdbmi.send_signal_to_gdb(2)
		self.gdbmi.interrupt_gdb()
		പ്രതിജ്ഞാ self.gdbmi.exit() is None
		പ്രതിജ്ഞാ self.gdbmi.gdb_process is None
		self.opLog.close()
		തിരികെ സത്യം

	def get_Response_Type_സന്ദേശം(self,response):
		Type_സന്ദേശം=""
		type_സന്ദേശം_അക്കം = str(response).എണ്ണം("payload")
		#get exact gdb console response.
		വേണ്ടി വരി ഇൽ range( type_സന്ദേശം_അക്കം ):
			എങ്കിൽ (str(response[വരി]['type'])) == "console":
				Type_സന്ദേശം += (str(response[വരി]['payload']))
		self.opLog.ലിഖ("The output of "+self.command+" :\n"+Type_സന്ദേശം+"\n")
		തിരികെ Type_സന്ദേശം	
	
	def gdbSendSignal(self,sig):
		എങ്കിൽ self.gdbmi is None:
			തിരികെ അസത്യം
		self.gdbmi.send_signal_to_gdb(sig)

എങ്കിൽ __name__ == "__main__":
	print("Starting copy to Flash\n")
	elf = "file "+ sys.argv[1]
	path_to_sdk = os.getenv("SHAKTISDK")
	എങ്കിൽ path_to_sdk == None:
		print("Set environmental variable SHAKTISDK")
		exit()
	print(path_to_sdk)
	#openocd = path_to_sdk +'/shakti-tools/bin/openocd'
	openocd = 'openocd'
	openocd_config = path_to_sdk +'/bsp/third_party/artix7_35t/ftdi.cfg'
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
	വേണ്ടി cmd ഇൽ command:
		response = gdbObject.gdbSendCommand(cmd)
		എങ്കിൽ (response == അസത്യം):
			print("\n cmd %s failed\n",cmd)
			നിർത്തുക
		gdbObject.get_Response_Type_സന്ദേശം(response)
#close gdb
	time.സുഷുപ്തി(60)
	gdbObject.gdbClose()
#close openocd
	os.system("pkill openocd")

