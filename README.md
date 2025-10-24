# My_irc

An implementation of an IRC (Internet Relay Chat) server in C++, compatible with RFC 2812.  
This project aims to build a fully functional IRC server that can interact with real IRC clients such as HexChat, irssi, or netcat.

---

## Installation

Clone the repository and build the project:

```bash
git clone https://github.com/<your-username>/ft_irc.git
cd ft_irc
make
```

This will produce an executable called ircserv.

## Usage

Run the server with a chosen port and password:

```bash
./ircserv <port> <password>
```

For example:

```bash
./ircserv 6667 mypass
```

The server will start listening for incoming connections on the given port.

## Testing with HexChat

To test your server using HexChat:

Install HexChat

- On macOS: brew install --cask hexchat
- On Linux (Debian/Ubuntu): sudo apt install hexchat
- On Windows: Download from the official site

Open HexChat → Network List → Add

- Name your network (e.g. ft_irc).
- Click Edit...
- Add a new server:

      localhost/6667

- Uncheck “Use global user information” and set:

  Nickname: your test nick (e.g. BillieBob)
  Login method: none
  Password: the same as the one you passed to ircserv (e.g. hello)

- Connect!

    You should see connection messages in the HexChat log window.
    You can now try commands such as /join, /nick, /privmsg, etc.

If you just want to test quickly without HexChat, you can also connect using nc (netcat):

```bash
nc localhost 6667
```

## Implemented Commands
🔹 Connection & Registration

    PASS <password> — authenticate before registration
    NICK <nickname> — set or change nickname
    USER <username> <hostname> <servername> <realname> — register user
    QUIT [message] — disconnect from the server

🔹 Channel Management

    JOIN <#channel> — join or create a channel
    PART <#channel> [message] — leave a channel
    TOPIC <#channel> [topic] — view or set the channel topic
    MODE <#channel> <modes> [parameters] — set channel modes (e.g. +i, +t, +k, +o, +l)
    KICK <#channel> <user> [comment] — remove a user from a channel
    INVITE <nickname> <#channel> — invite a user to a channel

🔹 Messaging

    PRIVMSG <target> <message> — send a private message to a user or channel

🔹 Miscellaneous

    WHOIS <nickname> — show information about a user


The server uses poll() to handle multiple clients concurrently in a single thread, ensuring non-blocking I/O and real-time communication.

## Authors

Project made with @shehanish and @mimonata

## References

    RFC 2812: Internet Relay Chat: Client Protocol

    RFC 1459: Original IRC Protocol Specification






