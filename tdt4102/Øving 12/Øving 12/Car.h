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
	/*  b) trenger ikke en destrukt�r fordi n�r alle cars som peker til engine g�r
		   ut av scope vil engine bli frigjort
	*/

	/*     engine-pekerene vil peke til samme minnelokasjon
		   hvis vi �nsker at de ikke skal peke til samme lokasjon b�r
		   vi heller bruke unique_ptr siden da er det klart hvem som
		   har ansvar over minnet. 
	*/

	/*	c) den vil slettes i slutten av main
	*/
};