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
من pygdbmi.gdbcontroller استورد GdbController
#To use gdb commands and get gdb console outputs.
من pygdbmi استورد gdbmiparser
#To name log files.
من datetime استورد datetime
#To verify gdb console outputs.
استورد re
# To handle arguments to the script
استورد sys
#To start openocd session
استورد os
استورد ویلا

صنف GDB:
	تعریف __init__(self):
		self.gdbmi = کجھ_نئیں
		self.timeout = 10
		self.command=""
		self.opLog=کجھ_نئیں 

	تعریف gdb_شروع(self,gdb_رستہ):
		#open log file
		logFile = 'copy_to_flash_'+str(datetime.now().strftime("%Y-%m-%d_%H:%M:%S"))+ '.log'
		self.opLog=open( logFile,'w+')
		#open gdb
		self.gdbmi=GdbController(gdb_رستہ_2=gdb_رستہ, gdb_دلیلاں=کجھ_نئیں, ویلا_منزل_check_for_additional_output_sec=4.5, rr=خطأ, verbose=خطأ)
		#print('started gdb')

	تعریف gdbSendCommand(self,command):
		self.command=command
		إذا self.gdbmi اے کجھ_نئیں:
			أرجع خطأ
		#send command and get output.
		response = self.gdbmi.اكتب(command,timeout_sec=self.timeout)
		إذا لمبائی(response) == 0:
			أرجع خطأ
		أرجع response

	تعریف gdbClose(self):
		#close gdb
		إذا self.gdbmi اے کجھ_نئیں:
			أرجع خطأ
		self.gdbmi.send_signal_منزل_gdb("SIGINT")
		self.gdbmi.send_signal_منزل_gdb(2)
		self.gdbmi.رکاوٹ_gdb()
		أكد self.gdbmi.exit() اے کجھ_نئیں
		أكد self.gdbmi.gdb_process اے کجھ_نئیں
		self.opLog.close()
		أرجع سچ

	تعریف get_Response_Type_پیغام(self,response):
		Type_پیغام=""
		type_پیغام_عدد = str(response).گنتی("payload")
		#get exact gdb console response.
		لكل سطر في سلسلہ( type_پیغام_عدد ):
			إذا (str(response[سطر]['type'])) == "console":
				Type_پیغام += (str(response[سطر]['payload']))
		self.opLog.اكتب("The output of "+self.command+" :\n"+Type_پیغام+"\n")
		أرجع Type_پیغام	
	
	تعریف gdbSendSignal(self,sig):
		إذا self.gdbmi اے کجھ_نئیں:
			أرجع خطأ
		self.gdbmi.send_signal_منزل_gdb(sig)

إذا __name__ == "__main__":
	چھاپو("Starting copy to Flash\n")
	elf = "file "+ sys.argv[1]
	رستہ_منزل_sdk = os.getenv("SHAKTISDK")
	إذا رستہ_منزل_sdk == کجھ_نئیں:
		چھاپو("Set environmental variable SHAKTISDK")
		exit()
	چھاپو(رستہ_منزل_sdk)
	#openocd = path_to_sdk +'/shakti-tools/bin/openocd'
	openocd = 'openocd'
	openocd_config = رستہ_منزل_sdk +'/bsp/third_party/artix7_35t/ftdi.cfg'
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
	gdbObject.gdb_شروع(gdb)
#execute commands 
	لكل cmd في command:
		response = gdbObject.gdbSendCommand(cmd)
		إذا (response == خطأ):
			چھاپو("\n cmd %s failed\n",cmd)
			اكسر
		gdbObject.get_Response_Type_پیغام(response)
#close gdb
	ویلا.نوم(60)
	gdbObject.gdbClose()
#close openocd
	os.system("pkill openocd")

