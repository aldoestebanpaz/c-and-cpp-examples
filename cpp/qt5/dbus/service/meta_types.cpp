
#include "meta_types.h"


QDBusArgument &operator << (QDBusArgument &argument, const GeneralActionInfo &generalActionInfo)
{
    argument.beginStructure();
    argument << generalActionInfo.shortcut
            << generalActionInfo.description
            << generalActionInfo.enabled
            << generalActionInfo.type
            << generalActionInfo.info;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator >> (const QDBusArgument &argument, GeneralActionInfo &generalActionInfo)
{
    argument.beginStructure();
    argument >> generalActionInfo.shortcut
            >> generalActionInfo.description
            >> generalActionInfo.enabled
            >> generalActionInfo.type
            >> generalActionInfo.info;
    argument.endStructure();
    return argument;
}

namespace
{

class TypeRegistrator
{
public:
    TypeRegistrator()
    {
        qDBusRegisterMetaType<GeneralActionInfo>();
        qDBusRegisterMetaType<QMap_qulonglong_GeneralActionInfo>();
    }

    ~TypeRegistrator()
    {}
};

static TypeRegistrator typeRegistrator;

}
