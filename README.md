# minitalk 💬

A lightweight communication program using UNIX signals to transmit strings between processes. This project explores inter-process communication, signal handling, and bitwise operations in a creative way.

## 📋 Table of Contents

- [About](#about)
- [The Magic Behind](#the-magic-behind)
- [Getting Started](#getting-started)
- [How It Works](#how-it-works)
- [Usage](#usage)
- [Signal Flow](#signal-flow)
- [Testing](#testing)
- [Project Structure](#project-structure)
- [Technical Deep Dive](#technical-deep-dive)
- [Challenges & Solutions](#challenges--solutions)
- [License](#license)

## 🎯 About

minitalk is a fascinating project from the 42 curriculum that I tackled at 1337 School. It's essentially building a chat system using only UNIX signals - no pipes, no sockets, just pure signal magic! The challenge was to create a client-server communication system where the client sends strings to the server using only `SIGUSR1` and `SIGUSR2` signals.

Think of it as **Morse code for computers** - but instead of dots and dashes, we use two different signals to represent binary data! 📡

## ✨ The Magic Behind

What makes this project special is its elegant simplicity:

- **Two signals, infinite possibilities**: Using just `SIGUSR1` and `SIGUSR2` to transmit entire messages
- **Binary communication**: Each character travels bit by bit through the signal highway  
- **Process synchronization**: Client and server dance together in perfect signal harmony
- **Real-time messaging**: Watch your messages appear character by character on the server side

It's like watching your message teleport through the system, one bit at a time! 🚀

## 🚀 Getting Started

### Prerequisites

- GCC compiler
- Make
- A UNIX-based system (Linux/macOS)
- Basic understanding of signals and processes

### Installation

1. Clone the repository:
```bash
git clone https://github.com/abnemili/minitalk.git
cd minitalk
```

2. Compile both programs:
```bash
make
```

This creates two executables: `server` and `client`

## ⚙️ How It Works

### The Protocol I Designed

My implementation uses a simple but effective binary protocol:

1. **Server starts** and displays its PID (Process ID)
2. **Client takes** the server PID and message as arguments
3. **Message encoding**: Each character is broken into 8 bits
4. **Signal mapping**: 
   - `SIGUSR1` = Binary `0`
   - `SIGUSR2` = Binary `1`
5. **Bit transmission**: Send each bit as a signal, LSB to MSB
6. **Character reconstruction**: Server rebuilds characters bit by bit
7. **Message display**: Server prints the complete message

### Visual Representation

```
Message: "Hi!"
H = 72  = 01001000₂  →  SIGUSR1,SIGUSR1,SIGUSR1,SIGUSR2,SIGUSR1,SIGUSR1,SIGUSR1,SIGUSR1
i = 105 = 01101001₂  →  SIGUSR2,SIGUSR1,SIGUSR1,SIGUSR1,SIGUSR2,SIGUSR2,SIGUSR1,SIGUSR2  
! = 33  = 00100001₂  →  SIGUSR2,SIGUSR1,SIGUSR1,SIGUSR1,SIGUSR1,SIGUSR1,SIGUSR2,SIGUSR1
```

## 💻 Usage

### Starting the Server

```bash
./server
```
Output:
```
🚀 Server started!
📡 PID: 12345
💭 Waiting for messages...
```

### Sending Messages

```bash
# Basic message
./client 12345 "Hello, World!"

# Special characters and emojis work too!
./client 12345 "42 School is awesome! 🎯"

# Long messages
./client 12345 "This is a really long message that will be transmitted bit by bit through signals. Pretty cool, right?"
```

### Real-time Communication

**Terminal 1 (Server):**
```bash
$ ./server
🚀 Server started!
📡 PID: 12345
💭 Waiting for messages...
📨 Received: Hello, World!
📨 Received: 42 School rocks! 🚀
📨 Received: Signal magic is real ✨
```

**Terminal 2 (Client):**
```bash
$ ./client 12345 "Hello, World!"
✅ Message sent successfully!

$ ./client 12345 "42 School rocks! 🚀"
✅ Message sent successfully!

$ ./client 12345 "Signal magic is real ✨"
✅ Message sent successfully!
```

## 🔄 Signal Flow

Here's how my communication protocol works:

```
CLIENT SIDE                           SERVER SIDE
┌─────────────┐                      ┌─────────────┐
│   "Hello"   │                      │   Server    │
│             │                      │  (PID:1234) │
└──────┬──────┘                      └──────┬──────┘
       │                                    │
       ▼                                    ▼
┌─────────────┐    SIGUSR1/SIGUSR2    ┌─────────────┐
│ Bit encoder │ ──────────────────────►│Signal handler│
│             │    (8 bits per char)   │             │
└─────────────┘                       └─────────────┘
                                             │
                                             ▼
                                      ┌─────────────┐
                                      │Bit collector│
                                      │& Character  │
                                      │Reconstruction│
                                      └──────┬──────┘
                                             │
                                             ▼
                                      ┌─────────────┐
                                      │   Display   │
                                      │  "Hello"    │
                                      └─────────────┘
```

## 🧪 Testing

### Basic Functionality Tests

```bash
# Test simple messages
./client $(pgrep server) "Test"
./client $(pgrep server) "42"
./client $(pgrep server) "Hello World!"

# Test special characters  
./client $(pgrep server) "Special chars: !@#$%^&*()"
./client $(pgrep server) "Numbers: 1234567890"

# Test empty message
./client $(pgrep server) ""
```

### Stress Testing

```bash
# Long message test
./client $(pgrep server) "$(cat /usr/share/dict/words | head -100 | tr '\n' ' ')"

# Multiple clients (run simultaneously)
for i in {1..5}; do
    ./client $(pgrep server) "Message from client $i" &
done
```

### Performance Testing

```bash
# Time measurement
time ./client $(pgrep server) "Performance test message"

# Character transmission rate
echo "Testing transmission speed..." 
./client $(pgrep server) "This message will show how fast our signal protocol works!"
```

## 📁 Project Structure

```
minitalk/
├── Makefile
├── minitalk.h           # Shared header file
├── server.c             # Server implementation  
├── client.c             # Client implementation
├── utils.c              # Helper functions (if any)
└── README.md
```

## 🔧 Technical Deep Dive

### Signal Handling Strategy

My approach to handling signals safely and efficiently:

```c
// Signal handler structure
void    handle_signal(int sig, siginfo_t *info, void *context)
{
    static int  bit_index = 0;
    static int  current_char = 0;
    
    // Build character bit by bit
    if (sig == SIGUSR2)
        current_char |= (1 << bit_index);
    
    bit_index++;
    
    // Character complete
    if (bit_index == 8)
    {
        if (current_char == 0)
            write(1, "\n", 1);
        else
            write(1, &current_char, 1);
        
        bit_index = 0;
        current_char = 0;
    }
}
```

### Client Transmission Logic

```c
void    send_char(int pid, unsigned char c)
{
    int bit_index;
    
    bit_index = 0;
    while (bit_index < 8)
    {
        if (c & (1 << bit_index))
            kill(pid, SIGUSR2);  // Send '1'
        else
            kill(pid, SIGUSR1);  // Send '0'
        
        usleep(100);  // Small delay for reliability
        bit_index++;
    }
}
```

## 🎯 Challenges & Solutions

### Challenge 1: Signal Reliability
**Problem**: Signals can be lost or arrive out of order
**My Solution**: Added small delays between transmissions and used static variables for state management

### Challenge 2: Process Synchronization  
**Problem**: Client sending too fast for server to process
**My Solution**: Implemented microsecond delays (`usleep`) to ensure reliable transmission

### Challenge 3: Character Encoding
**Problem**: Converting characters to bits and back reliably
**My Solution**: Used bitwise operations with clear bit indexing from LSB to MSB

### Challenge 4: Memory Safety
**Problem**: Signal handlers have restrictions on functions they can call
**My Solution**: Used only async-signal-safe functions like `write()` in signal handlers

### Challenge 5: Error Handling
**Problem**: Handling invalid PIDs and signal failures
**My Solution**: Comprehensive error checking with meaningful error messages

## 🏆 What I Learned

This project was an incredible journey into system-level programming:

- **Signal Mastery**: Deep understanding of UNIX signal handling
- **Bitwise Magic**: Became comfortable with bit manipulation operations  
- **Process Communication**: Learned alternative IPC methods beyond pipes/sockets
- **Async Programming**: Handled asynchronous signal-driven communication
- **System Calls**: Worked directly with low-level system interfaces
- **Debugging Skills**: Traced complex inter-process communication issues

## 🌟 Cool Features I Added

- **Visual feedback**: Server shows emoji indicators for different states
- **Error resilience**: Handles edge cases gracefully
- **Performance optimization**: Minimal delays for faster transmission
- **Clean output**: Proper formatting and user-friendly messages
- **Robust parsing**: Handles various input formats correctly

## 🤝 Contributing

This is my personal implementation of the minitalk project from the 42 curriculum at 1337 School. While the code is available for reference and learning purposes, please remember to follow 1337's academic integrity guidelines if you're a current student.

## 📄 License

This project was developed by me as part of the 42 curriculum studied at 1337 School. Feel free to explore and learn from the implementation!

---

**Note**: This implementation showcases the beauty of inter-process communication using the most fundamental UNIX concept - signals. It's amazing how two simple signals can carry entire conversations across processes! 

*Transmitted with 📡 by abnemili at 1337 School*
