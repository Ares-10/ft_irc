#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <limits>
#include <map>

#include "Client.hpp"
#include "Server.hpp"

class Server;
class Client;

class Channel {
 private:
  std::string _channel_name;  // channel name
  std::string _channel_topic;  // topic (info) // :은 뺴고 저장한다고 가정.
  std::string _channel_key;   // channel passwd
  std::string _channel_mode;  // i, t, k, l, o   && 기본적으로 nst

  std::string _channel_topic_set_time;  // unix timestamp => 찾아봐야할듯.
  std::string _channel_topic_set_member;

  // 첫 번쨰 문자는 채널의 접두사여야함 (# : 일반 채널, & : 지역 채널)
  // 제한 사항은 공백 (' ', 0x20), 제어 문자 G / BELL ('^G',
  // 0x07)또는 쉼표 (',', 0x2C)(프로토콜에서 목록 항목 구분
  // 기호로 사용됨)를 포함할 수 없다는 것입니다.

  // client_fd  : Client * (초대받은 사람)
  std::map<int, Client *> _invited_clients;
  std::map<int, Client *> _clients;    // channel client
  std::map<int, Client *> _operators;  // channel operator

  Server *_server;
  unsigned int _client_limit;
  unsigned int _client_number;

 public:
  Channel(Server *server, const std::string &channel_name);
  Channel(Server *server, Client *client, const std::string &channel_name);

  // Getters
  const std::string &getChannelName() const;
  const std::string &getChannelTopic() const;
  const std::string &getChannelKey() const;
  const std::string &getChannelMode() const;
  const std::string &getChannelTopicSetTime() const;
  const std::string &getChannelTopicSetMember() const;

  const std::map<int, Client *> &getInvitedClients() const;
  const std::map<int, Client *> &getClients() const;
  const std::map<int, Client *> &getOperators() const;
  unsigned int getClientLimit() const;
  unsigned int getClientNumber() const;

  // Setters
  void setChannelTopic(const std::string &channel_topic);
  void setChannelKey(const std::string &channel_key);
  // 완전 mode setting을 바꿀 경우
  void setChannelMode(const std::string &channel_mode);
  void setChannelTopicSetTime(const std::string &new_channel_topic_set_time);
  void setChannelTopicSetMember(
      const std::string &new_channel_topic_set_member);

  void setClientLimit(unsigned int client_limit);
  // void setClientNumber(unsigned int client_number); 이거 대신 inc, dec
  // 만들어야할듯.

  bool increaseClientNumber();
  bool decreaseClientNumber();

  bool removeClient(int client_fd);    // client_fd // 이거 쓴다음 꼭
                                       // _client_number 수 확인하기.
  bool removeOperator(int client_fd);  // client_fd
  bool removeInvitedClient(int client_fd);

  bool addInvitedClient(Client *client);
  bool addClient(Client *client);
  bool addOperator(Client *client);

  Client *findInvitedClient(int client_fd);  // 없으면 NULL
  Client *findClient(int client_fd);
  Client *findOperator(int client_fd);

  // 이거 return값이랑 인자 생각 좀 해봐야 할 듯. 리턴값 필요할 거 같음. 그리고
  // 하나 하나 옵션 체크도 해야할 수 도..
  void removeChannelMode(const std::string &channel_mode);
  void addChannelMode(const std::string &channel_mode);
  bool findChannelMode(const std::string &channel_mode);  // 이거 하나 씩 해야할
                                                          // 지 고민좀 해야할듯.

  // client_name : {@(true), not operator(false)}
  std::map<std::string, bool> getClientNamesWithPrefix();

  static bool checkChannelNameFormat(const std::string &channel_name);
  // static bool checkChannelKeyFormat(const std::string &channel_name); // mode
  // +k 일 때
};

#endif  // CHANNEL_HPP
