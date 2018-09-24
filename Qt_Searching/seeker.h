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
     * @brief setQuery
     * @param query
     * @return boolean
     * \note set the query ready to be passed to the parser
     */
    bool setQuery(const QString &query);
    /**
     * @brief search launches the parser search
     */
    bool search(const QString &query);

private:

    QRegularExpression _pattern;

    QString _query;

    SeekerTokenizer *_theTokenizer;

    SeekerParser *_theParser;
};

#endif // SEEKER_H
