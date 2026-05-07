//---------------------------------------------------------------------------

#ifndef MainUnitH
#define MainUnitH
//---------------------------------------------------------------------------
#include "vcl_utils.h"
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include "VirtualTrees.hpp"
#include <System.ImageList.hpp>
#include <Vcl.BaseImageCollection.hpp>
#include <Vcl.ImageCollection.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.VirtualImageList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include "SynEdit.hpp"
#include "SynEditHighlighter.hpp"
#include "SynHighlighterCpp.hpp"
#include "SynEditCodeFolding.hpp"
#include "SynHighlighterGeneral.hpp"
#include "SynMemo.hpp"
#include "SynHighlighter1C.h"
#include "ModuleTextStorage.h"

#include <memory>

#include "Requisite.h"
#include "Comand.h"
#include "Moxel.h"
#include "Tabular.h"
#include "Form.h"
#include "Enums.h"
#include "BaseMetadataObject.h"



#include "guids.h"
#include "MessageRegistration.h"
#include "MetaDataManager.h"
#include "Parse_tree.h"
#include "SmartPointers.h"
#include "SynEdit.hpp"
#include "SynMemo.hpp"
#include "SynEditHighlighter.hpp"
#include "SynHighlighterCpp.hpp"
#include "SynEditCodeFolding.hpp"
#include "SynHighlighterGeneral.hpp"
#include "SynHighlighter1C.h"

class Messager;

struct SubSys
{
	String              name;
	std::vector<String> children;
};

struct VirtualTreeData
{
	String Name;
	String text_module;
	String moduleItemGuid;
	TObject* MetadataObject = nullptr;
	ModuleTextLocation moduleLocation;
	bool moduleEditable = false;
	bool moduleDirty = false;
	int Age = 0;
	int ImgIndex = 0;
};


//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TEdit *EditNameCF;
	TButton *btnGO;
	TOpenDialog *dlgOpenCF;
	TVirtualStringTree *VirtualStringTreeValue1C;
	TImageList *ImageList1;
	TImageCollection *ImageCollection1;
	TVirtualImageList *VirtualImageList1;
	TStatusBar *StatusBar1;
	TOpenDialog *dlgOpenCatalog;
	TPanel *LeftPanel;
	TSplitter *split1;
	TPanel *rPanel;
	TPageControl *pagesEdit;
	TActionList *ActionList1;
	TAction *ActionOpenCF;
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TTabSheet *TabModuleObject;
	TTabSheet *TabModuleManager;
	TListView *ListViewMessager;
	TSplitter *Splitter1;
	TTabSheet *TabSheet1;
	TSynMemo *MemoObject;
	TSynMemo *MemoManager;
	TPanel *Panel1;
	TProgressBar *LoadProgressBar;
	TSynCppSyn *SynCppSyn1;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TAction *ActionSaveCF;
	TAction *ActionSaveModule;
	TMenuItem *N6;
	void  btnOpenEditNameClick(TObject *Sender);
	void  btnGOClick(TObject *Sender);
	void  VirtualStringTreeValue1CInitNode(TBaseVirtualTree *Sender, PVirtualNode ParentNode,
		  PVirtualNode Node, TVirtualNodeInitStates &InitialStates);
	void  VirtualStringTreeValue1CGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);
	void  VirtualStringTreeValue1CFreeNode(TBaseVirtualTree *Sender, PVirtualNode Node);
	void  VirtualStringTreeValue1CGetImageIndex(TBaseVirtualTree *Sender, PVirtualNode Node, TVTImageKind Kind, TColumnIndex Column,
		  bool &Ghosted, TImageIndex &ImageIndex);
	void  Button1Click(TObject *Sender);
	void  ActionFileOpenExecute(TObject *Sender);
	void  ActionOpenCFExecute(TObject *Sender);
	void  FormDestroy(TObject *Sender);
	void  VirtualStringTreeValue1CClick(TObject *Sender);
	void  VirtualStringTreeValue1CChange(TBaseVirtualTree *Sender, PVirtualNode Node);
	void  VirtualStringTreeValue1CNodeClick(TBaseVirtualTree *Sender, const THitInfo &HitInfo);
	void  VirtualStringTreeValue1CFocusChanged(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column);
	void  ModuleMemoScanForFoldRanges(TObject *Sender, TSynFoldRanges *FoldRanges,
		  TStrings *LinesToScan, int FromLine, int ToLine);
	void  ModuleSelectionTimerTimer(TObject *Sender);
	void  N4Click(TObject *Sender);
	void  ActionSaveCFExecute(TObject *Sender);
	void  MemoObjectChange(TObject *Sender);
	void  ActionSaveModuleExecute(TObject *Sender);
	void  FormCloseQuery(TObject *Sender, bool &CanClose);


private:	// User declarations
	Messager* mess; // регистратор сообщений
	TSyn1CSyn *Syn1CSyn;
	TSynGeneralSyn *ModuleGeneralSyn;
	TTabSheet *HighlightSettingsTab;
	TColorBox *HighlightKeywordColorBox;
	TColorBox *HighlightCommentColorBox;
	TColorBox *HighlightStringColorBox;
	TColorBox *HighlightNumberColorBox;
	TColorBox *HighlightPreprocessorColorBox;
	TColorBox *HighlightSymbolColorBox;
	TColorBox *HighlightAnnotationColorBox;
	TCheckBox *HighlightKeywordBoldCheckBox;
	TCheckBox *HighlightCommentItalicCheckBox;
	TCheckBox *UnpackCheckBox;

	TSynMemo *HighlightPreviewMemo;
	bool HighlightSettingsLoading;
	TTimer *ModuleSelectionTimer;
	PVirtualNode LastModuleNodeShown;
	PVirtualNode CurrentModuleNode;
	BaseMetadataObject* CurrentModuleObject;
	bool LoadingModuleText;
	bool CurrentModuleDirty;
	String CurrentModuleOriginalText;
	ModuleTextLocation CurrentModuleLocation;
	ModuleTextKind CurrentModuleKind;
	ModuleTextDocument CurrentStandaloneModuleDocument;
	bool CurrentModuleStandalone;
    std::unique_ptr<MetaDataManager> MDManager; // Умный указатель для автоматического управления памятью
	void  CreateHighlightSettingsTab();
	void  ApplyHighlightSettings();
	void  LoadHighlightSettings();
	void  SaveHighlightSettings();
	void  SetDefaultHighlightSettingsControls();
	void  HighlightSettingsChanged(TObject *Sender);
	void  ResetHighlightSettingsClick(TObject *Sender);
	void  ShowMetadataNodeText(PVirtualNode Node);
	bool  SaveCurrentModuleTextIfNeeded(bool forcePrompt);
	bool  FlushCurrentModuleBeforeBuild();
	void  SetModuleEditorState(BaseMetadataObject* metadataObject, PVirtualNode node, const String& text, ModuleTextKind kind);
public:		// User declarations
	 TMainForm(TComponent* Owner);
	void  ResetLoadProgress(int maxValue, const String& statusText = L"");
	void  AdvanceLoadProgress(const String& statusText);
	void  CompleteLoadProgress(const String& statusText);
	void  TreeInit();
	void 	FillVirtualTree();
	void  FillTreeMD(PVirtualNode parentNode, const MetadataVector<TObject>& mdData, const String& md_name, int imgIndex);
	void  FillTreeMDConcrete(TVirtualStringTree *tree1C, PVirtualNode parentNode, const MetadataVector<TObject>& mdData, const String& md_name, int imgIndex);


	String ConfigName;

	MetadataVector<TObject> mdCatalogs;
	MetadataVector<TObject> mdCommonss;
	MetadataVector<TObject> mdLanguages;
	MetadataVector<TObject> mdAccumulationRegisters;
	MetadataVector<TObject> mdAccountingRegisters;
	MetadataVector<TObject> mdCalculationRegisters;
	MetadataVector<TObject> mdBusinessProcesses;
	MetadataVector<TObject> mdChartsOfCharacteristicTypes;
	MetadataVector<TObject> mdCommandGroups;
	MetadataVector<TObject> mdCommonAttributes;
	MetadataVector<TObject> mdCommonCommands;
	MetadataVector<TObject> mdCommonForms;
	MetadataVector<TObject> mdCommonModules;
	MetadataVector<TObject> mdCommonPictures;
	MetadataVector<TObject> mdCommonTemplates;
	MetadataVector<TObject> mdConstants;
	MetadataVector<TObject> mdDataProcessors;
	MetadataVector<TObject> mdDefinedTypes;
	MetadataVector<TObject> mdDocumentJournals;
	MetadataVector<TObject> mdDocumentNumerators;
	MetadataVector<TObject> mdDocuments;
	MetadataVector<TObject> mdEnums;
	MetadataVector<TObject> mdEventSubscriptions;
	MetadataVector<TObject> mdExchangePlans;
	MetadataVector<TObject> mdChartOfAccounts;
	MetadataVector<TObject> mdChartOfCalculationTypes;
	MetadataVector<TObject> mdExternalDataSources;
	MetadataVector<TObject> mdFilterCriteria;
	MetadataVector<TObject> mdFunctionalOptions;
	MetadataVector<TObject> mdFunctionalOptionsParameters;
	MetadataVector<TObject> mdHTTPServices;
	MetadataVector<TObject> mdInformationRegisters;
	MetadataVector<TObject> mdInterfaces;
	MetadataVector<TObject> mdReports;
	MetadataVector<TObject> mdRoles;
	MetadataVector<TObject> mdBots;
	MetadataVector<TObject> mdScheduledJobs;
	MetadataVector<TObject> mdSessionParameters;
	MetadataVector<TObject> mdSettingsStorages;
	MetadataVector<TObject> mdStyleItems;
	MetadataVector<TObject> mdStyles;
	//std::vector<SubSys> Subsystems;  - возможно надо удалить, т.к. лишнее уже
	MetadataVector<TObject> mdSubsystems;
	MetadataVector<TObject> mdTasks;
	MetadataVector<TObject> mdWebServices;
	MetadataVector<TObject> mdWSReferences;
	MetadataVector<TObject> mdWebSocketClients;
	MetadataVector<TObject> mdXDTOPackages;
	MetadataVector<TObject> mdIntegrationServices;
	MetadataVector<TObject> mdSequences;

	std::unique_ptr<v8catalog> GlobalCF;
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------

class Messager : public MessageRegistrator
{
private:
	TListView* ListView;
	TStatusBar* StatusBar;
	String logfile;
	TFormatSettings FormatSettings;
	bool uiMessagesEnabled;
	bool fileLoggingEnabled;
public:
	 Messager(TListView* lv, TStatusBar* sb);
	void  setUiMessagesEnabled(bool enabled);
	bool  getUiMessagesEnabled() const;
	void  setFileLoggingEnabled(bool enabled);
	bool  getFileLoggingEnabled() const;
	void  setlogfile(String _logfile);
	String  getlogfile() const;
	virtual void  AddMessage(const String& message, const MessageState mstate, TStringList* param = NULL);
	virtual void  Status(const String& message);
};



void get_cf_name(v8catalog* cf, Messager* mess);
void get_cf_name(tree* tr,      Messager* mess);

#endif
