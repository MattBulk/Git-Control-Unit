#include "seeker.h"
#include <QDebug>

Seeker::Seeker()
{
    this->_theTokenizer = new SeekerTokenizer();
    this->_theParser = new SeekerParser(this->_theTokenizer);
    this->_theTokenizer->init();
}

Seeker::~Seeker()
{
    qDebug("Seeker::~Seeker");
    delete this->_theParser;
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

bool Seeker::search(const QString &query)

{
    this->_query = query.simplified();
    this->_query.replace(" ", "");
    if(this->_theTokenizer->parenthesisChecker(query) && this->_theTokenizer->multiOperatorChecker(this->_query)) {
        this->_theParser->queryParsing(this->_query);
        return(true);
    }
    else {
        return(false);
    }
}
