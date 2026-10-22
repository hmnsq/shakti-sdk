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
তঃ pygdbmi.gdbcontroller আনযন GdbController
#To use gdb commands and get gdb console outputs.
তঃ pygdbmi আনযন gdbmiparser
#To name log files.
তঃ datetime আনযন datetime
#To verify gdb console outputs.
আনযন re
# To handle arguments to the script
আনযন sys
#To start openocd session
আনযন os
আনযন time

শ্ৰেণী GDB:
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
		self.gdbmi=GdbController(gdb_path=gdbPath, gdb_args=None, time_to_check_for_additional_output_sec=4.5, rr=মিছা, verbose=মিছা)
		#print('started gdb')

	def gdbSendCommand(self,command):
		self.command=command
		যদি self.gdbmi is None:
			ঘূৰাই মিছা
		#send command and get output.
		response = self.gdbmi.লিখ(command,timeout_sec=self.timeout)
		যদি len(response) == 0:
			ঘূৰাই মিছা
		ঘূৰাই response

	def gdbClose(self):
		#close gdb
		যদি self.gdbmi is None:
			ঘূৰাই মিছা
		self.gdbmi.send_signal_to_gdb("SIGINT")
		self.gdbmi.send_signal_to_gdb(2)
		self.gdbmi.interrupt_gdb()
		প্রতিজ্ঞা self.gdbmi.exit() is None
		প্রতিজ্ঞা self.gdbmi.gdb_process is None
		self.opLog.close()
		ঘূৰাই সঁচা

	def get_Response_Type_বাৰ্তা(self,response):
		Type_বাৰ্তা=""
		type_বাৰ্তা_অঙ্ক = str(response).গুনতি("payload")
		#get exact gdb console response.
		বাবে সাৰি অন্তঃ range( type_বাৰ্তা_অঙ্ক ):
			যদি (str(response[সাৰি]['type'])) == "console":
				Type_বাৰ্তা += (str(response[সাৰি]['payload']))
		self.opLog.লিখ("The output of "+self.command+" :\n"+Type_বাৰ্তা+"\n")
		ঘূৰাই Type_বাৰ্তা	
	
	def gdbSendSignal(self,sig):
		যদি self.gdbmi is None:
			ঘূৰাই মিছা
		self.gdbmi.send_signal_to_gdb(sig)

যদি __name__ == "__main__":
	print("Starting copy to Flash\n")
	elf = "file "+ sys.argv[1]
	path_to_sdk = os.getenv("SHAKTISDK")
	যদি path_to_sdk == None:
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
	বাবে cmd অন্তঃ command:
		response = gdbObject.gdbSendCommand(cmd)
		যদি (response == মিছা):
			print("\n cmd %s failed\n",cmd)
			ভঙ্গ
		gdbObject.get_Response_Type_বাৰ্তা(response)
#close gdb
	time.সুষুপ্তি(60)
	gdbObject.gdbClose()
#close openocd
	os.system("pkill openocd")

