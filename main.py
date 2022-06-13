# Import the required libraries
from tkinter import *
from tkinter import ttk, messagebox
from click import command
from pystray import MenuItem as item
from PIL import Image
import pystray, serial, pyautogui, multiprocessing
import serial.tools.list_ports

serialPort = None
serialPorts = serial.tools.list_ports.comports()

serialPortInput = ''
serialPortOut = '[DECODE]'
programModeOut = '[MODE]'

def listenSerialPort():
    print ("Listining serial port")
    while True:
        try:
            serialPortInput = serialPort.readline().decode('ascii')
            if(serialPortInput):
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

# Create an instance of tkinter frame or window
win=Tk()
# Title windown
win.title("Modern Enigma Machine")
# Set the size of the window
win.geometry("720x360")
# não pode fazer o resize da tela
win.resizable(False,False)

# select da porta do arduino
selectSerialPort = ttk.Combobox(win, values=serialPorts)
selectSerialPort.place ( relx = 0.02, rely = 0.05, width = 250, height = 20)
selectSerialPort.current(0)

def callbackFunc(event):
    connectSerialPort()

selectSerialPort.bind("<<ComboboxSelected>>", callbackFunc)

# select da modo do programa
programMode = ttk.Combobox(win, values=['Normal Keyboard','encrypt','decrypt'])
programMode.place ( relx = 0.4, rely = 0.05, width = 250, height = 20)
programMode.current(0)

def callbackFunctionMode(event):
    if programMode.get() == 'Normal Keyboard':
        sendToSerial(programModeOut+str(0))
    elif programMode.get() == 'Encrypt':
        sendToSerial(programModeOut+str(1))
    elif programMode.get() == 'Decrypt':
        sendToSerial(programModeOut+str(2))
        

programMode.bind("<<ComboboxSelected>>", callbackFunctionMode)


# text para mandar para o arduino
textBox = Text(win,height = 15, width = 86)
textBox.place(relx = 0.02, rely = 0.15)

# botão de enviar o texto da caixa para o Arduino
def sendTextToSerial():
    sendToSerial(serialPortOut + textBox.get('1.0', END))

buttonSend = Button(win, text = 'Send', command= sendTextToSerial)
buttonSend.place ( relx = 0.02, rely = 0.9, width = 695, height = 30)

def sendToSerial(message):
    serialPort.write(message.encode())

# Define a function for quit the window
def quit_window(icon):
    global startThreading
    if startThreading.is_alive():
        startThreading.terminate()

    icon.stop()
    win.destroy()

# Define a function to show the window again
def show_window(icon):
   icon.stop()
   win.after(0,win.deiconify())

# Hide the window and show on the system taskbar
def hide_window():
   win.withdraw()
   image=Image.open("hidden.ico")
   menu=(item('Quit', quit_window), item('Send text to decrypt', show_window))
   icon=pystray.Icon("hidden", image, "Enigma Machine", menu)
   icon.run()

win.protocol('WM_DELETE_WINDOW', hide_window)

def connectSerialPort():
    try:
        global serialPort
        serialPort = serial.Serial(selectSerialPort.get().split('-')[0].strip(), 115200, timeout = 1) # ttyACM1 for Arduino board
    except FileNotFoundError as error:
        messagebox.showerror("Error", error)

connectSerialPort()
startThreading = multiprocessing.Process(target=listenSerialPort)
startThreading.start()

win.mainloop()