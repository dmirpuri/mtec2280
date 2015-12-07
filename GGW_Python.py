import serial
import random
import string
import time
from threading import Timer
ser = serial.Serial("/dev/cu.usbmodemFA131") # 0-based index; uses COM Port1
print("\033c")
def main():

	print("Welcome to Glitch Gone Wild")
	while (True):
		
		time.sleep(1)
		command = "1" + "\n"
		command = command.encode()
		ser.write(command)
		
		computerRandom2 = secretWordChoice(10)
		print(computerRandom2)
	
		timeout = 10
	
		t = Timer(timeout, print, ["\n" + "Sorry, time's up!!" + "\n" + "Press Enter to Continue"])
		t.start()
		userInput2 = userWord()
		t.cancel()
		print(userInput2)

		# print(type(userInput2))
		# print(type(computerRandom2))
		print(compareString(computerRandom2, userInput2))
		print("\033c")
	
		
	


def secretWordChoice(combinations):
	directions = 'UDLR'
	computerRandom = ''.join(random.choice(directions) for x in range(combinations))
	# print(type(computerRandom))
	return computerRandom

	
#print (secretWordChoice(10))


def userWord():
	userInput = input("Match it: ")
	print("evaluating......")
	time.sleep(.5)
	userInput = userInput[0:10]
	userInput = userInput.upper()

	convertFrom = "WASD"
	convertTo = "ULDR"
	converted = ''.maketrans(convertFrom, convertTo)

	userInput = userInput.translate(converted)
	return userInput


#print (userWord())

def compareString(string1, string2):
	if string1 == string2:
		print("Correct")
		c = "2" + "\n"
		c = c.encode()
		ser.write(c)

		time.sleep(5)
	
	else:

		print("Incorrect")
		w = "3" + "\n"
		w = w.encode()
		ser.write(w)
		time.sleep(5)
		
	

main()
ser.close()