# 🌐 Networking in C: The Journey

> "The hardest part of any journey is the first step. The second hardest part is the socket() call."

Welcome to my personal laboratory for mastering network programming in C. This repository is a living document of my progress through the legendary **[Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)**. 

![C](https://img.shields.io/badge/Language-C-blue.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Progress](https://img.shields.io/badge/Progress-Learning-orange.svg)

---

## 🚀 The Mission

The goal is simple but ambitious: to implement every core concept, system call, and technique discussed in Beej's Guide. From the basic "What is a socket?" to advanced I/O multiplexing with `poll()` and `epoll()`.

## 📂 Repository Structure

Right now, I'm laying the foundation with the essential system calls. Each directory represents a specific milestone:

- `getaddr_practice/`: Mastering `getaddrinfo()`—the modern way to prepare for launch.
- `socket/`: Getting that elusive File Descriptor.
- `socket_with_bind/`: Associating a socket with a local port.
- `socket_with_connect/`: Reaching out and touching a remote host.

---

## 🗺️ Roadmap & Progress

### Phase 1: The Fundamentals
- [x] **IP Addresses & Structs** (`struct addrinfo`, `sockaddr_in`)
- [x] **getaddrinfo()** — Prepare to launch!
- [x] **socket()** — Get the File Descriptor
- [x] **bind()** — What port am I on?
- [x] **connect()** — Hey, you!
- [ ] **listen()** — Will somebody please call me?
- [ ] **accept()** — "Thank you for calling port 3490."
- [ ] **send() & recv()** — Talk to me, baby!
- [ ] **sendto() & recvfrom()** — Datagram-style

### Phase 2: Building the Apps
- [ ] **Simple Stream Server**
- [ ] **Simple Stream Client**
- [ ] **Datagram Sockets**

### Phase 3: Advanced Techniques
- [ ] **Blocking & Non-blocking**
- [ ] **poll() / select()** — Synchronous I/O Multiplexing
- [ ] **Handling Partial sends**
- [ ] **Serialization** — Packing data like a pro

---

## 🛠️ Getting Started

Most examples can be compiled using `gcc` or `clang`. For instance:

```bash
cd getaddr_practice
gcc showip.c -o showip
./showip google.com
```

## 🧠 Lessons Learned

I'm keeping my notes directly inside the source files. You'll find my "Aha!" moments and occasional frustrations documented in the comments. It’s not just code; it’s a brain dump.

---

*“If you're not failing, you're not learning.”* — Someone who probably had a lot of `bind()` errors.
