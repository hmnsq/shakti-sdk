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
ತಃ pygdbmi.gdbcontroller ಆಮದು GdbController
#To use gdb commands and get gdb console outputs.
ತಃ pygdbmi ಆಮದು gdbmiparser
#To name log files.
ತಃ datetime ಆಮದು datetime
#To verify gdb console outputs.
ಆಮದು re
# To handle arguments to the script
ಆಮದು sys
#To start openocd session
ಆಮದು os
ಆಮದು ಸಮಯ

ವರ್ಗ GDB:
	ವ್ಯಾಖ್ಯಾನ __init__(self):
		self.gdbmi = ಏನೂಇಲ್ಲ
		self.timeout = 10
		self.command=""
		self.opLog=ಏನೂಇಲ್ಲ 

	ವ್ಯಾಖ್ಯಾನ gdb_ಆರಂಭ(self,gdb_ಮಾರ್ಗ):
		#open log file
		logFile = 'copy_to_flash_'+str(datetime.now().strftime("%Y-%m-%d_%H:%M:%S"))+ '.log'
		self.opLog=open( logFile,'w+')
		#open gdb
		self.gdbmi=GdbController(gdb_ಮಾರ್ಗ_2=gdb_ಮಾರ್ಗ, gdb_ವಾದಗಳು=ಏನೂಇಲ್ಲ, ಸಮಯ_ಗಮ್ಯ_check_for_additional_output_sec=4.5, rr=ಸುಳ್ಳು, verbose=ಸುಳ್ಳು)
		#print('started gdb')

	ವ್ಯಾಖ್ಯಾನ gdbSendCommand(self,command):
		self.command=command
		ಆದರೆ self.gdbmi ಆಗಿರುವ ಏನೂಇಲ್ಲ:
			ಹಿಂತಿರುಗಿ ಸುಳ್ಳು
		#send command and get output.
		response = self.gdbmi.ಲಿಖ(command,timeout_sec=self.timeout)
		ಆದರೆ ಉದ್ದ(response) == 0:
			ಹಿಂತಿರುಗಿ ಸುಳ್ಳು
		ಹಿಂತಿರುಗಿ response

	ವ್ಯಾಖ್ಯಾನ gdbClose(self):
		#close gdb
		ಆದರೆ self.gdbmi ಆಗಿರುವ ಏನೂಇಲ್ಲ:
			ಹಿಂತಿರುಗಿ ಸುಳ್ಳು
		self.gdbmi.send_signal_ಗಮ್ಯ_gdb("SIGINT")
		self.gdbmi.send_signal_ಗಮ್ಯ_gdb(2)
		self.gdbmi.ಅಡಚಣೆ_gdb()
		ಪ್ರತಿಜ್ಞಾ self.gdbmi.exit() ಆಗಿರುವ ಏನೂಇಲ್ಲ
		ಪ್ರತಿಜ್ಞಾ self.gdbmi.gdb_process ಆಗಿರುವ ಏನೂಇಲ್ಲ
		self.opLog.close()
		ಹಿಂತಿರುಗಿ ನಿಜ

	ವ್ಯಾಖ್ಯಾನ get_Response_Type_ಸಂದೇಶ(self,response):
		Type_ಸಂದೇಶ=""
		type_ಸಂದೇಶ_ಅಂಕೆ = str(response).ಎಣಿಕೆ_2("payload")
		#get exact gdb console response.
		ಗಾಗಿ ಸಾಲು ಒಳಗೆ ಶ್ರೇಣಿ( type_ಸಂದೇಶ_ಅಂಕೆ ):
			ಆದರೆ (str(response[ಸಾಲು]['type'])) == "console":
				Type_ಸಂದೇಶ += (str(response[ಸಾಲು]['payload']))
		self.opLog.ಲಿಖ("The output of "+self.command+" :\n"+Type_ಸಂದೇಶ+"\n")
		ಹಿಂತಿರುಗಿ Type_ಸಂದೇಶ	
	
	ವ್ಯಾಖ್ಯಾನ gdbSendSignal(self,sig):
		ಆದರೆ self.gdbmi ಆಗಿರುವ ಏನೂಇಲ್ಲ:
			ಹಿಂತಿರುಗಿ ಸುಳ್ಳು
		self.gdbmi.send_signal_ಗಮ್ಯ_gdb(sig)

ಆದರೆ __name__ == "__main__":
	ಮುದ್ರಿಸು("Starting copy to Flash\n")
	elf = "file "+ sys.argv[1]
	ಮಾರ್ಗ_ಗಮ್ಯ_sdk = os.getenv("SHAKTISDK")
	ಆದರೆ ಮಾರ್ಗ_ಗಮ್ಯ_sdk == ಏನೂಇಲ್ಲ:
		ಮುದ್ರಿಸು("Set environmental variable SHAKTISDK")
		exit()
	ಮುದ್ರಿಸು(ಮಾರ್ಗ_ಗಮ್ಯ_sdk)
	#openocd = path_to_sdk +'/shakti-tools/bin/openocd'
	openocd = 'openocd'
	openocd_config = ಮಾರ್ಗ_ಗಮ್ಯ_sdk +'/bsp/third_party/artix7_35t/ftdi.cfg'
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
	gdbObject.gdb_ಆರಂಭ(gdb)
#execute commands 
	ಗಾಗಿ cmd ಒಳಗೆ command:
		response = gdbObject.gdbSendCommand(cmd)
		ಆದರೆ (response == ಸುಳ್ಳು):
			ಮುದ್ರಿಸು("\n cmd %s failed\n",cmd)
			ನಿಲ್ಲಿಸು
		gdbObject.get_Response_Type_ಸಂದೇಶ(response)
#close gdb
	ಸಮಯ.ಸುಷುಪ್ತಿ(60)
	gdbObject.gdbClose()
#close openocd
	os.system("pkill openocd")

