import RPi.GPIO as GPIO
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(16, GPIO.OUT)  # Relay control pin as output
#GPIO.setup(INPUT_PIN, GPIO.IN)   # Input pin to read the sensor/button

# Start with the relay OFF (active-low, so set HIGH)
while True:
    GPIO.output(16, GPIO.HIGH)
