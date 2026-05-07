//---------------------------------------------------------------------------

#ifndef ExchangePlansH
#define ExchangePlansH

#include "MetadataObjectWithSections.h"
//---------------------------------------------------------------------------

/**
 * @class TExchangePlans
 * @brief Класс для хранения планов обмена (md_ExchangePlans)
 *
 * Планы обмена - это объекты метаданных, которые определяют
 * правила обмена данными между информационными базами 1С.
 */
class TExchangePlans : public MetadataObjectWithSections
{
private:
    String exchangePlanName;  // Имя плана обмена

public:
     TExchangePlans();
     TExchangePlans(v8catalog* _parent, const String& _guid);
     TExchangePlans(v8catalog* _parent, const String& _guid, const String& _name);
    virtual  ~TExchangePlans();

    // Методы для получения имени плана обмена
    String  GetExchangePlanName();
    void  SetExchangePlanName(String _name);

    void  initializeFromTree() override;
};

#endif
