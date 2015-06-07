//
// Created by mikcy on 15. 6. 8.
//

#include "DBConnection.h"

mongocxx::collection DataBase::DBConnection::getCollection(const char *dbName
        , const char *collectionName) {
    return _c[dbName][collectionName];
}
