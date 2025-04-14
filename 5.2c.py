import tkinter as tk
from tkinter import ttk
import RPi.GPIO as GPIO

# GPIO Setup
GPIO.setmode(GPIO.BCM)
LED_PINS = {'Red': 17, 'Green': 27, 'Blue': 22}
PWM_FREQ = 100
pwms = {}

# Set up LEDs and PWM
for color, pin in LED_PINS.items():
    GPIO.setup(pin, GPIO.OUT)
    pwm = GPIO.PWM(pin, PWM_FREQ)
    pwm.start(0)  # Start with LED off
    pwms[color] = pwm

# Function to update brightness
def update_brightness(color):
    def _update(val):
        duty = int(float(val))  # Convert string to float then int
        pwms[color].ChangeDutyCycle(duty)
    return _update

# GUI Setup
root = tk.Tk()
root.title("LED Brightness Control")
root.geometry("300x300")

for color in LED_PINS:
    frame = tk.Frame(root)
    frame.pack(pady=10)

    label = tk.Label(frame, text=f"{color} LED Intensity")
    label.pack()

    slider = ttk.Scale(frame, from_=0, to=100, orient='horizontal',
                       command=update_brightness(color))
    slider.set(0)
    slider.pack()

# Graceful exit
def on_close():
    for pwm in pwms.values():
        pwm.stop()
    GPIO.cleanup()
    root.destroy()

# Exit button
exit_button = tk.Button(root, text="Exit", command=on_close)
exit_button.pack(pady=20)

root.protocol("WM_DELETE_WINDOW", on_close)
root.mainloop(