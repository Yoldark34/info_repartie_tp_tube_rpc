You need to have a 64 bit OS or follow the step 2

Step 1

You can make the executable by using the command :

    make -f Makefile.signal
    
You will lunch the server before the client in a terminal with

    ./signal_server
    
And the client in another terminal after (it will create 2 clients in the same process)

    ./signal_client 127.0.0.1
    

The two clients will discuss with the use of tubes, each client will say hello to each other until never.
When a client receive or send a message it will inform the server by a RPC signal.

Step 2

if you have a 32 bit OS

Keep "signal_client.c" and "signal_server.c" in a folder.
Delete all the items except signal.x

execute in a terminal on the folder

    rpcgen -a signal.x
    
And now paste "signal_client.c" and "signal_server.c" saved before.

Now you can make the file like in the begening of the readme.
