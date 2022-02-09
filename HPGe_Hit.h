#ifndef HPGe_Hit_h
#define HPGe_Hit_h

struct HPGe_Hit{
	public:
		Int_t ADC;
		Double_t CalibE;
		Short_t Channel;
		Short_t TimeStamp;
		Bool_t isClean;
};

#endif
