#include "seekerparser.h"
#include <QDebug>

SeekerParser::SeekerParser(SeekerTokenizer *tok, const QString &query)
{
    this->_theTok = tok;
    this->_query = query;
}

SeekerParser::~SeekerParser()
{
    qDebug("SeekerParser::~SeekerParser");
    delete this->_theTok;
}

void SeekerParser::queryParsing()
{
    this->_operatorsPriVect.clear();
    QString parenthCont;
    QString currentOper;
    while(currentOper != "none") {
        QString queryRef;
        parenthCont = this->_theTok->parenthesisMatcher(this->_query, queryRef);
        if(parenthCont.isEmpty())
            break;
        if(this->_theTok->operatorsNumberChecker(parenthCont) == 1) {
            currentOper = this->_theTok->singleOperatorMatcher(parenthCont);
            this->parserSingleTokenizer(parenthCont, currentOper);
        }
        else {
            this->_operatorsPosVect = this->_theTok->multiOperatorMatcher(parenthCont);
            this->_operatorsPriVect = this->_operatorsPosVect;
            this->sortByProperty(this->_operatorsPriVect, "priority");
            this->parseNakedQuery(parenthCont);
        }
    }
    this->_operatorsPosVect = this->_theTok->multiOperatorMatcher(this->_query);
    this->_operatorsPriVect = this->_operatorsPosVect;
    this->sortByProperty(this->_operatorsPriVect, "priority");
    this->parseNakedQuery(this->_query);
    this->parserMultiTokenizer(this->_query, this->_theTok->singleOperatorMatcher(this->_query), this->_query);
}

void SeekerParser::sortByProperty(QVector<QHash<QString, QVariant>> &vect, const QString &property)
{
    std::stable_sort(vect.begin(), vect.end(), [&property](const QHash<QString, QVariant> &a, const QHash<QString, QVariant> &b) {
        int val_a = a.value(property).toInt();
        int val_b = b.value(property).toInt();
        return val_a > val_b;
    });
}

void SeekerParser::parseNakedQuery(QString &query)
{
    while(this->_operatorsPriVect.size() > 1) {
        QHash<QString, QVariant> currentOp = this->_operatorsPriVect.at(0);
        QString subStr, currentOpSign;
        int currentOpPos = 0, currentPos = 0, rightPos = 0, leftPos = 0, dist = 0;
        qDebug()<<"operator:"<<currentOp.value("operator").toString();
        for(int i = 0; i < this->_operatorsPosVect.size(); ++i) {
            currentOpPos = currentOp.value("start").toInt();
            currentOpSign = this->_operatorsPosVect.at(i).value("operator").toString();
            currentPos = this->_operatorsPosVect.at(i).value("start").toInt();
            if(currentOpPos == currentPos) {
                if(i == 0 && this->_operatorsPosVect.size() > 0) {
                    leftPos = 0;
                    rightPos = this->_operatorsPosVect.at(i+1).value("start").toInt();
                    subStr = query.mid(leftPos, rightPos);
                    qDebug()<<"subStr 0:"<<subStr;
                }
                else if(i > 0) {
                    leftPos = this->_operatorsPosVect.at(i-1).value("start").toInt() + this->_operatorsPosVect.at(i-1).value("length").toInt();
                    if(i < this->_operatorsPosVect.size()-1) {
                        rightPos = this->_operatorsPosVect.at(i+1).value("start").toInt();
                        dist = rightPos - leftPos;
                    }
                    else if(i == this->_operatorsPosVect.size()-1) {
                        dist = -1;
                    }
                    subStr = query.mid(leftPos, dist);
                    qDebug()<<"subStr >0:"<< subStr;
                }
                else qDebug()<<"mistake";
                this->parserMultiTokenizer(subStr, currentOpSign, query);
                this->_operatorsPosVect = this->_theTok->multiOperatorMatcher(query);
                this->_operatorsPriVect = this->_operatorsPosVect;
                this->sortByProperty(this->_operatorsPriVect, "priority");
                break;
            }
        }
    }
}

void SeekerParser::parserMultiTokenizer(QString &parenthCont, const QString &currentOperator, QString &currentQuery)
{
    QStringList listParenthCont = parenthCont.split(currentOperator);
    QString toReplace = QString("%1").arg(parenthCont);
    currentQuery.replace(toReplace, "result");
    this->_query.replace(toReplace, "result");
    qDebug() << this->_query;
}

void SeekerParser::parserSingleTokenizer(const QString &parenthCont, const QString &currentOperator)
{
    QStringList listParenthCont = parenthCont.split(currentOperator);
    QString toReplace = QString("(%1)").arg(parenthCont);
    this->_query.replace(toReplace, "result");
    qDebug() << this->_query;
}
