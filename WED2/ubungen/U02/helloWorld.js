const http = require('http');
const url = require('url');
const fs = require('fs')


function printNumbers(req, res) {
    // Parse url & load default values
    var url_parts = url.parse(req.url, true);
    var start = parseInt(url_parts.query.von) || 0;
    var end = parseInt(url_parts.query.bis) || 50;

    for (var i = start; i < end; i++) {
        res.write(String(i+1) + ' ');
    }
    res.end();
}

function writeDateFile(req, res) {
    fs.writeFile('datum.txt', new Date().toString(), function(err){
        fs.readFile('datum.txt', function(err, bf){
            res.end(bf);
        });
    });
}

function sendStatic(res, req, filename, contenttype){
    res.writeHeader(200, {"Content-Type": contenttype});
    fs.readFile(filename,  function(err, bf){
        res.end(bf);
    });
}

http.createServer( (req, res) => {
  res.writeHead(200, {'Content-Type': 'text/plain'});
  if (req.url.startsWith('/number')){
      printNumbers(req, res);
  }else if(req.url == '/file') {
      writeDateFile(req, res);
  }else if(req.url == '/ToSendHtml.html') {
      sendStatic(res, req, 'blub.html', 'text/html');
  // TODO: ToSendJavaScript.js
  }else{
      res.end(':(')
  }
}).listen(8000, '127.0.0.1');
