//---------------------------------------------------------------------------

#ifndef TempStreamH
#define TempStreamH

#include "vcl_utils.h"

class TTempStreamStaticInit
{
public:
	 TTempStreamStaticInit();
	 ~TTempStreamStaticInit();
};


//---------------------------------------------------------------------------
class TTempStream : public vcl_utils::TStream
{
public:
	static std::wstring tempcat;
	static std::wstring tempname;
	static long tempno;
	static std::wstring  gettempname();

	 TTempStream();
	virtual  ~TTempStream();
};

//---------------------------------------------------------------------------
#endif
