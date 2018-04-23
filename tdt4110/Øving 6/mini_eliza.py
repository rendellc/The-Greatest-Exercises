import random

def pick_sentence(sentences):
  return sentences[random.randint(0, len(sentences)-1)]
 
def print_sentence(string1, string2, string3):
  print(string1, ' ', string2, string3, sep='')

def intro_text():
  print("\n"*20)
  print("Hei, jeg heter ELiza og vil gjerne snakke med deg.")
  print("Ikke start svar med stor bokstav og bruk hele setninger.")
  print("Skriv 'hade' hvis du vil avslutte samtalen")
  print('\n')

def main():
  # Initialisering av variabler
  answer = "ikke hade" # Sørger for at while-løkka kjører første gang
 
  # En liste av spørsmål
  questions = ['Hva gjør du', 'Hvordan går det', 'Hvorfor heter du',
              'Liker du å hete', 'Føler du deg bra', 'Hva har du gjort idag',
              'Hva tenker du om framtida', 'Hva gjør deg glad', 'Hva gjør deg trist']
 
  # En liste av oppfølgningsspørsmål
  follow_ups = ['Hvorfor sier du', 'Hva mener du med', 'Hvor lenge har du sagt',
               'Hvilke tanker har du om', 'Kan du si litt mer om',
               'Når tenkte du første gang på']
 
  # En liste av responser
  responses = ['Fint du sier det', 'Det skjønner jeg godt', 'Så dumt da', 'Føler meg også sånn',
              'Blir trist av det du sier', 'Så bra', 'Du er jammen frekk']
 
  # Skriv velkomsttekst til konsoll vha funksjonen intro_text
  intro_text()
 
  # Spør brukeren om navnet og lagre svaret i en variabel
  navn = input("Hva heter du? ")
 
  # Programmet kjører i løkke helt til brukeren svarer "hade"
  while answer != "hade":
    print_sentence(pick_sentence(questions), navn, "?")
    answer = input("Svar: ")
    print_sentence(pick_sentence(follow_ups), answer, "?")
    input('Svar: ')
    print_sentence(pick_sentence(responses), navn, ".")

main()