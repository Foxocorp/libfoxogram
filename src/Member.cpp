#include <foxogram/Member.h>

foxogram::Member::Member(long long id, Channel *channel, const long long permissions, const std::string &username,
                         const std::string &avatar, const long long flags, const int type, const long long createdAt)
    : User(id, createdAt, username, avatar, flags, type),
      channel(channel), permissions(permissions) {
}

void foxogram::Member::addPermissions(const MemberPermissions permission) {
    permissions.addFlag(permission);
}

bool foxogram::Member::hasPermissions(const MemberPermissions permission) const {
    return permissions.hasFlag(permission);
}

void foxogram::Member::removePermissions(const MemberPermissions permission) {
    permissions.removeFlag(permission);
}
