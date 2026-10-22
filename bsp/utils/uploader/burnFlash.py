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
ତଃ pygdbmi.gdbcontroller ଆମଦାନୀ GdbController
#To use gdb commands and get gdb console outputs.
ତଃ pygdbmi ଆମଦାନୀ gdbmiparser
#To name log files.
ତଃ datetime ଆମଦାନୀ datetime
#To verify gdb console outputs.
ଆମଦାନୀ re
# To handle arguments to the script
ଆମଦାନୀ sys
#To start openocd session
ଆମଦାନୀ os
ଆମଦାନୀ time

ଶ୍ରେଣୀ GDB:
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
		self.gdbmi=GdbController(gdb_path=gdbPath, gdb_args=None, time_to_check_for_additional_output_sec=4.5, rr=ମିଥ୍ୟା, verbose=ମିଥ୍ୟା)
		#print('started gdb')

	def gdbSendCommand(self,command):
		self.command=command
		ଯଦି self.gdbmi is None:
			ଫେରନ୍ତୁ ମିଥ୍ୟା
		#send command and get output.
		response = self.gdbmi.ଲିଖ(command,timeout_sec=self.timeout)
		ଯଦି len(response) == 0:
			ଫେରନ୍ତୁ ମିଥ୍ୟା
		ଫେରନ୍ତୁ response

	def gdbClose(self):
		#close gdb
		ଯଦି self.gdbmi is None:
			ଫେରନ୍ତୁ ମିଥ୍ୟା
		self.gdbmi.send_signal_to_gdb("SIGINT")
		self.gdbmi.send_signal_to_gdb(2)
		self.gdbmi.interrupt_gdb()
		ପ୍ରତିଜ୍ଞା self.gdbmi.exit() is None
		ପ୍ରତିଜ୍ଞା self.gdbmi.gdb_process is None
		self.opLog.close()
		ଫେରନ୍ତୁ ସତ୍ୟ

	def get_Response_Type_ସନ୍ଦେଶ(self,response):
		Type_ସନ୍ଦେଶ=""
		type_ସନ୍ଦେଶ_ଅଙ୍କ = str(response).ଗଣନା_2("payload")
		#get exact gdb console response.
		ପାଇଁ ଧାଡ଼ି ଭିତରେ range( type_ସନ୍ଦେଶ_ଅଙ୍କ ):
			ଯଦି (str(response[ଧାଡ଼ି]['type'])) == "console":
				Type_ସନ୍ଦେଶ += (str(response[ଧାଡ଼ି]['payload']))
		self.opLog.ଲିଖ("The output of "+self.command+" :\n"+Type_ସନ୍ଦେଶ+"\n")
		ଫେରନ୍ତୁ Type_ସନ୍ଦେଶ	
	
	def gdbSendSignal(self,sig):
		ଯଦି self.gdbmi is None:
			ଫେରନ୍ତୁ ମିଥ୍ୟା
		self.gdbmi.send_signal_to_gdb(sig)

ଯଦି __name__ == "__main__":
	print("Starting copy to Flash\n")
	elf = "file "+ sys.argv[1]
	path_to_sdk = os.getenv("SHAKTISDK")
	ଯଦି path_to_sdk == None:
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
	ପାଇଁ cmd ଭିତରେ command:
		response = gdbObject.gdbSendCommand(cmd)
		ଯଦି (response == ମିଥ୍ୟା):
			print("\n cmd %s failed\n",cmd)
			ଭାଙ୍ଗ
		gdbObject.get_Response_Type_ସନ୍ଦେଶ(response)
#close gdb
	time.ସୁଷୁପ୍ତି(60)
	gdbObject.gdbClose()
#close openocd
	os.system("pkill openocd")

