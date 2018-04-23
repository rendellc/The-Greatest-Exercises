from tkinter import *

class ListeTest:

	def __init__(self, master, brett):
		frame = Frame(master)
		label1 = Label(frame, text=brett[0])
		label2 = Label(frame, text=brett[1])
		label3 = Label(frame, text=brett[2])

		label1.pack()
		label2.pack()
		label3.pack()
		frame.pack()


class IteratingTest:

	def __init__(self, master, listetest):
		masterFrame = Frame(master)
		layerFrame = Frame(masterFrame)

		# tester å pakke samme frame flere ganger
		for index in range(2):
			setning = listetest[index]
			for word in setning:
				label = Label(layerFrame, text=word, bg='red')
				label.pack(side=LEFT)
			layerFrame.grid(row=index)
		masterFrame.grid(row=0)




listetest = [['Dette', 'er', 'en', 'setning'], ['Dette', 'er', 'en', 'annen', 'setning']]

setninger = [[['Dette'], ['er'] ,['første'], ['kvadrat']], [['Dette'], ['er'], ['andre'], ['kvadrat']], [['Dette'], ['er'], ['tredje'], ['kvadrat']]]
		
root = Tk()
root.geometry('500x350')


#listetest = ListeTest(root, setninger)
g = IteratingTest(root, listetest)


root.mainloop()
