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
سے pygdbmi.gdbcontroller درآمد GdbController
#To use gdb commands and get gdb console outputs.
سے pygdbmi درآمد gdbmiparser
#To name log files.
سے datetime درآمد datetime
#To verify gdb console outputs.
درآمد re
# To handle arguments to the script
درآمد sys
#To start openocd session
درآمد os
درآمد وقت

جماعت GDB:
	تعریف __init__(self):
		self.gdbmi = کچھ_نہیں
		self.timeout = 10
		self.command=""
		self.opLog=کچھ_نہیں 

	تعریف gdb_آغاز(self,gdb_راستہ):
		#open log file
		logFile = 'copy_to_flash_'+str(datetime.now().strftime("%Y-%m-%d_%H:%M:%S"))+ '.log'
		self.opLog=open( logFile,'w+')
		#open gdb
		self.gdbmi=GdbController(gdb_راستہ_2=gdb_راستہ, gdb_دلائل=کچھ_نہیں, وقت_مقصد_check_for_additional_output_sec=4.5, rr=جھوٹ, verbose=جھوٹ)
		#print('started gdb')

	تعریف gdbSendCommand(self,command):
		self.command=command
		اگر self.gdbmi ہے کچھ_نہیں:
			واپس جھوٹ
		#send command and get output.
		response = self.gdbmi.اكتب(command,timeout_sec=self.timeout)
		اگر لمبائی(response) == 0:
			واپس جھوٹ
		واپس response

	تعریف gdbClose(self):
		#close gdb
		اگر self.gdbmi ہے کچھ_نہیں:
			واپس جھوٹ
		self.gdbmi.send_signal_مقصد_gdb("SIGINT")
		self.gdbmi.send_signal_مقصد_gdb(2)
		self.gdbmi.مداخلت_gdb()
		أكد self.gdbmi.exit() ہے کچھ_نہیں
		أكد self.gdbmi.gdb_process ہے کچھ_نہیں
		self.opLog.close()
		واپس سچ

	تعریف get_Response_Type_پیغام(self,response):
		Type_پیغام=""
		type_پیغام_عدد = str(response).گنتی("payload")
		#get exact gdb console response.
		برائے سطر میں سلسلہ( type_پیغام_عدد ):
			اگر (str(response[سطر]['type'])) == "console":
				Type_پیغام += (str(response[سطر]['payload']))
		self.opLog.اكتب("The output of "+self.command+" :\n"+Type_پیغام+"\n")
		واپس Type_پیغام	
	
	تعریف gdbSendSignal(self,sig):
		اگر self.gdbmi ہے کچھ_نہیں:
			واپس جھوٹ
		self.gdbmi.send_signal_مقصد_gdb(sig)

اگر __name__ == "__main__":
	چھاپو("Starting copy to Flash\n")
	elf = "file "+ sys.argv[1]
	راستہ_مقصد_sdk = os.getenv("SHAKTISDK")
	اگر راستہ_مقصد_sdk == کچھ_نہیں:
		چھاپو("Set environmental variable SHAKTISDK")
		exit()
	چھاپو(راستہ_مقصد_sdk)
	#openocd = path_to_sdk +'/shakti-tools/bin/openocd'
	openocd = 'openocd'
	openocd_config = راستہ_مقصد_sdk +'/bsp/third_party/artix7_35t/ftdi.cfg'
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
	gdbObject.gdb_آغاز(gdb)
#execute commands 
	برائے cmd میں command:
		response = gdbObject.gdbSendCommand(cmd)
		اگر (response == جھوٹ):
			چھاپو("\n cmd %s failed\n",cmd)
			توڑو
		gdbObject.get_Response_Type_پیغام(response)
#close gdb
	وقت.نوم(60)
	gdbObject.gdbClose()
#close openocd
	os.system("pkill openocd")

