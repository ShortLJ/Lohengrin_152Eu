#ifndef DET_SYS
#define DET_SYS
struct LaBr_Hit{
	public:
		Int_t ADC;
		Double_t CalibE;
		Short_t Channel;
		Short_t TimeStamp;
		Bool_t isClean;
};

struct TAC_Hit{
	public:
		Int_t ADC;
		Double_t CalibT;
		Short_t Channel;
		Short_t TimeStamp;
		Bool_t isClean;
};
#endif


