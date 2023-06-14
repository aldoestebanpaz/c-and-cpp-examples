
#ifndef GLOBAL_ACTION_SERVICE__SERVICE_ADAPTOR__INCLUDED
#define GLOBAL_ACTION_SERVICE__SERVICE_ADAPTOR__INCLUDED

#include <QObject>
#include <QDBusContext>
#include <QString>
#include <QStringList>
#include <QDBusObjectPath>
#include <QPair>

#include "meta_types.h"


class ServiceAdaptor : public QObject, protected QDBusContext
{
    Q_OBJECT
public:
    ServiceAdaptor(QObject *parent = nullptr);

public slots:
    void methodNoArgsNoReturn();
    void methodWithAnnotationNoReply();
    void methodSingleInputNoReturn(qulonglong argInUnit64);
    qulonglong methodSingleOutputNoReturn();
    QString methodSingleOutputNoReturn2();
    QString methodMultipleInputsMultipleOutputsNoReturn(
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
        , bool &argOutBoolean);
    QString methodNoArgsStringReturn();
    uint methodNoArgsUnit32Return();
    bool methodNoArgsBooleanReturn();
    QString methodMultipleArgsStringReturn(qulonglong argInUnit64, qulonglong &argOutUnit64);
    QList<qulonglong> methodNoArgsArrayOfUnit64Return();
    QMap<qulonglong, GeneralActionInfo> methodNoArgsArrayOfDictEntriesReturn();

/*dbus signals*/
// signals:
    // void signalOneArg(qulonglong argUnit64);

/*non-dbus signals*/
signals:
    void onMethodNoArgsNoReturn();
    void onMethodWithAnnotationNoReply();
    void onMethodSingleInputNoReturn(qulonglong);
    void onMethodSingleOutputNoReturn(qulonglong &);
    void onMethodSingleOutputNoReturn2(QString &);
    void onMethodMultipleInputsMultipleOutputsNoReturn(
        // result
        QString &,
        // in
        uint, qulonglong, const QString &, const QStringList &, const QDBusObjectPath &, bool,
        // out
        qulonglong &, QString &, bool &);
    void onMethodNoArgsStringReturn(QString &);
    void onMethodNoArgsUnit32Return(SampleEnum &);
    void onMethodNoArgsBooleanReturn(bool &);
    void onMethodMultipleArgsStringReturn(QString &, qulonglong, qulonglong &);
    void onMethodNoArgsArrayOfUnit64Return(QList<qulonglong> &);
    void onMethodNoArgsArrayOfDictEntriesReturn(QMap<qulonglong, GeneralActionInfo> &);
};

#endif // GLOBAL_ACTION_SERVICE__SERVICE_ADAPTOR__INCLUDED
