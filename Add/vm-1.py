MEM_SIZE=100

reg={'a':0, 'b':0, 'c':0, 'd':0, 'e':0,'f':0,'stack pointer':0,'acc':0, 'pc':0, 'ivec':0, 'interrupt':0, 'timer':6, 'halt':False};    
#acc to store outputs           stack pointer as stack pointer

memory=[0]*MEM_SIZE 					 					#To store the assembly code given in the file in a list

def mov(opr):                         						#opr is a list that contains the variable and its value
	reg[opr[0]]=reg[opr[1]]
	reg['pc']=reg['pc']+1			  						#Increments the program counter

def movv(opr):
	reg[opr[0]]=int(opr[1])
	reg['pc']=reg['pc']+1

def add(opr):
	reg['acc']=reg[opr[0]]+reg[opr[1]]
	reg['pc']=reg['pc']+1

def sub(opr):
	reg['acc']=reg[opr[0]]-reg[opr[1]]
	reg['pc']=reg['pc']+1

def mod(opr):
	reg['acc']=reg[opr[0]] % reg[opr[1]]
	reg['pc']=reg['pc']+1


def out(opr):
	print (reg[opr[0]])
	reg['pc']=reg['pc']+1

def halt(opr):
	reg['halt']=True
	reg['pc']=reg['pc']+1


f=open('ass-1.asm','r')      													#opening the file in read mode

def runm():
	while reg['halt']==False:													#To stop the program when there is an interrupt
		i=reg['pc']							
		op=globals()[memory[i][0]]												#getting the name of the function to execute 
		op(memory[i][1:])														#Calling the function
	
		reg['timer']=reg['timer']-1
		if reg['interrupt'] == 1 or reg['timer'] == 0:
			reg['stack pointer'] = reg['stack pointer'] + 1						#Incrementing the stack pointer "It works like TOP in stack data structure"
			memory[reg['stack pointer']] = reg['pc']							#sets the stack pointer to point to the current line which is yet to be executed
			reg['pc'] = reg['ivec']												#setting the pc to interrupt vector to handle the interrupt by going to that location in the memory
			reg['interrupt'] = 0												#setting the interrupt to 0 
	   
	
	
for l in f: 
	if l.startswith("#"): 														#to stop the programme from reading a comment
		continue

	comm= l.split()
	if comm: 																	#if the comm has a value of any type
		memory[int(comm[0])] = comm[1:]	 										#Assigns to the memory with the given location in the file

runm()
	
print (reg)
print (memory[0:5])
f.close()

