#include <foxogram/Message.h>
#include <foxogram/Channel.h>
#include <foxogram/exceptions.h>
#include <foxogram/HttpClient.h>
#include <utility>

foxogram::Message::Message(const long long int id, Channel *channel, const long long int authorId,
                           const long long int timestamp,
                           std::list<std::string> attachments): id(id), channel(channel), authorId(authorId),
                                                                timestamp(timestamp),
                                                                attachments(std::move(attachments)) {
}

void foxogram::Message::handleError(const nlohmann::json &response) const {
    if (!response.value("ok", true)) {
        switch (response.at("code").get<int>()) {
            case(301): throw UserUnauthorizatedException();
            case(302): throw UserEmailNotVerfiedException();
            case(403): throw MissingPermissionException();
            default: throw HttpException(response.at("message").get<std::string>());
        }
    }
}

void foxogram::Message::deleteMessage() const {
    handleError(HttpClient::request(Payload("DELETE", "/channels/" +
                                                                channel->getName() + std::to_string(id), token)));
}

void foxogram::Message::edit() const {
    handleError(HttpClient::request(Payload("PATCH", "/channels/" + std::to_string(id), token)));
}

std::string foxogram::Message::getIdOrName() const {
    return std::to_string(id);
}