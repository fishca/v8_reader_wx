//---------------------------------------------------------------------------

#ifndef EventSubscriptionsH
#define EventSubscriptionsH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TEventSubscriptions
 * @brief Класс для хранения подписок на события (md_EventSubscriptions)
 *
 * Подписки на события - это объекты метаданных, которые содержат
 * настройки подписок на различные события системы.
 */
class TEventSubscriptions : public BaseMetadataObject
{
private:
    // eventSubscriptionName хранится в унаследованном поле name из BaseMetadataObject

public:
     TEventSubscriptions();
     TEventSubscriptions(v8catalog* _parent, const String& _guid);
     TEventSubscriptions(v8catalog* _parent, const String& _guid, const String& _name);
    virtual  ~TEventSubscriptions();

    // Методы для получения имени подписки на событие
    String  GetEventSubscriptionName();
    void  SetEventSubscriptionName(String _name);

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
