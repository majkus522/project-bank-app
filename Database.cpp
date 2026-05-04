#include "Database.h"
#include <iostream>

using namespace std;

Database::Database(QObject* parent) : QObject(parent)
{
    conn = PQconnectdb("host=127.0.0.1 port=5432 dbname=aplikacja_bankowa user=postgres password=P@ssw0rd");
    if (PQstatus(conn) != CONNECTION_OK)
        throw std::runtime_error(PQerrorMessage(conn));
}

Database::~Database()
{
    if (conn)
        PQfinish(conn);
}

PGconn * Database::connection() const
{
    if (PQstatus(conn) != CONNECTION_OK)
        PQreset(conn);
    return conn;
}