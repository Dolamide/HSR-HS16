# NeDb

Simple Datenbank in Node, mit API Schnittstelle, die an MongoDB angelehnt ist.

```javascript

var Datastore = require('nedb');
var db = new Datastore({ filename: './data/order.db', autoload: true });

// insert a new entry
db.insert(order, function(err, newDoc){
    if(callback){
        callback(err, newDoc);
    }
});

// Find by id
db.findOne({ _id: id }, function (err, doc) {
    callback( err, doc);
});

// Update the state on all fileds with _id id to deleted
db.update({_id: id}, {$set: {"state": "DELETED"}}, {},
	  function (err, numReplaced, affectedDocuments) {
    // Load the entry (if it shall be returend) since we only get the numReplaced
    // from the update method back
    publicGet(id,callback);
});
```
