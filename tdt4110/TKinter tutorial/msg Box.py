from tkinter import *
import tkinter.messagebox

root = Tk()

tkinter.messagebox.showinfo('Window Title', 'blurb')

answer = tkinter.messagebox.askquestion('Question','You are stupid')

print(answer)

if answer != 'yes':
    print(':(') 

root.mainloop()
