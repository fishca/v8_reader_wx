//---------------------------------------------------------------------------

#ifndef FilterCriteriaH
#define FilterCriteriaH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TFilterCriteria
 * @brief Класс для хранения критериев отбора (md_FilterCriteria)
 *
 * Критерии отбора - это объекты метаданных, которые содержат
 * условия для фильтрации данных в запросах и отчетах.
 */
class TFilterCriteria : public BaseMetadataObject
{
private:
    // filterCriteriaName хранится в унаследованном поле name из BaseMetadataObject

public:
     TFilterCriteria();
     TFilterCriteria(v8catalog* _parent, const String& _guid);
     TFilterCriteria(v8catalog* _parent, const String& _guid, const String& _name);
    virtual  ~TFilterCriteria();

    // Методы для получения имени критерия отбора
    String  GetFilterCriteriaName();
    void  SetFilterCriteriaName(String _name);

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
