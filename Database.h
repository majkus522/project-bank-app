#pragma once

#include <QObject>
#include <libpq-fe.h>

class Database : public QObject
{
    Q_OBJECT

    private:
        PGconn* conn{};

    public:
        explicit Database(QObject* parent = nullptr);
        ~Database() override;
        PGconn* connection() const;
};