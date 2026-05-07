//---------------------------------------------------------------------------

#ifndef TempStreamH
#define TempStreamH

#include <System.Classes.hpp>

class TTempStreamStaticInit
{
public:
	 TTempStreamStaticInit();
	 ~TTempStreamStaticInit();
};


//---------------------------------------------------------------------------
class TTempStream : public THandleStream
{
public:
	static String tempcat;
	static String tempname;
	static long tempno;
	static String  gettempname();

	 TTempStream();
	virtual  ~TTempStream();
};

//---------------------------------------------------------------------------
#endif
