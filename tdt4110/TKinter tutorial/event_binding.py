from tkinter import *

root = Tk()

def printName(event):
    print('Hello world')
def printName2(event):
    print('asdkln')

button_1 = Button(root, text='Print text')
button_1.bind('<Button-1>', printName) #venstreklikk
button_1.bind('<Button-3>', printName2) #høyreklikk
button_1.pack()

button_1.pack()
root.mainloop()
