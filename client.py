import asyncio
import re
import websockets
import sys

async def hello():
    async with websockets.client.unix_connect("/tmp/meow.sock",subprotocols=["ws_echo"] ,compression=None) as websocket:
        while (True):
            msg = input('Enter Message to send("exit" to close connection): ')
            if msg.strip() == "exit":
                await websocket.close(reason="user wants to close the websocket connection.")
                print("Connection closed.")
                break
            else:
                await websocket.send(msg)
                reply = await websocket.recv()
                print("Server Replied :", reply)
asyncio.get_event_loop().run_until_complete(hello())