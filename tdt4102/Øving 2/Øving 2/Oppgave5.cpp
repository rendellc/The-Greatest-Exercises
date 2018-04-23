#include <iostream>

double paymentCalc(double totalLoan, double remainingLoan, const double rent, const int nrOfDeductions)
{
	return totalLoan / nrOfDeductions + (rent / 100) * remainingLoan;
}

void calculateLoanPayments() 
{	
	// **** innstillinger (konstanter) ****
	const int YEARS = 10;	//totalt antall år som programmet skal regne ut
	const int NR_OF_DEDUCTIONS = 10;	// antall innbetalinger, 1 per år

	// variabeldeklarasjon
	double rent = 0;		//rente, hentes fra bruker
	double totalLoan = 0;	//totalt lånebeløp, hentes fra bruker
	double remainingLoan = 0; //resterende lånebeløp
	double payment = 0;		//hvor mye som innbetales hvert år
	
	
	// henter input fra bruker
	std::cout << "Totalt lånebeløp: ";
	std::cin >> totalLoan;
	std::cout << "Rente (prosent): ";
	std::cin >> rent;
	std::cout << std::endl << std::endl;

	
	// skriver ut og formaterer
	std::cout << "År\t\tInnbetaling\tGjenstående lån" << std::endl;

	remainingLoan = totalLoan; // "initialiserer" remainingLoan (før nedbetalinger begynner)

	for (int year = 0; year < YEARS; year++) {
		payment = paymentCalc(totalLoan, remainingLoan, rent, NR_OF_DEDUCTIONS);
		
		if (payment <= remainingLoan) {
			remainingLoan -= payment;
		}
		else {
			payment = remainingLoan; // siste betaling
			remainingLoan = 0;
		}

		std::cout << year << "\t\t" << payment << "\t\t" << remainingLoan << std::endl;
	}
}