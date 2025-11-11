/*
 * HaveIBeenPwned Local
 * Copyleft 2025
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
