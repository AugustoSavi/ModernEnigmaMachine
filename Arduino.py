import serial, pyautogui
import serial.tools.list_ports
from tkinter import messagebox

class Arduino:
    def __init__(self):
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
            self.serialPort = serial.Serial(port.split('-')[0].strip(), 115200, timeout=1)
        except FileNotFoundError as error:
            messagebox.showerror("Error", error)

    # listening the serial port
    def listenSerialPort(self):
        while True:
            try:
                self.serialPortInput += self.serialPort.readline().decode('ascii')
                if len(self.serialPortInput):
                    self.serialPortInput = self.verifyString()
            except KeyboardInterrupt:
                break
            except serial.serialutil.SerialException:
                pyautogui.alert('Arduino desconectado')

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
        while self.serialPortInput:
            for key in self.keysAccepts:
                if self.serialPortInput.find(key) == 0:
                    keyFormated = key.replace("[", "").replace("]", "").lower()
                    pyautogui.press(keyFormated)
                    self.serialPortInput = self.serialPortInput[len(key):]
                    break
            else:
                break
        
        if self.serialPortInput:
            pyautogui.write(self.serialPortInput)
            self.serialPortInput = ''
        
        return self.serialPortInput
