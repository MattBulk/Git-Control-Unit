#ifndef SEEKERPARSER_H
#define SEEKERPARSER_H

#include <seekertokenizer.h>
#include <QHash>
#include <QVariant>
/**
 * @brief The SeekerParser class
 * \note this parser class collects informations from the QRegularExpressionMatcher and works the contents of parenthesis recursively
 */
class SeekerParser
{
public:
    /**
     * @brief SeekerParser
     * @param tok
     * @param query
     */
    SeekerParser(SeekerTokenizer *tok, const QString &query);

    ~SeekerParser();
    /**
     * @brief queryParsing starts the parsing
     */
    void queryParsing();

private:
    /**
     * @brief sortByProperty
     * @param vect
     * @param property
     * \note this method uses the stable_sort descending order
     */
    void sortByProperty(QVector<QHash<QString, QVariant>> &vect, const QString &property);
    /**
     * @brief parseNakedQuery
     * @param query
     * \note it parses a line of operations without parenthesis
     */
    void parseNakedQuery(QString &query);
    /**
     * @brief parserSingleTokenizer
     * @param parenthCont
     * @param currentOperator
     * \note it parse the content on a single parenthesis
     */
    void parserSingleTokenizer(const QString &parenthCont, const QString &currentOperator);
    /**
     * @brief parserMultiTokenizer
     * @param parenthCont
     * @param currentOperator
     * @param currentQuery
     * \note it takes the content from a line of operation and return the query with the right results correctly positioned
     */
    void parserMultiTokenizer(QString &parenthCont, const QString &currentOperator, QString &currentQuery);

    SeekerTokenizer *_theTok;

    QString _query;

    QVector<QHash<QString, QVariant>> _operatorsPriVect;

    QVector<QHash<QString, QVariant>> _operatorsPosVect;


};

#endif // SEEKERPARSER_H
