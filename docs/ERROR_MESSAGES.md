# IRC Error Messages Implementation

This document lists the IRC numeric replies and error messages implemented by the current server code (srcs/Server.cpp) and documents formats and usage observed in the program.

Notes:
- The server identifies itself as "localhost" in all replies.
- Numeric replies and errors are formatted according to RFC 1459/2812 conventions used in the code.
- Messages are appended to each client's send buffer by the server; buffering and actual socket writes occur in the main loop.
- When a client is not registered, the server includes "*" or the client's temporary nick where applicable.
- The implementation targets IPv4 and uses poll()-based I/O for socket management.

---

## Implemented Success Replies

| Code | Name | Format used in code | Description |
|------|------|---------------------|-------------|
| 001 | RPL_WELCOME | `:localhost 001 <nick> :Welcome to the IRC Network <nick>!<user>@localhost` | Welcome message sent after successful registration (NICK+USER+PASS as required). |
| 324 | RPL_CHANNELMODEIS | `:localhost 324 <nick> <channel> <modes> [params]` | Channel mode response. |
| 331 | RPL_NOTOPIC | `:localhost 331 <nick> <channel> :No topic is set` | No topic is set for the channel. |
| 332 | RPL_TOPIC | `:localhost 332 <nick> <channel> :<topic>` | Current topic for channel. |
| 341 | RPL_INVITING | `:localhost 341 <nick> <target> <channel>` | Invite confirmation. |
| 353 | RPL_NAMREPLY | `:localhost 353 <nick> = <channel> :<names>` | Names list for a channel. |
| 366 | RPL_ENDOFNAMES | `:localhost 366 <nick> <channel> :End of /NAMES list` | End of names list. |
| 315 | RPL_ENDOFWHO | `:localhost 315 <nick> <mask> :End of WHO list` | End of WHO list. |
| 352 | RPL_WHOREPLY | `:localhost 352 <nick> <channel> <user> <host> <server> <nick> <flags> :<hopcount> <realname>` | WHO reply entry format. |

---

## Implemented Error Replies

### Authentication / Registration
| Code | Name | Format | Used in |
|------|------|--------|---------|
| 451 | ERR_NOTREGISTERED | `:localhost 451 <nick> :You have not registered` | Sent when a client issues commands before successful registration. |
| 462 | ERR_ALREADYREGISTERED | `:localhost 462 <nick> :You may not reregister` | Sent when a client attempts to re-run registration commands (PASS/NICK/USER) after already registered. |
| 464 | ERR_PASSWDMISMATCH | `:localhost 464 <nick> :Password incorrect` | Sent when PASS does not match server password. |

### Command Parameters
| Code | Name | Format | Used in |
|------|------|--------|---------|
| 431 | ERR_NONICKNAMEGIVEN | `:localhost 431 :No nickname given` | NICK called without parameter. |
| 461 | ERR_NEEDMOREPARAMS | `:localhost 461 <nick> <command> :Not enough parameters` | Missing parameters for commands (JOIN, KICK, INVITE, TOPIC, MODE, PRIVMSG, etc.). |
| 421 | ERR_UNKNOWNCOMMAND | `:localhost 421 <nick> <command> :Unknown command` | Unrecognized command discovered in parse(). |

### Nickname Errors
| Code | Name | Format | Used in |
|------|------|--------|---------|
| 432 | ERR_ERRONEUSNICKNAME | `:localhost 432 <nick> <badnick> :Erroneous nickname` | Invalid nickname syntax. |
| 433 | ERR_NICKNAMEINUSE | `:localhost 433 <nick> <badnick> :Nickname is already in use` | Nickname already taken by another connected client. |

### Channel-related Errors
| Code | Name | Format | Used in |
|------|------|--------|---------|
| 401 | ERR_NOSUCHNICK | `:localhost 401 <nick> <target> :No such nick/channel` | Target nick or channel does not exist (PRIVMSG, KICK, INVITE). |
| 403 | ERR_NOSUCHCHANNEL | `:localhost 403 <nick> <channel> :No such channel` | Channel doesn't exist (MODE, TOPIC, INVITE, PART). |
| 404 | ERR_CANNOTSENDTOCHAN | `:localhost 404 <nick> <channel> :Cannot send to channel` | Client not permitted to send to channel (PRIVMSG). |
| 405 | ERR_TOOMANYCHANNELS | `:localhost 405 <nick> <channel> :You have joined too many channels` | Client exceeded configured max channels (JOIN). |
| 412 | ERR_NOTEXTTOSEND | `:localhost 412 <nick> :No text to send` | PRIVMSG with empty message. |
| 441 | ERR_USERNOTINCHANNEL | `:localhost 441 <nick> <target> <channel> :They aren't on that channel` | KICK target is not on channel. |
| 442 | ERR_NOTONCHANNEL | `:localhost 442 <nick> <channel> :You're not on that channel` | Client is not a member of the channel (PART, TOPIC, INVITE). |
| 443 | ERR_USERONCHANNEL | `:localhost 443 <nick> <target> <channel> :is already on channel` | Invite target already present on channel. |
| 471 | ERR_CHANNELISFULL | `:localhost 471 <nick> <channel> :Cannot join channel (+l)` | Channel reached user limit. |
| 473 | ERR_INVITEONLYCHAN | `:localhost 473 <nick> <channel> :Cannot join channel (+i)` | Channel is invite-only. |
| 475 | ERR_BADCHANNELKEY | `:localhost 475 <nick> <channel> :Cannot join channel (+k) - bad key` | Wrong channel key provided. |
| 482 | ERR_CHANOPRIVSNEEDED | `:localhost 482 <nick> <channel> :You're not channel operator` | Operator privileges required (KICK, MODE, TOPIC +t, INVITE +i). |

---

## Command-specific error usage (summary)

- JOIN: 461, 405, 475, 473, 471
- PART: 461, 403, 442
- PRIVMSG: 461, 412, 401, 404
- KICK: 461, 403, 442, 482, 401, 441
- INVITE: 461, 401, 403, 442, 443, 482
- TOPIC: 461, 403, 442, 482
- MODE: 461, 403, 482
- NICK: 431, 432, 433, 462
- PASS: 464, 462
- USER: 461, 462
- WHO: returns 352 entries and 315 end marker for who lists

---
