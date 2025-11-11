#ifndef PWNEDRESULT_H
#define PWNEDRESULT_H

#include <QObject>

class PwnedResult : public QObject
{
public:
    explicit PwnedResult(QObject *parent = nullptr);

    void setPassword(const QString& password) {mPassword = password;}
    void setNTLMHash(const QString& NTLMHash) {mNTLMHash = NTLMHash;}
    void setResult(const QString& result) {mResult = result;}
    void setPrevalence(const QString& prevalence) {mPrevalence = prevalence;}

    QString getPassword() {return mPassword;}
    QString getNTLMHash() {return mNTLMHash;}
    QString getResult() {return mResult;}
    QString getPrevalence() {return mPrevalence;}

private:
    QString mPassword;
    QString mNTLMHash;
    QString mResult;
    QString mPrevalence;
};

#endif // PWNEDRESULT_H
