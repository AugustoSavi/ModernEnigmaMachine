import pyautogui, serial, pyautogui, multiprocessing
import serial.tools.list_ports
from tkinter import messagebox



class Arduino:

    def __init__(self):
        self.serial = serial
        self.serialPort = None
        self.serialPorts = self.getSerialPorts()
        self.programModes = ['Normal Keyboard', 'encrypt', 'decrypt']

    def getSerialPorts(self):
        return serial.tools.list_ports.comports()

    def connectSerialPort(self, port):
        try:
            self.serialPort = self.serial.Serial(
                port.split('-')[0].strip(), 115200,
                timeout=1)  # ttyACM1 for Arduino board
        except FileNotFoundError as error:
            messagebox.showerror("Error", error)

    def listenSerialPort(self):
        print("Listining serial port")
        while True:
            try:
                serialPortInput = self.serialPort.readline().decode(
                    'ascii')
                if (serialPortInput):
                    # print(serialPortInput)
                    if serialPortInput == "[ESC]":
                        pyautogui.press('esc')
                    elif serialPortInput == "[Enter]":
                        pyautogui.press('enter')
                    elif serialPortInput == "[PgDn]":
                        pyautogui.press('pgdn')
                    elif serialPortInput == "[PgUp]":
                        pyautogui.press('pgup')
                    elif serialPortInput == "[Left]":
                        pyautogui.press('left')
                    elif serialPortInput == "[Right]":
                        pyautogui.press('right')
                    elif serialPortInput == "[Up]":
                        pyautogui.press('up')
                    elif serialPortInput == "[Down]":
                        pyautogui.press('down')
                    elif serialPortInput == "[Del]":
                        pyautogui.press('backspace')
                    else:
                        pyautogui.write(serialPortInput)
            except:
                pass
            # serialPort.flush()

    # botão de enviar o texto da caixa para o Arduino descriptografar
    def sendTextToDecryptSerial(self, message):
        self.sendToSerial('[DECODE]' + message)

    def sendToSerial(self, message):
        self.serialPort.write(message.encode())

    def sendModeToSerial(self, message):
        self.sendToSerial('[MODE]' + message)