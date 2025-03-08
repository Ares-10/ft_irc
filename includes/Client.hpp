#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <sys/socket.h>

#include <Server.hpp>
#include <string>

#include "Channel.hpp"

class Channel;

enum ClientState { HANDSHAKE, LOGIN, REGISTERED, DISCONNECTED };

class Client {
 private:
  int _fd;
  int _port;

  // static int _max_channel;  // 가입 가능한 채널의 최대 값. 이거 서버 설정인데
  // 서버가 가지고 있어야 하나?

  std::string _nickname;
  std::string _username;
  std::string _realname;
  std::string _hostname;

	std::string _id;

  ClientState _state;
  Channel* _channel;

 public:
  Client(int fd, int port, const std::string& hostname);

	int getFd() const;
	int getPort() const;
	std::string getNickname() const;
	std::string getUsername() const;
	std::string getRealname() const;
	std::string getHostname() const;
	std::string getId() const;
	ClientState getClientState() const;

	void setNickname(const std::string &nickname);
	void setUsername(const std::string &username);
	void setRealname(const std::string &realname);
	void setHostname(const std::string &hostname);
	void setId(const std::string &id);
	void setClientState(ClientState state);

  void write(const std::string& message) const;
};

#endif  // CLIENT_HPP
