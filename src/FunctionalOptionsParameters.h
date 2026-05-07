//---------------------------------------------------------------------------

#ifndef FunctionalOptionsParametersH
#define FunctionalOptionsParametersH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TFunctionalOptionsParameters
 * @brief Класс для хранения параметров функциональных опций (md_FunctionalOptionsParameters)
 *
 * Параметры функциональных опций - это объекты метаданных, которые содержат
 * параметры, доступные для функциональных опций системы.
 */
class TFunctionalOptionsParameters : public BaseMetadataObject
{
private:
    // name хранится в унаследованном поле name из BaseMetadataObject

public:
     TFunctionalOptionsParameters();
     TFunctionalOptionsParameters(v8catalog* _parent, const String& _guid);
     TFunctionalOptionsParameters(v8catalog* _parent, const String& _guid, const String& _name);
    virtual  ~TFunctionalOptionsParameters();

    // Методы для получения имени параметра функциональной опции
    String  GetParameterName();
    void  SetParameterName(String _name);

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
