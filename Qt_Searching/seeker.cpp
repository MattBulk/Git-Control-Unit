#include "seeker.h"
#include <QDebug>

Seeker::Seeker()
{

}

Seeker::~Seeker()
{
    qDebug("Seeker::~Seeker");
    delete this->_theParser;
}

void Seeker::setTokens(const QRegularExpression &reg)
{
    this->_pattern = reg;
    this->_theTokenizer = new SeekerTokenizer(this->_pattern);
    this->_theTokenizer->init();
}

bool Seeker::setQuery(const QString &query)
{
    // reduce whitespaces to one then remove all whitespace
    this->_query = query.simplified();
    this->_query.replace(" ", "");
    if(this->_theTokenizer->parenthesisChecker(query) && this->_theTokenizer->multiOperatorChecker(this->_query))
        return(true);
    else
        return(false);
}

void Seeker::search()
{
    this->_theParser = new SeekerParser(this->_theTokenizer, this->_query);
    this->_theParser->queryParsing();
}
