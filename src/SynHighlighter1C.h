//---------------------------------------------------------------------------

#ifndef SynHighlighter1CH
#define SynHighlighter1CH
//---------------------------------------------------------------------------

#include "vcl_utils.h"
#include <Vcl.Graphics.hpp>
#include "SynEditHighlighter.hpp"

enum Ttk1CTokenKind
{
	tk1CComment,
	tk1CDirective,
	tk1CIdentifier,
	tk1CKeyword,
	tk1CNull,
	tk1CNumber,
	tk1CSpace,
	tk1CString,
	tk1CSymbol,
	tk1CAnnotation,
	tk1CUnknown
};

class TSyn1CSyn : public TSynCustomHighlighter
{
private:
	Ttk1CTokenKind FTokenID;
	TSynHighlighterAttributes* FCommentAttri;
	TSynHighlighterAttributes* FDirectiveAttri;
	TSynHighlighterAttributes* FIdentifierAttri;
	TSynHighlighterAttributes* FKeyAttri;
	TSynHighlighterAttributes* FNumberAttri;
	TSynHighlighterAttributes* FSpaceAttri;
	TSynHighlighterAttributes* FStringAttri;
	TSynHighlighterAttributes* FSymbolAttri;
	TSynHighlighterAttributes* FAnnotationAttri;
	TStringList* FKeywords;
	TStringList* FEnglishKeywords;
	TStringList* FAnnotations;

	bool  IsIdentifierChar(WideChar ch) const;
	bool  IsKeywordToken(const String& token) const;
	bool  IsAnnotationToken(const String& token) const;
	void  LoadRussianKeywords();
	void  LoadEnglishKeywordPlaceholders();
	void  LoadAnnotations();
	void  NullProc();
	void  SpaceProc();
	void  CommentProc();
	void  StringProc();
	void  NumberProc();
	void  DirectiveProc();
	void  AnnotationProc();
	void  IdentifierProc();
	void  SymbolProc();

protected:
	virtual TSynHighlighterAttributes*  GetDefaultAttribute(int Index);
	virtual String  GetSampleSource();

public:
	 virtual TSyn1CSyn(TComponent* AOwner);
	 virtual ~TSyn1CSyn();
	__classmethod virtual String  GetLanguageName();
	__classmethod virtual String  GetFriendlyLanguageName();
	virtual bool  GetEol();
	virtual String  GetToken();
	virtual TSynHighlighterAttributes*  GetTokenAttribute();
	virtual int  GetTokenKind();
	virtual int  GetTokenPos();
	virtual bool  IsIdentChar(WideChar AChar);
	virtual bool  IsKeyword(const String AKeyword);
	virtual void  Next();
	virtual void  SetLine(const String Value, int LineNumber);
	virtual String  GetKeyWords(int TokenKind);

	__property TSynHighlighterAttributes* CommentAttri = {read=FCommentAttri};
	__property TSynHighlighterAttributes* DirectiveAttri = {read=FDirectiveAttri};
	__property TSynHighlighterAttributes* IdentifierAttri = {read=FIdentifierAttri};
	__property TSynHighlighterAttributes* KeyAttri = {read=FKeyAttri};
	__property TSynHighlighterAttributes* NumberAttri = {read=FNumberAttri};
	__property TSynHighlighterAttributes* SpaceAttri = {read=FSpaceAttri};
	__property TSynHighlighterAttributes* StringAttri = {read=FStringAttri};
	__property TSynHighlighterAttributes* SymbolAttri = {read=FSymbolAttri};
	__property TSynHighlighterAttributes* AnnotationAttri = {read=FAnnotationAttri};
};

//---------------------------------------------------------------------------
#endif
