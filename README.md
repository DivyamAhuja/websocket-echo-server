# WebSocket Echo Server
---

A simple websocket server written in c using libwebsockets library.
<br>
Demo client in nodejs and python.

# Build

If you have libwebsockets installed, just run `make`, <br>
otherwise make and install libwebsockets with cmake flags <br>
(`-DLIB_SUFFIX=64 -DLWS_UNIX_SOCK=1 -DLWS_WITHOUT_EXTENSIONS=0`)<br>
(`-DCMAKE_INSTALL_PREFIX:PATH=/usr` for global install) <br>
Or you can link dynamically with libwebsockets.a

# Running Client

## Node JS
```
npm install
node client.js
```

## Python
```
pip install -r python-requirements.txt
python client.py
```