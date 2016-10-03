NeDb
====

Simple Datenbank in Node, mit API Schnittstelle, die an MongoDB angelehnt ist.

.. code:: javascript

    var Datastore = require('nedb');
    var db = new Datastore({ filename: './data/order.db', autoload: true });

    db.insert(order, function(err, newDoc){
        if(callback){
            callback(err, newDoc);
        }
    });
    db.findOne({ _id: id }, function (err, doc) {
        callback( err, doc);
    });

    db.update({_id: id}, {$set: {"state": "DELETED"}}, {}, function (err, doc) {
        publicGet(id,callback);
    });
