# lagrer til fil
    # ha mange brett i en fil
    # samme formatering som her http://pythonsudoku.sourceforge.net/sudokus/0/2009-04-13.sdk

# henter fra fil
    # spør om lokasjon til fil (kun filnavn hvis den er i sammen folder)
    # bruk windows explorer, 'filedialog' modul i python

# lager nytt sudoku-brett
    # shuffle et eksisterende brett

# sudoku, rekkefølge
    # forutsetter at brettet allerede er der halvveis fylt inn
    # 1. spør hva bruker vil gjøre, (slett eller skriv inn)
        # kjører funksjonen som bruker ønsker
    # 2. printer brettet
    # 3. sjekker brettet
        # hvis ferdig hopp til 5.
    # 4. gå tilbake til 1. 
    # 5. gratuler bruker

#********************************************************************************************************

from tkinter import *

EMPTY_CELL = 0
NUMBER_FONT = ('Helvetica', 8)

class SudokuGUI:

    #colorScheme = [LYSEST, LYS, MIDDEL, STERK, STERKEST]
    activeCell = [0, 0, 0, 0, 0] # [tall, grid_row_index, grid_col_index, row_index, col_index]

    def __init__(self, master, brett):

        self.color_selector()

        masterFrame = Frame(master, bg=self.colorScheme[0])
        sudokuFrame = Frame(masterFrame, bg=self.colorScheme[4], relief=SUNKEN)
        userinputFrame = Frame(master)
        #lager 3x3 grid med kvadratFrame
        kvadratFrameList = [[Frame(sudokuFrame, bd=0.5, bg=self.colorScheme[4], relief=SUNKEN) for _ in range(3)] for __ in range(3)]
        
        self.numberFrameList =  [[[[Frame(kvadratFrame) for col in range(3)] for row in range(3)] \
                                for kvadratFrame in kvadratFrame_Row] for kvadratFrame_Row in kvadratFrameList] #3^2*3^2 liste med frames

        
        # *** Sudokubrettet ***
        for grid_row_index in range(3): # range(len(brett))
            grid_row = brett[grid_row_index]
            for kvadrat_index in range(3):          # range(len(grid_row))
                kvadrat = grid_row[kvadrat_index].grid
                kvadratFrame = kvadratFrameList[grid_row_index][kvadrat_index]
                kvadratFrame.grid(row=grid_row_index, column=kvadrat_index) #, padx=1, pady=1
                for row_index in range(3):          # range(len(kvadrat))
                    row = kvadrat[row_index]
                    for number_index in range(3):   # range(len(row))
                        number = row[number_index]
                        numberFrame = self.numberFrameList[grid_row_index][kvadrat_index][row_index][number_index]
                        if number == 0: 
                            number='  '

                        # *** Farger, formatering, knapper og kommandoer til knapper ***
                        if (row_index+number_index)%2 == 0 and (grid_row_index+kvadrat_index)%2 == 0: # hjørne og midt-kvadrat/grid
                            self.numberButton = Button(numberFrame, \
                                text=number, bg=self.colorScheme[2], font=NUMBER_FONT, relief=FLAT, \
                                 command=lambda event='<Button-1>', tall=number, grid_row_index=grid_row_index, kvadrat_index=kvadrat_index, \
                                 row_index=row_index, number_index=number_index: self.numButtonPress(event, tall, grid_row_index, kvadrat_index,\
                                  row_index, number_index)).pack()
                        elif (row_index+number_index) % 2 == 0:     
                            self.numberButton = Button(numberFrame,\
                                text=number, bg=self.colorScheme[3], font=NUMBER_FONT, relief=FLAT, \
                                 command=lambda event='<Button-1>', tall=number, grid_row_index=grid_row_index, kvadrat_index=kvadrat_index, \
                                 row_index=row_index, number_index=number_index: self.numButtonPress(event, tall, grid_row_index, kvadrat_index,\
                                  row_index, number_index)).pack()
                        elif (row_index+number_index) % 2 != 0 and (grid_row_index+kvadrat_index)%2 != 0:
                            self.numberButton = Button(numberFrame, \
                                text=number, bg=self.colorScheme[2], font=NUMBER_FONT, relief=FLAT, \
                                 command=lambda event='<Button-1>', tall=number, grid_row_index=grid_row_index, kvadrat_index=kvadrat_index, \
                                 row_index=row_index, number_index=number_index: self.numButtonPress(event, tall, grid_row_index, kvadrat_index,\
                                  row_index, number_index)).pack()
                        else:
                            self.numberButton = Button(numberFrame,\
                                text=number, bg=self.colorScheme[1], font=NUMBER_FONT, relief=FLAT, \
                                 command=lambda event='<Button-1>', tall=number, grid_row_index=grid_row_index, kvadrat_index=kvadrat_index, \
                                 row_index=row_index, number_index=number_index:  self.numButtonPress(event, tall, grid_row_index, kvadrat_index\
                                    , row_index, number_index)).pack()

                        numberFrame.grid(row=row_index, column=number_index)
        
        sudokuFrame.config(cursor='target')
        sudokuFrame.pack(side=LEFT, padx=30)

        # *** Main Menu ***
        mainMenu = Menu(master)
        master.config(menu=mainMenu)

        fileMenu = Menu(mainMenu)
        mainMenu.add_cascade(label='File', menu=fileMenu)
        fileMenu.add_command(label='Save Progress', command=lambda brett=brett: game.save_sudoku_to_file(brett)) #må ta inn filnavn fra bruker
        fileMenu.add_separator()
        fileMenu.add_command(label='Exit Game', command=master.quit) #burde spørre om å lagre først

        settingsMenu = Menu(mainMenu)
        colorMenu = Menu(settingsMenu)
        mainMenu.add_cascade(label='Settings', menu=settingsMenu)
        settingsMenu.add_cascade(label='Color Scheme', menu=colorMenu) #legg til command
        colorMenu.add_command(label='Blue (default)', command=self.color_selector)
        colorMenu.add_command(label='Red', command=lambda color='Red': self.color_selector(color))
        colorMenu.add_command(label='Green Camo', command=lambda color='Green Camo': self.color_selector(color))

        # *** Status Bar ***
        self.percent = StringVar()
        self.percent.set(self.percent_complete(brett))

        status = Label(master, textvariable='Brettet er ' + self.percent.get() + '% fullført' , \
                        bd=1, relief=SUNKEN, anchor=W).pack(side=BOTTOM, fill=X)

        # *** Knapper ***
        inputFrame = Frame(masterFrame)
        initNumber = StringVar(master=inputFrame)
        initNumber.set(self.activeCell[0])
        self.numEntry = Entry(inputFrame, width=5)
        self.numEntry.insert(0, initNumber.get())
        addButton = Button(inputFrame, text = 'Add', command=lambda master=master: self.addNumberButton(master))
        self.numEntry.grid(row=0, column=0, padx=0, sticky=E)
        addButton.grid(row=0, column=1)
        inputFrame.pack(side=RIGHT)

        masterFrame.pack()

    def numButtonPress(self, event, tall, grid_row_index, kvadrat_index, row_index, number_index):
        # når knapp (tall) på brett trykkes skal følgende skje:
            # activeCell skal oppdateres til å svare til den ruten - OK
            # entryboxen skal oppdateres slik at det viser riktig tall -OK
            # cursor skal flyttes til entryboxen
            # endre farge på knappen slik at det er tydelig hvilken knapp som er presset ned - OK

        # fjerner forrige utheving
        numberFrame = self.numberFrameList[self.activeCell[1]][self.activeCell[2]][self.activeCell[3]][self.activeCell[4]]
        numberButton = numberFrame.winfo_children()[0] #kun én item i frame
        numberButton.config(relief=FLAT)
        # oppdaterer uthveing
        numberFrame = self.numberFrameList[grid_row_index][kvadrat_index][row_index][number_index]
        numberButton = numberFrame.winfo_children()[0] #kun én item i frame
        numberButton.config(relief=SUNKEN)

        self.activeCell = (tall, grid_row_index, kvadrat_index, row_index, number_index)
        
        # oppdater tall i entryboxen
        self.numEntry.delete(0, END)
        self.numEntry.insert(0, tall)

    def addNumberButton(self, master):
        try:
            tall = int(self.numEntry.get())
        except ValueError:
            print('Ugyldig input')
            print('Må være et heltall mellom 0 og 9, 0 betyr slett')
            return None
        
        grid_row_index, grid_col_index, row_index, col_index = self.activeCell[1], self.activeCell[2], self.activeCell[3], self.activeCell[4]

        row, col = 3*grid_row_index+row_index+1, 3*grid_col_index+col_index+1 #gjør det om til 1-til-9 koordinater

        if tall in [1,2,3,4,5,6,7,8,9]: #sjekker gyldig inputt
            game.write_to_board(brett, row, col, tall)
            numberFrame = self.numberFrameList[grid_row_index][grid_col_index][row_index][col_index]
            numberButton = numberFrame.winfo_children()[0] #kun én item i frame
            numberButton.config(text=tall)

        elif tall == 0:
            game.delete_from_board(brett, row, col)

            # oppdaterer knappteksten
            numberFrame = self.numberFrameList[grid_row_index][grid_col_index][row_index][col_index]
            numberButton = numberFrame.winfo_children()[0]
            numberButton.config(text='  ')
        else:
            print('ugyldig input... \nMå være et heltall mellom 0 og 9')

        # fjerner utheving av knapp
        numberButton.config(relief=FLAT)

        # oppdaterer status bar
        self.percent.set(self.percent_complete(brett))

        # sjekker om brettet er fullført
        if game.complete_check(brett):
                print('Wow! Bra jobba')
                print('Lagrer filen nå')
                game.save_sudoku_to_file(brett)
                root.destroy()

    def percent_complete(self, brett):
        antall = 0
        for grid_row in brett:
            for kvadrat in grid_row:
                for row in kvadrat.grid:
                    for number in row:
                        if number in [1,2,3,4,5,6,7,8,9]:
                            antall += 1
        return str(round(100*antall/81, 0))

    def color_selector(self, color='Blue'):

        blue = ['#E5F2FF', '#BEDEFF', '#82C1FF', '#3399FF', '#002C58']
        red = ['#FFE5E5', '#FFB3B3', '#FF8080', '#FF6666', '#FF4D4D']
        green_camo = ['#B8B894', '#A3A375', '#999966', '#97974C', '#B0763B']

        if color == 'Blue':
            self.colorScheme = blue
        elif color == 'Red':
            self.colorScheme = red
            print('red')
        elif color == 'Green Camo':
            self.colorScheme = green_camo

class Kvadrat:

    def __init__(self):
        self.grid = [[EMPTY_CELL,EMPTY_CELL,EMPTY_CELL],\
                    [EMPTY_CELL,EMPTY_CELL,EMPTY_CELL],\
                    [EMPTY_CELL,EMPTY_CELL,EMPTY_CELL]]
    
    def check_square(self):  # true når kvadratene er fylt med tall fra 1 til 9
        numbers = []
        for row in self.grid:
            for n in row:
                numbers.append(n)
        if len(numbers) == len(set(numbers)) and EMPTY_CELL not in numbers: #impliserer ingen kopier
            return True
        else:
            return False

    def write_to_kvadrat(self, row, col, tall, fortsett = 'nei', delete_mode=False):
        if delete_mode: #sletter
            self.grid[row][col] = EMPTY_CELL
        elif (tall>=1) and (tall<=9) and (type(tall) is int): #sjekker gyldig input, eller om vi skal slette
            if self.grid[row][col] == EMPTY_CELL or fortsett=='ja': #tom celle -> skriv inn 
                self.grid[row][col] = tall
            else:   #okkupert celle, spør bruker om å fortsette
                print(self.grid[row][col], 'er allerede der')
                fortsett = input('Slett og fortsett? (ja/nei) ') #sjekker om bruker fortsatt ønsker å skrive inn tall der
                if fortsett.lower() == 'ja':
                    self.write_to_kvadrat(row, col, tall, 'ja')
        else:
            print(tall, 'er ikke mellom 1 og 9, eller ikke heltall')

    def delete_from_kvadrat(self, row, col):
        self.write_to_kvadrat(row, col, EMPTY_CELL, delete_mode=True)

class Game:

    def konverter_koordinat(self, row, col): 
        #funksjon som tar inn koordinater x,y fra 1-9 og konverterer det til 0-2 i riktige kvadrater

        if row>=1 and row<=9 and col>=1 and col<=9 and type(col) is int and type(row) is int:   #sjekker gyldig input først
            #finner riktig kvadrat
            grid_row = (row-1)//3
            grid_col = (col-1)//3

            kvadrat = brett[grid_row][grid_col]
            #må gjøre row og col til tall mellom 0 og 2
            new_row = (row-1)%3
            new_col = (col-1)%3
            return grid_row, grid_col, new_row, new_col
        else:
            print('Ugyldige koordinater')
            print('Må være heltall mellom 1 og 9')

    def check_board_at_pos(self, brett,row,col):
        #funksjon som tar inn posisjon
        #sjekker om raden og kollonnen til den posisjonen er fullført

        grid_row, grid_col, NEW_ROW, NEW_COL = self.konverter_koordinat(row, col)
        numbers = []
        
        #sjekker kollonne
        for grid_index in range(3): #går gjennom radene med konstant kollonne
            kvadrat = brett[grid_index][grid_col]
            for row_index in range(3):
                numbers.append(kvadrat.grid[row_index][NEW_COL]) #legger til tall i kollonne til liste
        if len(set(numbers)) == len(numbers) and EMPTY_CELL not in numbers:
            kollonne_check = True
        else:
            kollonne_check = False

        #sjekker rad
        numbers = []
        if kollonne_check: #sjekker bare raden hvis kollone er riktig
            for grid_index in range(3):
                kvadrat = brett[grid_row][grid_index]
                for col_index in range(3):
                    numbers.append(kvadrat.grid[NEW_ROW][col_index])
            if len(set(numbers)) == len(numbers) and EMPTY_CELL not in numbers:
                return True #både rad og kollone er riktig
            else:
                return False #kollone riktig, men rad feil
        else:
            return False 

    def complete_check(self, brett):
        #funksjon som sjekker hele brettet
        #sjekker rader og kollonner
        for i in range(1,10):
            if not self.check_board_at_pos(brett, i,i):
                return False

        #sjekker kvadrater
        for grid_row in brett:
            for kvadrat in grid_row:
                if not kvadrat.check_square():
                    return False
        return True

    def write_to_board(self, brett, row, col, tall):
        grid_row, grid_col, new_row, new_col = self.konverter_koordinat(row,col)
        brett[grid_row][grid_col].write_to_kvadrat(new_row, new_col, tall, fortsett='ja')

    def delete_from_board(self, brett, row, col):
        grid_row, grid_col, new_row, new_col = self.konverter_koordinat(row,col)
        brett[grid_row][grid_col].delete_from_kvadrat(new_row, new_col)

    def create_board(self):
        # setter sammen Kvadrat klassen til et helt sudokubrett

        kvadrat_00 = Kvadrat()
        kvadrat_01 = Kvadrat()
        kvadrat_02 = Kvadrat()
        kvadrat_10 = Kvadrat()
        kvadrat_11 = Kvadrat()
        kvadrat_12 = Kvadrat()
        kvadrat_20 = Kvadrat()
        kvadrat_21 = Kvadrat()
        kvadrat_22 = Kvadrat()

        brett = [[kvadrat_00, kvadrat_01, kvadrat_02],\
                [kvadrat_10, kvadrat_11, kvadrat_12],\
                [kvadrat_20, kvadrat_21, kvadrat_22]]

        return brett

    def get_sudoku_from_file(self, filename, brett):
        # importerer sudoku fra fil

        try:
            with open(filename, 'r') as fil:
                line_counter = 0
                grid_counter = 0
                grid_collection = []
                grid1, grid2, grid3 = [],[],[]
                for line in fil:
                    line_counter += 1
                    if line_counter >=2 and len(line)>30:
                        grid1.append([int(line[2]), int(line[5]), int(line[8])])
                        grid2.append([int(line[13]), int(line[16]), int(line[19])])
                        grid3.append([int(line[24]), int(line[27]), int(line[30])])
                    if len(grid1) == 3:
                        grid_collection.append([grid1, grid2, grid3])
                        grid1, grid2, grid3 = [],[],[]

            #grid_collection er hele sudokubrettet. legger det inn i kvadratformatet under
            for grid_row_index in range(len(brett)):
                for kvadrat_index in range(len(brett[grid_row_index])):
                    for row in range(3):
                        for col in range(3):
                            kvadrat = brett[grid_row_index][kvadrat_index]
                            tall = grid_collection[grid_row_index][kvadrat_index][row][col]
                            if tall == 0:
                                kvadrat.delete_from_kvadrat(row, col)
                            else:
                                kvadrat.write_to_kvadrat(row, col, tall ,fortsett = 'ja')
        except FileNotFoundError:
            print('Fil ikke funnet, sjekk staving og husk extensions')

    def save_sudoku_to_file(self, brett):
        # lagrer sudoku til fil
        filename = input('Hva skal filen hete? ')

        
        with open(filename, 'w') as fil:
            fil.write(filename +'\n')
            for grid_row_index in range(3):
                for row_index in range(3): 
                    line = '' #reset line, ny linje for hver rad
                    for kvadrat_index in range(3):
                        kvadrat = brett[grid_row_index][kvadrat_index]
                        row = kvadrat.grid[row_index]
                        line += ' '*2 + str(row[0]) + ' '*2 + str(row[1]) + ' '*2 + str(row[2]) #row[col_index] gir tall
                        line += ' '*2
                    fil.write(line + '\n')
                fil.write('\n')

    def open_new_game(self, brett, old_filename='gammel fil.sdk', new_filename='ny fil.sdk'):
        #old_filename=input('Hva skal dette spillet lagres som? '), new_filename=input('Nytt spill: '))
        self.save_sudoku_to_file(old_filename, brett)
        brett = self.create_board()
        self.get_sudoku_from_file(new_filename, brett)
        return brett



# starter spillet

game = Game() #oppretter spillet

brett = game.create_board() #lager tom sudokubrett

print('Velkommen til sudoku!')
filename_get = input('Hva heter filen du vil jobbe på? ')

game.get_sudoku_from_file(filename_get, brett) # henter og legger inn lagret brett


# ***** run GUI *****

root = Tk()

root.geometry('400x300')
#game.game_logic(brett)
display = SudokuGUI(root, brett)
root.config(bg='#E5F2FF')
root.mainloop()

if complete_check(brett):
    print('Wow! Bra jobba\n\n')
else:
    print('Lykke til neste gang\n\n')