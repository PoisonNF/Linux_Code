#ifndef _UGID_FUNCTIONS_H_
#define _UGID_FUNCTIONS_H_

char *userNameFromId(uid_t uid);
uid_t userIdFromName(const char *name);
char *groupNameFromId(gid_t gid);
gid_t groupIdFromName(const char *name);

#endif // !_UGID_FUNCTIONS_H_

