import serial
import pyautogui

ser = serial.Serial('/dev/ttyUSB1', 115200, timeout = 1) # ttyACM1 for Arduino board

readOut = ''

print ("Starting up")
commandToSend = '[DECODE]'

while True:
    try:
        readOut = ser.readline().decode('ascii')
        if(readOut):
            # print(readOut)
            if readOut == "[ESC]":
                pyautogui.press('esc')
            elif readOut == "[PgDn]":
                pyautogui.press('pgdn')
            elif readOut == "[PgUp]":
                pyautogui.press('pgup')
            elif readOut == "[Left]":
                pyautogui.press('left')
            elif readOut == "[Right]":
                pyautogui.press('right')
            elif readOut == "[Up]":
                pyautogui.press('up')
            elif readOut == "[Down]":
                pyautogui.press('down')
            elif readOut == "[Del]":
                pyautogui.press('backspace')
            else:
                pyautogui.write(readOut)
    except:
        pass
    # ser.flush()