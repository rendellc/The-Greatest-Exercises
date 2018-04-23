#pragma once
#include <memory>


struct Engine {
	int RPM; // revolutions per minute
};

class Car {
private:
	std::unique_ptr<Engine[]> engine;
	size_t numberOfEngines;

public:
	Car(int engineRPM, size_t number) 
		: numberOfEngines( number )
		, engine( std::make_unique<Engine[]>(number) )
	{
		for (size_t i = 0; i < numberOfEngines; ++i) {
			this->engine[i].RPM = engineRPM;
		}
	}
	/*  b) trenger ikke en destruktør fordi når alle cars som peker til engine går
		   ut av scope vil engine bli frigjort
	*/

	/*     engine-pekerene vil peke til samme minnelokasjon
		   hvis vi ønsker at de ikke skal peke til samme lokasjon bør
		   vi heller bruke unique_ptr siden da er det klart hvem som
		   har ansvar over minnet. 
	*/

	/*	c) den vil slettes i slutten av main
	*/
};