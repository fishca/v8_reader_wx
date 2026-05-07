//---------------------------------------------------------------------------

#ifndef FunctionalOptionsH
#define FunctionalOptionsH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TFunctionalOptions
 * @brief Класс для хранения функциональных опций (md_FunctionalOptions)
 *
 * Функциональные опции - это объекты метаданных, которые содержат
 * настройки функциональности системы.
 */
class TFunctionalOptions : public BaseMetadataObject
{
private:
    // name хранится в унаследованном поле name из BaseMetadataObject

public:
     TFunctionalOptions();
     TFunctionalOptions(v8catalog* _parent, const String& _guid);
     TFunctionalOptions(v8catalog* _parent, const String& _guid, const String& _name);
    virtual  ~TFunctionalOptions();

    // Методы для получения имени функциональной опции
    String  GetOptionName();
    void  SetOptionName(String _name);

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
