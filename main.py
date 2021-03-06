# Import the required libraries
from tkinter import *
from tkinter import ttk
from pystray import MenuItem as item
from PIL import Image
import pystray, multiprocessing

from Arduino import Arduino

arduino = Arduino()


class Application():

    def __init__(self):
        self.root = Tk()
        self.screen()
        self.inputs()
        self.buttons()
        self.initListener()
        self.root.protocol('WM_DELETE_WINDOW', self.hide_window)
        self.root.mainloop()

    def screen(self):
        self.root.title("Modern Enigma Machine")
        self.root.geometry("720x360")
        self.root.resizable(False, False)

    def buttons(self):
        # select arduino port
        self.selectSerialPort = ttk.Combobox(self.root,
                                             values=arduino.serialPorts)
        self.selectSerialPort.place(relx=0.02, rely=0.05, width=250, height=20)
        self.selectSerialPort.current(0)
        self.selectSerialPort.bind(
            "<<ComboboxSelected>>",
            self.callbackFunctionPort(self.selectSerialPort.get()))

        # select the mode
        self.programModeButton = ttk.Combobox(self.root,
                                              values=arduino.programModes)
        self.programModeButton.place(relx=0.4, rely=0.05, width=250, height=20)
        self.programModeButton.current(0)
        self.programModeButton.bind("<<ComboboxSelected>>",
                                    self.callbackFunctionMode)

        # button
        self.buttonSend = Button(
            self.root,
            text='Send',
            command=self.callbackFunctionSendTextToDecrypt)
        self.buttonSend.place(relx=0.02, rely=0.9, width=695, height=30)

    # input text to send to Arduino
    def inputs(self):
        self.textBox = Text(self.root, height=15, width=86)
        self.textBox.place(relx=0.02, rely=0.15)

    def callbackFunctionPort(self, port):
        arduino.connectSerialPort(port)

    def callbackFunctionMode(self, event):
        mode = self.programModeButton.get()
        if mode == arduino.programModes[0]:
            arduino.sendModeToSerial(str(0))
        elif mode == arduino.programModes[1]:
            arduino.sendModeToSerial(str(1))
        elif mode == arduino.programModes[2]:
            arduino.sendModeToSerial(str(2))

    def callbackFunctionSendTextToDecrypt(self):
        arduino.sendTextToDecryptSerial(self.textBox.get('1.0', END))

    # function for quit the window
    def quit_window(self, icon):
        if self.startThreading.is_alive():
            self.startThreading.terminate()

        icon.stop()
        self.root.destroy()

    # show the window again
    def show_window(self, icon):
        icon.stop()
        self.root.after(0, self.root.deiconify())

    # Hide the window and show on the system taskbar
    def hide_window(self):
        self.root.withdraw()
        image = Image.open("hidden.ico")
        menu = (item('Quit', self.quit_window), item('Open', self.show_window))
        icon = pystray.Icon("hidden", image, "Enigma Machine", menu)
        icon.run()

    def initListener(self):
        arduino.connectSerialPort(self.selectSerialPort.get())
        self.startThreading = multiprocessing.Process(
            target=arduino.listenSerialPort)
        self.startThreading.start()


Application()