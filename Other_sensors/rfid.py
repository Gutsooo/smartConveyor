import RPi.GPIO as GPIO
from mfrc522 import SimpleMFRC522

reader = SimpleMFRC522()
#GPIO.cleanup()

while True:
    try:
            print(4)
            id, text = reader.read()
            print(id)
            print(5)
    finally:
            GPIO.cleanup()
