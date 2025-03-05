import serial
import time

# Configure the serial port
ser = serial.Serial(
    port='/dev/ttyS0',  # Replace with your serial port
    baudrate=9600,
    timeout=1
)

def send_command(command, data):
    full_command = f"{command}{data}\n"
    ser.write(full_command.encode())
    print(f"Sent: {full_command}")

def main():
    try:
        while True:
            # Example commands to send
            send_command('x', 0)  # Set rotation to counter clockwise
            time.sleep(2)
            send_command('x', 1)  # Set rotation to clockwise
            time.sleep(2)
            send_command('U', 100)  # Float up with 100 steps
            time.sleep(2)
            send_command('D', 100)  # Float down with 100 steps
            time.sleep(2)
            send_command('d', 500)  # Set motor speed to 500
            time.sleep(2)
            send_command('!', 0)  # Emergency stop
            time.sleep(2)
    except KeyboardInterrupt:
        print("Program interrupted")
    finally:
        ser.close()

if __name__ == "__main__":
    main()