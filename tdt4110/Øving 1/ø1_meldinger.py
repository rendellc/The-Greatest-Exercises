#logg funksjon lager innlegget med variablene
#main funksjon inneholder alle variablene

#global variabel, brukes til å telle i logg
count=0

        #a og b, fjern "c" før bruk
        #def logg(t,navn,mld):
        #    print("Klokken ",t," sendte ",navn,\
        #    " foelgende melding: ",'"',mld,'"',sep='')

#c, fjern "a og b" før bruk
def logg(t,navn,mld):
    global count
    count=count+1
    print("Msg ",count,",",t," ",navn," sendte foelgende melding: ",\
          '"',mld,'"',sep='')

#definerer variablene, linje 1
def main():
    #linje 1
    t="23:59"
    navn="Mr. Y."
    mld="Har du mottatt pakken?"
    logg(t,navn,mld)
    #linje 2
    t="0:00"
    navn="Mdm. Evil."
    mld="Ja. Pakken er mottatt."
    logg(t,navn,mld)
    #linje 3
    t="0:03"
    navn="Dr. Horrible"
    mld="All you need is love!"
    logg(t,navn,mld)
    #linje 4
    t="0:09"
    navn="Mr. Y"
    mld="Dr. Horrible, Dr. Horrible , calling Dr. Horrible ."
    logg(t,navn,mld)
    #linje 5
    t="0:09"
    navn="Mr. Y"
    mld="Dr. Horrible, Dr. Horrible wake up now."
    logg(t,navn,mld)
    #linje 6
    t="0:09"
    navn="Dr. Horrible"
    mld="Up now"
    logg(t,navn,mld)

main()
