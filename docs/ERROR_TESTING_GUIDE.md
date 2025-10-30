# IRC Server Error Messages Testing Guide

This guide provides test cases for all error messages implemented in the IRC server.

## Setup
1. Start server: `./ircserv 5506 hello`
2. Connect 3 HexChat clients (f.i. Sheha, Lotte, Saby)
3. Connect 1 netcat client (f.i. Iroh)
```
nc -C 127.0.0.1 <port>
```
(-C will allow you to send \r\n without having to use very complicated key combinations)
4. All clients should authenticate and join #test

---

## Authentication Error Tests

Open extra terminal
Run test script from folder /tests
---

## JOIN Command Error Tests

### Test ERR_TOOMANYCHANNELS (405)
**What to test:** Exceeded max channels
```
/join #channel1
/join #channel2
/join #channel3
... (continue until limit - default is 10)
/join #channel11
Expected: :localhost 405 sheha #channel11 :You have joined too many channels
```

### Test ERR_BADCHANNELKEY (475)
**What to test:** Wrong channel password
```
Client 1: /join #private
Client 1: /mode #private +k secret123
Client 2: /join #private
Expected: :localhost 475 Lotte #private :Cannot join channel (+k) - bad key

Client 2: /join #private wrongkey
Expected: :localhost 475 Lotte #private :Cannot join channel (+k) - bad key

Client 2: /join #private secret123
Expected: Success (joins channel)
```

### Test ERR_INVITEONLYCHAN (473)
**What to test:** Join invite-only channel without invite
```
Client 1: /join #exclusive
Client 1: /mode #exclusive +i
Client 2: /join #exclusive
Expected: :localhost 473 Lotte #exclusive :Cannot join channel (+i)
```

### Test ERR_CHANNELISFULL (471)
**What to test:** Channel user limit reached
```
Client 1: /join #limited
Client 1: /mode #limited +l 2
Client 2: /join #limited
Client 3: /join #limited
Expected: :localhost 471 Saby #limited :Cannot join channel (+l)
```

---

## PART Command Error Tests

### Test ERR_NEEDMOREPARAMS (461) - PART
**What to test:** PART without channel name
```
/quote PART
Expected: :localhost 461 sheha PART :Not enough parameters
```

### Test ERR_NOSUCHCHANNEL (403) - PART
**What to test:** PART from non-existent channel
```
/part #nonexistent
Expected: :localhost 403 sheha #nonexistent :No such channel
```

### Test ERR_NOTONCHANNEL (442) - PART
**What to test:** PART from channel you're not in
```
Client 1: /join #test
Client 2: /part #test (without joining first)
Expected: :localhost 442 Lotte #test :You're not on that channel
```

---

## PRIVMSG Command Error Tests

### Test ERR_NEEDMOREPARAMS (461) - PRIVMSG
**What to test:** PRIVMSG without parameters
```
/quote PRIVMSG
Expected: :localhost 461 sheha PRIVMSG :Not enough parameters
```

### Test ERR_NOTEXTTOSEND (412)
**What to test:** PRIVMSG without message
```
/quote PRIVMSG #test
Expected: :localhost 412 sheha :No text to send
```

### Test ERR_NOSUCHNICK (401) - PRIVMSG
**What to test:** Message to non-existent user
```
/msg nonexistentuser hello
Expected: :localhost 401 sheha nonexistentuser :No such nick/channel
```

### Test ERR_NOSUCHCHANNEL (401) - PRIVMSG
**What to test:** Message to non-existent channel
```
/msg #nonexistent hello
Expected: :localhost 401 sheha #nonexistent :No such nick/channel
```

### Test ERR_CANNOTSENDTOCHAN (404)
**What to test:** Send message to channel you're not in
```
Client 1: /join #test
Client 2: (not in #test)
Client 2: /msg #test hello
Expected: :localhost 404 Lotte #test :Cannot send to channel
```

---

## KICK Command Error Tests

### Test ERR_NEEDMOREPARAMS (461) - KICK
**What to test:** KICK without enough parameters
```
/quote KICK
/quote KICK #test
Expected: :localhost 461 sheha KICK :Not enough parameters
```

### Test ERR_NOSUCHCHANNEL (403) - KICK
**What to test:** KICK from non-existent channel
```
/kick #nonexistent Lotte
Expected: :localhost 403 sheha #nonexistent :No such channel
```

### Test ERR_NOTONCHANNEL (442) - KICK
**What to test:** KICK when not on channel
```
Client 1: (not in #test)
Client 1: /kick #test Lotte
Expected: :localhost 442 sheha #test :You're not on that channel
```

### Test ERR_CHANOPRIVSNEEDED (482) - KICK
**What to test:** KICK without operator status
```
Client 1: /join #test (creator, has ops)
Client 2: /join #test (regular user)
Client 2: /kick #test Saby
Expected: :localhost 482 Lotte #test :You're not channel operator
```

### Test ERR_NOSUCHNICK (401) - KICK
**What to test:** KICK non-existent user
```
/kick #test nonexistentuser
Expected: :localhost 401 sheha nonexistentuser :No such nick/channel
```

### Test ERR_USERNOTINCHANNEL (441)
**What to test:** KICK user not on channel
```
Client 1: /join #test
Client 2: /join #other
Client 1: /kick #test Lotte (Lotte is not in #test)
Expected: :localhost 441 sheha Lotte #test :They aren't on that channel
```

---

## INVITE Command Error Tests

### Test ERR_NEEDMOREPARAMS (461) - INVITE
**What to test:** INVITE without parameters
```
/quote INVITE
/quote INVITE Lotte
Expected: :localhost 461 sheha INVITE :Not enough parameters
```

### Test ERR_NOSUCHNICK (401) - INVITE
**What to test:** Invite non-existent user
```
/invite nonexistentuser #test
Expected: :localhost 401 sheha nonexistentuser :No such nick/channel
```

### Test ERR_NOSUCHCHANNEL (403) - INVITE
**What to test:** Invite to non-existent channel
```
/invite Lotte #nonexistent
Expected: :localhost 403 sheha #nonexistent :No such channel
```

### Test ERR_NOTONCHANNEL (442) - INVITE
**What to test:** Invite when not on channel
```
Client 1: (not in #test)
Client 1: /invite Lotte #test
Expected: :localhost 442 sheha #test :You're not on that channel
```

### Test ERR_USERONCHANNEL (443)
**What to test:** Invite user already on channel
```
Client 1: /join #test
Client 2: /join #test
Client 1: /invite Lotte #test
Expected: :localhost 443 sheha Lotte #test :is already on channel
```

### Test ERR_CHANOPRIVSNEEDED (482) - INVITE
**What to test:** Invite to +i channel without ops
```
Client 1: /join #private
Client 1: /mode #private +i
Client 2: /join #private (fails, but gets invited)
Client 1: /invite Lotte #private
Client 2: /join #private (success)
Client 3: /join #private (also gets in through invite)
Client 2: /invite Saby #private
Expected: :localhost 482 Lotte #private :You're not channel operator
```

---

## TOPIC Command Error Tests

### Test ERR_NEEDMOREPARAMS (461) - TOPIC
**What to test:** TOPIC without parameters
```
/quote TOPIC
Expected: :localhost 461 sheha TOPIC :Not enough parameters
```

### Test ERR_NOSUCHCHANNEL (403) - TOPIC
**What to test:** TOPIC on non-existent channel
```
/topic #nonexistent
Expected: :localhost 403 sheha #nonexistent :No such channel
```

### Test ERR_NOTONCHANNEL (442) - TOPIC
**What to test:** TOPIC when not on channel
```
Client 1: (not in #test)
Client 1: /topic #test
Expected: :localhost 442 sheha #test :You're not on that channel
```

### Test ERR_CHANOPRIVSNEEDED (482) - TOPIC
**What to test:** Set topic on +t channel without ops
```
Client 1: /join #test
Client 1: /mode #test +t
Client 2: /join #test
Client 2: /topic #test :New topic
Expected: :localhost 482 Lotte #test :You're not channel operator
```

---

## MODE Command Error Tests

### Test ERR_NEEDMOREPARAMS (461) - MODE
**What to test:** MODE without parameters
```
/quote MODE
Expected: :localhost 461 sheha MODE :Not enough parameters
```

### Test ERR_NOSUCHCHANNEL (403) - MODE
**What to test:** MODE on non-existent channel
```
/mode #nonexistent +i
Expected: :localhost 403 sheha #nonexistent :No such channel
```

### Test ERR_CHANOPRIVSNEEDED (482) - MODE
**What to test:** MODE without operator status
```
Client 1: /join #test (creator, has ops)
Client 2: /join #test (regular user)
Client 2: /mode #test +i
Expected: :localhost 482 Lotte #test :You're not channel operator
```

## DCC file transfer testing (netcat -> HexChat)

In your open netcat session enter:

```
privmsg <nickname> :ctrl-v ctrl-a DCC SEND <filename> 2130706433 <port> <filesize> ctrl-v ctrl-a
# Example:
privmsg Lotte :ctrl-v ctrl-a DCC SEND testfile.txt 2130706433 6000 8 ctrl-v ctrl-a

```
Before sending the command by pressing enter, open a different terminal, in a folder you want to send a file from, and enter:

```
nc -l <port> <filename>
# Example:
nc -l 9001 testfile.txt
```

> **Note:** The `ctrl-v ctrl-a` sequence inserts an ASCII SOH (Start of Header, character code 1) into the command. These SOH characters are required by the IRC DCC protocol to delimit the DCC SEND message, and must appear before and after the command.
> **Note:** <filename> and <port> must match the filename used in the DCC SEND command above. You will also have to use a different port than the one your server is running on!


## Suspend with CTRL-Z
--> only possible in nc
after suspending the process by entering ctrl-Z, enter

```
fg

```
and the client will be working again, and can receive all messages that have been posted in joined channels 

---

## Success Cases (No Errors)

### Successful Commands
```
# Successful JOIN
/join #test

# Successful PART
/part #test

# Successful PRIVMSG
/msg #test Hello everyone!
/msg Lotte Hi there!

# Successful KICK (as operator)
/kick #test Lotte Spamming

# Successful INVITE
/invite Lotte #test

# Successful TOPIC (view)
/topic #test

# Successful TOPIC (set, as operator)
/topic #test :Welcome to our channel!

# Successful MODE (view)
/mode #test

# Successful MODE (set, as operator)
/mode #test +i
/mode #test +t
/mode #test +k password123
/mode #test +l 10
/mode #test +o Lotte

# Successful WHO
/who #test

# Successful NICK change
/nick newnickname
```