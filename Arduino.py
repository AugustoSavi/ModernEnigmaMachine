import pyautogui, serial, pyautogui
import serial.tools.list_ports
from tkinter import messagebox

class Arduino:

    def __init__(self):
        self.serial = serial
        self.serialPort = None
        self.serialPorts = self.getSerialPorts()
        self.serialPortInput = ''
        self.programModes = ['Normal Keyboard', 'encrypt', 'decrypt']
        self.keysAccepts = ["[ESC]", "[Enter]", "[PgDn]", "[PgUp]", "[Left]", "[Right]", "[Up]", "[Down]", "[Backspace]","[Tab]"]

    # get list of serial ports
    def getSerialPorts(self):
        return serial.tools.list_ports.comports()

    # connect with the serial port
    def connectSerialPort(self, port):
        try:
            self.serialPort = self.serial.Serial(
                port.split('-')[0].strip()
                , 115200
                , timeout=1
            )  # ttyACM1 for Arduino board
        except FileNotFoundError as error:
            messagebox.showerror("Error", error)

    # listening the serial port
    def listenSerialPort(self):
        print("Listining serial port")
        while True:
            try:
                self.serialPortInput += self.serialPort.readline().decode('ascii')
                if len(self.serialPortInput):
                    self.serialPortInput = self.verifyString()
            except:
                pass
            # serialPort.flush()

    # send text to decode in arduino
    def sendTextToDecryptSerial(self, message):
        self.sendToSerial('[DECODE]' + message)

    # send text to arduino
    def sendToSerial(self, message):
        self.serialPort.write(message.encode())

    # send mode to arduino
    def sendModeToSerial(self, message):
        self.sendToSerial('[MODE]' + message)

    # works with the string that arrives from the serial
    def verifyString(self):
        for key in self.keysAccepts:
            if self.serialPortInput.find(key) == 0:
                keyFormated = key.replace("[", "").replace("]", "").lower()
                pyautogui.press(keyFormated)
                self.serialPortInput = self.serialPortInput[len(key): len(self.serialPortInput)]
                if(len(self.serialPortInput)):
                    self.verifyString()

        if(len(self.serialPortInput)):
            pyautogui.write(self.serialPortInput)
        
        return ''