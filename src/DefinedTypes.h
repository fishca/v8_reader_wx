//---------------------------------------------------------------------------

#ifndef DefinedTypesH
#define DefinedTypesH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TDefinedTypes
 * @brief Класс для хранения определяемых типов (md_DefinedTypes)
 *
 * Определяемые типы - это объекты метаданных, которые содержат
 * пользовательские типы данных, используемые в конфигурации.
 */
class TDefinedTypes : public BaseMetadataObject
{
private:
    String typeName;  // Имя определяемого типа

public:
     TDefinedTypes();
     TDefinedTypes(v8catalog* _parent, const String& _guid);
     TDefinedTypes(v8catalog* _parent, const String& _guid, const String& _name);
    virtual  ~TDefinedTypes();

    // Методы для получения имени определяемого типа
    String  GetTypeName();
    void  SetTypeName(String _name);

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
