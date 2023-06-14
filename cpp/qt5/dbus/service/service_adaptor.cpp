#include "service_adaptor.h"

#include "com.aldos.dbus_sample.service.h"


ServiceAdaptor::ServiceAdaptor(QObject *parent)
    : QObject(parent)
    , QDBusContext()
{
    new ComAldosDbusSampleServiceAdaptor(this);
}

void ServiceAdaptor::methodNoArgsNoReturn()
{
    emit onMethodNoArgsNoReturn();
}

void ServiceAdaptor::methodWithAnnotationNoReply()
{
    emit onMethodWithAnnotationNoReply();
}

void ServiceAdaptor::methodSingleInputNoReturn(qulonglong argInUnit64)
{
    emit onMethodSingleInputNoReturn(argInUnit64);
}

qulonglong ServiceAdaptor::methodSingleOutputNoReturn()
{
    qulonglong result;
    emit onMethodSingleOutputNoReturn(result);
    return result;
}

QString ServiceAdaptor::methodSingleOutputNoReturn2()
{
    QString result;
    emit onMethodSingleOutputNoReturn2(result);
    return result;
}

QString ServiceAdaptor::methodMultipleInputsMultipleOutputsNoReturn(
    // in
    uint argInUnit32
    , qulonglong argInUnit64
    , const QString &argInString
    , const QStringList &argInArrayOfStrings
    , const QDBusObjectPath &argInObjectPath
    , bool argInBoolean
    // out
    , qulonglong &argOutUnit64
    , QString &argOutString2
    , bool &argOutBoolean)
{
    QString result;
    emit onMethodMultipleInputsMultipleOutputsNoReturn(
        // result
        result,
        // in
        argInUnit32, argInUnit64, argInString, argInArrayOfStrings, argInObjectPath, argInBoolean,
        // out
        argOutUnit64, argOutString2, argOutBoolean);
    return result;
}

QString ServiceAdaptor::methodNoArgsStringReturn()
{
    QString result;
    emit onMethodNoArgsStringReturn(result);
    return result;
}

uint ServiceAdaptor::methodNoArgsUnit32Return()
{
    SampleEnum result;
    emit onMethodNoArgsUnit32Return(result);
    // SampleEnum result = static_cast<SampleEnum>(0);
    // SampleEnum result = static_cast<SampleEnum>(SAMPLE_ENUM_FIRST);
    return result;
}

bool ServiceAdaptor::methodNoArgsBooleanReturn()
{
    bool result;
    emit onMethodNoArgsBooleanReturn(result);
    return result;
}

QString ServiceAdaptor::methodMultipleArgsStringReturn(qulonglong argInUnit64, qulonglong &argOutUnit64)
{
    QString result;
    emit onMethodMultipleArgsStringReturn(result, argInUnit64, argOutUnit64);

    // argOutUnit64 = 0ull;

    return result;
}

QList<qulonglong> ServiceAdaptor::methodNoArgsArrayOfUnit64Return()
{
    QList<qulonglong> result;
    emit onMethodNoArgsArrayOfUnit64Return(result);
    
    // QList<qulonglong> result = {256, 224, 192, 160, 128, 96, 64};

    return result;
}

QMap<qulonglong, GeneralActionInfo> ServiceAdaptor::methodNoArgsArrayOfDictEntriesReturn()
{
    QMap<qulonglong, GeneralActionInfo> result;
    emit onMethodNoArgsArrayOfDictEntriesReturn(result);
    
    // result[0] =  {
    //     { .shortcut = "", .description = "", .enabled = true },
    //     .type = "", .info = ""
    // };
    // result[1] =  {
    //     { .shortcut = "", .description = "", .enabled = true },
    //     .type = "", .info = ""
    // };

    return result;
}
