//
// Created by mikcy on 15. 6. 8.
//

#ifndef JUDGESERVER_DBCONNECTION_H
#define JUDGESERVER_DBCONNECTION_H

#include <string>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>

namespace DataBase {
    class DBConnection {
    public :

        DBConnection(const char *path = "mongodb://192.168.0.38"):
                _path(path), _c(_path) { }

        mongocxx::collection getCollection(const char *dbName
                , const char *collectionName);

    private :
        mongocxx::instance _i;
        mongocxx::uri _path;
        mongocxx::client _c;
    };
}


#endif //JUDGESERVER_DBCONNECTION_H
