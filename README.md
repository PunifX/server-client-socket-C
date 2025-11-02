# server-client-socket-C

Simple TCP server/client example in C (work in progress).

## Overview
- This repository contains a minimal TCP server and client implemented in C.
- `server.c`: multi-threaded TCP server that accepts connections, receives a client name, then echoes messages back to the sender.
- `client.c`: simple TCP client that connects to the server, sends a name, and exchanges messages.

## Build
- Requires a POSIX environment and gcc.
- Example build commands:
  - `gcc -pthread server.c -o server`
  - `gcc client.c -o client`

## Run
- **Server:**
  - `./server`
  - The server currently listens on `0.0.0.0:8080` (hardcoded).
- **Client:**
  - `./client <server-ip> <port>`
  - Example: `./client 127.0.0.1 8080`
  - After connecting, the client prompts for a name, then you can type messages.

## Current status / known limitations
- Project is not finished.
- **Server:**
  - Accepts connections and spawns a detached pthread per client.
  - Receives a client name, prints connect/disconnect messages, and echoes received data back to the same client.
  - Port is hardcoded to 8080.
  - No graceful shutdown or signal handling.
- **Client:**
  - Connects to the server and sends user-entered messages.
  - Blocking calls; no concurrent receive loop (client sends then waits for a server reply in sequence).
- **Protocol:**
  - Very minimal, no framing or length-prefixing; relies on simple send/recv and buffer sizes.
- **Error handling:**
  - Basic; needs improvement (partial writes/reads are not fully handled).

## Suggested next steps / TODO
- Make server port configurable via command-line arguments.
- Add proper signal handling (SIGINT) for graceful shutdown and socket cleanup.
- Improve send/recv robustness (handle partial reads/writes, define message framing).
- Add a client-side receive thread so the client can both send and receive asynchronously.
- Add logging and better error messages.
- Consider using a simple protocol (length-prefix) or newline-terminated messages.
- Add a Makefile and basic tests or example scripts.
- Add LICENSE and CONTRIBUTING notes.

## Files
- `server.c` — multi-threaded echo-like server (pthread, accept loop).
- `client.c` — simple client that connects, sends a name, and exchanges messages.
- `README.md` — this file.

If you want, I can:
- Make the server port configurable.
- Add client-side receiving in a separate thread.
- Add a Makefile and basic run scripts.
