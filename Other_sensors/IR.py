import RPi.GPIO as IO
import time
IO.setwarnings(False)
IO.setmode (IO.BCM)
IO.setup(16,IO.OUT)
IO.setup(21,IO.IN)
flag=0
print(flag)
while True:

    print(flag)

    if(IO.input(21)==0 and flag==0):
        IO.output(16,False)
        print("convoyer off")
        flag=1
        time.sleep(4)
        IO.output(16,True)
        print("convoyer on")
        if(IO.input(21)==1):
            flag=0
            
            
    if(IO.input(21)==1):
        IO.output(16,True)
        print("convoyer on")
        flag=0
