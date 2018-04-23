from tkinter import *


class Knapper:

    def __init__(self, master):
        frame = Frame(master)
        frame.pack()

        self.printButton = Button(frame, text='Print Message',\
                                  command=self.printMessage)
        self.printButton.pack(side=LEFT)

        self.quitButton = Button(frame, text='Quit Button', \
                                 command=frame.quit)
        self.quitButton.pack(side=LEFT)

    def printMessage(self):
        print('Will this work?')
        print('Yes, it will')



root = Tk()

b = Knapper(root)

root.mainloop()
