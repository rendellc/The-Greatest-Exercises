def main():
    print("Et program for å regne ut nettopris på bil")
    #får informasjon om bilen
    bil_navn = input("Bilnavn: ")
    brutto = int(input("Bruttopris [kr]: "))
    vekt = int(input("Vekt [kg]: "))
    hk = int(input("Antall hestekrefter [hk]: "))
    co2 = int(input("CO2 utslipp [antall gram]: "))
    volum = float(input("Motorvolum [liter]: "))

    
    beregn_avgift(bil_navn, brutto, vekt, hk, co2, volum)
    
    
def beregn_avgift(bil_navn, brutto, vekt, hk, co2, volum):
    #beregn nettopris
    vekt_p = brutto*vekt*0.00034
    hk_p = brutto*hk*0.00015
    co2_p = brutto*co2*0.004
    volum_p = brutto*volum*0.00055
    netto = brutto+vekt_p+hk_p+co2_p+volum_p
    
    #skriver ut netto til skjerm
    print("Utsalgspris på", bil_navn, "vil bli", netto, "kr.")

main()
