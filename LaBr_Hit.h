#ifndef LaBr_Hit_h
#define LaBr_Hit_h

struct LaBr_Hit{
	public:
		Int_t ADC;
		Double_t CalibE;
		Short_t Channel;
		Short_t TimeStamp;
		Bool_t isClean;
};

#endif
