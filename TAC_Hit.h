#ifndef TAC_Hit_h
#define TAC_Hit_h

struct TAC_Hit{
	public:
		Int_t ADC;
		Double_t CalibT;
		Short_t Channel;
		Short_t TimeStamp;
		Bool_t isClean;
};

#endif
