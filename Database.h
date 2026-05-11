#pragma once

#include <libpq-fe.h>
#include <QObject>

class Database : public QObject
{
    Q_OBJECT

    public:
        static Database& getInstance()
        {
            static Database instance;
            return instance;
        }

        Database(const Database&) = delete;
        Database& operator=(const Database&) = delete;
        Database(Database&&) = delete;
        Database& operator=(Database&&) = delete;

        PGconn* connection() const;

    private:
        Database();
        ~Database() override;
        PGconn* conn;
};
