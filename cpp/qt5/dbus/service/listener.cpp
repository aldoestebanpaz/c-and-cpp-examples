
#include <QDBusConnectionInterface>
#include <QDebug>

#include <stdexcept>

#include "service_adaptor.h"

// required for listening the Dbus signal: signalOneArg
#include "com.aldos.dbus_sample.service_interface.h"

#include "listener.h"


Listener::Listener()
    : QThread(nullptr)
    , mReady(false)
    , mServiceWatcher(nullptr)
    //, mServiceWatcher(new QDBusServiceWatcher(QLatin1String("com.aldos.dbus_sample"), QDBusConnection::sessionBus(), QDBusServiceWatcher::WatchForOwnerChange, this))
    , mServiceAdaptor(nullptr)
{
    try
    {
        // mServiceWatcher = new QDBusServiceWatcher{this};
        // mServiceWatcher->setConnection(QDBusConnection::sessionBus());

        if (!QDBusConnection::sessionBus().registerService(QStringLiteral("com.aldos.dbus_sample")))
        {
            throw std::runtime_error(std::string("Cannot register service"));
        }

        mServiceAdaptor = new ServiceAdaptor(this);
        if (!QDBusConnection::sessionBus().registerObject(QStringLiteral("/service"), mServiceAdaptor))
        {
            throw std::runtime_error(std::string("Cannot create adaptor"));
        }

        mServiceProxy = new com::aldos::dbus_sample::service_interface(
            QLatin1String("com.aldos.dbus_sample")
            , QStringLiteral("/service")
            , QDBusConnection::sessionBus()
            , this);

        qDebug() << "Started DBus service";

        start(); // execute run()

        connect(mServiceAdaptor, &ServiceAdaptor::onMethodNoArgsNoReturn,                        this, &Listener::MethodNoArgsNoReturn);
        connect(mServiceAdaptor, &ServiceAdaptor::onMethodWithAnnotationNoReply,                 this, &Listener::MethodWithAnnotationNoReply);
        connect(mServiceAdaptor, &ServiceAdaptor::onMethodSingleInputNoReturn,                   this, &Listener::MethodSingleInputNoReturn);
        connect(mServiceAdaptor, &ServiceAdaptor::onMethodSingleOutputNoReturn,                  this, &Listener::MethodSingleOutputNoReturn);
        connect(mServiceAdaptor, &ServiceAdaptor::onMethodSingleOutputNoReturn2,                 this, &Listener::MethodSingleOutputNoReturn2);
        connect(mServiceAdaptor, &ServiceAdaptor::onMethodMultipleInputsMultipleOutputsNoReturn, this, &Listener::MethodMultipleInputsMultipleOutputsNoReturn);
        connect(mServiceAdaptor, &ServiceAdaptor::onMethodNoArgsStringReturn,                    this, &Listener::MethodNoArgsStringReturn);
        connect(mServiceAdaptor, &ServiceAdaptor::onMethodNoArgsUnit32Return,                    this, &Listener::MethodNoArgsUnit32Return);
        connect(mServiceAdaptor, &ServiceAdaptor::onMethodNoArgsBooleanReturn,                   this, &Listener::MethodNoArgsBooleanReturn);
        connect(mServiceAdaptor, &ServiceAdaptor::onMethodMultipleArgsStringReturn,              this, &Listener::MethodMultipleArgsStringReturn);
        connect(mServiceAdaptor, &ServiceAdaptor::onMethodNoArgsArrayOfUnit64Return,             this, &Listener::MethodNoArgsArrayOfUnit64Return);
        connect(mServiceAdaptor, &ServiceAdaptor::onMethodNoArgsArrayOfDictEntriesReturn,        this, &Listener::MethodNoArgsArrayOfDictEntriesReturn);

        // dbus signal capture
        connect(mServiceProxy, &com::aldos::dbus_sample::service_interface::signalOneArg,        this, &Listener::on_signalOneArg);

        mReady = true;
    }
    catch (const std::exception &err)
    {
        qDebug() << err.what();
    }
}

void Listener::run()
{
    runInfiniteLoop();
}

void Listener::runInfiniteLoop()
{
    while (true)
    {
        ;
    }
}

void Listener::MethodNoArgsNoReturn()
{
    qDebug("Listener::MethodNoArgsNoReturn was invoked");
}

void Listener::MethodWithAnnotationNoReply()
{
    qDebug("Listener::MethodWithAnnotationNoReply was invoked");
}

void Listener::MethodSingleInputNoReturn(qulonglong argInUnit64) const
{
    qDebug("Listener::MethodSingleInputNoReturn was invoked. argInUnit64: %llu", argInUnit64);
}

void Listener::MethodSingleOutputNoReturn(qulonglong &result) const
{
    result = 0ull;
    qDebug("Listener::MethodSingleOutputNoReturn was invoked. result: %llu", result);
}

void Listener::MethodSingleOutputNoReturn2(QString &result) const
{
    result = QString();
    qDebug("Listener::MethodSingleOutputNoReturn2 was invoked. result: %s", qPrintable(result));
}

void Listener::MethodMultipleInputsMultipleOutputsNoReturn(
    // result
    QString &result,
    // in
    const uint &argInUnit32, const qulonglong &argInUnit64, const QString &argInString, const QStringList &argInArrayOfStrings, const QDBusObjectPath &argInObjectPath, bool argInBoolean,
    // out
    qulonglong &argOutUnit64, QString &argOutString2, bool &argOutBoolean)
{
    result = QString();
    argOutUnit64 = 0ull;
    argOutString2 = QString();
    argOutBoolean = true;
    qDebug("Listener::MethodMultipleInputsMultipleOutputsNoReturn was invoked. result: %s, argInUnit32: %u, argInUnit64: %llu, argInString: %s, argInArrayOfStrings: %s, argInObjectPath: %s, argInBoolean: %s, argOutUnit64: %llu, argOutString2: %s, argOutBoolean: %s",
        qPrintable(result),
        argInUnit32, argInUnit64, qPrintable(argInString), /*qPrintable(argInArrayOfStrings)*/qPrintable("<argInArrayOfStrings>"), qPrintable(argInObjectPath.path()), argInBoolean ? " true" : "false",
        argOutUnit64, qPrintable(argOutString2), argOutBoolean ? " true" : "false");
}

void Listener::MethodNoArgsStringReturn(QString &result) const
{
    result = QString();
    qDebug("Listener::MethodNoArgsStringReturn was invoked. result: %s", qPrintable(result));
}

void Listener::MethodNoArgsUnit32Return(SampleEnum &result) const
{
    result = SAMPLE_ENUM_ALL;
    qDebug("Listener::MethodNoArgsUnit32Return was invoked. result: %u", result);
}

void Listener::MethodNoArgsBooleanReturn(bool &result) const
{
    result = true;
    qDebug("Listener::MethodNoArgsBooleanReturn was invoked. result: %s", result ? " true" : "false");
}

void Listener::MethodMultipleArgsStringReturn(QString &result, const qulonglong &argInUnit64, qulonglong &argOutUnit64) const
{
    result = QString();
    argOutUnit64 = 0ull;
    qDebug("Listener::MethodMultipleArgsStringReturn was invoked. result: %s, argInUnit64: %llu, argOutUnit64: %llu", qPrintable(result), argInUnit64, argOutUnit64);
}

void Listener::MethodNoArgsArrayOfUnit64Return(QList<qulonglong> &result) const
{
    result = {256, 224, 192, 160, 128, 96, 64};
    qDebug("Listener::MethodNoArgsArrayOfUnit64Return was invoked. result: %s", /*qPrintable(result)*/qPrintable("<result>"));
}

void Listener::MethodNoArgsArrayOfDictEntriesReturn(QMap<qulonglong, GeneralActionInfo> &result) const
{
    result[0ull] = {
        { .shortcut = "", .description = "", .enabled = true },
        .type = "", .info = ""
    };
    result[1ull] = {
        { .shortcut = "", .description = "", .enabled = true },
        .type = "", .info = ""
    };
    qDebug("Listener::MethodNoArgsArrayOfDictEntriesReturn was invoked. result: %s", /*qPrintable(result)*/qPrintable("<result>"));
}

void Listener::on_signalOneArg(qulonglong argUnit64)
{
    qDebug("Listener::on_signalOneArg was invoked. id: %llu", argUnit64);
}

Listener::~Listener()
{
    qDebug() << "Listener destroyed";
    delete mServiceAdaptor;
}
