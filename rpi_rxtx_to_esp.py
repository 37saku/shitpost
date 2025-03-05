import serial
import time

# Configure the serial port
ser = serial.Serial(
    port='/dev/ttyAMA0',  # Replace with your serial port
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
            send_command('D', 100)  # Float down with 100 steps
            time.sleep(2)
    except KeyboardInterrupt:
        print("Program interrupted")
    finally:
        ser.close()

if __name__ == "__main__":
    main()
