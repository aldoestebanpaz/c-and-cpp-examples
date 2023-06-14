
#ifndef GLOBAL_ACTION__META_TYPES__INCLUDED
#define GLOBAL_ACTION__META_TYPES__INCLUDED


#include <QtGlobal>
#include <QDBusMetaType>


typedef enum SampleEnum
{
    SAMPLE_ENUM_FIRST = 0,
    SAMPLE_ENUM_LAST,
    SAMPLE_ENUM_NONE,
    SAMPLE_ENUM_ALL,
    SAMPLE_ENUM__COUNT
} SampleEnum;


typedef struct CommonActionInfo
{
    QString shortcut;
    QString description;
    bool enabled;
} CommonActionInfo;

typedef struct GeneralActionInfo : CommonActionInfo
{
    QString type;
    QString info;
} GeneralActionInfo;


typedef QMap<qulonglong, GeneralActionInfo> QMap_qulonglong_GeneralActionInfo;

Q_DECLARE_METATYPE(GeneralActionInfo)
Q_DECLARE_METATYPE(QMap_qulonglong_GeneralActionInfo)

QDBusArgument &operator << (QDBusArgument &argument, const GeneralActionInfo &generalActionInfo);
const QDBusArgument &operator >> (const QDBusArgument &argument, GeneralActionInfo &generalActionInfo);

#endif // GLOBAL_ACTION_MANAGER__META_TYPES__INCLUDED
