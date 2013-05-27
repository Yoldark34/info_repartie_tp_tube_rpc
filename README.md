You can make the executable by using the command :

    make -f Makefile.signal
    
You will lunch the server before the client in a terminal with

    ./signal_server
    
And the client after (it will create 2 clients in the same process)

    ./signal_client 127.0.0.1
    

The two clients will discuss with the use of tubes, each client will say hello to each other until never.
When a client receive or send a message it will inform the server by a RPC signal.
