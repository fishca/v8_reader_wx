//---------------------------------------------------------------------------

#ifndef CommonTemplatesH
#define CommonTemplatesH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TCommonTemplates
 * @brief Класс для хранения общих макетов (md_CommonTemplates)
 *
 * Общие макеты - это объекты метаданных, которые содержат
 * макеты, доступные в различных частях конфигурации.
 */
class TCommonTemplates : public BaseMetadataObject
{
private:
    // templateName хранится в унаследованном поле name из BaseMetadataObject

public:
     TCommonTemplates();
     TCommonTemplates(v8catalog* _parent, const String& _guid);
     TCommonTemplates(v8catalog* _parent, const String& _guid, const String& _name);
    virtual  ~TCommonTemplates();

    // Методы для получения имени общего макета
    String  GetTemplateName();
    void  SetTemplateName(String _name);

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