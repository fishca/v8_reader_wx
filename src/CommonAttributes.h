//---------------------------------------------------------------------------

#ifndef CommonAttributesH
#define CommonAttributesH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TCommonAttributes
 * @brief Класс для хранения общих реквизитов (md_CommonAttributes)
 *
 * Общие реквизиты - это объекты метаданных, которые содержат
 * реквизиты, доступные для использования в различных элементах конфигурации.
 */
class TCommonAttributes : public BaseMetadataObject
{
private:
    // attributeName хранится в унаследованном поле name из BaseMetadataObject

public:
     TCommonAttributes();
     TCommonAttributes(v8catalog* _parent, const String& _guid);
     TCommonAttributes(v8catalog* _parent, const String& _guid, const String& _name);
    virtual  ~TCommonAttributes();

    // Методы для получения имени общего реквизита
    String  GetAttributeName();
    void  SetAttributeName(String _name);

    // Реализация виртуальных методов BaseMetadataObject
    std::vector<std::unique_ptr<TRequisite>>& getAttributes() override;
    std::vector<std::unique_ptr<TComand>>& getCommands() override;
    std::vector<std::unique_ptr<TMoxel>>& getLayouts() override;
    std::vector<std::unique_ptr<TTabular>>& getTabularSections() override;
    std::vector<std::unique_ptr<TForm1C>>& getForms() override;

    void  initializeFromTree() override;

private:
    // Внутренние хранилища для совместимости с интерфейсом
    std::vector<std::unique_ptr<TRequisite>> attributes;
    std::vector<std::unique_ptr<TComand>> commands;
    std::vector<std::unique_ptr<TMoxel>> layouts;
    std::vector<std::unique_ptr<TTabular>> tabularSections;
    std::vector<std::unique_ptr<TForm1C>> forms;
};

#endif
