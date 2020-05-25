# Dice-with-C
A console based client-server multiplayer dice game with advanced C programming using sockets.

## Commands to run - 
1. gcc server.c -o server
2. gcc client.c -o client
3. ./server portNo
4. ./client IPAddr portNo

### Note
1. Client/server can be named anything after compiling
2. portNo in both server and client should be same for a successful connection.
3. IPAddr (IP Address) in the case of server is the one where server is hosted (get using the command: hostname -i)
