//---------------------------------------------------------------------------

#ifndef ScheduledJobsH
#define ScheduledJobsH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TScheduledJobs
 * @brief Класс для хранения регламентных заданий (md_ScheduledJobs)
 *
 * Регламентные задания - это объекты метаданных, которые содержат
 * настройки автоматического выполнения задач по расписанию.
 */
class TScheduledJobs : public BaseMetadataObject
{
private:
    // scheduledJobsName хранится в унаследованном поле name из BaseMetadataObject

public:
     TScheduledJobs();
     TScheduledJobs(v8catalog* _parent, const String& _guid);
     TScheduledJobs(v8catalog* _parent, const String& _guid, const String& _name);
    virtual  ~TScheduledJobs();

    // Методы для получения имени регламентного задания
    String  GetScheduledJobsName();
    void  SetScheduledJobsName(String _name);

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
