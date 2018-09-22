#ifndef SEEKER_H
#define SEEKER_H

#include <QRegularExpression>
#include <seekertokenizer.h>
#include <seekerparser.h>
#include <operatorpriority.h>
#include <QMap>
/**
 * @brief The Seeker class
 * \note this class cope with the
 */
class Seeker
{
public:
    /**
     * @brief Seeker
     */
    explicit Seeker();

    ~Seeker();
    /**
     * @brief setTokens
     * @param reg
     * \note set the regular expression to the token class
     */
    void setTokens(const QRegularExpression &reg);
    /**
     * @brief setQuery
     * @param query
     * @return boolean
     * \note set the query ready to be passed to the parser
     */
    bool setQuery(const QString &query);
    /**
     * @brief search launches the parser search
     */
    void search();

private:

    QRegularExpression _pattern;

    QString _query;

    SeekerTokenizer *_theTokenizer;

    SeekerParser *_theParser;
};

#endif // SEEKER_H
