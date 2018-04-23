#program som sier noe om løsningene til andregradsligninger

#hent inn a,b,c fra bruker
a=float(input('Hva er a? '))
b=float(input('Hva er b? '))
c=float(input('Hva er c? '))

#regn ut d
d = b**2-4*a*c

#test de forskjellige verdiene
if (d>0):
    print("Polynomet har 2 reelle røtter")
elif (d<0):
    print("Polynomet har 2 imaginære røtter")
elif (d==0):
    print("polynomet har 1 dobbeltrot")
else:
    print("Her gikk noe galt...")
