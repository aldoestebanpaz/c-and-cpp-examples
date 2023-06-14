
#pragma once

#include <QThread>
#include <QDBusServiceWatcher>
#include <QDBusMessage>
#include <QDBusObjectPath>

#include "meta_types.h"


class ComAldosDbus_sampleServiceInterface;
namespace com
{
namespace aldos
{
namespace dbus_sample
{
typedef ::ComAldosDbus_sampleServiceInterface service_interface;
}
}
}


class ServiceAdaptor;

class Listener : public QThread
{
    Q_OBJECT

public:
    Listener();
    ~Listener() override;

    bool ready() const { return mReady; }

private:
    Listener(const Listener&) = delete;
    Listener(const Listener&&) = delete;
    Listener& operator =(const Listener&) = delete;
    Listener& operator =(const Listener&&) = delete;

private:
    void run() override;
    void runInfiniteLoop();

private:
    void MethodNoArgsNoReturn();
    void MethodWithAnnotationNoReply();
    void MethodSingleInputNoReturn(qulonglong argInUnit64) const;
    void MethodSingleOutputNoReturn(qulonglong &result) const;
    void MethodSingleOutputNoReturn2(QString &result) const;
    void MethodMultipleInputsMultipleOutputsNoReturn(
        // result
        QString &result,
        // in
        const uint &argInUnit32, const qulonglong &argInUnit64, const QString &argInString, const QStringList &argInArrayOfStrings, const QDBusObjectPath &argInObjectPath, bool argInBoolean,
        // out
        qulonglong &argOutUnit64, QString &argOutString2, bool &argOutBoolean);
    void MethodNoArgsStringReturn(QString &result) const;
    void MethodNoArgsUnit32Return(SampleEnum &result) const;
    void MethodNoArgsBooleanReturn(bool &result) const;
    void MethodMultipleArgsStringReturn(QString &result, const qulonglong &argInUnit64, qulonglong &argOutUnit64) const;
    void MethodNoArgsArrayOfUnit64Return(QList<qulonglong> &result) const;
    void MethodNoArgsArrayOfDictEntriesReturn(QMap<qulonglong, GeneralActionInfo> &result) const;

private slots:
    void on_signalOneArg(qulonglong argUnit64);

private:
    bool mReady;
    QDBusServiceWatcher *mServiceWatcher;
    ServiceAdaptor *mServiceAdaptor;
    com::aldos::dbus_sample::service_interface *mServiceProxy;
};
