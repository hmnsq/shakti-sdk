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
ਤਃ pygdbmi.gdbcontroller ਆਯਾਤ GdbController
#To use gdb commands and get gdb console outputs.
ਤਃ pygdbmi ਆਯਾਤ gdbmiparser
#To name log files.
ਤਃ datetime ਆਯਾਤ datetime
#To verify gdb console outputs.
ਆਯਾਤ re
# To handle arguments to the script
ਆਯਾਤ sys
#To start openocd session
ਆਯਾਤ os
ਆਯਾਤ ਸਮਾਂ

ਵਰਗ GDB:
	ਪਰਿਭਾਸ਼ਾ __init__(self):
		self.gdbmi = ਕੁਝ_ਨਹੀਂ
		self.timeout = 10
		self.command=""
		self.opLog=ਕੁਝ_ਨਹੀਂ 

	ਪਰਿਭਾਸ਼ਾ gdb_ਸ਼ੁਰੂ(self,gdb_ਰਸਤਾ):
		#open log file
		logFile = 'copy_to_flash_'+str(datetime.now().strftime("%Y-%m-%d_%H:%M:%S"))+ '.log'
		self.opLog=open( logFile,'w+')
		#open gdb
		self.gdbmi=GdbController(gdb_ਰਸਤਾ_2=gdb_ਰਸਤਾ, gdb_ਦਲੀਲਾਂ=ਕੁਝ_ਨਹੀਂ, ਸਮਾਂ_ਮੰਜ਼ਿਲ_check_for_additional_output_sec=4.5, rr=ਝੂਠ, verbose=ਝੂਠ)
		#print('started gdb')

	ਪਰਿਭਾਸ਼ਾ gdbSendCommand(self,command):
		self.command=command
		ਜੇ self.gdbmi ਹੈ ਕੁਝ_ਨਹੀਂ:
			ਵਾਪਸ ਝੂਠ
		#send command and get output.
		response = self.gdbmi.ਲਿਖ(command,timeout_sec=self.timeout)
		ਜੇ ਲੰਬਾਈ(response) == 0:
			ਵਾਪਸ ਝੂਠ
		ਵਾਪਸ response

	ਪਰਿਭਾਸ਼ਾ gdbClose(self):
		#close gdb
		ਜੇ self.gdbmi ਹੈ ਕੁਝ_ਨਹੀਂ:
			ਵਾਪਸ ਝੂਠ
		self.gdbmi.send_signal_ਮੰਜ਼ਿਲ_gdb("SIGINT")
		self.gdbmi.send_signal_ਮੰਜ਼ਿਲ_gdb(2)
		self.gdbmi.ਰੁਕਾਵਟ_gdb()
		ਪ੍ਰਤਿਜ੍ਞਾ self.gdbmi.exit() ਹੈ ਕੁਝ_ਨਹੀਂ
		ਪ੍ਰਤਿਜ੍ਞਾ self.gdbmi.gdb_process ਹੈ ਕੁਝ_ਨਹੀਂ
		self.opLog.close()
		ਵਾਪਸ ਸੱਚ

	ਪਰਿਭਾਸ਼ਾ get_Response_Type_ਸੁਨੇਹਾ(self,response):
		Type_ਸੁਨੇਹਾ=""
		type_ਸੁਨੇਹਾ_ਅੰਕ = str(response).ਗਿਣਤੀ_2("payload")
		#get exact gdb console response.
		ਲਈ ਸਤਰ ਵਿੱਚ ਸੀਮਾ( type_ਸੁਨੇਹਾ_ਅੰਕ ):
			ਜੇ (str(response[ਸਤਰ]['type'])) == "console":
				Type_ਸੁਨੇਹਾ += (str(response[ਸਤਰ]['payload']))
		self.opLog.ਲਿਖ("The output of "+self.command+" :\n"+Type_ਸੁਨੇਹਾ+"\n")
		ਵਾਪਸ Type_ਸੁਨੇਹਾ	
	
	ਪਰਿਭਾਸ਼ਾ gdbSendSignal(self,sig):
		ਜੇ self.gdbmi ਹੈ ਕੁਝ_ਨਹੀਂ:
			ਵਾਪਸ ਝੂਠ
		self.gdbmi.send_signal_ਮੰਜ਼ਿਲ_gdb(sig)

ਜੇ __name__ == "__main__":
	ਛਾਪੋ("Starting copy to Flash\n")
	elf = "file "+ sys.argv[1]
	ਰਸਤਾ_ਮੰਜ਼ਿਲ_sdk = os.getenv("SHAKTISDK")
	ਜੇ ਰਸਤਾ_ਮੰਜ਼ਿਲ_sdk == ਕੁਝ_ਨਹੀਂ:
		ਛਾਪੋ("Set environmental variable SHAKTISDK")
		exit()
	ਛਾਪੋ(ਰਸਤਾ_ਮੰਜ਼ਿਲ_sdk)
	#openocd = path_to_sdk +'/shakti-tools/bin/openocd'
	openocd = 'openocd'
	openocd_config = ਰਸਤਾ_ਮੰਜ਼ਿਲ_sdk +'/bsp/third_party/artix7_35t/ftdi.cfg'
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
	gdbObject.gdb_ਸ਼ੁਰੂ(gdb)
#execute commands 
	ਲਈ cmd ਵਿੱਚ command:
		response = gdbObject.gdbSendCommand(cmd)
		ਜੇ (response == ਝੂਠ):
			ਛਾਪੋ("\n cmd %s failed\n",cmd)
			ਰੋਕੋ
		gdbObject.get_Response_Type_ਸੁਨੇਹਾ(response)
#close gdb
	ਸਮਾਂ.ਸੁਸ਼ੁਪ੍ਤਿ(60)
	gdbObject.gdbClose()
#close openocd
	os.system("pkill openocd")

